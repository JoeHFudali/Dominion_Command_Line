#include "Card.h"

using namespace std;

Card::Card() {
	name = "Coppper";
	cost = 0;

	types.push_back("Treasure");
	description = {" "};
}

Card::Card(string nm, int cst, vector<string> tps, vector<string> desc) {
	name = nm;
	cost = cst;

	types = tps;
	description = desc;
}

void Card::printCardInfo() {

	int cardWidth = 16;
	int cardHeight = 9;
	int nameSetWidth = (cardWidth - 2 - name.length()) / 2;

	cout << "+" << setfill('-') << setw(cardWidth - 2) << "" << "+" << endl;

	if (name.length() % 2 == 0) {
		cout << setfill(' ') << "|" << setw(nameSetWidth) << "" << name << setw(nameSetWidth) << "" << "|" << endl;
	}
	else {
		cout << setfill(' ') << "|" << setw(nameSetWidth) << "" << name << setw(nameSetWidth + 1) << "" << "|" << endl;
	}
	

	for (int i = 0; i < cardHeight / 2; i++) {
		cout << "|" << setw(cardWidth - 2) << "" << "|" << endl;
	}


	for(int )
	cout << "|" << setw(nameSetWidth)

	

	
}