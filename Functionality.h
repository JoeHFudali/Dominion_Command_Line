#pragma once

#include "Deck.h";
#include "Turn.h"
#include "Player.h"

using namespace std;

class Functionality {
public:

	Functionality();

	void PlayCard(Card c, Player& player, Board& board);

private:
	
	void addActions(int& actionCount, int amount);
	void addBuys(int& buyCount, int amount);
	void addCards(Player& player, int amount);

};