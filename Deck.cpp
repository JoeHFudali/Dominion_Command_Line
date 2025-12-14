#include "Deck.h"

using namespace std;

Deck::Deck() {
	//do nothing
}

Deck::Deck(vector<Card> cards) {
	this->cards = cards;
}

void Deck::shuffleDeck() {
	Card tempCard;

	for (int i = 0; i < cards.size(); i++) {
		int randIndex = rand() % cards.size();

		tempCard = cards[randIndex];
		cards[randIndex] = cards[i];
		cards[i] = tempCard;
	}


}

void Deck::addCard(Card c) {
	cards.push_back(c);
}

Card Deck::takeCard() {
	Card retCard = cards[cards.size() - 1];
	cards.pop_back();
	return retCard;
}

bool Deck::takeCard(string name, Card& retCard) {
	bool retVal = false;

	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].getName() == name) {
			retVal = true;
			retCard = cards[i];
			cards.erase(cards.begin() + i);
			break;
		}
	}

	return retVal;
}

void Deck::deleteDeck() {
	cards.clear();
}

int Deck::totalCards() {
	return cards.size();
}

bool Deck::isEmptyDeck() {
	bool retVal = cards.empty() ? true : false;
	return retVal;
}

int Deck::sumVP() {
	int sum = 0;

	for (int i = 0; i < cards.size(); i++) {
		for (int j = 0; j < cards[i].getTypes().size(); j++) {
			if (cards[i].getTypes()[j].find("Victory") != string::npos) {
				sum += cards[i].getDesc()[j][0] - '0';
				break;
			}
			else if (cards[i].getTypes()[j].find("Curse") != string::npos) {
				sum -= cards[i].getDesc()[j][1] - '0';
				break;
			}
		}
	}

	return sum;
}

void Deck::printDeck() {
	for (int i = 0; i < cards.size(); i++) {
		cards[i].printCardInfo();
		cout << "\n\n\n";
	}
}

Card Deck::getSingleCard(int index) {
	return cards[index];
}