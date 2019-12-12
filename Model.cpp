#include "Model.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "Rival.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
using namespace std;

Model::Model() {
    time = 0;
    //Pokemon 1
    Pokemon *p1 = new Pokemon("Pikachu", 2.0, 20, 5, 4, 15, 1, 'P', Point2D(5, 1));
    pokemon_ptrs.push_back(p1);
    object_ptrs.push_back(p1);
    active_ptrs.push_back(p1);
    //Pokemon 2
    Pokemon *p2 = new Pokemon("Bulbasaur", 1.0, 20, 5, 4, 15, 2, 'P', Point2D(10, 1));
    pokemon_ptrs.push_back(p2);
    object_ptrs.push_back(p2);
    active_ptrs.push_back(p2);
    //PokemonCenter 1
    PokemonCenter *c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    center_ptrs.push_back(c1);
    object_ptrs.push_back(c1);
    //PokemonCenter 2
    PokemonCenter *c2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    center_ptrs.push_back(c2);
    object_ptrs.push_back(c2);
    //PokemonGym 1
    PokemonGym *g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    gym_ptrs.push_back(g1);
    object_ptrs.push_back(g1);
    //PokemonGym 2
    PokemonGym *g2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
    gym_ptrs.push_back(g2);
    object_ptrs.push_back(g2);
    //BattleArena
    BattleArena *a1 = new BattleArena(3, 3, 2.5, 1, Point2D(15, 12));
    arena_ptrs.push_back(a1);
    object_ptrs.push_back(a1);
    cout << "Model default constructed. " << endl;
    //Rival 1
    Rival *r1 = new Rival("Arcanine", 13, 30, 3, 6, 10, 1, a1, Point2D(15, 12));
    rival_ptrs.push_back(r1);
    object_ptrs.push_back(r1);
    active_ptrs.push_back(r1);
    //Rival 2
    Rival *r2 = new Rival("Onix", 8, 40, 20, 10, 20, 2, a1, Point2D(15, 12));
    rival_ptrs.push_back(r2);
    object_ptrs.push_back(r2);
    active_ptrs.push_back(r2);
    //Rival 3
    Rival *r3 = new Rival("Jolteon", 17, 25, 12, 20, 15, 3, a1, Point2D(15, 12));
    rival_ptrs.push_back(r3);
    object_ptrs.push_back(r3);
    active_ptrs.push_back(r3);
    cout << "Model default constructed. " << endl;
}

Model::~Model(){
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++){
        delete *iter;
    }
    cout << "Model destructed. " << endl;
}

Pokemon *Model::GetPokemonPtr(int id){
    for (auto iter = pokemon_ptrs.begin(); iter != pokemon_ptrs.end(); iter++){
        if ((*iter)->GetId() == id){
            return (*iter);
        }
    }
    return 0;
}

PokemonCenter *Model::GetPokemonCenterPtr(int id){
    for (auto iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++){
        if ((*iter)->GetId() == id){
            return (*iter);
        }
    }
    return 0;
}

PokemonGym *Model::GetPokemonGymPtr(int id){
    for (auto iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++){
        if ((*iter)->GetId() == id){
            return (*iter);
        }
    }
    return 0;
}

Rival *Model::GetRivalPtr(int id){
    for (auto iter = rival_ptrs.begin(); iter != rival_ptrs.end(); iter++){
        if ((*iter)->GetId() == id){
            return (*iter);
        }
    }
    return 0;
}

BattleArena *Model::GetBattleArenaPtr(int id){
    for (auto iter = arena_ptrs.begin(); iter != arena_ptrs.end(); iter++){
        if ((*iter)->GetId() == id){
            return (*iter);
        }
    }
    return 0;
}

bool Model::Update(){
    time++;
    bool updated = false;
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter){
        GameObject *obj = *iter;
        if (obj->Update()){
            updated = true;
        }
    }
    int gyms_beaten = 0;
    for (auto iter = gym_ptrs.begin(); iter != gym_ptrs.end(); ++iter){
        PokemonGym *gym = *iter;
        if (gym->IsBeaten() == true){
            gyms_beaten++;
            if (gyms_beaten == gym_ptrs.size()){
                cout << "GAME OVER: You win! All Pokemon Gyms beaten!\n";
                exit(EXIT_SUCCESS);
            }
        }
    }
    int arenas_beaten = 0;
    for (auto iter = arena_ptrs.begin(); iter != arena_ptrs.end(); ++iter){
        BattleArena *arena = *iter;
        if (arena->IsBeaten() == true){
            arenas_beaten++;
            if (arenas_beaten == arena_ptrs.size()){
                cout << "GAME OVER: You win! All Battle Arenas beaten!\n";
                exit(EXIT_SUCCESS);
            }
        }
    }
    int tired_pokemon = 0;
    for (auto iter = pokemon_ptrs.begin(); iter != pokemon_ptrs.end(); ++iter){
        Pokemon *pokemon = *iter;
        if (pokemon->IsExhausted() == true){
            tired_pokemon++;
            if (tired_pokemon == pokemon_ptrs.size()){
                cout << "GAME OVER: You lose! All of your Pokemon are tired!\n";
                exit(EXIT_SUCCESS);
            }
        }
    }
    int fainted_pokemon = 0;
    for (auto iter = pokemon_ptrs.begin(); iter != pokemon_ptrs.end(); ++iter){
        Pokemon *pokemon = *iter;
        if (pokemon->IsAlive() == false){
            active_ptrs.remove(pokemon);
            fainted_pokemon++;
            if (fainted_pokemon == pokemon_ptrs.size()){
                cout << "GAME OVER: You lose! All of your Pokemon fainted!\n";
                exit(EXIT_SUCCESS);
            }
        }
    }
    for (auto iter = rival_ptrs.begin(); iter != rival_ptrs.end(); ++iter){
        Rival *rival = *iter;
        if (rival->IsAlive() == false){
            active_ptrs.remove(rival);
        }
    }
    return updated;
}

void Model::Display(View &view) {
    view.Clear();
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter){
        GameObject *obj = *iter;
        view.Plot(obj);
    }
    view.Draw();
}

void Model::ShowStatus() {
    cout << "Time: " << time << endl;
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter){
        GameObject *obj = *iter;
        obj->ShowStatus();
    }
}
