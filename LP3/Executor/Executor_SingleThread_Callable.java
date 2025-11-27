public class Executor_SingleThread_Callable {
    public static void main (String[] args) throws Exception {
        ExecutorService executor = null;
        try {
            executor = Executors.newSingleThreadExecutor();
            Future<String> future = executor.submit(new MeuCallable());
            System.out.println(future.isDone());
            System.out.println(future.get());
            System.out.println(future.isDOne());
        } catch (Exception e) {
            throw e;
        } finally {
            if (executor != null) {
                executor.shutdownNow();
            }
        }
    }
    public static class MeuCallable implements Callable<String> {
        public String call() throws Exception {
            Thread.sleep
            String nome = Thread.currentThread().getName();
            System.out.println(nome + ": LP-III");
        }
    }
}