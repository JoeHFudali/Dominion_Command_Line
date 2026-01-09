#include "Turn.h"
#include "Player.h"
#include "Functionality.h"


Turn::Turn() {
	actions = 1;
	buys = 1;
	coins = 0;

	merchantBuff = 0;
	

	board = new Board();

	
	//Do nothing for now
}

Turn::Turn(vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board* b, bool isAgent) {

	actions = 1;
	buys = 1;
	coins = 0;

	merchantBuff = 0;
	

	board = b;

	

	if (!isAgent) {

		/*for (int i = 0; i < hand->size(); i++) {
			hand->at(i).printCardInfo();
		}*/

		takeActions(players, hand, draw, discard);

		takeBuys(hand, draw, discard);

		cleanUp(hand, draw, discard);
	}
	else {
		agentActions(players, hand, draw, discard);

		agentBuys(hand, draw, discard);

		cleanUp(hand, draw, discard);
	}
	

}

void Turn::takeActions(vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard) {
	string cName;
	vector<Card> actionsChoices;
	vector<int> actionIndexHand;

	cout << "Action turn. Cards available: " << endl;

	int num = 1;

	for (int i = 0; i < hand->size(); i++) {
		for (int j = 0; j < (*hand)[i].getTypes().size(); j++) {
			if ((*hand)[i].getTypes()[j] == "Action") {
				cout << num << ". " << (*hand)[i].getName();
				actionsChoices.push_back((*hand)[i]);
				actionIndexHand.push_back(i);
				cout << "\n\n";
				num++;
				break;
			}
			
		}
	}

	cout << endl;

	while (actions > 0 && actionsChoices.size() > 0) {

		printBoardAndPlayerDecks(hand, draw, discard);

		cout << "Action play: " << endl;
		getline(cin, cName);
		int choice = stoi(cName) - 1;

		if (choice >= actionsChoices.size()) {
			choice = actionsChoices.size() - 1;
		}
		else if (choice < 0) {
			choice = 0;
		}


		Card c = actionsChoices[choice];

		Functionality action;

		//Do action - board neeeds to be changed here
		hand->erase(hand->begin() + actionIndexHand[choice]);
		actionsChoices.erase(actionsChoices.begin() + choice);

		action.PlayCard(c, players, hand, draw, discard, *board, actions, buys, coins, merchantBuff);
		
		
		//Then put the current card "in play," A.K.A. put it in our vector in the turn private data
		inPlay.push_back(c);

		actions--;
	}
	
}

void Turn::takeBuys(vector<Card>* hand, Deck* draw, Deck* discard) {
	cout << "Buy Phase" << endl << endl;

	for (int i = 0; i < hand->size(); i++) {
		if (hand->at(i).getName() == "Silver") {
			coins += merchantBuff;
			break;
		}
	}

	for (int i = 0; i < hand->size(); i++) {
		if (hand->at(i).isOfType("Treasure")) {
			coins += hand->at(i).getDesc()[0][0] - '0';
		}
	}



	for (int i = 0; i < buys; i++) {

		printBoardAndPlayerDecks(hand, draw, discard);


		cout << "Coins: " << coins << endl;
		cout << "Num of buys: " << buys - i << endl;

		//Print out mini-view of board

		string choice;
		do {
			cout << "1. Look at specific card in deck - look [card name]" << endl;
			cout << "2. Buy a card - buy [card name]" << endl;
			cout << "3. Pass this buy - pass" << endl;

			getline(cin, choice);

			if(choice.find("look ") != string::npos) {
				string cName = choice.substr(5);
				board->printCardInfo(cName);

			}
			else if (choice.find("buy ") != string::npos && board->isCardAvaliable(choice.substr(4))) {
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
				cout << "That is not a choice, or that card pile is empty! Either look at a card, buy a card (that is still in stock), or skip you buy" << endl << endl;
				choice = "";
			}

		} while (choice[0] != 'b' || choice[0] != 'p');


		
	}

	cout << "End of Buy phase" << endl << endl;
}

void Turn::cleanUp(vector<Card>* hand, Deck* draw, Deck* discard) {

	cout << "Clean up phase!" << endl << endl;

	for (int i = 0; i < inPlay.size(); i++) {
		Card c = inPlay[i];
		discard->addCard(c);
	}

	inPlay.clear();


}

void Turn::agentActions(vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard) {

	for (int i = 0; i < hand->size(); i++) {
		if (actions == 0) {
			break;
		}

		if (hand->at(i).isOfType("Action")) {
			Functionality action;
			Card c = hand->at(i);
			hand->erase(hand->begin() + i);

			cout << "Agent is playing a " << c.getName() << endl;

			action.PlayCard(c, players, hand, draw, discard, *board, actions, buys, coins, merchantBuff);

			inPlay.push_back(c);
			actions--;
		}
		
	}

}

