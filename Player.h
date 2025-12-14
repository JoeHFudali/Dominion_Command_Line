#pragma once

#include "Board.h"

using namespace std;

class Player {
public:

	Player();
	
	void resetHand();
	void discardToDraw();
	
	void takeTurn();



private:
	Deck drawPile;
	Deck discardPile;

	vector<Card> hand;

	int coins;

};