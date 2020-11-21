#pragma once

#include "Pokemon.h"

class BulbasaurPokemon : public Pokemon
{
public:
    BulbasaurPokemon();

    void setSpecialAttack(int damage) override;
    int getSpecialAttack() const override;

    void setSpecialDefense(int power) override;
    int getSpecialDefense() const override;

    Type type() const override;

private:
    int poisonAttackDamage = 60;
    int onionDefensePower = 20;
};

