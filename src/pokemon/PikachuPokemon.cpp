#include "PikachuPokemon.h"

PikachuPokemon::PikachuPokemon() :
    Pokemon("Pikachu")
{
    setHealth(30);
    setAttackDamage(80);
    setDefensePower(40);
    setSpeed(70);
}

void PikachuPokemon::setSpecialAttack(int damage)
{
    electricalAttackDamage = damage;
}

int PikachuPokemon::getSpecialAttack() const
{
    return electricalAttackDamage;
}

void PikachuPokemon::setSpecialDefense(int power)
{
    electricalDefensePower = power;
}

int PikachuPokemon::getSpecialDefense() const
{
    return electricalDefensePower;
}

Pokemon::Type PikachuPokemon::type() const
{
    return Pokemon::Type::Pikachu;
}
