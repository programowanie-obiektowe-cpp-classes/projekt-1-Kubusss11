#include "Pracownik.hpp"


Pracownik::Pracownik(std::string imie) : imie(std::move(imie)) {}


Inz::Inz(std::string imie, std::string wydzial)
    : Pracownik(std::move(imie)), wydzial(std::move(wydzial)) {}

void Inz::print() const
{
    std::cout << "Inzynier: " << imie << ", Wydzial: " << wydzial << "\n";
}


Mag::Mag(std::string imie, bool obsluga)
    : Pracownik(std::move(imie)), obsluga(obsluga) {}

void Mag::print() const
{
    std::cout << "Magazynier: " << imie
              << ", Obsluga wozka widlowego: " << (obsluga ? "Tak" : "Nie") << "\n";
}


Mkt::Mkt(std::string imie, int followers)
    : Pracownik(std::move(imie)), followers(followers) {}

void Mkt::print() const
{
    std::cout << "Marketer: " << imie
              << ", Liczba obserwujacych: " << followers << "\n";
}


Rob::Rob(std::string imie, double rozmiar_buta)
    : Pracownik(std::move(imie)), rozmiar_buta(rozmiar_buta) {}

void Rob::print() const
{
    std::cout << "Robotnik: " << imie
              << ", Rozmiar buta: " << rozmiar_buta << "\n";
}