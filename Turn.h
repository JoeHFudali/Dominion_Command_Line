#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"

using namespace std;

class Turn
{
public:

	Turn();
	Turn(vector<Card>* hand, Deck* draw, Deck* discard, Board* b);

private:

	void takeActions(vector<Card>* hand, Deck* draw, Deck* discard);
	void takeBuys(vector<Card>* hand, Deck* draw, Deck* discard);
	void cleanUp(vector<Card>* hand, Deck* draw, Deck* discard);

	int actions;
	int buys;
	int coins;

	vector<Card> inPlay;

	Board* board;


};

