#include "Firma.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

const double MAX_ZADLUZENIE_MULTIPLIER = 2.0;
const int MAX_CZAS_SPLATY = 60;
const double CI = 100.0;
const double CMag = 50.0;
const double CMkt = 80.0;
const double CR = 120.0;
const double CEL_GRY = 100000.0;
const int HISTORIA_MIESIECY = 6; 

Firma::Firma() : stan_konta(10000), n_prac(4), n_kredytow(0), wartosc_spolki(10000), magazyn(0),
                 zadluzenie(0), cena_produktu(CI), popyt(CMkt), teoretyczna_produkcja(CR), pojemnosc_magazynu(CMag)
{
    pracownicy.push_back(std::make_unique<Inz>("Jakub Kubaczynski", "MEiL"));
    pracownicy.push_back(std::make_unique<Mag>("Marek Mostowiak", "tak"));
    pracownicy.push_back(std::make_unique<Mkt>("Angela Murawska", 70000));
    pracownicy.push_back(std::make_unique<Rob>("Mateusz Robol", 44.5));
}

void Firma::drukuj_pracownikow() const
{
    if (pracownicy.empty())
    {
        std::cout << "Brak pracownikow w firmie.\n";
        return;
    }
    for (const auto& pracownik : pracownicy)
    {
        pracownik->print();
    }
}

void Firma::zatrudnij(std::unique_ptr<Pracownik> pracownik)
{
    pracownicy.push_back(std::move(pracownik));
    n_prac++;
    oblicz_statystyki();
    oblicz_wartosc_spolki();
}

void Firma::wez_kredyt(double kwota, int czas_splaty)
{
    if (czas_splaty > MAX_CZAS_SPLATY)
    {
        std::cout << "Czas splaty nie moze przekraczac " << MAX_CZAS_SPLATY << " miesiecy.\n";
        return;
    }

    oblicz_wartosc_spolki();
    double maksymalne_zadluzenie = wartosc_spolki * MAX_ZADLUZENIE_MULTIPLIER;

    if (zadluzenie + kwota > maksymalne_zadluzenie)
    {
        std::cout << "Nie mozna zaciagnac kredytu. Zadluzenie przekroczy maksymalny dopuszczalny poziom.\n";
        return;
    }

    double oprocentowanie = 12.0;
    double odsetki = kwota * (oprocentowanie / 12.0) / 100.0 * czas_splaty;
    kredyty.emplace_back(kwota + odsetki, czas_splaty, oprocentowanie);
    zadluzenie += kwota + odsetki;
    stan_konta += kwota;

    std::cout << "Zaciagnieto kredyt na kwote: " << kwota
              << " zl z czasem splaty: " << czas_splaty
              << " miesiecy. Odsetki: " << odsetki << " zl.\n";
}

void Firma::zakoncz_miesiac()
{
    for (auto& kredyt : kredyty)
    {
        double rata = kredyt.splac_rate();
        stan_konta -= rata;
        zadluzenie -= rata;
    }
    kredyty.erase(std::remove_if(kredyty.begin(), kredyty.end(),
                                 [](const Kredyt& k) { return k.pozostale_raty() <= 0; }),
                  kredyty.end());

    double wynagrodzenie = n_prac * 2000;
    stan_konta -= wynagrodzenie;

    double produkty_dostepne = magazyn + teoretyczna_produkcja;
    magazyn = std::min(produkty_dostepne, pojemnosc_magazynu);
    double sprzedane_produkty = std::min(magazyn, popyt);
    magazyn -= sprzedane_produkty;
    double przychod = sprzedane_produkty * cena_produktu;

    stan_konta += przychod;

    historia_przychodow.push_back(przychod);
    if (historia_przychodow.size() > HISTORIA_MIESIECY)
    {
        historia_przychodow.erase(historia_przychodow.begin());
    }

    oblicz_statystyki();
    oblicz_wartosc_spolki();

    std::cout << "Miesiac zakonczony.\n";
    std::cout << "Przychod: " << przychod << " zl\n"
              << "Wynagrodzenie pracownikow: " << wynagrodzenie << " zl\n"
              << "Zadluzenie: " << zadluzenie << " zl\n";

    if (stan_konta < 0)
    {
        std::cout << "Twoja firma zbankrutowala! Stan konta spadl ponizej zera.\n";
        exit(0);
    }

    double netto_wartosc_spolki = wartosc_spolki - zadluzenie;

    if (netto_wartosc_spolki >= CEL_GRY)
    {
        std::cout << "Gratulacje! Twoja firma osiagnela wartosc netto " << netto_wartosc_spolki
                  << " zl. Wygrales gre!\n";
        exit(0);
    }
}

void Firma::wyswietl_stan() const
{
    std::cout << "Stan konta: " << stan_konta << " zl\n"
              << "Liczba pracownikow: " << n_prac << "\n"
              << "Cena produktu: " << cena_produktu << " zl\n"
              << "Popyt: " << popyt << "\n"
              << "Produkcja: " << teoretyczna_produkcja << "\n"
              << "Pojemnosc magazynu: " << pojemnosc_magazynu << "\n"
              << "Magazyn: " << magazyn << " sztuk\n"
              << "Zadluzenie: " << zadluzenie << " zl\n"
              << "Wartosc spolki: " << wartosc_spolki << " zl\n";
}

void Firma::tick()
{
    oblicz_statystyki();
}

void Firma::oblicz_wartosc_spolki()
{
    if (!historia_przychodow.empty())
    {
        double suma_przychodow = std::accumulate(historia_przychodow.begin(), historia_przychodow.end(), 0.0);
        wartosc_spolki = suma_przychodow / historia_przychodow.size();
    }
    else
    {
        wartosc_spolki = 0;
    }
}

void Firma::oblicz_statystyki()
{
    int liczba_inz = 0, liczba_mag = 0, liczba_mkt = 0, liczba_rob = 0;
    for (const auto& pracownik : pracownicy)
    {
        if (dynamic_cast<Inz*>(pracownik.get()))
            liczba_inz++;
        else if (dynamic_cast<Mag*>(pracownik.get()))
            liczba_mag++;
        else if (dynamic_cast<Mkt*>(pracownik.get()))
            liczba_mkt++;
        else if (dynamic_cast<Rob*>(pracownik.get()))
            liczba_rob++;
    }

    cena_produktu = liczba_inz * CI;
    pojemnosc_magazynu = liczba_mag * CMag;
    popyt = liczba_mkt * CMkt;
    teoretyczna_produkcja = liczba_rob * CR;
}