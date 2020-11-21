#pragma once

#include "json/JsonObject.h"

#include <string>
#include <memory>

class Pokemon
{
public:
    enum class Type {
        Bulbasaur,
        Pikachu,
        Slowpoke
    };

    explicit Pokemon(const std::string& name);

    const std::string& getName() const;
    void setName(const std::string& name);

    int getHealth() const;
    void setHealth(int hp);

    int getAttackDamage() const;
    void setAttackDamage(int damage);

    int getDefensePower() const;
    void setDefensePower(int power);

    int getSpeed() const;
    void setSpeed(int speed);

    virtual void setSpecialAttack(int damage) = 0;
    virtual int getSpecialAttack() const = 0;

    virtual void setSpecialDefense(int power) = 0;
    virtual int getSpecialDefense() const = 0;

    JsonObject toJson() const;
    void fromJson(const JsonObject& obj);

    virtual Type type() const = 0;

    static std::unique_ptr<Pokemon> createPokemon(const JsonObject& obj);

private:
    std::string name;
    int health = 0;
    int attackDamage = 0;
    int defensePower = 0;
    int speed = 0;
};

