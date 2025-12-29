#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "Card.h"
#include "Deck.h"

using namespace std;

class Player;

class Turn
{
public:

	Turn();
	Turn(vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board* b);

private:

	void takeActions(vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard);
	void takeBuys(vector<Card>* hand, Deck* draw, Deck* discard);
	void cleanUp(vector<Card>* hand, Deck* draw, Deck* discard);

	int actions;
	int buys;
	int coins;

	int merchantBuff;

	vector<Card> inPlay;

	Board* board;


};

