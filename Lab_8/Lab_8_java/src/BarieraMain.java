public class BarieraMain {
    public static void main(String[] args)
    {
        int liczbaWatkow = 4;
        Bariera bariera1 = new Bariera(4);

        for (int i = 0; i < liczbaWatkow; i++) {
            ThreadExample threadExample = new ThreadExample(i, bariera1);
            new Thread(threadExample).start();
        }
    }
}
