#pragma once

#include "Firma.hpp"
#include <iostream>
#include <memory>

class Gra
{
public:
    Gra();
    void akcja_gracza();
    void tick();
    bool get_stan() const;

private:
    std::unique_ptr<Firma> firma;
    bool stan;
};