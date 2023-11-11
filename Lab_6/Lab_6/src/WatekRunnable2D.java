public class WatekRunnable2D implements Runnable {

    private Obraz obraz;
    int w_start;
    int w_end;
    int k_start;
    int k_end;

    public WatekRunnable2D(Obraz n_obraz, int nw_start, int nw_end, int nk_start, int nk_end)
    {
        obraz = n_obraz;
        w_start = nw_start;
        w_end = nw_end;
        k_start = nk_start;
        k_end = nk_end;
    }


    @Override
    public void run() {
        obraz.calculate_histogram_parallel_zabezpieczone(
                w_start, w_end, 1,
                k_start, k_end, 1,
                0, 12, 1);
    }


}
