#include <iostream>
#include <string>
#include "gra.hpp"

int main()
{
    int rozmiar;         //Pole zawierajace informacje o rozmiarze planszy
    int iloscwRzedzie;   //Pole zawierajace informacje o ilosci w rzedzie potrzebnych do wygranej
    int wygrana = 0;     //Zmienna zawierajaca informacje jaki jest wynik gry
    int pierwszaWsp = 0; //Wspolrzedna wiersza
    int drugaWsp = 0;    //Wspolrzedna kolumny
    Pole gdzieRuch;      //Nastepny ruch zapisany w strukturze

    //Wczytanie wielkosci planszy oraz ilosci figur potrzebnych do wygranej
    std::cout << "Podaj rozmiar pola kwadratowego" << std::endl;
    std::cin >> rozmiar;
    std::cout << "Podaj ilość potrzebnych do wygranej" << std::endl;
    std::cin >> iloscwRzedzie;

    //Utworzenie obiektu gry oraz zdefiniowanie wielkosci planszy
    //oraz ilosci figur potrzebnych do wygranej
    Gra Nowa(rozmiar, iloscwRzedzie);
    //Wyswietlenie pustej planszy
    Nowa.wyswietl();

    //Petla wykonywujaca sie dopoki nie ma roztrzygniecia
    while (!wygrana)
    {
        std::cin >> pierwszaWsp >> drugaWsp; //Wczytanie wsolrzednych

        //Przypiasanie wartosci do strukutury
        gdzieRuch.wiersz = pierwszaWsp - 1;
        gdzieRuch.kolumna = drugaWsp - 1;

        Nowa.ruch(gdzieRuch); //Wykonanie ruchu gracza
        Nowa.wyswietl();      //Wyswietlenie planszy po wykonanych ruchach

        //std::cout << "Wartosc pozycji " << Nowa.wartoscPozycji(0) << std::endl;
        wygrana = Nowa.sprawdzWynik(); //Sprawdzenie jaki jest stan gry

        //Switch odczytujacy kto wygrywa
        switch (wygrana)
        {
        case 0:
            break;
        case 1:
            std::cout << "Krzyzyk wygrywa" << std::endl;
            break;
        case 2:
            std::cout << "Kolko wygrywa" << std::endl;
            break;
        case 3:
            std::cout << "Remis" << std::endl;
            break;
        }
    }
}