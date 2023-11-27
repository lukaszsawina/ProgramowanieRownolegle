import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Bariera {
    private int liczbaWatkow;
    private int liczbaWatkowWywolujaca;
    private final Lock lock = new ReentrantLock();
    private final Condition condition = lock.newCondition();

    public Bariera(int liczbaWatkow) {
        this.liczbaWatkow = liczbaWatkow;
        this.liczbaWatkowWywolujaca = 0;
    }

    public void bariera() throws InterruptedException {
        lock.lock();
        liczbaWatkowWywolujaca++;

        if (liczbaWatkow > liczbaWatkowWywolujaca) {
            condition.await();
        } else {
            condition.signalAll();
            liczbaWatkowWywolujaca = 0;
        }

        lock.unlock();
    }
}
