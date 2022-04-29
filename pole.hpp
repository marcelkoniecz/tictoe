#include <iostream>
#include <string>

//Struktura przeznaczona do przechowywania wspolrzednych
struct Pole
{
    int wiersz = 0;
    int kolumna = 0;

    //Przeciazenie operatora () aby ulatwic przypisanie wartosci
    Pole operator()(int pierwsza, int druga)
    {
        this->wiersz = pierwsza - 1;
        this->kolumna = druga - 1;
        return *this;
    }
};