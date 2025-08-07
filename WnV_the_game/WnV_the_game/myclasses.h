#pragma once

#define max_health 5
#define change_time 10

enum element { LAND, WATER, TREE };
enum time { DAY, NIGHT };
enum kind { VAMPIRE, WEREWOLF, AVATAR };

class Ancestor;

class Tile {
private:
	int element;
	int cx, cy;
	int potion;
	Ancestor* entity;
	Tile* north;
	Tile* northeast;
	Tile* east;
	Tile* southeast;
	Tile* south;
	Tile* southwest;
	Tile* west;
	Tile* northwest;
public:
	Tile();
	~Tile() {};
	void print();
	void set_potion();
	void get_potion();
	bool check_for_potion();
	int get_element() const;
	void set_coordinates(int, int);
	void set_entity(Ancestor*);
	void set_adjacent(int, Tile*);
	Ancestor* get_entity() const;
	Tile* get_adjacent(int) const;
};

class Map {
private:
	int time;
	int xdimension, ydimension;
	Tile** tiles;
public:
	Map(int, int);
	~Map();
	void manage_tiles();
	void print();
	int get_time() const;
	void toggle_time();
	Tile* get_tile(int, int);
	void place_entity(Ancestor*);
	void place_potion();
	void interact(Ancestor*, Ancestor*);
};

class Ancestor
{
protected:
	int health;
	int healing;
	int attack;
	int defence;
	Tile* coordinates;
	int type;
public:
	Ancestor();
	~Ancestor() {};
	virtual void move() = 0;
	virtual void print() = 0;
	int get_health() const;
	int get_healing() const;
	int get_attack() const;
	int get_defence() const;
	int get_type() const;
	void mod_health(int);
	void full_health();
	void set_healing();
	void set_coordinates(Tile*);
	void heals(Ancestor*);
	void attacks(Ancestor*);
	virtual bool flee() { return false; };
	void dies();
};

class Vampire : public Ancestor
{
public:
	Vampire();
	~Vampire();
	void print();
	void move();
	bool flee();
	static int alive_vampires;
private:
};

class Werewolf : public Ancestor
{
public:
	Werewolf();
	~Werewolf();
	void print();
	void move();
	bool flee();
	static int alive_werewolves;
};

class Avatar : public Ancestor
{
public:
	Avatar(char);
	~Avatar() {};
	void print();
	void move() {};
	void move(int);
	int get_potions() const;
	char get_team() const;
	void use_potion(Vampire**, int);
	void use_potion(Werewolf**, int);
	void pick_up_potion();
private:
	int potions;
	char team;
};