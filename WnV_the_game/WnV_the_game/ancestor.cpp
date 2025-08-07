#include <iostream>
#include <random>
#include "myclasses.h"
using namespace std;

//-------------
//| Ancestor  |
//-------------

Ancestor::Ancestor()
{
	coordinates = NULL;
	type = -1;

	health = max_health;
	healing = rand() % 3;	//[0-2]
	attack = rand() % 3 + 1;	//[1-3]
	defence = rand() % 2 + 1;	//[1-2]
}

int Ancestor::get_health() const
{
	return health;
}

int Ancestor::get_healing() const
{
	return healing;
}

int Ancestor::get_attack() const
{
	return attack;
}

int Ancestor::get_defence() const
{
	return defence;
}

int Ancestor::get_type() const
{
	return type;
}

void Ancestor::mod_health(int x)
{
	health += x;
}

void Ancestor::full_health() 
{
	health = max_health;
}

void Ancestor::set_healing()
{
	healing--;
}

void Ancestor::set_coordinates(Tile* til)
{
	coordinates = til;
}

void Ancestor::heals(Ancestor* ancestor2) 
{
	int random = rand() % 2;

	if (random && (this->healing)) 
	{
		ancestor2->mod_health(1);
		this->healing--;
	}
}

void Ancestor::attacks(Ancestor* prey)
{
	int difference;

	difference = prey->get_defence() - this->attack;

	if (difference >= 0) 
	{
		return;
	}
	else 
	{
		prey->mod_health(difference);
	}
}

void Ancestor::dies() 
{
	coordinates->set_entity(NULL);
	coordinates = NULL;
}

//-------------
//|  Vampire  |
//-------------

int Vampire::alive_vampires = 0;

Vampire::Vampire()
{
	alive_vampires++;

	type = VAMPIRE;
}

Vampire::~Vampire()
{
	alive_vampires--;
}

void Vampire::print()
{
	cout << "|V|";
}

void Vampire::move() 
{
	int random;

	random = rand() % 9;

	if (!random) 
	{
		return;
	}
	else 
	{
		Tile* newtile=NULL;
		int flag = 0;

		while (!flag) {
			switch (random)
			{
			case 1:
				newtile = coordinates->get_adjacent(0);
				break;
			case 2:
				newtile = coordinates->get_adjacent(1);
				break;
			case 3:
				newtile = coordinates->get_adjacent(2);
				break;
			case 4:
				newtile = coordinates->get_adjacent(3);
				break;
			case 5:
				newtile = coordinates->get_adjacent(4);
				break;
			case 6:
				newtile = coordinates->get_adjacent(5);
				break;
			case 7:
				newtile = coordinates->get_adjacent(6);
				break;
			case 8:
				newtile = coordinates->get_adjacent(7);
			}

			if ((newtile != NULL) && (newtile->get_entity() == NULL) && (newtile->get_element() == LAND))
				flag = 1;
			else
				random = rand() % 8 + 1;
		}

		coordinates->set_entity(NULL);
		coordinates = newtile;
		coordinates->set_entity(this);
	}
}

bool Vampire::flee() {
	int random; 

	random = rand() % 10;

	if (random >= 8) {
		return false;
	}
	else {
		Tile* possibletiles[8];
		Tile* newtile = NULL;
		int i, flag = 0;

		for (i = 0; i < 8; i++) {
			possibletiles[i] = coordinates->get_adjacent(i);
		}

		if (possibletiles[0] != NULL && possibletiles[0]->get_entity() != NULL &&  (*possibletiles[0]->get_entity()).get_type() == WEREWOLF) {
			possibletiles[0] = NULL;
			possibletiles[1] = NULL;
			possibletiles[7] = NULL;
 		}
		else if (possibletiles[2] != NULL && possibletiles[2]->get_entity() != NULL && (*possibletiles[2]->get_entity()).get_type() == WEREWOLF) {
			possibletiles[2] = NULL;
			possibletiles[1] = NULL;
			possibletiles[3] = NULL;
		}
		else if (possibletiles[4] != NULL && possibletiles[4]->get_entity() != NULL && (*possibletiles[4]->get_entity()).get_type() == WEREWOLF) {
			possibletiles[4] = NULL;
			possibletiles[3] = NULL;
			possibletiles[5] = NULL;
		}
		else {
			possibletiles[6] = NULL;
			possibletiles[5] = NULL;
			possibletiles[7] = NULL;
		}

		while (!flag) {
			newtile = possibletiles[random];

			if ((newtile != NULL) && (newtile->get_entity() == NULL) && (newtile->get_element() == LAND))
				flag = 1;
			else
				random = rand() % 8;
		}

		coordinates->set_entity(NULL);
		coordinates = newtile;
		coordinates->set_entity(this);

		return true;
	}
}

