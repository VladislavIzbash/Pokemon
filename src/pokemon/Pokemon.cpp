#include "Pokemon.h"

#include "BulbasaurPokemon.h"
#include "SlowpokePokemon.h"
#include "PikachuPokemon.h"

Pokemon::Pokemon(const std::string& name) :
    name(name)
{}

const std::string& Pokemon::getName() const
{
    return name;
}

void Pokemon::setName(const std::string& name)
{
    this->name = name;
}

int Pokemon::getHealth() const
{
    return health;
}

void Pokemon::setHealth(int hp)
{
    health = hp;
}

int Pokemon::getAttackDamage() const
{
    return attackDamage;
}

void Pokemon::setAttackDamage(int damage)
{
    attackDamage = damage;
}

int Pokemon::getDefensePower() const
{
    return defensePower;
}

void Pokemon::setDefensePower(int power)
{
    defensePower = power;
}

int Pokemon::getSpeed() const
{
    return speed;
}

void Pokemon::setSpeed(int speed)
{
    this->speed = speed;
}

JsonObject Pokemon::toJson() const
{
    JsonObject obj;

    obj["name"] = name;
    obj["type"] = static_cast<int>(type());
    obj["health"] = health;
    obj["damage"] = attackDamage;
    obj["defense"] = defensePower;
    obj["speed"] = speed;

    obj["damage_special"] = getSpecialAttack();
    obj["defense_special"] = getSpecialDefense();

    return obj;
}

void Pokemon::fromJson(const JsonObject& obj)
{
    name = obj["name"].asString();
    health = obj["health"].asInt();
    attackDamage = obj["damage"].asInt();
    defensePower = obj["defense"].asInt();
    speed = obj["speed"].asInt();

    setSpecialAttack(obj["damage_special"].asInt());
    setSpecialDefense(obj["defense_special"].asInt());
}

std::unique_ptr<Pokemon> Pokemon::createPokemon(const JsonObject& obj)
{
    Pokemon* pokemon;

    switch (static_cast<Pokemon::Type>(obj["type"].asInt())) {
    case Pokemon::Type::Bulbasaur:
        pokemon = new BulbasaurPokemon();
        break;
    case Pokemon::Type::Pikachu:
        pokemon = new PikachuPokemon();
        break;
    case Pokemon::Type::Slowpoke:
        pokemon = new SlowpokePokemon();
        break;
    }

    pokemon->fromJson(obj);
    return std::unique_ptr<Pokemon>(pokemon);
}
