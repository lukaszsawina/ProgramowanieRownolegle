public class SekwencyjnaCalka {
    static double xs = 0;
    static double xe = Math.PI;
    static double dx = 0.000001;

    public static void main(String[] args)
    {
        Calka_callable calka = new Calka_callable(xs, xe, dx);
        System.out.println("Wynik calki: " + calka.compute_integral() );
    }
}
