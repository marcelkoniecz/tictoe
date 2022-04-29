#include <iostream>
#include <string>
#include <algorithm>
#include "pole.hpp"

class Gra
{
public:
    int **planszaGry;   //Wskaznik na wskaznik, tu bedzie zawarte obszar gry
    int rozPlanszy = 0; //Informacja o rozmiarze planszy
    int iloRzad = 0;    //Informacja o ilosci figur potrzebnej do wygranej

    int kogoRuch = 0; // Liczba sygnalizujaca kogo jest teraz ruch 0- krzyzyk 1 - kolko

    Gra(int rozmiar, int ilosc);   //Konstruktor tworzacy plansze
    void wyswietl();               //Funkcja wyswietlajaca plansze
    bool sprawdzWolne(Pole pole);  //Funkcja sprawdzajaca czy dane pole jest wolne
    bool sprawdzZakres(Pole pole); //Funkcja sprawdzjaca czy podana liczba miesci sie w zakresie
    void ruch(Pole pole);          //Funkcja wykonujaca ruch
    int sprawdzWygrana();          //Funkcja zwracajaca czy ktos wygral
    bool sprawdzRemis();           //Funkcja sprawdzajaca czy jest remis
    void najlepszyRuch();          //Funkcja wykonujaca najlepszy ruch

    //Funkcja obliczajaca wartosc danej pozycji, jest ona potrzebna
    //aby komputer mogl wykonac najbardziej korzystny ruch
    int wartoscPozycji(int kogo);
    int minimax(int **plansza, int glebokosc, int alpha, int beta, int czyMaks); //Funkcja  algorytmu minimax zwracjaca wartosc danej pozycji
    int sprawdzWynik();                                                          //Funkcja zwracajaca jaki jest wynik gry
};