#include "SlowpokePokemon.h"

SlowpokePokemon::SlowpokePokemon() :
    Pokemon("Slowpoke")
{
    setHealth(90);
    setAttackDamage(50);
    setDefensePower(60);
    setSpeed(5);
}

void SlowpokePokemon::setSpecialAttack(int damage)
{
    biteAttackDamage = damage;
}

int SlowpokePokemon::getSpecialAttack() const
{
    return biteAttackDamage;
}

void SlowpokePokemon::setSpecialDefense(int power)
{
    tailDefensePower = power;
}

int SlowpokePokemon::getSpecialDefense() const
{
    return tailDefensePower;
}

Pokemon::Type SlowpokePokemon::type() const
{
    return Pokemon::Type::Slowpoke;
}