//-------------
//| Werewolf  |
//-------------

int Werewolf::alive_werewolves = 0;

Werewolf::Werewolf()
{
	alive_werewolves++;

	type = WEREWOLF;
}

Werewolf::~Werewolf()
{
	alive_werewolves--;
}

void Werewolf::print()
{
	cout << "|W|";
}

void Werewolf::move() 
{
	int random;

	random = rand() % 5;

	if (!random) 
	{
		return;
	}
	else 
	{
		Tile* newtile=NULL;
		int flag = 0;

		while (!flag) {
			switch (random)
			{
			case 1:
				newtile = coordinates->get_adjacent(0);
				break;
			case 2:
				newtile = coordinates->get_adjacent(2);
				break;
			case 3:
				newtile = coordinates->get_adjacent(4);
				break;
			case 4:
				newtile = coordinates->get_adjacent(6);
			}
			
			if ((newtile != NULL) && (newtile->get_entity() == NULL) && (newtile->get_element() == LAND))
				flag = 1;
			else
				random = rand() % 4 + 1;
		}

		coordinates->set_entity(NULL);
		coordinates = newtile;
		coordinates->set_entity(this);
	}
}

bool Werewolf::flee() {
	int random;

	random = rand() % 8;

	if (random >= 4) {
		return false;
	}
	else {
		Tile* newtile = NULL;
		int flag = 0;

		while (!flag) {
			switch (random)
			{
			case 0:
				newtile = coordinates->get_adjacent(0);
				break;
			case 1:
				newtile = coordinates->get_adjacent(2);
				break;
			case 2:
				newtile = coordinates->get_adjacent(4);
				break;
			case 3:
				newtile = coordinates->get_adjacent(6);
			}

			if ((newtile != NULL) && (newtile->get_entity() == NULL) && (newtile->get_element() == LAND))
				flag = 1;
			else
				random = rand() % 4;
		}

		coordinates->set_entity(NULL);
		coordinates = newtile;
		coordinates->set_entity(this);

		return true;
	}
}

//-------------
//|  Avatar   |
//-------------

Avatar::Avatar(char t)
{
	if (t == 'w' || t == 'W')
		team = 'w';
	else
		team = 'v';

	type = AVATAR;
	potions = 1;
}

void Avatar::print()
{
	cout << "|A|";
}

void Avatar::pick_up_potion() {
	coordinates->get_potion();
	potions++;
}

void Avatar::move(int direction) {
	Tile* newtile = NULL;

	switch (direction) 
	{
	case 0:
		newtile = coordinates->get_adjacent(0);
		break;
	case 2:
		newtile = coordinates->get_adjacent(2);
		break;
	case 4:
		newtile = coordinates->get_adjacent(4);
		break;
	case 6:
		newtile = coordinates->get_adjacent(6);
	}

	if (newtile != NULL && newtile->get_element() == LAND && newtile->get_entity() == NULL)
	{
		coordinates->set_entity(NULL);
		coordinates = newtile;
		coordinates->set_entity(this);

		if (coordinates->check_for_potion())
			this->pick_up_potion();
	}
}

int Avatar::get_potions() const
{
	return potions;
}

char Avatar::get_team() const
{
	return team;
}

void Avatar::use_potion(Vampire** group, int crowd) {
	int i;
	
	potions--;

	for (i = 0; i < crowd; i++) {
		if (group[i] != NULL)
			group[i]->full_health();
	}
}

void Avatar::use_potion(Werewolf** group, int crowd) {
	int i;

	potions--;

	for (i = 0; i < crowd; i++) {
		if (group[i] != NULL)
			group[i]->full_health();
	}
}