#include "Card.h"

using namespace std;

Card::Card() {
	name = "Coppper";
	cost = 0;

	types.push_back("Treasure");
	description = {"1 o"};
}

Card::Card(string nm, int cst, vector<string> tps, vector<string> desc) {
	name = nm;
	cost = cst;

	types = tps;
	description = desc;
}

string Card::getName() {
	return name;
}

vector<string> Card::getTypes() {
	return types;
}

vector<string> Card::getDesc() {
	return description;
}

void Card::printCardInfo() {

	int cardWidth = 26;
	int cardHeight = 12;
	int nameSetWidth = (cardWidth - 2 - name.length()) / 2;
	int descriptionSetWidth;

	cout << "+" << setfill('-') << setw(cardWidth - 2) << "" << "+" << endl;

	if (name.length() % 2 == 0) {
		cout << setfill(' ') << "|" << setw(nameSetWidth) << "" << name << setw(nameSetWidth) << "" << "|" << endl;
	}
	else {
		cout << setfill(' ') << "|" << setw(nameSetWidth) << "" << name << setw(nameSetWidth + 1) << "" << "|" << endl;
	}
	

	if (description.size() == 1 && description[0] == " ") {
		for (int i = 0; i < cardHeight; i++) {
			cout << "|" << setw(cardWidth - 2) << "" << "|" << endl;
		}
	}
	else {
		for (int i = 0; i < (cardHeight / 2) - description.size() / 2; i++) {
			cout << "|" << setw(cardWidth - 2) << "" << "|" << endl;
		}

		for (int i = 0; i < description.size(); i++) {
			descriptionSetWidth = (cardWidth - 2 - description[i].size()) / 2;

			if (description[i].size() > 12) {
				int longDescLength = (cardWidth - 14) / 2;
				cout << "|" << setw(cardWidth - 2) << "" << "|" << endl;

				cout << "|" << setw(longDescLength) << "";

				for (int j = 0; j < description[i].size(); j++) {
					if ((j % 12 == 0 && j != 0)) {
						cout << setw(longDescLength) << "" << "|" << endl;
						cout << "|" << setw(longDescLength) << "";
					}
					cout << description[i][j];
				}
				
				cout << setw(longDescLength + (12 -  ((description[i].size() % 12 != 0) ? description[i].length() % 12 : 12))) << "" << "|" << endl;
			}
			else {
				if (description[i].size() % 2 == 0) {
					cout << "|" << setw(descriptionSetWidth) << "" << description[i] << setw(descriptionSetWidth) << "" << "|" << endl;
				}
				else {
					cout << "|" << setw(descriptionSetWidth) << "" << description[i] << setw(descriptionSetWidth + 1) << "" << "|" << endl;
				}
			}


			


		}

		for (int i = 0; i < (cardHeight / 2) - description.size() / 2; i++) {
			cout << "|" << setw(cardWidth - 2) << "" << "|" << endl;
		}

	}

	int typeLength = 0;

	for (int i = 0; i < types.size(); i++) {
		typeLength += types[i].size();
		if (i > 0) {
			typeLength += 3;
		}
	}

	if (typeLength % 2 == 0) {
		typeLength = (cardWidth - 2 - typeLength) / 2;
		cout << "|" << cost << setw(typeLength - to_string(cost).length()) << "";
	}
	else {
		typeLength = ((cardWidth - 2 - typeLength) / 2);
		cout << "|" << cost << setw(typeLength - to_string(cost).length() + 1) << "";
	}
	
	
	for (int i = 0; i < types.size(); i++) {
		cout << types[i];
		if (i < types.size() - 1) {
			cout << " - ";
		}
	}

	cout << setw(typeLength) << "" << "|" << endl;
	cout << "+" << setfill('-') << setw(cardWidth - 2) << "" << "+" << endl << endl;

	
}