#include <iostream>
#include <string>
#include <algorithm>
#include "gra.hpp"

//Konstruktor tworzacy plansze
Gra::Gra(int rozmiar, int ilosc) : rozPlanszy(rozmiar), iloRzad(ilosc)
{
    //Dynamicznie stworzenie tablicy z wskaznikami do nastepnej tablicy
    planszaGry = new int *[rozmiar];
    for (int i = 0; i < rozmiar; i++)
        planszaGry[i] = new int[rozmiar];

    //Przypisanie kazdemu elementowi stworzonej planszy wartosc 0 - puste pole
    for (int i = 0; i < rozmiar; i++)
    {
        for (int j = 0; j < rozmiar; j++)
        {
            planszaGry[i][j] = 0;
        }
    }
}

//Funkcja wyswietlajaca plansze
void Gra::wyswietl()
{
    for (int i = 0; i < rozPlanszy; i++)
    {
        std::cout << "  -";
        for (int k = 0; k < rozPlanszy; k++)
            std::cout << "----";
        std::cout << std::endl;

        std::cout << i + 1 << " ";
        for (int j = 0; j < rozPlanszy; j++)
        {
            if (planszaGry[i][j] == 0)
                std::cout << "|   ";
            else if (planszaGry[i][j] == 1)
                std::cout << "| x ";
            else if (planszaGry[i][j] == 2)
                std::cout << "| o ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " ";
    for (int i = 0; i < rozPlanszy; i++)
    {
        std::cout << "   " << i + 1;
    }
    std::cout << std::endl;
}

//Funkcja sprawdzajaca czy dane pole jest wolne
//Jesli dane pole jest wolne zwraca true
//Jesli nie jest wolne zwraca false
bool Gra::sprawdzWolne(Pole pole)
{
    if (planszaGry[pole.wiersz][pole.kolumna] == 0)
        return true;
    else
        return false;
}

//Funkcja sprawdzjaca czy podana liczba miesci sie w zakresie
// Jesli wartosc miesci sie w zakresie zwraca true
// Jesli nie miesci sie w zakresie zwraca false
bool Gra::sprawdzZakres(Pole pole)
{
    if ((pole.wiersz < rozPlanszy && pole.wiersz >= 0) && (pole.kolumna < rozPlanszy && pole.kolumna >= 0))
        return true;
    else
        return false;
}

//Funkcja wykonujaca ruch
void Gra::ruch(Pole pole)
{
    if (sprawdzZakres(pole)) //Sprawdzenie czy miesci sie w zakresie
    {
        if (kogoRuch == 0) //Sprawdzenie czy jest ruch krzyzyka
        {
            if (sprawdzWolne(pole)) //Sprawdzenie czy wskazanie pole jest wolne
            {
                planszaGry[pole.wiersz][pole.kolumna] = 1; //Wpisanie w wskazane pole wartosc odpowiadajace krzyzykowi
                kogoRuch = 1;                              //Zmiana ze kolejny ruch bedzie kolka
            }
            else
                std::cout << "Podaj ruch jeszcze raz" << std::endl; //Jesli podano ruch na zajete pole pojawia sie komunikat
        }
        else // Sprawdzenie czy jest ruch kolka
        {
            if (sprawdzWolne(pole)) //Sprawdzenie czy wskazanie pole jest wolne
            {
                planszaGry[pole.wiersz][pole.kolumna] = 2; //Wpisanie w wskazane pole wartosc odpowiadajace kolku
                kogoRuch = 0;                              //Zmiana ze kolejny ruch bedzie krzyzyka
            }
            else
                std::cout << "Podaj ruch jeszcze raz" << std::endl; //Jesli podano ruch na zajete pole pojawia sie komunikat
        }
        if (sprawdzWynik() != 0)
            return;
        najlepszyRuch();
    }
    else
        std::cout << "Blad zakresu podaj ruch jeszcze raz" << std::endl; //Wyswietlenie informacji o bledzie zakresu

}

//Funkcja zwracajaca czy ktos wygral
//0-nikt
//1-gracz krzyzyk
//2-gracz kolko
int Gra::sprawdzWygrana()
{
    int iloscRzad = 0; //Informacja ile jest liczb pod rzad
    int pomSkos = 0;   //Liczba iloscRzedu potrzebna przy badaniu wygranych po skosach

    //Petla odczytujaca kazda pozycje na planszy
    for (int i = 0; i < rozPlanszy; i++)
    {
        for (int j = 0; j < rozPlanszy; j++)
        {
            if (planszaGry[i][j] == 1) //W chwili gdy znajdzie krzyzyk
            {
                iloscRzad = 0; //Zerowanie ilosci krzyzykow pod rzad

                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie wygranej w pionie
                {
                    if (k < i + iloRzad) //Sprawdzenie czy jest mozliwa wygrana
                    {
                        if (planszaGry[k][j] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            if (iloscRzad == iloRzad) //Jesli ilosc w pionie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura w pionie nie jest krzyzykiem przerywa sprawdzanie w pionie
                    }
                }

                iloscRzad = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                for (int k = j; k < rozPlanszy; k++) //Sprawdzenie w poziomie
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[i][k] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            if (iloscRzad == iloRzad) //Jesli ilosc w poziomie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura w pozimie nie jest krzyzykiem przerywa sprawdzanie w poziomie
                    }
                }

                iloscRzad = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                pomSkos = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie po skosie na prawo ( z lewej  gory na prawo dol)
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[k][pomSkos] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            pomSkos++;
                            if (pomSkos > rozPlanszy) //Jesli zmienna jest wieksza niz wielkosc planszy przerywa petle
                                break;
                            if (iloscRzad == iloRzad) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura po skosie nie jest krzyzykiem przerywa sprawdzanie po skosie
                    }
                }

                iloscRzad = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                pomSkos = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie po skosie na lewo( prawej gory na lewo dol)
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[k][pomSkos] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;

                            if (pomSkos < 0) //Jesli zmienna jest mniejsza niz zero przerywa petle
                                break;
                            if (iloscRzad == iloRzad) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                            pomSkos--;
                        }
                        else
                            break; //Jesli kolejna figura po skosie nie jest krzyzykiem przerywa sprawdzanie po skosie
                    }
                }
            }
            else if (planszaGry[i][j] == 2) // Jesli petla glowna spotyka kolko na planszy
            {

                iloscRzad = 0;                       //Zerowanie ilosci kolek pod rzad
                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie w pionie
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[k][j] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            if (iloscRzad == iloRzad) //Jesli ilosc w pionie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                        }
                        else
                            continue; //Jesli kolejna figura w pionie nie jest kolkiem przerywa sprawdzanie w pionie
                    }
                }

                iloscRzad = 0;                       //Zerowanie ilosci kolek pod rzad
                for (int k = j; k < rozPlanszy; k++) //Sprawdzenie w poziomie
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[i][k] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            if (iloscRzad == iloRzad) //Jesli ilosc w poziomie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                            continue;
                        }
                        else
                            break; //Jesli kolejna figura w poziomie nie jest kolkiem przerywa sprawdzanie w poziomie
                    }
                }

                iloscRzad = 0;                       //Zerowanie ilosci kolek pod rzad
                pomSkos = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie po skosie na prawo
                {
                    if (k < i + iloRzad)
                    {
                        if (planszaGry[k][pomSkos] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            pomSkos++;
                            if (pomSkos > rozPlanszy) //Jesli zmienna jest wieksza niz wielkosc planszy przerywa petle
                                break;
                            if (iloscRzad == iloRzad) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                        }
                        else
                            break;
                    }
                }
                iloscRzad = 0;                       //Zerowanie ilosci kolek pod rzad
                pomSkos = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < rozPlanszy; k++) //Sprawdzenie po skosie na lewo
                {
                    if (k < i + iloRzad)
                    {

                        if (planszaGry[k][pomSkos] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            iloscRzad++;
                            if (pomSkos < 0) //Jesli zmienna jest mniejsza niz zero przerywa petle
                                break;
                            if (iloscRzad == iloRzad) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                            pomSkos--;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
    return false;
}

bool Gra::sprawdzRemis()
{
    int liczbaWszystkich = rozPlanszy * rozPlanszy; //Obliczenie ilosc wszystkich pol
    //Petla sprawdzajaca kazde pole planszy
    //Jezeli pole jest puste odejmuje -1 od zmiennej liczbaWszystkich
    for (int i = 0; i < rozPlanszy; i++)
    {
        for (int j = 0; j < rozPlanszy; j++)
        {
            if (planszaGry[i][j] != 0) //Jesli rozne od 0 odejmuje 1
            {
                liczbaWszystkich--;
            }
        }
    }
    if (liczbaWszystkich == 0) //Jesli nie ma wolnych pol zwraca true
        return true;
    else //Jesli sa wolne pola zwra false
        return false;
}

void Gra::najlepszyRuch()
{
    int najlepszyWynik = -1000; //Pocztkowa wartosc (komputer szuka jak najwiekszej)
    int glebokosc = 5;          // Na ile ruchow do przodu sprawdza warianty
    Pole najlepszePosuniecie;   //Pole zawierajce najlepsz mozliwe posuniecie
    int alpha = -1000;          //Wartosc alpha potrzeba do zastosowania alpha beta ciec
    int beta = 1000;            //Wartosc beta potrzeba do zastosowania alpha beta ciec
    //Petle potrzebne do poruszania sie po planszy
    for (int i = 0; i < rozPlanszy; i++)
    {
        for (int j = 0; j < rozPlanszy; j++)
        {
            if (planszaGry[i][j] == 0) //Jesli pole jest wolne
            {
                planszaGry[i][j] = 2;                                           //Wstawiamy tam wartosc kolka i sprawdzamy jaki nam wychodzi wynik
                int wynik = minimax(planszaGry, glebokosc - 1, alpha, beta, 0); //Symulacja kolejnych posuniec z ta wartoscia
                planszaGry[i][j] = 0;                                           // Przypisanie zpowrotem 0
                //std::cout << wynik << std::endl;
                if (wynik > najlepszyWynik) //Sprawdzenie czy uzyskany wynik jest najlepszy
                {
                    najlepszyWynik = wynik;            //Jesli jest najlepszy przypisanie go jako najlepszy wynik
                    najlepszePosuniecie(i + 1, j + 1); //Zapisanie jako najlepszy ruch
                }
            }
        }
    }
    //Po przesymulowaniu kazdej pozycji uzykujemy najlepsz
    //I dla niej przypisuje wartosc kolko
    planszaGry[najlepszePosuniecie.wiersz][najlepszePosuniecie.kolumna] = 2;
    kogoRuch = 0; //0- gracz  1 -komputer
}

//Funkcja obliczajaca wartosc danej pozycji
//Komputer sprawdza mozliwosci kolka i krzyzyka w pionie, poziomie i skosie
//Komputer dodaje do siebie wartosci np jesli w pionie sa 2 figury i jest mozliwosc zeby dostawic odpowiednia ilos figur aby wygrac
//dodaje 2 do ogolego wyniku, jesli nie ma pozliwosci wygranej w pionie nie dodaje nic
//Funkcja ta sprawdza dla kolka i krzyzyka wartosc pozycji i odejmuje na koncu kolko od krzyzyka
//Poniewaz zakladam ze kolko(komputer) maksymalizuje gracz(krzyzyk) minimalizuje
int Gra::wartoscPozycji(int kogo)
{
    int iloscRzedu = 0; //Ilosc kolka/krzyzyka w rzedzie
    int pomSkosKol = 0;
    int pustePole = 0; //Ile jest pustych pol w danym rzedzie
    int pomSkosy = 0;
    int pomocniczaWynik1 = 0; //Wynik kolka
    int pomocniczaWynik2 = 0; //Wynik krzyzyka

    //Glowne petle sprawdzajace kazda polzycje na planszy
    for (int i = 0; i < rozPlanszy; i++)
    {
        for (int j = 0; j < rozPlanszy; j++)
        {
            if (planszaGry[i][j] == 2) //Sprawdzenie czy jest kolko
            {
                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pustePole = 0;

                for (int k = 0; k < rozPlanszy; k++) //Sprawdzenie w pionie
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (planszaGry[k][j] == 2)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[k][j] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[k][j] == 0)
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;

                pomocniczaWynik1 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pustePole = 0;

                for (int k = 0; k < rozPlanszy; k++) //Sprawdzenie w poziomie
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (planszaGry[i][k] == 2)
                        iloscRzedu++;

                    else if (planszaGry[i][k] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[i][k] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik1 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pomSkosKol = 0;
                pustePole = 0;
                pomSkosy = j + 1;

                for (int m = i; m >= 0; m--) //funkcja wracajaca na poczatek skosu
                {
                    pomSkosKol = m;
                    pomSkosy--;
                    if (pomSkosy <= 0)
                    {
                        pomSkosy = 0;
                        break;
                    }
                }

                for (int m = pomSkosKol; m <= rozPlanszy - 1; m++) //sprawdzenie skosu w prawo
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (planszaGry[m][pomSkosy] == 2)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[m][pomSkosy] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[m][pomSkosy] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;

                    pomSkosy++;
                    if (pomSkosy >= rozPlanszy)
                        break;
                }

                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;

                pomocniczaWynik1 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pomSkosKol = 0;
                pustePole = 0;
                pomSkosy = j + 1;

                for (int k = i; k < rozPlanszy; k++) //na dol skosu
                {

                    pomSkosKol = k;
                    pomSkosy--;
                    if (pomSkosy <= 0)
                    {
                        break;
                    }
                }

                for (int m = pomSkosKol; m >= 0; m--) //sprawdzenie skosu w lewo
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (planszaGry[m][pomSkosy] == 2)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[m][pomSkosy] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[m][pomSkosy] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;

                    pomSkosy++;
                    if (pomSkosy >= rozPlanszy)
                        break;
                }

                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik1 += iloscRzedu; //Dodanie do wyniku
            }

            if (planszaGry[i][j] == 1)
            {
                iloscRzedu = 0;
                pustePole = 0;

                for (int k = 0; k < rozPlanszy; k++) //Sprawdzenie w pionie
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (planszaGry[k][j] == 1)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[k][j] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[k][j] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik2 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pustePole = 0;

                for (int k = 0; k < rozPlanszy; k++) //Sprawdzenie w poziomie
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (planszaGry[i][k] == 1)
                        iloscRzedu++;

                    else if (planszaGry[i][k] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[i][k] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik2 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pomSkosKol = 0;
                pustePole = 0;
                pomSkosy = j + 1;

                for (int m = i; m >= 0; m--) //funkcja wracajaca na poczatek skosu
                {
                    pomSkosKol = m;
                    pomSkosy--;
                    if (pomSkosy <= 0)
                    {
                        pomSkosy = 0;
                        break;
                    }
                }

                for (int m = pomSkosKol; m <= rozPlanszy - 1; m++) //sprawdzenie skosu w prawo
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (planszaGry[m][pomSkosy] == 1)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[m][pomSkosy] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[m][pomSkosy] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                    pomSkosy++;
                    if (pomSkosy >= rozPlanszy)
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik2 += iloscRzedu; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                iloscRzedu = 0;
                pomSkosKol = 0;
                pustePole = 0;
                pomSkosy = j + 1;

                for (int k = i; k < rozPlanszy; k++) //na dol skosu
                {

                    pomSkosKol = k;
                    pomSkosy--;
                    if (pomSkosy <= 0)
                    {
                        break;
                    }
                }
                for (int m = pomSkosKol; m >= 0; m--) //sprawdzenie skosu w lewo 
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (planszaGry[m][pomSkosy] == 1)
                    {
                        iloscRzedu++;
                    }
                    else if (planszaGry[m][pomSkosy] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        iloscRzedu = 0;
                        pustePole = 0;
                    }
                    else if (planszaGry[m][pomSkosy] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        pustePole++;
                    if (iloscRzedu + pustePole == iloRzad) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                    pomSkosy++;
                    if (pomSkosy >= rozPlanszy)
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (iloscRzedu + pustePole < iloRzad)
                    iloscRzedu = 0;
                pomocniczaWynik2 += iloscRzedu; //Dodanie do wyniku
            }
        }
    }

    return pomocniczaWynik1 - pomocniczaWynik2; //Zwraca wartosc pozycja kolko minus pozycja krzyzyk
}

//Funkcja  algorytmu minimax zwracjaca wartosc jaka osiagnie gracz przy danym ruchu
int Gra::minimax(int **plansza, int glebokosc, int alpha, int beta, int czyMaks)
{
    int wynik = 0; //Zmienna zawierajaca wynik

    if ((glebokosc == 0)) //Jesli glebokosc ==0 zwraca aktualny wynik symulowanej planszy
    {
        wynik = wartoscPozycji(czyMaks);
        return wynik;
    }
    else if (sprawdzWygrana() == 1) //Jesli wygrywa krzyzyk zwraca -200
        return -200;
    else if (sprawdzWygrana() == 2) //Jesli wygrywa kolko zwraca 200
        return 200;
    else if (sprawdzRemis()) //Jesli remis nie zwraca nic
        return 0;

    //1 - gracza maksymalizujacy(komputer)
    //2 - gracz minimalizujacy(gracz)
    if (czyMaks == 1) //Sprawdza kogo ruch
    {

        int najlepszyWynik = -100; //Wynik taki aby byl wiekszy
        for (int i = 0; i < rozPlanszy; i++)
        {
            for (int j = 0; j < rozPlanszy; j++)
            {
                if (plansza[i][j] == 0) //Jesli pole jest wolne
                {
                    plansza[i][j] = 2;                                       //Wstawiamy tam wartosc kolka i sprawdzamy jaki nam wychodzi wynik
                    wynik = minimax(plansza, glebokosc - 1, alpha, beta, 0); //Symulacja kolejnych posuniec z ta wartoscia
                    plansza[i][j] = 0;                                       //Ustawiamy do poczatkowego stanu
                    najlepszyWynik = std::max(wynik, najlepszyWynik);        //Przypisanie wiekszej wartosci do najlepszego wyniku
                    alpha = std::max(alpha, wynik);                          //Przypisanie do alphy wiekszej wartosci
                    if (beta <= alpha)                                       //Jesli alpha wieksza od bety przerwanie petli
                        break;
                }
            }
        }

        return najlepszyWynik;
    }
    else
    {
        int najlepszyWynik = 100;
        for (int i = 0; i < rozPlanszy; i++)
        {
            for (int j = 0; j < rozPlanszy; j++)
            {
                if (plansza[i][j] == 0) //Jesli pole jest wolne
                {
                    plansza[i][j] = 1;                                       //Wstawiamy tam wartosc krzyzyka i sprawdzamy jaki nam wychodzi wynik
                    wynik = minimax(plansza, glebokosc - 1, alpha, beta, 1); //Symulacja kolejnych posuniec z ta wartoscia
                    plansza[i][j] = 0;                                       //Ustawiamy do poczatkowego stanu
                    najlepszyWynik = std::min(wynik, najlepszyWynik);        //Przypisanie mniejszej wartosci do najlepszego wyniku
                    beta = std::min(beta, wynik);                            //Przypisanie do bety mniejszej wartosci
                    if (beta <= alpha)                                       //Jesli alpha wieksza od bety przerwanie petli
                        break;
                }
            }
        }
        return najlepszyWynik;
    }
}

//Funkcja zwracajaca jaki jest wynik gry
//0-nikt nie wygrywa i mozna grac dalej
//1-wygrywa krzyzyk
//2-wyrgywa kolko
//3 -remis
int Gra::sprawdzWynik()
{
    if (sprawdzWygrana())
        return sprawdzWygrana();
    if (sprawdzRemis())
        return 3;
    else
        return 0;
}