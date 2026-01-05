#pragma once
#include "Deck.h"

using namespace std;

class Board {
public:

	Board();
	Board(vector<Deck> baseCards, vector<Deck> kingdomCards, int players);

	void addToTrash(Card c);

	Card findCardOnBoard(string name);
	bool isCardAvaliable(string name);

	Card takeCard(string name);

	bool checkForGameEnd();
	int numEmptyDecks();

	void printBaseInfo();
	void printKingdomInfo();
	void printTrashInfo();
	void printCardInfo(string name);

	Deck getBase(int index);
	Deck getKingdom(int index);


private:
	vector<Deck> baseDecks;
	vector<Deck> kingdomDecks;
	Deck trashDeck;

	int numPlayers;

};