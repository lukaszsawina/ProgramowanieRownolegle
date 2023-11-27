import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class LepszaCalka {
    static double xs = 0;
    static double xe = Math.PI;
    static double dx = 0.000001;
    private static final int NTHREADS = 4;
    private static final int NTASK = 40;

    public static void main(String[] args)
    {
        double offset = (xe/NTASK);

        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future<Double>> wyniki_czastkowe = new ArrayList<Future<Double>>();

        for (int i = 0; i < NTASK; i++) {
            Callable<Double> calka = new Calka_callable(i*offset, (i+1)*offset, dx);
            Future<Double> wynik = executor.submit(calka);
            wyniki_czastkowe.add(wynik);
        }

        double wynik_Calki = 0;

        for(Future<Double> wynik : wyniki_czastkowe){
            try {
                wynik_Calki+=wynik.get();
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
        executor.shutdown();

        while(!executor.isTerminated()){}

        System.out.println("Wynik calki: " + wynik_Calki );
    }
}
