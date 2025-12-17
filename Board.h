#pragma once
#include "Deck.h"

using namespace std;

class Board {
public:

	Board();
	Board(vector<Deck> baseCards, vector<Deck> kingdomCards, int players);

	Card findCardOnBoard(string name);

	Card takeCard(string name);

	bool checkForGameEnd();

	void printBaseInfo();
	void printKingdomInfo();
	void printTrashInfo();
	void printCardInfo(string name);


private:
	vector<Deck> baseDecks;
	vector<Deck> kingdomDecks;
	Deck trashDeck;

	int numPlayers;

};