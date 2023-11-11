public class WatekRunnable1DBlokowy implements Runnable{

    private Obraz obraz;
    private int ID;
    private int start;
    private int end;
    public WatekRunnable1DBlokowy(int id, int n_start, int n_end, Obraz n_obraz)
    {
        obraz = n_obraz;
        ID = id;
        start = n_start;
        end = n_end;
    }

    public void run() {
        obraz.calculate_histogram_parallel_zabezpieczone(
                0, obraz.getSizeN(), 1,
                start, end, 1,
                0, 12, 1);
    }
}
