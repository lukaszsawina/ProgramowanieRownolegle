public class WatekRunnable1D implements Runnable{

    private Obraz obraz;
    private int ID;
    private int l_w;
    public WatekRunnable1D(int id, int n_l_w, Obraz n_obraz)
    {
        obraz = n_obraz;
        ID = id;
        l_w = n_l_w;
    }

    public void run() {
        obraz.calculate_histogram_parallel_zabezpieczone(
                ID, obraz.getSizeN(), l_w,
                0, obraz.getSizeM(), 1,
                0, 12, 1);
    }
}
