public class WatekRunnable implements Runnable {

    private Obraz obraz;
    private int ID;
    private int start;
    private int end;

    public WatekRunnable(int id, int n_start, int n_end, Obraz n_obraz)
    {
        obraz = n_obraz;
        ID = id;
        start = n_start;
        end = n_end;
    }
    public void run()
    {
        obraz.calculate_histogram_parallel(
                0, obraz.getSizeN(), 1,
                0, obraz.getSizeM(), 1,
                start, end, 1);

        for(int i = start; i < end; i++)
            obraz.better_print_histogram(ID, i);
    }
}
