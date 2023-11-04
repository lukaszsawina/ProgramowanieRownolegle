public class Watek extends Thread{

    public Watek(int id, Obraz obraz)
    {
        obraz.calculate_histogram_parallel(
                0, obraz.getSizeN(), 1,
                0, obraz.getSizeM(), 1,
                id, id+1, 1);

        obraz.better_print_histogram(id, id);
    }

}
