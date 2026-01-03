#include "Player.h"


Player::Player() {
	//do nothing
}

Player::Player(string pName) {

	//coins = 0;

	Card copper;

	Card estate("Estate", 2, { "Victory" }, { "1 VP" });

	for (int i = 0; i < 7; i++) {
		drawPile->addCard(copper);
	}

	for (int i = 0; i < 3; i++) {
		drawPile->addCard(estate);
	}

	name = pName;

}

Player::~Player() {
	drawPile->deleteDeck();
	delete drawPile;
	drawPile = 0;

	discardPile->deleteDeck();
	delete discardPile;
	discardPile = 0;

	hand->clear();
	delete hand;
	hand = 0;
}

void Player::takeTurn(Board* b, vector<Player>& players) {
	Turn t(players, hand, drawPile, discardPile, b, false);
	//Turn class will reset the cards in play on it's own, this class will reset the hand and draw new cards (50/50 clean up between these two classes)
	
	resetHand();


}

void Player::ComputerTurn(Board* b, vector<Player>& oPlayers) {
	Turn t(oPlayers, hand, drawPile, discardPile, b, true);

	

	//Need to do some decision here, have the computer decide what cards to choose, whether that is randomly or through a heuristic, or through a NN.
	resetHand();
}



void Player::resetHand() {
	
	discardHand();

	for (int i = 0; i < 5; i++) {
		if (drawPile->totalCards() < 1) {
			discardToDraw();
		}
		Card tCard = drawPile->takeCard();
		hand->push_back(tCard);
		
	}
}

void Player::discardHand() {
	for (int i = 0; i < hand->size(); i++) {
		Card tCard = (*hand)[i];
		discardPile->addCard(tCard);
	}
	hand->clear();
}

void Player::discardToDraw() {
	discardPile->shuffleDeck();
	
	//drawPile->deleteDeck();
	*drawPile = *discardPile;

	discardPile->deleteDeck();

}


Deck* Player::getDraw() {
	return drawPile;
}

Deck* Player::getDiscard() {
	return discardPile;
}

vector<Card>* Player::getHand() {
	return hand;
}

string Player::getName() {
	return name;
}

int Player::totalVP() {
	int retVal = 0;
	retVal += drawPile->sumVP() + discardPile->sumVP();

	return retVal;
}