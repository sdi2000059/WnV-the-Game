#include <iostream>
#include "myfunctions.h"
#include "myclasses.h"
using namespace std;

void welcoming_print() {
	cout << "WnV The game" << endl;
	cout << "Choose between the vampires and the werewolves and assist your team to win" << endl;
	cout << "Use your arrow keys to move, press P to pause the game and see the info" << endl
		<< "and last press H to fully heal the vampires during the day" << endl
		<< "or if you chose the werewolves heal them during night" << endl;
	system("pause");
}

void introduction(int& xdimension, int& ydimension, char& team) {
	system("cls");
	cout << "Give dimensions for the map" << endl;
	cout << "X dimension: ";
	cin >> xdimension;
	cout << "Y dimension: ";
	cin >> ydimension;

	cout << "Type W if you're teaming with the werewolves \n  or V if you're teaming with the vampires" << endl;
	cout << "Choose your team: ";
	cin >> team;
}

void pause_print(Avatar& bella) {
	cout << "Potions: " << bella.get_potions() << endl;
	cout << "Vampires alive: " << Vampire::alive_vampires << endl;
	cout << "Werewolves alive: " << Werewolf::alive_werewolves << endl;
	system("pause");
}

void ending_print(char winningteam, char myteam) {

	if (winningteam == myteam) {
		system("cls");
		cout << "Congratulations!" << endl;
		cout << "Your team, ";
		if (myteam == 'v')
			cout << "the vampires, ";
		else
			cout << "the werewolves, ";
		cout << "won" << endl;
	}
	else {
		system("cls");
		cout << "Your opposing team, ";
		if (myteam == 'v')
			cout << "the vampires, ";
		else
			cout << "the werewolves, ";
		cout << "won" << endl;
		cout << "You lost" << endl;
	}
}