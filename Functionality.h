#pragma once

#include "Deck.h";
#include "Turn.h"
#include "Player.h"

using namespace std;

class Functionality {
public:

	Functionality();

	void PlayCard(Card c, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount);

private:
	
	void addActions(int& actionCount, int amount);
	void addBuys(int& buyCount, int amount);
	void addCoins(int& coinCount, int amount);
	void addCards(vector<Card>* hand, Deck* draw, int amount);

	void decideAction(string cardName);

};