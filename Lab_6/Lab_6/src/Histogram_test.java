import java.util.Scanner;

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



//         for (int i = 0; i < num_threads; i++) {
//             try {
//         	NewThr[i].join();
//             } catch (InterruptedException e) {}
//         }

        //Wariant 1
//        System.out.println("Set number of threads");
//        int num_threads = 94;
//
//         Watek[] NewThr = new Watek[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//             (NewThr[i] = new Watek(i,obraz_1)).start();
//        }

        //Wariant 2
//        System.out.println("Set number of threads");
//        int num_threads = scanner.nextInt();
//
//        WatekRunnable[] NewRunn = new WatekRunnable[num_threads];
//
//        int offset = (int)ceil(94.0/(double)num_threads);
//        for (int i = 0; i < num_threads; i++) {
//            int start = i*offset;
//            int end = (i+1)*offset;
//            if(end > 94)
//                end = 94;
//            (NewRunn[i] = new WatekRunnable(i,start, end, obraz_1)).run();
//        }

        //Wariant 1D cykliczny po wierszach
//        System.out.println("Set number of threads");
//        int num_threads = scanner.nextInt();
//
//        WatekRunnable1D[] NewRunn = new WatekRunnable1D[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//            (NewRunn[i] = new WatekRunnable1D(i, num_threads, obraz_1)).run();
//        }
//
//        obraz_1.prittier_print_histogram();

        //Wariant 2D blokowy każdy wątek dostaje ileś wierszy
        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        WatekRunnable2D[] NewRunn = new WatekRunnable2D[num_threads];
        int offset = (int)ceil(obraz_1.getSizeM()/(double)num_threads);

        for (int i = 0; i < num_threads; i++) {
            int start = i*offset;
            int end = (i+1)*offset;
            if(end > obraz_1.getSizeM())
                end = obraz_1.getSizeM();
            (NewRunn[i] = new WatekRunnable2D(i, start, end, obraz_1)).run();
        }

        obraz_1.prittier_print_histogram();

        obraz_1.sprawdz_wynik();
    }

}
