#pragma once
#include "Card.h"
#include <vector>
#include <string>

using namespace std;

class Deck {
public:

	Deck();
	Deck(vector<Card> cards);

	void shuffleDeck();

	void addCard(Card c);
	Card takeCard();
	bool takeCard(string name, Card& retCard);
	void deleteDeck();

	int totalCards();
	bool isEmptyDeck();
	int sumVP();

	void printDeck();
	Card getSingleCard(int index);


private:
	vector<Card> cards;

};