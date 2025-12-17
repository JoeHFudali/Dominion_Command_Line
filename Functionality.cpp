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
			decideAction(c.getName());
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

void Functionality::decideAction(string cardName) {
	 
}