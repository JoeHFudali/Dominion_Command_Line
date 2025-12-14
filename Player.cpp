#include "Player.h"

Player::Player() {

	coins = 0;

	Card copper;

	Card estate("Estate", 2, { "Victory" }, { "1 VP" });

	for (int i = 0; i < 7; i++) {
		drawPile.addCard(copper);
	}

	for (int i = 0; i < 3; i++) {
		drawPile.addCard(estate);
	}


}

void Player::resetHand() {
	for (int i = 0; i < hand.size(); i++) {
		Card tCard = hand[i];
		discardPile.addCard(tCard);
	}
	hand.clear();

	for (int i = 0; i < 5; i++) {
		if (drawPile.totalCards() < 1) {
			discardToDraw();
		}
		Card tCard = drawPile.takeCard();
		hand.push_back(tCard);
		
	}
}

void Player::discardToDraw() {
	discardPile.shuffleDeck();
	
	drawPile.deleteDeck();
	drawPile = discardPile;

	discardPile.deleteDeck();

}

