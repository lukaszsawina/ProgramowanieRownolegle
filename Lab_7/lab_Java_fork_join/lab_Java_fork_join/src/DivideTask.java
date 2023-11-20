import jdk.jfr.Threshold;

import java.util.concurrent.RecursiveTask;

class DivideTask extends RecursiveTask<int[]> {

    int[] arrayToDivide;
    int start_index;
    int end_index;

    final private int THRESHOLD = 0;

    public DivideTask(int[] arrayToDivide, int start, int end)
    {
        this.start_index = start;
        this.end_index = end;
        this.arrayToDivide = arrayToDivide;
    }

    protected int[] compute() {

        if (arrayToDivide.length > 1)
        {
            int mid_index = (arrayToDivide.length) / 2;


            int[] t1 = new int[mid_index];
            int[] t2 = new int[arrayToDivide.length - mid_index];

            for (int i = 0; i < mid_index; i++) {
                t1[i] = arrayToDivide[i];
            }

            for (int i = mid_index; i < arrayToDivide.length; i++) {
                t2[i - mid_index] = arrayToDivide[i];
            }

            DivideTask task1 = new DivideTask(t1, 0, mid_index);
            DivideTask task2 = new DivideTask(t2, mid_index, t2.length);

            task1.fork();
            task2.fork();

            int[] tab1 = task1.join();
            int[] tab2 = task2.join();

            scal_tab(tab1, tab2, arrayToDivide);
        }
        return arrayToDivide;
    }

    private void scal_tab(
            int[] tab1,
            int[] tab2,
            int[] scal_tab) {

        int i = 0, j = 0, k = 0;

        while ((i < tab1.length) && (j < tab2.length)) {

            if (tab1[i] < tab2[j]) {
                scal_tab[k] = tab1[i++];
            } else {
                scal_tab[k] = tab2[j++];
            }

            k++;
        }

        if (i == tab1.length) {

            for (int a = j; a < tab2.length; a++) {
                scal_tab[k++] = tab2[a];
            }

        } else {

            for (int a = i; a < tab1.length; a++) {
                scal_tab[k++] = tab1[a];
            }

        }
    }

}