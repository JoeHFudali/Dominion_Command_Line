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

	int totalCards();
	int sumVP();

	void printDeck();


private:
	vector<Card> cards;

};