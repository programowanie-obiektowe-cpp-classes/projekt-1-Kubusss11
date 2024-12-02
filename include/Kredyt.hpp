#ifndef KREDYT_HPP
#define KREDYT_HPP

class Kredyt {
    double kwota;
    int czas_splaty;
    int pozostale_miesiace;
    double oprocentowanie;

public:
    Kredyt(double kwota, int czas_splaty, double oprocentowanie = 12.0);
    double splac_rate();
    int pozostale_raty() const;
    double get_kwota() const;
};

#endif