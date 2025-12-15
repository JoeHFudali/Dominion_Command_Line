#pragma once

#include "Board.h"
#include "Turn.h"

using namespace std;

class Player {
public:

	Player();
	
	void resetHand();
	void discardToDraw();
	
	void takeTurn();

	Deck* getDraw();
	Deck* getDiscard();
	vector<Card>* getHand();


private:
	Deck* drawPile;
	Deck* discardPile;

	vector<Card>* hand;

};