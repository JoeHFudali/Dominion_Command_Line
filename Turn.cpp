#include "Turn.h"


Turn::Turn() {
	//Do nothing for now
}

Turn::Turn(vector<Card>& hand, Deck& draw, Deck& discard) {

	actions = 1;
	buys = 1;

	takeActions(hand, draw, discard);

	//takeBuys(hand, draw, discard);

	//cleanUp(hand, draw, discard);

}

void Turn::takeActions(vector<Card>& hand, Deck& draw, Deck& discard) {
	string cName;
	cout << "Action turn. Cards available: " << endl;

	for (int i = 0; i < hand.size(); i++) {
		for (int j = 0; j < hand[i].getTypes().size(); j++) {
			if (hand[i].getTypes()[j] == "Action") {
				cout << hand[i].getName();
				break;
			}
			cout << " - ";
		}
	}

	cout << endl;

	cout << "Type the card name you want to play: " << endl;
	getline(cin, cName);

	Card pCard;
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].getName() == cName) {

		}
	}
	
}