#include "Card.h"

using namespace std;

Card::Card() {
	name = "Copper";
	cost = 0;

	types.push_back("Treasure");
	description = {"1 $"};
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

int Card::getCost() {
	return cost;
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

				vector<string> splitUpDesc = splitUpLongDescription(12, description[i]);


				for (int j = 0; j < splitUpDesc.size(); j++) {

					cout << splitUpDesc[j];

					cout << setw(cardWidth - 2 - (longDescLength + splitUpDesc[j].length())) << "" << "|" << endl;

					if (j != splitUpDesc.size() - 1) {
						cout << "|" << setw(longDescLength) << "";
					}
					
				}
				
				//cout << setw(longDescLength + (12 -  ((description[i].size() % 12 != 0) ? description[i].length() % 12 : 12))) << "" << "|" << endl;
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

	cout << setfill(' ');

	
}

bool Card::isOfType(string type) {
	bool retVal = false;
	for (int i = 0; i < types.size(); i++) {
		if (types[i] == type) {
			retVal = !retVal;
			break;
		}
	}

	return retVal;
}

vector<string> Card::splitUpLongDescription(int endIndex, string description) {
	vector<string> retSentences;

	string fragment = "";
	int currentIndex = 0;

	while (true) {

		if (description.find(' ') != string::npos && fragment.size() + description.find(' ') <= 12) {
			fragment += description.substr(0, description.find(' ')) + ' ';
			description = description.substr(description.find(' ') + 1);
		}
		else if(description.find(' ') == string::npos) {
			retSentences.push_back(fragment + description.substr(currentIndex));
			currentIndex = description.size();
			break;
		}
		else {
			retSentences.push_back(fragment);
			fragment = "";

		}
		
	}

	return retSentences;
}