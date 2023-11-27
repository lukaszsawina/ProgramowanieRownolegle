public class ThreadExample implements Runnable
{
    private final int mojId;
    private final Bariera b1;

    public ThreadExample(int mojId, Bariera bariera1) {
        this.mojId = mojId;
        this.b1 = bariera1;
    }

    @Override
    public void run(){
        try
        {
            System.out.printf("przed bariera 1 - watek %d\n", mojId);
            b1.bariera();

            System.out.printf("przed bariera 2 - watek %d\n", mojId);
            b1.bariera();

            System.out.printf("przed bariera 3 - watek %d\n", mojId);
            b1.bariera();

            System.out.printf("przed bariera 4 - watek %d\n", mojId);
            b1.bariera();

            System.out.printf("po ostatniej barierze - watek %d\n", mojId);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}
