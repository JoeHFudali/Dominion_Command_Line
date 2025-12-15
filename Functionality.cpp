#include "Functionality.h"

using namespace std;


Functionality::Functionality() {
	//Do nothing for now
}


void Functionality::addActions(int& actionCount, int amount) {
	actionCount += amount;
}

void Functionality::addBuys(int& buyCount, int amount) {
	buyCount += amount;
}

void Functionality::addCards(Player& player, int amount) {
	for (int i = 0; i < amount; i++) {
		Card c = player.getDraw()->takeCard();
		player.getHand()->push_back(c);
	}

}