#include "Gra.hpp"

Gra::Gra() : firma(std::make_unique<Firma>()), stan(true) {}

void Gra::akcja_gracza()
{
    std::string komenda;
    std::cout << "\nOpcje:\n"
              << "lp - Lista pracownikow\n"
              << "zinz - Zatrudnij inzyniera\n"
              << "zmag - Zatrudnij magazyniera\n"
              << "zmkt - Zatrudnij marketera\n"
              << "zrob - Zatrudnij robotnika\n"
              << "kred - Wez kredyt\n"
              << "kt - Zakoncz ture\n"
              << "info - Informacje o firmie\n"
              << "exit - Zakoncz gre\n"
              << "Twoj wybor: ";

    std::cin >> komenda;
    std::cout << std::endl;

    if (komenda == "lp")
        firma->drukuj_pracownikow();
    else if (komenda == "zinz")
    {
        std::string imie, wydzial;
        std::cout << "Podaj imie inzyniera: ";
        std::cin >> imie;
        std::cout << "Podaj wydzial inzyniera: ";
        std::cin >> wydzial;
        firma->zatrudnij(std::make_unique<Inz>(imie, wydzial));
    }
    else if (komenda == "zmag")
    {
        std::string imie, odpowiedz;
        bool obsluga_widlaka = false;

        std::cout << "Podaj imie magazyniera: ";
        std::cin >> imie;
        std::cout << "Czy moze obslugiwac wozek widlowy (tak/nie): ";
        std::cin >> odpowiedz;

        obsluga_widlaka = (odpowiedz == "tak");

        firma->zatrudnij(std::make_unique<Mag>(imie, obsluga_widlaka));
    }
    else if (komenda == "zmkt")
    {
        std::string imie;
        int followers;
        std::cout << "Podaj imie marketera: ";
        std::cin >> imie;
        std::cout << "Podaj liczbe obserwujacych: ";
        std::cin >> followers;
        firma->zatrudnij(std::make_unique<Mkt>(imie, followers));
    }
    else if (komenda == "zrob")
    {
        std::string imie;
        double rozmiar_buta;
        std::cout << "Podaj imie robotnika: ";
        std::cin >> imie;
        std::cout << "Podaj rozmiar buta robotnika: ";
        std::cin >> rozmiar_buta;
        firma->zatrudnij(std::make_unique<Rob>(imie, rozmiar_buta));
    }
    else if (komenda == "kred")
    {
        double kwota;
        int czas_splaty;
        std::cout << "Podaj kwote kredytu: ";
        std::cin >> kwota;
        std::cout << "Podaj czas splaty (w miesiacach): ";
        std::cin >> czas_splaty;
        firma->wez_kredyt(kwota, czas_splaty);
    }
    else if (komenda == "kt")
    {
        firma->zakoncz_miesiac();
        firma->wyswietl_stan();
    }
    else if (komenda == "info")
        firma->wyswietl_stan();
    else if (komenda == "exit")
        stan = false;
    else
        std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
}

void Gra::tick()
{
    firma->tick();
}

bool Gra::get_stan() const
{
    return stan;
}