#include "Player.h"

Player::Player() {

	//coins = 0;

	Card copper;

	Card estate("Estate", 2, { "Victory" }, { "1 VP" });

	for (int i = 0; i < 7; i++) {
		drawPile->addCard(copper);
	}

	for (int i = 0; i < 3; i++) {
		drawPile->addCard(estate);
	}


}

void Player::takeTurn(Board* b, vector<Player>& players) {
	Turn t(players, hand, drawPile, discardPile, b);
	//Turn class will reset the cards in play on it's own, this class will reset the hand and draw new cards (50/50 clean up between these two classes)
	resetHand();


}

void Player::resetHand() {
	for (int i = 0; i < hand->size(); i++) {
		Card tCard = (*hand)[i];
		discardPile->addCard(tCard);
	}
	hand->clear();

	for (int i = 0; i < 5; i++) {
		if (drawPile->totalCards() < 1) {
			discardToDraw();
		}
		Card tCard = drawPile->takeCard();
		hand->push_back(tCard);
		
	}
}

void Player::discardToDraw() {
	discardPile->shuffleDeck();
	
	drawPile->deleteDeck();
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