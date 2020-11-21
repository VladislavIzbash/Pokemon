#pragma once

#include "Pokemon.h"

class PikachuPokemon : public Pokemon
{
public:
    PikachuPokemon();

    void setSpecialAttack(int damage) override;
    int getSpecialAttack() const override;

    void setSpecialDefense(int power) override;
    int getSpecialDefense() const override;

    Type type() const override;

private:
    int electricalAttackDamage = 100;
    int electricalDefensePower = 34;
};

