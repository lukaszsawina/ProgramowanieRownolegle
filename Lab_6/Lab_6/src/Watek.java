public class Watek extends Thread{
    private int ID;
    private Obraz obraz;
    public Watek(int id, Obraz n_obraz)
    {
        ID = id;
        obraz = n_obraz;
    }

    public void run()
    {
        obraz.calculate_histogram_parallel(
                0, obraz.getSizeN(), 1,
                0, obraz.getSizeM(), 1,
                ID, ID+1, 1);

        synchronized (obraz){
            obraz.better_print_histogram(ID, ID);
        }
    }

}
