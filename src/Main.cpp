#include <iostream>
#include <fstream>

#include "json/JsonObject.h"
#include "json/JsonArray.h"

#include "pokemon/BulbasaurPokemon.h"
#include "pokemon/SlowpokePokemon.h"
#include "pokemon/PikachuPokemon.h"

JsonObject createPokemons()
{
    BulbasaurPokemon bulbasaur;
    SlowpokePokemon slowpoke;

    PikachuPokemon pikachu1;
    pikachu1.setName("FirstPickachu");
    PikachuPokemon pikachu2;
    pikachu2.setName("SecondPickachu");

    JsonArray pokemonArray;
    pokemonArray.values().push_back(bulbasaur.toJson());
    pokemonArray.values().push_back(slowpoke.toJson());
    pokemonArray.values().push_back(pikachu1.toJson());
    pokemonArray.values().push_back(pikachu2.toJson());

    JsonObject root;
    root["pokemons"] = pokemonArray;
    return root;
}

int main(int argc, char** argv)
{
    std::string filename = argc == 2 ? argv[1] : "pokemons.json";

    std::ifstream file(filename);
    JsonObject root;

    if (!file) {
        std::cout << "Could not open " << filename << ", creating new..." << std::endl;
        root = createPokemons();
        std::ofstream newFile(filename);
        newFile << root;

    } else {
        file >> root;
    }

    JsonArray pokemonArray = root["pokemons"].asArray();
    std::cout << "Loaded " << pokemonArray.values().size() << " pokemons:" << std::endl;

    for (const JsonValue& value : pokemonArray.values()) {
        std::unique_ptr<Pokemon> pokemon = Pokemon::createPokemon(value.asObject());
        std::cout << pokemon->getName()
                  << " (Special attack = " << pokemon->getSpecialAttack()
                  << ", special defense = " << pokemon->getSpecialDefense()
                  << ")" << std::endl;
    }

    return 0;
}
