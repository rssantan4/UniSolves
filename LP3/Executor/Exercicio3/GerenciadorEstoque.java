import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Lock;

public class AlocadorAssentos implements Runnable {
    private final PriorityBlockingQueue<RequisicaoReserva> filaRequisicoes;
    private final MapaAssentos mapaAssentos;
    private final Semaphore limitadorTaxa;
    private volatile boolean executando = true;
    
    public AlocadorAssentos(PriorityBlockingQueue<RequisicaoReserva> filaRequisicoes, MapaAssentos mapaAssentos, Semaphore limitadorTaxa) {
        this.filaRequisicoes = filaRequisicoes;
        this.mapaAssentos = mapaAssentos;
        this.limitadorTaxa = limitadorTaxa;
    }
    
    @Override
    public void run() {
        System.out.println("[AlocadorAssentos] Iniciado");
        
        while (executando) {
            try {
                // Tenta remover uma requisição com timeout de 1 segundo
                RequisicaoReserva requisicao = filaRequisicoes.poll(1, TimeUnit.SECONDS);
                if (requisicao == null){
                     continue;
                }
                processarRequisicao(requisicao);
                
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
        System.out.println("[AlocadorAssentos] Encerrado");
    }
    
    private void processarRequisicao(RequisicaoReserva requisicao) {
        RespostaReserva resposta = null;
        boolean permissaoAdquirida = false;
        
        try {
            // 1. Tentar adquirir permissão do Semaphore com timeout de 10 segundos
            permissaoAdquirida = limitadorTaxa.tryAcquire(10, TimeUnit.SECONDS);

            if (permissaoAdquirida) {
                String codigoAssento = requisicao.getCodigoAssento();
                
                // 3. Verificar se o código do assento é "ANY" (case-insensitive)
                if ("ANY".equalsIgnoreCase(codigoAssento)) {
                    // 4. Se "ANY": chamar alocarQualquerAssento()
                    resposta = alocarQualquerAssento(requisicao);
                } else {
                    // 5. Se específico: chamar alocarAssentoEspecifico()
                    resposta = alocarAssentoEspecifico(requisicao, codigoAssento);
                }
                
            } else {
                // 2. Se timeout, enviar resposta de falha "TIMEOUT"
                resposta = RespostaReserva.falha("TIMEOUT", "Sistema sobrecarregado. Tente novamente mais tarde.");
            }

        } catch (InterruptedException e) {
            // 8. Tratar InterruptedException
            Thread.currentThread().interrupt(); // Restaurar flag de interrupção
            resposta = RespostaReserva.falha("ERRO_SERVIDOR", "Operação interrompida no servidor.");
            
        } finally {
            // 7. SEMPRE liberar o Semaphore no bloco finally
            if (permissaoAdquirida) {
                limitadorTaxa.release();
            }
            
            // 6. Enviar a resposta usando enviarResposta()
            if (resposta != null) {
                enviarResposta(requisicao, resposta);
            }
        }
    }
    
    private RespostaReserva alocarQualquerAssento(RequisicaoReserva requisicao) {
        // 8. Se nenhum assento disponível, retornar RespostaReserva.falha("VOO_LOTADO", "Voo lotado")
        if (mapaAssentos.getQuantidadeAssentosLivres() <= 0) {
            return RespostaReserva.falha("VOO_LOTADO", "Voo lotado");
        }
        
        try {
            // 1. Iterar por todos os assentos disponíveis
            for (String codigoAssento : mapaAssentos.getTodosCodigosAssentos()) {
                Assento assento = mapaAssentos.getAssento(codigoAssento);
                
                // 2. Para cada assento, verificar se está ocupado (pular se estiver)
                if (assento.estaOcupado()) {
                    continue;
                }
                
                Lock assentoTrava = assento.getTrava();
                
                // 3. Tentar adquirir o lock do assento com timeout de 5 segundos
                if (assentoTrava.tryLock(5, TimeUnit.SECONDS)) {
                    try {
                        // 4. Fazer verificação dupla (double-check) se o assento ainda está livre
                        if (assento.estaOcupado()) {
                            continue; // Outra thread reservou enquanto tentávamos o lock
                        }

                        // 5. Usar compareAndSet() do AtomicBoolean para garantir atomicidade
                        AtomicBoolean flagOcupado = assento.getFlagOcupado();
                        if (flagOcupado.compareAndSet(false, true)) {
                            // 6. Se conseguir alocar:
                            String codigoReserva = gerarCodigoReserva();
                            assento.ocupar(requisicao.getNomePassageiro(), requisicao.getCategoria(), codigoReserva);
                            mapaAssentos.decrementarAssentosLivres();
                            registrarReserva(requisicao, codigoAssento, codigoReserva);
                            
                            // Retornar RespostaReserva.sucesso()
                            return RespostaReserva.sucesso(codigoAssento, codigoReserva);
                        }
                    } finally {
                        // 7. SEMPRE liberar o lock no bloco finally
                        assentoTrava.unlock();
                    }
                }
            }
        } catch (InterruptedException e) {
            // 9. Tratar InterruptedException adequadamente
            Thread.currentThread().interrupt();
            return RespostaReserva.falha("ERRO_SERVIDOR", "Operação de alocação interrompida.");
        }
        
        // 8. Se nenhum assento disponível, retornar RespostaReserva.falha("VOO_LOTADO", "Voo lotado")
        return RespostaReserva.falha("VOO_LOTADO", "Voo lotado");
    }
    
    private RespostaReserva alocarAssentoEspecifico(RequisicaoReserva requisicao, String codigoAssento) {
        
        Assento assento = mapaAssentos.getAssento(codigoAssento);
        
        if (assento == null) {
            return RespostaReserva.falha("ASSENTO_INVALIDO", "Assento " + codigoAssento + " não existe");
        }
        
        try {
            if (!assento.getTrava().tryLock(5, TimeUnit.SECONDS)) {
                return RespostaReserva.falha("TIMEOUT", "Timeout ao acessar assento");
            }
            
            try {
                if (assento.estaOcupado()) {
                    return RespostaReserva.falha("ASSENTO_OCUPADO", "Assento " + codigoAssento + " já está reservado");
                }
                
                if (assento.getFlagOcupado().compareAndSet(false, true)) {
                    String codigoReserva = gerarCodigoReserva();
                    assento.ocupar(requisicao.getNomePassageiro(), requisicao.getCategoria(), codigoReserva);
                    mapaAssentos.decrementarAssentosLivres();
                    registrarReserva(requisicao, codigoAssento, codigoReserva);
                    return RespostaReserva.sucesso(codigoAssento, codigoReserva);
                } else {
                    return RespostaReserva.falha("ASSENTO_OCUPADO", "Assento " + codigoAssento + " foi reservado por outro cliente");
                }
            } finally {
                assento.getTrava().unlock();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return RespostaReserva.falha("TIMEOUT", "Operação interrompida");
        }
    }
    
    private void enviarResposta(RequisicaoReserva requisicao, RespostaReserva resposta) {
        try {
            requisicao.getFilaResposta().put(resposta);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println("[AlocadorAssentos] Erro ao enviar resposta: " + e.getMessage());
        }
    }
    
    private String gerarCodigoReserva() {
        return UUID.randomUUID().toString().substring(0, 8);
    }
    
    private void registrarReserva(RequisicaoReserva requisicao, String codigoAssento, String codigoReserva) {
        System.out.printf("[RESERVA] %s %s → %s (%s)%n", requisicao.getNomePassageiro(), requisicao.getCategoria(), codigoAssento, codigoReserva);
    }
    
    public void encerrar() {
        executando = false;
    }
}