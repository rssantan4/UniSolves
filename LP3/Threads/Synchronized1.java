public class synchronized1 {

    private static int i = 0;

    public static void main(String[] args){

        MeuRunnable r = new MeuRunnable();

        Thread t0 = new Thread(r);
        Thread t1 = new Thread(r);
        Thread t2 = new Thread(r);
        Thread t3 = new Thread(r);
        Thread t4 = new Thread(r);

        t0.start();
        t1.start();
        t2.start();
        t3.start();
        t4.start();
    
        public static void imprime() {
            synchronized (synchronized1.class) {
                i++;
                String name = Thread.currentThread().getName();
                System.out.println(name + ":" + 1);
        }
        }
        public static class MeuRunnable implements Runnable {
            @Override
            public void run() {
                imprime();
            }
        }
    }
}