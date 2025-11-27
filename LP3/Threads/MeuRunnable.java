public class MeuRunnable implements Runnable{
    int i = -1;
    public synchronized void run(){
        i++;
        String nome = Thread.currentThread().getName();
        System.out.println(nome + ": " + i);
    }
}