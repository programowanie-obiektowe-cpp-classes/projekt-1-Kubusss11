#include "Gra.hpp"

int main()
{
    Gra gra;

    while (gra.get_stan())
    {
        gra.akcja_gracza();
        gra.tick();
    }

    return 0;
}