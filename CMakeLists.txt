cmake_minimum_required(VERSION 3.5)

project(Pokemon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(Pokemon
    src/Main.cpp
    src/json/JsonValue.cpp
    src/json/JsonValue.h
    src/json/JsonObject.cpp
    src/json/JsonObject.h
    src/json/JsonArray.cpp
    src/json/JsonArray.h
    src/pokemon/Pokemon.cpp
    src/pokemon/Pokemon.h
    src/pokemon/BulbasaurPokemon.cpp
    src/pokemon/BulbasaurPokemon.h
    src/pokemon/PikachuPokemon.cpp
    src/pokemon/PikachuPokemon.h
    src/pokemon/SlowpokePokemon.cpp
    src/pokemon/SlowpokePokemon.h)
