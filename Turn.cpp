#include "Turn.h"
#include "Functionality.h"


Turn::Turn() {
	//Do nothing for now
}

Turn::Turn(vector<Card>* hand, Deck* draw, Deck* discard) {

	actions = 1;
	buys = 1;
	coins = 0;

	takeActions(hand, draw, discard);

	takeBuys(hand, draw, discard);

	cleanUp(hand, draw, discard);

}

void Turn::takeActions(vector<Card>* hand, Deck* draw, Deck* discard) {
	string cName;
	vector<int> actionsChoices;
	cout << "Action turn. Cards available: " << endl;

	for (int i = 0; i < hand->size(); i++) {
		for (int j = 0; j < (*hand)[i].getTypes().size(); j++) {
			if ((*hand)[i].getTypes()[j] == "Action") {
				cout << i + 1 << ". " << (*hand)[i].getName();
				actionsChoices.push_back(i);
				break;
			}
			cout << "\n\n";
		}
	}

	cout << endl;

	while (actions > 0) {
		cout << "Action play: " << endl;
		getline(cin, cName);
		int choice = stoi(cName);

		Functionality action;

		//Do action
	}

	

	
	
}