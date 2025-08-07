#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <time.h>
#include <cmath>
#include <windows.h>
#include "myclasses.h"
#include "myfunctions.h"
using namespace std;

int main() {
	
	srand((unsigned)time(NULL));

	int x_dimension, y_dimension;
	int crowd;
	char team, winning_team;
	int rounds = 0;
	int i, j, k;
	int exit = 0;
	int flag = 0;
	Ancestor* current_entity;
	Ancestor* adjacent_entity;

	//Introductory prints
	welcoming_print();
	introduction(x_dimension, y_dimension, team);

	//Create the map, the entities and place them on the map
	crowd = floor((x_dimension * y_dimension) / 15);

	Map map(x_dimension, y_dimension);
	map.manage_tiles();

	Vampire** edward = new Vampire * [crowd];
	Werewolf** jacob = new Werewolf * [crowd];
	Avatar bella(team);

	for (i = 0; i < crowd; i++) {
		edward[i] = new Vampire;
		jacob[i] = new Werewolf;
	}

	map.place_entity(&bella);

	for (i = 0; i < crowd; i++) {
		map.place_entity(edward[i]);
		map.place_entity(jacob[i]);
	}

	map.place_potion();

	//First print of the map
	system("cls");
	map.print();

	//The loop of the game

	using namespace chrono_literals;

	while (!exit) {
		flag = 0;

		//Check every other tile and their adjacent for entities able to interact
		for (i = 0; i < x_dimension; i++) {
			for (j = 0; j < y_dimension; j++) {
				if ((i + j) % 2)
					continue;
				if (map.get_tile(i, j)->get_entity() == NULL)
					continue;

				current_entity = map.get_tile(i, j)->get_entity();

				if (map.get_tile(i, j)->get_adjacent(0) != NULL && map.get_tile(i, j)->get_adjacent(0)->get_entity() != NULL) {
					adjacent_entity = map.get_tile(i, j)->get_adjacent(0)->get_entity();
					map.interact(current_entity, adjacent_entity);
				}
				else if (map.get_tile(i, j)->get_adjacent(2) != NULL && map.get_tile(i, j)->get_adjacent(2)->get_entity() != NULL) {
					adjacent_entity = map.get_tile(i, j)->get_adjacent(2)->get_entity();
					map.interact(current_entity, adjacent_entity);
				}
				else if (map.get_tile(i, j)->get_adjacent(4) != NULL && map.get_tile(i, j)->get_adjacent(4)->get_entity() != NULL) {
					adjacent_entity = map.get_tile(i, j)->get_adjacent(4)->get_entity();
					map.interact(current_entity, adjacent_entity);
				}
				else if (map.get_tile(i, j)->get_adjacent(6) != NULL && map.get_tile(i, j)->get_adjacent(6)->get_entity() != NULL) {
					adjacent_entity = map.get_tile(i, j)->get_adjacent(6)->get_entity();
					map.interact(current_entity, adjacent_entity);
				}
			}
		}

		system("cls");
		map.print();
		
		//Check for entities with 0 health and kill them
		for (k = 0; k < crowd; k++) {
			if (edward[k] != NULL && edward[k]->get_health() <= 0) {
				edward[k]->dies();
				delete edward[k];
				edward[k] = NULL;
			}
			if (jacob[k] != NULL && jacob[k]->get_health() <= 0) {
				jacob[k]->dies();
				delete jacob[k];
				jacob[k] = NULL;
			}
		}

		//If all entities of one team die end the game
		if (Vampire::alive_vampires == 0) {
			winning_team = 'w';
			cout << "wolves won";
			exit = 1;
			continue;
		}
		if (Werewolf::alive_werewolves == 0) {
			winning_team = 'v';
			cout << "vamps won";
			exit = 1;
			continue;
		}

		//Player's input
		while (!flag) {
			
			this_thread::sleep_for(200ms);

			if (GetKeyState(0x48) & 0x8000) { //Pressed H
				if (bella.get_team() == 'v' && map.get_time() == DAY)
					bella.use_potion(edward, crowd);
				else if (bella.get_team() == 'w' && map.get_time() == NIGHT)
					bella.use_potion(jacob, crowd);
			}
			else if (GetKeyState(0x50) & 0x8000) { //Pressed P
				pause_print(bella);
			}
			else if (GetKeyState(VK_UP) & 0x8000) {
				bella.move(0);
				flag = 1;
			}
			else if (GetKeyState(VK_RIGHT) & 0x8000) {
				bella.move(2);
				flag = 1;
			}
			else if (GetKeyState(VK_DOWN) & 0x8000) {
				bella.move(4);
				flag = 1;
			}
			else if (GetKeyState(VK_LEFT) & 0x8000) {
				bella.move(6);
				flag = 1;
			}
		}

		system("cls");
		map.print();
		
		//At the end of turn all entities move
		for (k = 0; k < crowd; k++) {
			if (edward[k] != NULL)
				edward[k]->move();
			if (jacob[k] != NULL)
				jacob[k]->move();
		}

		//Add a round played and if enough time has passed day changes into night and the other way around
		rounds++;

		if (rounds == change_time) {
			rounds = 0;
			map.toggle_time();
		}
	}

	ending_print(winning_team, bella.get_team());

	//Free the allocated memory
	for (i = 0; i < crowd; i++) {
		delete edward[i];
		delete jacob[i];
	}
	delete[] edward;
	delete[] jacob;

	return 0;
};