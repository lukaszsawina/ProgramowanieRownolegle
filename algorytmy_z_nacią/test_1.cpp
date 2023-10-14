#include <iostream>

using namespace std;

struct osoba {
    int wiek;
    int wzrost;
    string imie;
};

void fun(osoba* a)
{
    cout << a->wiek << endl;
    cout << a->imie << endl;
    cout << a->wzrost << endl;
}

int main()
{
    osoba os;

    os.imie = "Luki";
    os.wiek= 21;
    os.wzrost = 183;

    fun(&os);

    cout << "kc luki, dzieki ze mi pomagasz <3" << endl;
    return 0;
}