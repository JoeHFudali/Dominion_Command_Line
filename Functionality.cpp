#include "Functionality.h"

using namespace std;


Functionality::Functionality() {
	//Do nothing for now
}

void Functionality::PlayCard(Card c, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount) {
	for (int i = 0; i < c.getDesc().size(); i++) {

		if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Card") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addCards(hand, draw, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Action") != string::npos) {
			int amount = c.getDesc()[i][1] - '0';
			addActions(actionCount, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" Buy") != string::npos) {
			int amount = c.getDesc()[i][1];
			addBuys(buyCount, amount);
		}

		else if (c.getDesc()[i].find("+") != string::npos && c.getDesc()[i].find(" $") != string::npos) {
			int amount = c.getDesc()[i][1];
			addCoins(coinCount, amount);
		}

		else if (c.getDesc()[i].length() > 12) {
			//Do our specialty action here
			decideAction(c.getName(), hand, draw, discard, b, actionCount, buyCount, coinCount);
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

void Functionality::addCards(vector<Card>* hand, Deck* draw, int amount) {
	for (int i = 0; i < amount; i++) {
		Card c = draw->takeCard();
		hand->push_back(c);
	}

}

//Need to come back to this function later, many of the cases are inefficient, and can be reorganized more efficiently
void Functionality::decideAction(string cardName, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount) {
	 
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
		Card c = draw->takeCard();
		for (int i = 0; i < c.getTypes().size(); i++) {
			if (c.getTypes()[i] == "Action") {
				actionOrNot = !actionOrNot;
				cout << "Action card! Play it? (yes or no)" << endl << endl;

				string yOrN = "";

				do {
					getline(cin, yOrN);

					if (yOrN == "yes") {
						PlayCard(c, hand, draw, discard, b, actionCount, buyCount, coinCount);
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
								else if (choice2.find("buy ") != string::npos) {
									string cName2 = choice2.substr(4);
									Card cToBuy = b.findCardOnBoard(cName2);
									if (price >= cToBuy.getCost()) {
										Card c = b.takeCard(cName2);
										discard->addCard(c);
										cardBought = !cardBought;
										break;
									}
									else {
										cout << "Oops, looks like you do not have enough money to buy this card." << endl << endl;
										choice2 = "";
									}
								}
								else {
									cout << "That is not a choice! Either look at a card, buy a card, or skip you buy" << endl << endl;
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

		cout << "Which card would you like to put onto the top of your deck? (Enter in the specific card name)" << endl << endl;

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

		} while (true);

		
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
			else if (choice.find("buy ") != string::npos) {
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
				cout << "That is not a choice! Either look at a card, or gain a card that costs up to 4$" << endl << endl;
			}

		} while (choice[0] != 'b');
	}

	else if (cardName == "Mine") {
		cout << "Trash a treasure to gain a new treasure - type 'trash [treasure card name]' to trash it or 'no' to skip this card" << endl << endl;

		string choice;

		do {
			getline(cin, choice);

			if (choice.substr(0, 5) == "trash") {

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
							else if (choice2.find("buy ") != string::npos) {
								string cName2 = choice2.substr(4);
								Card cToBuy = b.findCardOnBoard(cName2);
								if (cToBuy.getCost() <= cToBuy.getCost() + 3 && cToBuy.isOfType("Treasure")) {
									Card c = b.takeCard(cName2);
									hand->push_back(c);
									break;
								}
								else {
									cout << "Oops, looks like this card is either not a treasure, not on the board, or is too expensive" << endl << endl;
									choice2 = "";
								}
							}
							else {
								cout << "That is not a choice! Either look at a card, or gain a card that costs up to 4$" << endl << endl;
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
			else if (choice.find("buy ") != string::npos) {
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
				cout << "That is not a choice! Either look at a card, or gain a card that costs up to 4$" << endl << endl;
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
}