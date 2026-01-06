#include "Functionality.h"

using namespace std;


Functionality::Functionality() {
	//Do nothing for now
}

void Functionality::PlayCard(Card c, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff) {
	for (int i = 0; i < c.getDesc().size(); i++) {

		if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Card") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addCards(hand, draw, discard, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Action") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addActions(actionCount, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Buy") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addBuys(buyCount, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" $") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addCoins(coinCount, amount);
		}

		else if (c.getDesc()[i].length() > 12) {
			//Do our specialty action here
			decideAction(c.getName(), players, hand, draw, discard, b, actionCount, buyCount, coinCount, mBuff);
		}
	}
}

void Functionality::addActions(int& actionCount, int amount) {
	actionCount += amount;
}

void Functionality::addBuys(int& buyCount, int amount) {
	buyCount += amount;
}

void Functionality::addCoins(int& coinCount, int amount) {
	coinCount += amount;
}

void Functionality::addCards(vector<Card>* hand, Deck* draw, Deck* discard, int amount) {
	for (int i = 0; i < amount; i++) {
		isDrawEmpty(draw, discard);
		Card c = draw->takeCard();
		hand->push_back(c);

		cout << "Pulled a " << c.getName() << " into hand" << endl;
	}

}

bool Functionality::hasMoat(vector<Card>* hand) {
	bool retVal = false;
	for (int i = 0; i < hand->size(); i++) {
		if (hand->at(i).getName() == "Moat") {
			retVal = !retVal;
			break;
		}
	}

	return retVal;
}

void Functionality::isDrawEmpty(Deck* draw, Deck* discard) {
	if (draw->totalCards() == 0) {
		discard->shuffleDeck();

		*draw = *discard;

		discard->deleteDeck();
	}
}

