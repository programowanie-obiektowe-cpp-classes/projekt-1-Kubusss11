#pragma once

#include "Pracownik.hpp"
#include "Kredyt.hpp"
#include <vector>
#include <memory>
#include <string>

class Firma {
private:
    double stan_konta;
    int n_prac;
    int n_kredytow;
    double wartosc_spolki;
    double magazyn;
    double zadluzenie;
    double cena_produktu;
    double popyt;
    double teoretyczna_produkcja;
    double pojemnosc_magazynu;
    std::vector<std::unique_ptr<Pracownik>> pracownicy;
    std::vector<Kredyt> kredyty;
    std::vector<double> historia_przychodow;

    void oblicz_statystyki();
    void oblicz_wartosc_spolki();

public:
    Firma();
    void drukuj_pracownikow() const;
    void zatrudnij(std::unique_ptr<Pracownik> pracownik);
    void wez_kredyt(double kwota, int czas_splaty);
    void zakoncz_miesiac();
    void wyswietl_stan() const;
    void tick();
};