#pragma once

#include "Deck.h"
#include "Turn.h"
#include "Player.h"

using namespace std;

class Functionality {
public:

	Functionality();

	void PlayCard(Card c, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff);
	void AgentPlayCard(Card c, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff);

private:
	
	void addActions(int& actionCount, int amount);
	void addBuys(int& buyCount, int amount);
	void addCoins(int& coinCount, int amount);
	void addCards(vector<Card>* hand, Deck* draw, Deck* discard, int amount);

	bool hasMoat(vector<Card>* hand);

	void isDrawEmpty(Deck* draw, Deck* discard);

	void decideAction(string cardName, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff);
	void decideAIAction(string cardName, vector<Player>& players, vector<Card>* hand, Deck* draw, Deck* discard, Board& b, int& actionCount, int& buyCount, int& coinCount, int& mBuff);

};