public class TestCzytelnia {
    public static void main(String[] args)
    {
        Czytelnia czytelnia = new Czytelnia();
        czytelnia.init();
        // Tworzenie wątków
        for (int i = 0; i < 5; i++) {
            new Thread(() -> {
                while (true) {
                    try {
                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - przed zamkiem");
                        czytelnia.chce_czytac();
                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wchodzę");
                        czytelnia.czytam();
                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wychodzę");
                        czytelnia.koniec_czytania();
                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - po zamku");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }

        for (int i = 0; i < 5; i++) {
            new Thread(() -> {
                while (true) {
                    try {
                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - przed zamkiem");
                        czytelnia.chce_pisac();
                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - wchodzę");
                        czytelnia.pisze();
                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - wychodzę");
                        czytelnia.koniec_pisania();
                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - po zamku");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }
    }
}
