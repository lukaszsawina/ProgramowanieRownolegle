public class PrzekazywaczDanych implements IPrzekazywaczDanych{
    private double wynikCalki = 0;


    @Override
    public synchronized void ZapiszWynikCzastkowy(double wynik) {
        wynikCalki += wynik;
    }

    public double ZwrocWynik() {
        return wynikCalki;
    }
}
