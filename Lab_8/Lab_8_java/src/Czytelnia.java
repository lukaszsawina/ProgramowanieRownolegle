import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Czytelnia {

    private int liczba_czyt = 0;
    private int liczba_pis = 0;
    private int piszacych = 0;
    private Lock lock ;
    private Condition condC;
    private Condition condP;

    public void init()
    {
        lock = new ReentrantLock();
        condC = lock.newCondition();
        condP = lock.newCondition();
    }

    public void chce_czytac() throws InterruptedException
    {
        lock.lock();

        try {
            while (liczba_pis > 0 /*Tutaj brakuje czegoś*/) {
                condC.await();
            }

            liczba_czyt++;
            condC.signal();
        } finally {
            lock.unlock();
        }
    }

    public void czytam()
    {
        System.out.println("Liczba czytających " + liczba_czyt + ", piszących: " + liczba_pis);

        if (liczba_pis > 1 || (liczba_pis == 1 && liczba_czyt > 0) || liczba_pis < 0 || liczba_czyt < 0) {
            System.out.println("Warunek czytania niespełniony");
            System.exit(0);
        }

        try {
            Thread.sleep(300000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void koniec_czytania()
    {
        lock.lock();

        try {
            liczba_czyt--;


            if (liczba_czyt == 0) {
                lock.notifyAll();
            }
        } finally {
            lock.unlock();
        }
    }

    public void chce_pisac() throws InterruptedException
    {
        lock.lock();

        try {
            if (liczba_czyt + liczba_pis > 0) {
                condP.await();
            }

            liczba_pis++;
        } finally {
            lock.unlock();
        }
    }

    public void pisze()
    {
        System.out.println("Liczba czytających " + liczba_czyt + ", piszących: " + liczba_pis);

        if (liczba_pis>1 || (liczba_pis==1 && liczba_czyt>0) || liczba_pis<0 || liczba_czyt<0 ) {
            System.out.println("Warunek pisania niespełniony");
            System.exit(0);
        }

        try {
            Thread.sleep(300000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void koniec_pisania() throws InterruptedException
    {
        lock.lock();

        try {
            liczba_pis--;

            if (condC != null) {
                condC.await();
            } else {
                condP.await();
            }
        } finally {
            lock.unlock();
        }
    }

}
