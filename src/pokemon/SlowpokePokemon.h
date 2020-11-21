#pragma once

#include "Pokemon.h"

class SlowpokePokemon : public Pokemon
{
public:
    SlowpokePokemon();

    void setSpecialAttack(int damage) override;
    int getSpecialAttack() const override;
    void setSpecialDefense(int power) override;
    int getSpecialDefense() const override;

    Type type() const override;

private:
    int biteAttackDamage = 20;
    int tailDefensePower = 10;
};

