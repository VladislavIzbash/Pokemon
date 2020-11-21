#include "BulbasaurPokemon.h"

BulbasaurPokemon::BulbasaurPokemon() :
    Pokemon("Bulbasaur")
{
    setHealth(50);
    setAttackDamage(40);
    setDefensePower(60);
    setSpeed(50);
}

void BulbasaurPokemon::setSpecialAttack(int damage)
{
    poisonAttackDamage = damage;
}

int BulbasaurPokemon::getSpecialAttack() const
{
    return poisonAttackDamage;
}

void BulbasaurPokemon::setSpecialDefense(int power)
{
    onionDefensePower = power;
}

int BulbasaurPokemon::getSpecialDefense() const
{
    return onionDefensePower;
}

Pokemon::Type BulbasaurPokemon::type() const
{
    return Pokemon::Type::Bulbasaur;
}

