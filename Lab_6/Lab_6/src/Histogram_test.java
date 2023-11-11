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




        //Wariant 1
//        System.out.println("Set number of threads");
//        int num_threads = 12;
//
//         Watek[] NewThr = new Watek[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//             (NewThr[i] = new Watek(i,obraz_1)).start();
//        }
//
//         for (int i = 0; i < num_threads; i++) {
//             try {
//         	NewThr[i].join();
//             } catch (InterruptedException e) {}
//         }


        //Wariant 2
//        System.out.println("Set number of threads");
//        int num_threads = scanner.nextInt();
//
//        Thread[] NewRunn = new Thread[num_threads];
//
//        int offset = (int)ceil(12.0/(double)num_threads);
//        for (int i = 0; i < num_threads; i++) {
//            int start = i*offset;
//            int end = (i+1)*offset;
//            if(end > 12)
//                end = 12;
//            (NewRunn[i] = new Thread(new WatekRunnable(i,start, end, obraz_1))).start();
//        }
//
//         for (int i = 0; i < num_threads; i++) {
//             try {
//                 NewRunn[i].join();
//             } catch (InterruptedException e) {}
//         }

        //Wariant 1D cykliczny po wierszach
//        System.out.println("Set number of threads");
//        int num_threads = scanner.nextInt();
//
//        Thread[] NewRunn = new Thread[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//            (NewRunn[i] = new Thread(new WatekRunnable1D(i, num_threads, obraz_1))).start();
//        }
//
//        for (int i = 0; i < num_threads; i++) {
//             try {
//                 NewRunn[i].join();
//             } catch (InterruptedException e) {}
//         }
//
//        obraz_1.prittier_print_histogram();

        //Wariant 1D blokowy każdy wątek dostaje ileś kolumn
//        System.out.println("Set number of threads");
//        int num_threads = scanner.nextInt();
//
//        Thread[] NewRunn = new Thread[num_threads];
//        int offset = (int)ceil(obraz_1.getSizeM()/(double)num_threads);
//
//        for (int i = 0; i < num_threads; i++) {
//            int start = i*offset;
//            int end = (i+1)*offset;
//            if(end > obraz_1.getSizeM())
//                end = obraz_1.getSizeM();
//            (NewRunn[i] = new Thread(new WatekRunnable1DBlokowy(i, start, end, obraz_1))).start();
//        }
//        for (int i = 0; i < num_threads; i++) {
//             try {
//                 NewRunn[i].join();
//             } catch (InterruptedException e) {}
//         }
//
//        obraz_1.prittier_print_histogram();

        //Wariant 2D blokowy
        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        Thread[] NewRunn = new Thread[num_threads];
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

                (NewRunn[k] = new Thread(new WatekRunnable2D(obraz_1, w_start, w_end, k_start, k_end))).start();
            }
        }
        for (int i = 0; i < num_threads; i++) {
             try {
                 NewRunn[i].join();
             } catch (InterruptedException e) {}
         }

        obraz_1.prittier_print_histogram();

        obraz_1.sprawdz_wynik();
    }

}
