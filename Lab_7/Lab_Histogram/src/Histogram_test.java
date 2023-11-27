import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static java.lang.Math.*;


class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        obraz_1.calculate_histogram();
        obraz_1.print_histogram();

        //Wariant 2D blokowy
        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        ExecutorService executor = Executors.newFixedThreadPool(num_threads);

        int w_offset = (int)ceil(obraz_1.getSizeN()/((double)num_threads/2));
        int k_offset = (int)ceil(obraz_1.getSizeM()/((double)num_threads/2));

        for (int i = 0, k = 0; i < num_threads/2; i++) {
            for(int j = 0; j < num_threads/2; j++, k++)
            {
                int w_start = i*w_offset;
                int w_end = (i+1)*w_offset;
                int k_start = j*k_offset;
                int k_end = (j+1)*k_offset;
                if(w_end > obraz_1.getSizeN())
                    w_end = obraz_1.getSizeN();

                if(k_end > obraz_1.getSizeM())
                    k_end = obraz_1.getSizeM();

                WatekRunnable2D watekRunnable = new WatekRunnable2D(obraz_1, w_start, w_end, k_start, k_end);
                executor.execute(watekRunnable);
            }
        }

        executor.shutdown();

        while(!executor.isTerminated()) {}

        obraz_1.prittier_print_histogram();

        obraz_1.sprawdz_wynik();
    }

}
