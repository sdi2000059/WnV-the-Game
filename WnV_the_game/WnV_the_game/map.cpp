#include <iostream>
#include <random>
#include "myclasses.h"
using namespace std;

//-------------
//|   Tile    |
//-------------

// For every tile i,j there exists the following grid where the tile i,j is the center and around it its adjacent tiles
// -------------
// | 7 | 0 | 1 |
// -------------
// | 6 | i | 2 |
// -------------
// | 5 | 4 | 3 |
// -------------
// Adjacent(0) is the one on top of it and so the north tile, adjacent(1) is the one on top right of it and so the northeast tile and so forth


Tile::Tile() {
	cx = 0;
	cy = 0;
	potion = 0;
	entity = NULL;
	north = NULL;
	northeast = NULL;
	east = NULL;
	southeast = NULL;
	south = NULL;
	southwest = NULL;
	west = NULL;
	northwest = NULL;

	int random;

	random = rand() % 10;

	if (random <= 7)
		element = LAND;
	else if (random == 8)
		element = WATER;
	else
		element = TREE;
}

int Tile::get_element() const {
	return element;
}

void Tile::set_coordinates(int x, int y) {
	cx = x;
	cy = y;
}

void Tile::set_potion() {
	potion = 1;
}

void Tile::get_potion() {
	potion = 0;
}

bool Tile::check_for_potion() {
	if (potion == 1)
		return true;
	else
		return false;
}

void Tile::print() {
	if (entity != NULL) {
		entity->print();
	}
	else {
		if (potion == 1)
			cout << " P ";
		else if (element == LAND)
			cout << "---";
		else if (element == WATER)
			cout << " ~ ";
		else
			cout << "/|\\";
	}
}

void Tile::set_entity(Ancestor* anc) {
	entity = anc;
}

Ancestor* Tile::get_entity() const {
	return entity;
}

void Tile::set_adjacent(int direction, Tile* adjacent) {
	switch (direction) {
	case 0:
		north = adjacent;
		break;
	case 1:
		northeast = adjacent;
		break;
	case 2:
		east = adjacent;
		break;
	case 3:
		southeast = adjacent;
		break;
	case 4:
		south = adjacent;
		break;
	case 5:
		southwest = adjacent;
		break;
	case 6:
		west = adjacent;
		break;
	case 7:
		northwest = adjacent;
	}
}

Tile* Tile::get_adjacent(int direction) const {
	switch (direction){
	case 0:
		return north;
	case 1:
		return northeast;
	case 2:
		return east;
	case 3:
		return southeast;
	case 4:
		return south;
	case 5:
		return southwest;
	case 6:
		return west;
	case 7:
		return northwest;
	default:
		return NULL;
	}
}

//-------------
//|   Map     |
//-------------

Map::Map(int x, int y) {
	int random, i, j;

	xdimension = x;
	ydimension = y;

	tiles = new Tile * [xdimension];

	for (i = 0; i < xdimension; i++) {
		tiles[i] = new Tile[ydimension];
	}

	for (i = 0; i < xdimension; i++)
		for (j = 0; j < ydimension; j++)
			tiles[i][j].set_coordinates(i, j);

	random = rand() % 2;

	if (random)
		time = DAY;
	else
		time = NIGHT;
}

Map::~Map() {
	int i;

	for (i = 0; i < xdimension; i++) {
		delete[] tiles[i];
	}

	delete[] tiles;
}

void Map::manage_tiles() {
	int i, j;
	
	for (i = 0; i < xdimension; i++) {
		for (j = 0; j < ydimension; j++) {
			if ((0 <= i-1) && ( i-1 < xdimension) && (0 <= j-1) && (j-1 < ydimension))
				tiles[i][j].set_adjacent(7, this->get_tile(i-1, j-1));

			if ((0 <= i-1) && (i-1 < xdimension) && (0 <= j) && (j < ydimension))
				tiles[i][j].set_adjacent(0, this->get_tile(i-1, j));

			if ((0 <= i-1) && (i-1 < xdimension) && (0 <= j+1) && (j+1 < ydimension))
				tiles[i][j].set_adjacent(1, this->get_tile(i-1, j+1));

			if ((0 <= i) && (i < xdimension) && (0 <= j-1) && (j-1 < ydimension))
				tiles[i][j].set_adjacent(6, this->get_tile(i, j-1));

			if ((0 <= i) && (i < xdimension) && (0 <= j+1) && (j+1 < ydimension))
				tiles[i][j].set_adjacent(2, this->get_tile(i, j+1));

			if ((0 <= i+1) && (i+1 < xdimension) && (0 <= j-1) && (j-1 < ydimension))
				tiles[i][j].set_adjacent(5, this->get_tile(i+1, j-1));

			if ((0 <= i+1) && (i+1 < xdimension) && (0 <= j) && (j < ydimension))
				tiles[i][j].set_adjacent(4, this->get_tile(i+1, j));

			if ((0 <= i+1) && (i+1 < xdimension) && (0 <= j+1) && (j+1 < ydimension))
				tiles[i][j].set_adjacent(3, this->get_tile(i+1, j+1));
		}
	}
}

void Map::print() {
	int i, j;

	for (i = 0; i < xdimension; i++) {
		for (j = 0; j < ydimension; j++)
			tiles[i][j].print();
		cout << endl;
	};
	cout << endl;

	cout << "Time: ";
	if (time == DAY)
		cout << "Day" << endl;
	else
		cout << "Night" << endl;
}

int Map::get_time() const {
	return time;
}

void Map::toggle_time() {
	if (time == DAY)
		time = NIGHT;
	else
		time = DAY;
}

Tile* Map::get_tile(int x, int y) {
	return &tiles[x][y];
}

void Map::place_entity(Ancestor* entity) {
	int randomx, randomy;
	int flag = 0;

	randomx = rand() % xdimension;
	randomy = rand() % ydimension;

	while (!flag) {
		if (tiles[randomx][randomy].get_element() == LAND && tiles[randomx][randomy].get_entity() == NULL) {
			tiles[randomx][randomy].set_entity(entity);
			entity->set_coordinates(&tiles[randomx][randomy]);
			flag = 1;
		}
		else {
			randomx = rand() % xdimension;
			randomy = rand() % ydimension;
		}
	}
}

void Map::place_potion() {
	int rx, ry;
	int flag = 0;

	rx = rand() % xdimension;
	ry = rand() % ydimension;

	while (!flag) {
		if (tiles[rx][ry].get_element() == LAND && tiles[rx][ry].get_entity() == NULL) {
			tiles[rx][ry].set_potion();
			flag = 1;
		}
		else {
			rx = rand() % xdimension;
			ry = rand() % ydimension;
		}
	}
}

void Map::interact(Ancestor* entity1, Ancestor* entity2) {
	if (entity1->get_type() == AVATAR || entity2->get_type() == AVATAR) {
		return;
	}
	else if (entity1->get_type() == entity2->get_type()) {
		if (entity2->get_health() < 10) {
			entity1->heals(entity2);
		}
		if (entity1->get_health() < 10) {
			entity2->heals(entity1);
		}
	}
	else {
		if (entity1->get_attack() >= entity2->get_attack()) {
			//ent2 tries to get away, if not succesful:
				//ent1 attacks ent2
			if (!entity2->flee()) {
				entity1->attacks(entity2);
			}
		}
		else {
			//ent1 tries to get away, if not succesful:
				//ent2 attacks ent1
			if (!entity1->flee()) {
				entity2->attacks(entity1);
			}
		}
	}
}