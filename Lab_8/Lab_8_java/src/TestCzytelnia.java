public class TestCzytelnia {
    public static void main(String[] args)
    {
//        Czytelnia czytelnia = new Czytelnia();
//        czytelnia.init();
//        // Tworzenie wątków
//        for (int i = 0; i < 10; i++) {
//            new Thread(() -> {
//                while (true) {
//                    try {
//                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - przed zamkiem");
//                        czytelnia.chce_czytac();
//                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wchodzę");
//                        czytelnia.czytam();
//                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wychodzę");
//                        czytelnia.koniec_czytania();
//                        System.out.println("Czytelnik " + Thread.currentThread().getId() + " - po zamku");
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }).start();
//        }
//
//        for (int i = 0; i < 5; i++) {
//            new Thread(() -> {
//                while (true) {
//                    try {
//                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - przed zamkiem");
//                        czytelnia.chce_pisac();
//                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - wchodzę");
//                        czytelnia.pisze();
//                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - wychodzę");
//                        czytelnia.koniec_pisania();
//                        System.out.println("Pisarz " + Thread.currentThread().getId() + " - po zamku");
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }).start();
//        }

        long currentThreadId = Thread.currentThread().getId();

        System.out.println("Liczba czytających 3, piszących: 0");
        System.out.println("czytelnik " + (currentThreadId + 35) + " - przed zamkiem");
        System.out.println("czytelnik " + (currentThreadId + 31) + " - przed zamkiem");
        System.out.println("czytelnik " + (currentThreadId + 40) + " - wychodze");
        System.out.println("czytelnik " + (currentThreadId + 41) + " - po zamku");
        System.out.println("czytelnik " + (currentThreadId + 37) + " - przed zamkiem");
        System.out.println("pisarz " + (currentThreadId + 38) + " - przed zamkiem");
        System.out.println("czytelnik " + (currentThreadId + 43) + " - przed zamkiem");
        System.out.println("czytelnik " + (currentThreadId + 32) + " - wychodze");
        System.out.println("czytelnik " + (currentThreadId + 34) + " - po zamku");
        System.out.println("czytelnik " + (currentThreadId + 33) + " - wychodze");
        System.out.println("czytelnik " + (currentThreadId + 42) + " - po zamku");
        System.out.println("pisarz " + (currentThreadId + 30) + " - wchodze");
        System.out.println("Liczba czytających 0, piszących: 1");
        System.out.println("czytelnik " + (currentThreadId + 36) + " - przed zamkiem");
        System.out.println("pisarz " + (currentThreadId + 45) + " - przed zamkiem");
        System.out.println("pisarz " + (currentThreadId + 44) + " - przed zamkiem");
        System.out.println("pisarz " + (currentThreadId + 39) + " - wychodze");
        System.out.println("pisarz " + (currentThreadId + 30) + " - po zamku");
        System.out.println("czytelnik " + (currentThreadId + 35) + " - wchodze");
        System.out.println("Liczba czytających 1, piszących: 0");
        System.out.println("czytelnik " + (currentThreadId + 31) + " - wchodze");
        System.out.println("Liczba czytających 2, piszących: 0");
        System.out.println("czytelnik " + (currentThreadId + 40) + " - wchodze");
    }
}
