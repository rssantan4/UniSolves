import java.io.*;
import java.net.*;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class ChatServer {

    private static final int PORT = 12345;

    private static final List<ClientHandler> clients = new CopyOnWriteArrayList<>();

    public static void main(String[] args) {
        System.out.println("[Servidor] Ouvindo na porta " + PORT + "...");
        try (ServerSocket server = new ServerSocket(PORT)) {
            while (true) {
                Socket socket = server.accept();
                new Thread(new ClientHandler(socket)).start();
            }
        } catch (IOException e) {
            System.err.println("[Servidor] Erro: " + e.getMessage());
        }
    }

    private static class ClientHandler implements Runnable {
        private final Socket socket;
        private PrintWriter out;
        private String name;

        ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override public void run() {
            try (
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))
            ) {
                out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                // 1) registrar cliente
                out.println("Digite seu nome:");
                name = in.readLine().trim();

                // Adiciona cliente
                clients.add(this);

                // 2) dar boas-vindas
                out.println("Bem-vindo, " + name + "! Digite mensagens. Use 'exit' para sair.");
                broadcast("[Servidor] " + name + " entrou no chat.", this);

                // 3) laço principal de leitura
                String line;
                // TODO [Aluno]: se a linha for "exit", encerrar este cliente graciosamente (remover da lista e fechar socket).
                    // TODO [Aluno]: fazer broadcast da mensagem para TODOS os outros clientes.
                    //   - dica: itere sobre 'clients' e chame println(...)
                    //   - não envie de volta para o próprio 'out' (opcional)
                while ((line = in.readLine()) != null) {
                    if ("exit".equalsIgnoreCase(line.trim())) {
                        out.println("Você saiu do chat. Até logo!");
                        break;
                    }
                    broadcast("[" + name + "] " + line, this);
                }
            } catch (IOException e) {
                System.out.println("[Servidor] Cliente desconectou.");
            } finally {
                // Remove cliente
                clients.remove(this);
                if (name != null) {
                    broadcast("[Servidor] " + name + " saiu do chat.", this);
                }
                try {
                    socket.close();
                } catch (IOException ignore) {}
            }
        }

        private void broadcast(String msg, ClientHandler sender) {
            for (ClientHandler ch : clients) {
                if (ch != sender) {
                    ch.out.println(msg);
                }
            }
            System.out.println(msg); // log no servidor também
        }
    }
}