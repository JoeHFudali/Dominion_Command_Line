#pragma once

#include "Board.h"
#include "Turn.h"

using namespace std;

class Player {
public:

	Player();
	Player(string pName);
	void deletePlayer();
	
	void resetHand();
	void discardHand();
	void discardToDraw();
	
	void takeTurn(Board* b, vector<Player>& players);

	void ComputerTurn(Board* b, vector<Player>& oPlayers);

	string getName();

	Deck* getDraw();
	Deck* getDiscard();
	vector<Card>* getHand();

	int totalVP();


private:

	


	string name;

	Deck* drawPile;
	Deck* discardPile;

	vector<Card>* hand;

};