public class WatekRunnable implements Runnable {

    private Obraz obraz;
    private int ID;
    private int start_i;
    private int end_i;

    public WatekRunnable(int id, int n_start, int n_end, Obraz n_obraz)
    {
        obraz = n_obraz;
        ID = id;
        start_i = n_start;
        end_i = n_end;
    }
    public void run()
    {
        obraz.calculate_histogram_parallel(
                0, obraz.getSizeN(), 1,
                0, obraz.getSizeM(), 1,
                start_i, end_i, 1);

        synchronized (obraz)
        {
            for(int i = start_i; i < end_i; i++)
                obraz.better_print_histogram(ID, i);
        }
    }
}
