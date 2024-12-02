#pragma once

#include <iostream>
#include <string>

class Pracownik
{
public:
    Pracownik(std::string imie);
    virtual ~Pracownik() = default;

    virtual void print() const = 0;

protected:
    std::string imie;
};

class Inz : public Pracownik
{
public:
    Inz(std::string imie, std::string wydzial);
    void print() const override;

private:
    std::string wydzial;
};

class Mag : public Pracownik
{
public:
    Mag(std::string imie, bool obsluga);
    void print() const override;

private:
    bool obsluga;
};

class Mkt : public Pracownik
{
public:
    Mkt(std::string imie, int followers);
    void print() const override;

private:
    int followers;
};

class Rob : public Pracownik
{
public:
    Rob(std::string imie, double rozmiar_buta);
    void print() const override;

private:
    double rozmiar_buta;
};