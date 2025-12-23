#pragma once

#include "Deck.h";
#include "Turn.h"
#include "Player.h"

using namespace std;

class Functionality {
public:

	Functionality();

	void PlayCard(Card c, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount);

private:
	
	void addActions(int& actionCount, int amount);
	void addBuys(int& buyCount, int amount);
	void addCoins(int& coinCount, int amount);
	void addCards(vector<Card>* hand, Deck* draw, int amount);

	//Add a function here later to check if player has a moat in their hand to block an attack card

	void decideAction(string cardName, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount);

};