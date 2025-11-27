import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class ServerInitializer {
    private final CountDownLatch latch;

    public ServerInitializer(CountDownLatch latch) {
        this.latch = latch;
    }

    public void waitForInitialization() {
        try {
            latch.await(); // espera todos os módulos terminarem
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void startServer() {
        waitForInitialization();
        System.out.println("====================================");
        System.out.println("Servidor Principal Online: Pronto para aceitar conexões (Socket.bind())");
        System.out.println("====================================");
        System.out.println("[SISTEMA] Processo de inicialização concluído.");
    }

    static class ModuleLoader implements Runnable {
        private final String moduleName;
        private final int loadTime; 
        private final CountDownLatch latch;

        public ModuleLoader(String moduleName, int loadTime, CountDownLatch latch) {
            this.moduleName = moduleName;
            this.loadTime = loadTime;
            this.latch = latch;
        }

        @Override
        public void run() {
            try {
                System.out.println("[CARREGANDO] Módulo " + moduleName + " iniciando...");
                Thread.sleep(loadTime);

                System.out.println("[OK] Módulo " + moduleName + " carregado.");
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            } finally {
                latch.countDown();
            }
        }
    }
}

public class ExercicioExecutor {
    public static void main(String[] args) {
        CountDownLatch latch = new CountDownLatch(4);
        ServerInitializer server = new ServerInitializer(latch);
        ExecutorService executor = Executors.newCachedThreadPool();

        executor.submit(new ServerInitializer.ModuleLoader("Configuração", 6000, latch));
        executor.submit(new ServerInitializer.ModuleLoader("Cache", 9000, latch));
        executor.submit(new ServerInitializer.ModuleLoader("Chaves de Criptografia", 12000, latch));
        executor.submit(new ServerInitializer.ModuleLoader("Conexão de Log", 4000, latch));

        executor.submit(server::startServer);

        executor.shutdown();
    }
}
