#include "Turn.h"
#include "Functionality.h"


Turn::Turn() {
	actions = 1;
	buys = 1;
	coins = 0;

	board = new Board();

	
	//Do nothing for now
}

Turn::Turn(vector<Card>* hand, Deck* draw, Deck* discard, Board* b) {

	actions = 1;
	buys = 1;
	coins = 0;

	board = b;

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
		//Then put the current card "in play," A.K.A. put it in our vector in the turn private data
	}
	
}

void Turn::takeBuys(vector<Card>* hand, Deck* draw, Deck* discard) {
	cout << "Buy Phase" << endl << endl;
	for (int i = 0; i < buys; i++) {
		cout << "Coins: " << coins << endl;
		cout << "Num of buys: " << buys - i << endl;

		//Print out mini-view of board

		string choice;
		do {
			cout << "1. Look at specific card in deck - look [card name]" << endl;
			cout << "2. Buy a card - buy [card name]" << endl;
			cout << "3. Pass this buy - pass" << endl;

			if(choice.find("look ") != string::npos) {
				string cName = choice.substr(5);
				board->printCardInfo(cName);

			}
			else if (choice.find("buy ") != string::npos) {
				string cName = choice.substr(4);
				Card cToBuy = board->findCardOnBoard(cName);
				if (coins >= cToBuy.getCost()) {
					Card c = board->takeCard(cName);
					discard->addCard(c);
					coins -= c.getCost();
					break;
				}
				else {
					cout << "Oops, looks like you do not have enough money to buy this card." << endl << endl;
					choice = "";
				}
			}
			if (choice == "pass") {
				break;
			}
			else {
				cout << "That is not a choice! Either look at a card, buy a card, or skip you buy" << endl << endl;
			}

		} while (choice[0] != 'b' || choice[0] != 'p');


		
	}

	cout << "End of Buy phase" << endl << endl;
}

void Turn::cleanUp(vector<Card>* hand, Deck* draw, Deck* discard) {
	for (int i = 0; i < inPlay.size(); i++) {
		Card c = inPlay[i];
		discard->addCard(c);
	}

	inPlay.clear();


}