void Turn::agentBuys(vector<Card>* hand, Deck* draw, Deck* discard) {

	for (int i = 0; i < hand->size(); i++) {
		if (hand->at(i).getName() == "Silver") {
			coins += merchantBuff;
			break;
		}
	}

	for (int i = 0; i < hand->size(); i++) {
		if (hand->at(i).isOfType("Treasure")) {
			coins += hand->at(i).getDesc()[0][0] - '0';
		}
	}

	while (buys > 0) {
		Card cToBuy;
		int randIndex;

		if (coins < 2) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				//do nothing
			}
			else {
				cToBuy = board->takeCard("Copper");
				discard->addCard(cToBuy);

			}
		}

		else if (coins == 2) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				if (board->isCardAvaliable("Estate")) {
					cToBuy = board->takeCard("Estate");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				
			}

			else {
				if (board->isCardAvaliable("Moat")) {
					cToBuy = board->takeCard("Moat");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Chapel")) {
					cToBuy = board->takeCard("Chapel");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Cellar")) {
					cToBuy = board->takeCard("Cellar");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
		}

		else if (coins == 3) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				cToBuy = board->takeCard("Silver");

				discard->addCard(cToBuy);
				coins -= cToBuy.getCost();
			}
			else {
				if (board->isCardAvaliable("Village")) {
					cToBuy = board->takeCard("Village");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Vassal")) {
					cToBuy = board->takeCard("Vassal");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Merchant")) {
					cToBuy = board->takeCard("Merchant");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Workshop")) {
					cToBuy = board->takeCard("Workshop");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Harbinger")) {
					cToBuy = board->takeCard("Harbinger");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
		}

		else if (coins == 4) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				cToBuy = board->takeCard("Silver");

				discard->addCard(cToBuy);
				coins -= cToBuy.getCost();
			}
			else {
				if (board->isCardAvaliable("Militia")) {
					cToBuy = board->takeCard("Militia");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Poacher")) {
					cToBuy = board->takeCard("Poacher");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Remodel")) {
					cToBuy = board->takeCard("Remodel");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Throne Room")) {
					cToBuy = board->takeCard("Throne Room");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("MoneyLender")) {
					cToBuy = board->takeCard("MoneyLender");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Gardens")) {
					cToBuy = board->takeCard("Gardens");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Smithy")) {
					cToBuy = board->takeCard("Smithy");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Bureaucrat")) {
					cToBuy = board->takeCard("Bureaucrat");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
		}

		else if (coins == 5) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				if (board->isCardAvaliable("Duchy")) {
					cToBuy = board->takeCard("Duchy");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
			else {
				if (board->isCardAvaliable("Festival")) {
					cToBuy = board->takeCard("Festival");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Market")) {
					cToBuy = board->takeCard("Market");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Sentry")) {
					cToBuy = board->takeCard("Sentry");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Witch")) {
					cToBuy = board->takeCard("Witch");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Laboratory")) {
					cToBuy = board->takeCard("Laboratory");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Mine")) {
					cToBuy = board->takeCard("Mine");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Library")) {
					cToBuy = board->takeCard("Library");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Bandit")) {
					cToBuy = board->takeCard("Bandit");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
				else if (board->isCardAvaliable("Council Room")) {
					cToBuy = board->takeCard("Council Room");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
		}

		else if (coins == 6) {
			randIndex = rand();

			if (randIndex % 2 == 0) {
				cToBuy = board->takeCard("Gold");

				discard->addCard(cToBuy);
				coins -= cToBuy.getCost();
			}
			else {
				if (board->isCardAvaliable("Artisan")) {
					cToBuy = board->takeCard("Artisan");

					discard->addCard(cToBuy);
					coins -= cToBuy.getCost();
				}
			}
		}

		else if (coins >= 8) {

			if (board->isCardAvaliable("Province")) {
				cToBuy = board->takeCard("Province");

				discard->addCard(cToBuy);
				coins -= cToBuy.getCost();
			}
		}

		cout << "Agent bought a " << cToBuy.getName() << endl << endl;
		buys--;
	}

}

void Turn::printBoardAndPlayerDecks(vector<Card>* hand, Deck* draw, Deck* discard) {
	cout << "Current Board/Player State:" << endl;

	//Printing out the board
	for (int i = 0; i < 7; i++) {
		cout << setw(10) << board->getBase(i).getSingleCard(0).getName() << " ";
	}
	cout << endl;

	for (int i = 0; i < 7; i++) {
		cout << setw(10) << board->getBase(i).totalCards() << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			cout << setw(10) << board->getKingdom((i * 5) + j).getSingleCard(0).getName() << " ";
		}
		cout << endl;

		for (int j = 0; j < 5; j++) {
			cout << setw(10) << board->getKingdom((i * 5) + j).totalCards() << " ";
		}
		cout << endl << endl << endl << endl;
	}


	//Printing out your hand/decks
	cout << setw(10) << "Draw" << " ";

	for (int i = 0; i < hand->size(); i++) {
		cout << setw(10) << hand->at(i).getName() << " ";
	}

	if (discard->totalCards() > 0) {
		cout << setw(10) << "Discard - " << discard->getSingleCard(0).getName() << endl;
	}
	else {
		cout << setw(10) << "Discard" << endl;
	}

	cout << setw(10) << draw->totalCards() << setw(60) << discard->totalCards() << endl << endl;


}