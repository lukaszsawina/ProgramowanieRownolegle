import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.*;

public class Main {

    static double xs = 0;
    static double xe = Math.PI;
    static double dx = 0.000001;
    private static final int NTHREADS = 4;
    private static final int NTASK = 40;
    public static void main(String[] args)
    {
        PrzekazywaczDanych przekazywacz = new PrzekazywaczDanych();
        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future> wyniki_czastkowe = new ArrayList<Future>();

        double offset = (xe/NTASK);

        for (int i = 0; i < NTASK; i++) {
            Runnable calka = new Calka_runnable((double) i * offset, (double) (i + 1) * offset, dx, przekazywacz);
            Future future = executor.submit(calka);
            wyniki_czastkowe.add(future);
        }

        Iterator<Future> iterator = wyniki_czastkowe.iterator();

        while(iterator.hasNext()){
            Future future = iterator.next();
            try {
                future.get();
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();

        while(!executor.isTerminated()){}

        System.out.println("Wynik calki: " + przekazywacz.ZwrocWynik() );
    }
}