//Need to come back to this function later, many of the cases are inefficient, and can be reorganized more efficiently
void Functionality::decideAction(string cardName, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff) {
	 
	if (cardName == "Moneylender") {
		cout << "Trash a card? ('trash' to trash a copper for +3 $, and 'no' to not do so)" << endl;

		string choice;

		do {
			getline(cin, choice);

			if (choice.substr(0, 5) == "trash") {

				for (int i = 0; i < hand->size(); i++) {
					if (hand->at(i).getName() == "Copper") {
						Card c = hand->at(i);
						hand->erase(hand->begin() + i);
						b.addToTrash(c);
						coinCount += 3;
						break;
					}
				}

			}
			else if(choice != "no") {
				cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'trash' or 'no' " << endl << endl;
			}

		} while (choice != "no" || choice.substr(0, 5) != "trash");
	}

	else if (cardName == "Vassal") {
		bool actionOrNot = false;
		isDrawEmpty(draw, discard);
		Card c = draw->takeCard();
		for (int i = 0; i < c.getTypes().size(); i++) {
			if (c.getTypes()[i] == "Action") {
				actionOrNot = !actionOrNot;
				cout << "Action card! Play it? (yes or no)" << endl << endl;

				string yOrN = "";

				do {
					getline(cin, yOrN);

					if (yOrN == "yes") {
						PlayCard(c, players, hand, draw, discard, b, actionCount, buyCount, coinCount, mBuff);
						break;
					}
					else if (yOrN != "no") {
						cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'yes' or 'no' " << endl << endl;
					}
					

				} while (yOrN != "yes" || yOrN != "no");
				
				
			}
		}

		if (!actionOrNot) {
			cout << "Card was not an action card. discarding it" << endl << endl;
			discard->addCard(c);
		}
	}

	else if (cardName == "Remodel") {
		cout << "Trash a card? ('trash [card name]' to trash a card, and 'no' to not do so)" << endl;

		string choice;
		bool cardBought = false;

		do {
			getline(cin, choice);

			if (choice.substr(0, 5) == "trash") {
				string cardToTrash = choice.substr(6);

				for (int i = 0; i < hand->size(); i++) {
					if (!cardBought) {
						if (hand->at(i).getName() == cardToTrash) {
							int price = hand->at(i).getCost() + 2;
							b.addToTrash(hand->at(i));
							hand->erase(hand->begin() + i);

							cout << "Buy a card, up to 2 more $ than the trashed one" << endl << endl;

							string choice2;
							do {
								cout << "1. Look at specific card in deck - look [card name]" << endl;
								cout << "2. Buy a card - buy [card name]" << endl;

								getline(cin, choice2);

								if (choice2.find("look ") != string::npos) {
									string cName2 = choice2.substr(5);
									b.printCardInfo(cName2);

								}
								else if (choice2.find("buy ") != string::npos && b.isCardAvaliable(choice2.substr(4))) {
									string cName2 = choice2.substr(4);
									Card cToBuy = b.findCardOnBoard(cName2);
									if (price >= cToBuy.getCost()) {
										Card c = b.takeCard(cName2);
										discard->addCard(c);
										cardBought = !cardBought;
										break;
									}
									else {
										cout << "Oops, looks like you do not have enough money to buy this card" << endl << endl;
										choice2 = "";
									}
								}
								else {
									cout << "That is not a choice, or the card pile is empty! Either look at a card, buy a card (that is still in stock), or skip your buy" << endl << endl;
								}

							} while (choice2[0] != 'b');

						}
					}
				}

			}
			else if (choice != "no") {
				cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'trash [card name]' or 'no' " << endl << endl;
			}

		} while (choice != "no" && !cardBought);
		//May need to come back and edit this function, it's a bit much.

	}

	else if (cardName == "Cellar") {
		
		vector<Card> toDiscard;

		for (int i = 0; i < hand->size(); i++) {
			cout << "Discard this card?" << endl << endl;

			string choice = "";

			do {
				getline(cin, choice);

				if (choice == "yes") {
					toDiscard.push_back(hand->at(i));
					hand->erase(hand->begin() + i);
				}
				else if (choice != "no") {
					cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'yes' or 'no' " << endl << endl;
				}

			} while (choice != "yes" || choice != "no");


		}

		for (int i = 0; i < toDiscard.size(); i++) {
			//Check for draw being empty, will implement later
			discard->addCard(toDiscard[i]);
			isDrawEmpty(draw, discard);
			hand->push_back(draw->takeCard());
		}
		toDiscard.clear();


	}

	else if (cardName == "Chapel") {
		bool trashed = false;
		for (int i = 0; i < 4; i++) {
			
			do {
				cout << "Trash a card?" << endl << endl;

				cout << "1. Trash a card in your hand - trash [card name]" << endl;
				cout << "2. Don't trash - pass" << endl;

				string choice;

				getline(cin, choice);

				if (choice.substr(0, 5) == "trash") {
					for (int j = 0; j < hand->size(); j++) {
						if (hand->at(j).getName() == choice.substr(6)) {
							trashed = !trashed;
							Card c = hand->at(i);
							hand->erase(hand->begin() + j);
							b.addToTrash(c);
							break;
						}
					}
					if (!trashed) {
						cout << "The card you want to trash is not in your hand. Trash a card that is in your hand please!" << endl << endl;
					}
					
				}
				else if (choice != "pass") {
					cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'trash [card name]' or 'pass' " << endl << endl;
				}

			} while (!trashed);
			trashed = !trashed;
		}
	}

	else if (cardName == "Harbinger") {

		for (int i = 0; i < discard->totalCards(); i++) {
			cout << i + 1 << ". " << discard->getSingleCard(i).getName() << endl;
		}

		if (discard->totalCards() > 0) {
			cout << "Which card would you like to put onto the top of your deck? (Enter in the specific card name)" << endl << endl;
		}

		string choice = "";

		Card c;

		do {
			getline(cin, choice);

			if (discard->takeCard(choice, c)) {
				draw->addCard(c);
				break;
			}

			else {
				cout << "Looks like you entered in a card name that is not in your discard. Please enter a card name that is actually in your discard deck" << endl << endl;
			}

		} while (true && discard->totalCards() > 0);

		
	}

	else if(cardName == "Workshop") {
		cout << "Which card would you like to get? (costing a max of 4$)" << endl << endl;

		string choice;
		do {
			cout << "1. Look at specific card in deck - look [card name]" << endl;
			cout << "2. Buy a card - buy [card name]" << endl;

			getline(cin, choice);

			if (choice.find("look ") != string::npos) {
				string cName2 = choice.substr(5);
				b.printCardInfo(cName2);

			}
			else if (choice.find("buy ") != string::npos && b.isCardAvaliable(choice.substr(4))) {
				string cName2 = choice.substr(4);
				Card cToBuy = b.findCardOnBoard(cName2);
				
				if (cToBuy.getCost() <= 4) {
					Card c = b.takeCard(cName2);
					
					discard->addCard(c);
					
					break;
				}
				else {
					cout << "Oops, looks like this card costs more than 4$." << endl << endl;
					choice = "";
				}
				
			}
			else {
				cout << "That is not a choice, or the card pile is emptied! Either look at a card, or gain a card (that is still in stock) that costs up to 4$" << endl << endl;
			}

		} while (choice[0] != 'b');
	}

	else if (cardName == "Mine") {
		cout << "Trash a treasure to gain a new treasure - type 'trash [treasure card name]' to trash it or 'no' to skip this card" << endl << endl;

		string choice;

		do {
			getline(cin, choice);

			if (choice.find("trash") != string::npos) {

				for (int i = 0; i < hand->size(); i++) {
					if (hand->at(i).getName() == choice.substr(6)) {
						Card c = hand->at(i);
						hand->erase(hand->begin() + i);
						b.addToTrash(c);
						//We now get a new treasure

						string choice2;
						do {
							cout << "1. Look at specific card in deck - look [card name]" << endl;
							cout << "2. Buy a card - buy [card name]" << endl;

							getline(cin, choice2);

							if (choice2.find("look ") != string::npos) {
								string cName2 = choice2.substr(5);
								b.printCardInfo(cName2);

							}
							else if (choice2.find("buy ") != string::npos && b.isCardAvaliable(choice2.substr(4))) {
								string cName2 = choice2.substr(4);
								Card cToBuy = b.findCardOnBoard(cName2);
								if (cToBuy.getCost() <= cToBuy.getCost() + 3 && cToBuy.isOfType("Treasure")) {
									Card c = b.takeCard(cName2);
									hand->push_back(c);
									break;
								}
								else {
									cout << "Oops, looks like this card is either not a treasure, not on the board, has been emptied, or is too expensive" << endl << endl;
									choice2 = "";
								}
							}
							else {
								cout << "That is not a choice, or the card pile is empty! Either look at a card, or gain a treasure up to 3$ more than the trashed treasure (that is still in stock)" << endl << endl;
							}

						} while (choice2[0] != 'b');
						break;
					}
				}

			}
			else if (choice != "no") {
				cout << "Oops, looks like you enetered something that wasn't one of the two options. Enter either 'trash' or 'no' " << endl << endl;
			}

		} while (choice != "no" || choice.substr(0, 5) != "trash");


	}

	else if (cardName == "Artisan") {
		bool cardBought = false;
		cout << "First, gain a card to your hand that costs up to 5$, then put a card from your hand onto your draw pile" << endl << endl;

		string choice;
		do {
			cout << "1. Look at specific card in deck - look [card name]" << endl;
			cout << "2. Buy a card - buy [card name]" << endl;

			getline(cin, choice);

			if (choice.find("look ") != string::npos) {
				string cName2 = choice.substr(5);
				b.printCardInfo(cName2);

			}
			else if (choice.find("buy ") != string::npos && b.isCardAvaliable(choice.substr(4))) {
				string cName2 = choice.substr(4);
				Card cToBuy = b.findCardOnBoard(cName2);
				if (cToBuy.getCost() <= 5) {
					Card c = b.takeCard(cName2);
					hand->push_back(c);
					break;
				}
				else {
					cout << "Oops, looks like this card is either too expensive or not in the game" << endl << endl;
					choice = "";
				}
			}
			else {
				cout << "That is not a choice, or the card pile is empty! Either look at a card, or gain a card that costs up to 5$ (that is still in stock) " << endl << endl;
			}

		} while (choice[0] != 'b');

		for (int i = 0; i < hand->size(); i++) {
			cout << i + 1 << ". " << hand->at(i).getName() << endl;
		}
		cout << endl;

		string choice2;
		Card c;

		do {
			getline(cin, choice2);

			for (int i = 0; i < hand->size(); i++) {
				if (hand->at(i).getName() == choice2) {
					c = hand->at(i);
					hand->erase(hand->begin() + i);
					draw->addCard(c);
					cardBought = !cardBought;
					break;
				}
			}
			
			if (!cardBought) {
				cout << "Looks like you entered in a card name that is not in your hand. Please enter a card name that is actually in your hand" << endl << endl;
			}

		} while (!cardBought);
	}

	else if (cardName == "Poacher") {

		int numToDiscard = b.numEmptyDecks();
		bool trashed = false;

		for (int i = 0; i < numToDiscard; i++) {
			if (hand->empty()) {
				break;
			}

			do {
				cout << "1. Discard a card in your hand - discard [card name]" << endl;

				string choice;

				getline(cin, choice);

				if (choice.substr(0, 7) == "discard") {
					for (int j = 0; j < hand->size(); j++) {
						if (hand->at(j).getName() == choice.substr(6)) {
							Card c = hand->at(i);
							hand->erase(hand->begin() + j);
							discard->addCard(c);
							trashed = !trashed;
							break;
						}
					}
					if (!trashed) {
						cout << "The card you want to discard is not in your hand. Discard a card that is in your hand please!" << endl << endl;
					}

				}
				else {
					cout << "Oops, looks like you enetered something that wasn't discard. Enter 'discard [card name]' " << endl << endl;
				}

			} while (!trashed);
			trashed = !trashed;

		}
	}

	else if (cardName == "Sentry") {

		vector<Card> topTwoCards;

		isDrawEmpty(draw, discard);
		topTwoCards.push_back(draw->takeCard());

		isDrawEmpty(draw, discard);
		topTwoCards.push_back(draw->takeCard());

		cout << "Looks at the top two cards of your deck, and either trash, discard, or put them back on top. You can do this to one or both of the cards, and you don't have to do the same action for both" << endl << endl;

		topTwoCards[0].printCardInfo();
		topTwoCards[1].printCardInfo();

		string choice;

		cout << "NOTE: current is the first care taken" << endl << endl;

		do {
			cout << "1. Look at the current card - look" << endl;
			cout << "2. Discard the current card - discard" << endl;
			cout << "3. Trash the current card - trash" << endl;
			cout << "4. Rearrange card order/switch to other card - switch" << endl;
			cout << "5. Put card back on deck - deck" << endl;

			getline(cin, choice);

			if (choice == "look") {
				topTwoCards[0].printCardInfo();
			}
			else if (choice == "discard") {
				discard->addCard(topTwoCards[0]);
				topTwoCards.erase(topTwoCards.begin());
			}
			else if (choice == "trash") {
				b.addToTrash(topTwoCards[0]);
				topTwoCards.erase(topTwoCards.begin());
			}
			else if (choice == "switch") {
				Card tempC = topTwoCards[0];
				topTwoCards[0] = topTwoCards[1];
				topTwoCards[1] = tempC;
			}
			else if (choice == "deck") {
				draw->addCard(topTwoCards[0]);
				topTwoCards.erase(topTwoCards.begin());
			}

		} while (!topTwoCards.empty());
	}

	else if (cardName == "Library") {
		cout << "Drawing until you have 7 cards..." << endl << endl;

		vector<Card> setAsideActions;

		while (hand->size() < 7) {
			//Check to see if draw is empty, and then replace it. will do later
			isDrawEmpty(draw, discard);
			Card c = draw->takeCard();
			if (!c.isOfType("Action")) {
				hand->push_back(c);
			}
			else {

				cout << "Keep this action card in your hand? - type 'yes' or 'no' " << endl << endl;
				
				string choice;
				do {
					getline(cin, choice);

					if (choice == "yes") {
						hand->push_back(c);
					}

					else if (choice == "no") {
						setAsideActions.push_back(c);
					}

					else {
						cout << "Oops, looks like you did not enter either 'yes' or 'no'. Please try again" << endl << endl;
					}


				} while (choice != "no" || choice != "yes");


			}

		}

		for (int i = 0; i < setAsideActions.size(); i++) {
			discard->addCard(setAsideActions[i]);
		}
		setAsideActions.clear();


	}

	else if (cardName == "Witch") {

		if (b.getBase(6).totalCards() > 0) {
			for (int i = 0; i < players.size(); i++) {
				if (!hasMoat(players[i].getHand()) || b.isCardAvaliable("Witch")) {
					Card witch = b.takeCard("Witch");

					players[i].getDiscard()->addCard(witch);

					if (b.getBase(6).totalCards() == 0) {
						break;
					}
				}
				else if(hasMoat(players[i].getHand())){
					cout << "Player" << i + 1 << " has a moat. Attack blocked." << endl << endl;
				}
				else {
					cout << "No more witches left on the board. Attack failed." << endl << endl;
				}
			}
		}


		
	}

	else if (cardName == "Council Room") {
		for (int i = 0; i < players.size(); i++) {
			isDrawEmpty(players[i].getDraw(), players[i].getDiscard());
			Card c = players[i].getDraw()->takeCard();

			players[i].getHand()->push_back(c);

		}
	}

	else if (cardName == "Militia") {

		for (int i = 0; i < players.size(); i++) {

			if (!hasMoat(players[i].getHand())) {
				while (players[i].getHand()->size() > 3) {
					int randIndex = rand() % players[i].getHand()->size();

					Card c = players[i].getHand()->at(randIndex);
					players[i].getDiscard()->addCard(c);
					players[i].getHand()->erase(players[i].getHand()->begin() + randIndex);

				}
			}
			else {
				cout << "Player" << i + 1 << " has a moat. Attack blocked." << endl << endl;
			}
			
		}
	}

	else if (cardName == "Bandit") {

		for (int i = 0; i < players.size(); i++) {

			if (!hasMoat(players[i].getHand())) {
				vector<Card> topTwoCards;

				isDrawEmpty(players[i].getDraw(), players[i].getDiscard());
				topTwoCards.push_back(players[i].getDraw()->takeCard());

				isDrawEmpty(players[i].getDraw(), players[i].getDiscard());
				topTwoCards.push_back(players[i].getDraw()->takeCard());

				if (topTwoCards[0].getName() == "Gold" || topTwoCards[0].getName() == "Silver") {
					b.addToTrash(topTwoCards[0]);
					topTwoCards.erase(topTwoCards.begin());
				}

				else if (topTwoCards[1].getName() == "Gold" || topTwoCards[1].getName() == "Silver") {
					b.addToTrash(topTwoCards[1]);
					topTwoCards.erase(topTwoCards.begin() + 1);
				}

				for (int j = 0; j < topTwoCards.size(); j++) {
					players[i].getDiscard()->addCard(topTwoCards[j]);
				}

			}
			else {
				cout << "Player" << i + 1 << " has a moat. Attack blocked." << endl << endl;
			}
			

		}
	}

	else if (cardName == "Bureaucrat") {
		//This function acts a bit differently than normal game. This goes through the other players hand and will reveal the first victory card, not one of their choosing. 
		//Have to also edit this function in board to check for empty decks and return nothing
		Card c;
		if (b.isCardAvaliable("Silver")) {
			c = b.takeCard("Silver");

			draw->addCard(c);
		}
		

		for (int i = 0; i < players.size(); i++) {

			if (!hasMoat(players[i].getHand())) {
				bool containsVictory = false;

				for (int j = 0; j < players[i].getHand()->size(); j++) {

					if (players[i].getHand()->at(j).isOfType("Victory")) {
						cout << "Player " << i + 1 << " revealed a " << players[i].getHand()->at(j).getName() << "!" << endl;
						players[i].getHand()->at(j).printCardInfo();

						c = players[i].getHand()->at(j);
						players[i].getHand()->erase(players[i].getHand()->begin() + j);

						players[i].getDraw()->addCard(c);
						containsVictory = !containsVictory;
						break;
					}

				}
				if (!containsVictory) {
					cout << "Player " << i + 1 << " did not have a victory card. This is their hand: " << endl;
					for (int j = 0; j < players[i].getHand()->size(); j++) {
						players[i].getHand()->at(j).printCardInfo();
					}
				}
			}
			else {
				cout << "Player" << i + 1 << " has a moat. Attack blocked." << endl << endl;
			}
			
		}
	}

	else if (cardName == "Merchant") {
		mBuff += 1;
	}

	else if (cardName == "Throne Room") {
		int numOtherActions = 0;
		bool cardPlayed = false;

		for (int i = 0; i < hand->size(); i++) {
			if (hand->at(i).isOfType("Action")) {
				numOtherActions++;
			}
		}

		if (numOtherActions > 0) {
			
			string choice;
			do {

				cout << "Play an action card in your hand, it will be played twice - play [card name]" << endl << endl;

				getline(cin, choice);

				for (int i = 0; i < hand->size(); i++) {
					if (hand->at(i).getName() == choice.substr(5)) {
						cardPlayed = !cardPlayed;
						Card c = hand->at(i);

						//Card will be imedietly be put into discard, but really should be put onto the in-Play area, will fix this someday.
						hand->erase(hand->begin() + i);
						PlayCard(c, players, hand, draw, discard, b, actionCount, buyCount, coinCount, mBuff);
						PlayCard(c, players, hand, draw, discard, b, actionCount, buyCount, coinCount, mBuff);

						discard->addCard(c);
						break;

					}
				}
				if (!cardPlayed) {
					cout << "Oops, looks like you either entered a card name incorrectly, the card is not in this game, or entered something else other than 'play [card name]'." << endl << endl;
				}


			} while (!cardPlayed);
		}
		else {
			//This isn't really neccisary, will delete later
			cout << "No other action cards in your hand" << endl << endl;
		}

	}

	//If not any of these, this is either a custom card, a dlc card (will be implemented at a later date), or is moat, which is implemented in a different way.
}