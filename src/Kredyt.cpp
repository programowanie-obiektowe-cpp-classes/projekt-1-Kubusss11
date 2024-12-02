#include "Kredyt.hpp"

Kredyt::Kredyt(double kwota, int czas_splaty, double oprocentowanie)
    : kwota(kwota), czas_splaty(czas_splaty), pozostale_miesiace(czas_splaty), oprocentowanie(oprocentowanie) {}

double Kredyt::splac_rate() {
    if (pozostale_miesiace > 0) {
        double miesieczne_oprocentowanie = (oprocentowanie / 12.0) / 100.0;
        double odsetki = kwota * miesieczne_oprocentowanie;
        double rata_kapitalowa = kwota / czas_splaty;
        pozostale_miesiace--;
        return rata_kapitalowa + odsetki;
    }
    return 0.0;
}

int Kredyt::pozostale_raty() const {
    return pozostale_miesiace;
}

double Kredyt::get_kwota() const {
    return kwota;
}