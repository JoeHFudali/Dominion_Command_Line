#include "Board.h"

using namespace std;

Board::Board() {


	numPlayers = 2;

	Card copper;
	Card silver("Silver", 3, { "Treasure" }, { "2 $" });
	Card gold("Gold", 6, { "Treasure" }, { "3 $" });
	Card estate("Estate", 2, { "Victory" }, { "1 VP" });
	Card duchy("Duchy", 5, { "Victory" }, { "3 VP" });
	Card province("Province", 8, { "Victory" }, { "6 VP" });
	Card curse("Curse", 0, { "Curse" }, { "-1 VP" });

	vector<Card> base = { copper, silver, gold, estate, duchy, province, curse };
	vector<int> deckSizes = { 46, 40, 30, 8, 8, 8, 10 };

	for (int i = 0; i < base.size(); i++) {
		Deck tDeck;

		for (int j = 0; j < deckSizes[i]; j++) {
			tDeck.addCard(base[i]);
		}

		baseDecks.push_back(tDeck);
	}

	Card cellar("Cellar", 2, { "Action" }, { "+1 Action", "Discard any number of cards, then draw that many." });
	Card moat("Moat", 2, { "Action", "Reaction" }, { "+2 Cards", "When another player plays an Attack card, you may first reveal this from your hand, to be unnaffected by it." });
	Card village("Village", 3, { "Action" }, { "+1 Card", "+2 Actions" });
	Card merchant("Merchant", 3, { "Action" }, { "+1 Card", "+1 Action", "The first time you play a Silver this turn, +1 $." });
	Card workshop("Workshop", 4, { "Action" }, { "Gain a card costing up to 4 $." });
	Card smithy("Smithy", 4, { "Action" }, { "+3 Cards" });
	Card remodel("Remodel", 4, { "Action" }, { "Trash a card from your hand. Gain a card costing up to 2 $ more than it." });
	Card militia("Militia", 4, { "Action", "Attack" }, { "+2 $", "Each other player discards down to 3 cards in hand." });
	Card market("Market", 5, { "Action" }, { "+1 Card", "+1 Action", "+1 Buy", "+1 $" });
	Card mine("Mine", 5, { "Action" }, { "You may trash a Treasure from your hand. Gain a Treasure to your hand costing up to 3 o more than it." });

	vector<Card> kingdom = { cellar, moat, village, merchant, workshop, smithy, remodel, militia, market, mine };

	for (int i = 0; i < kingdom.size(); i++) {
		Deck tDeck;

		for (int j = 0; j < 10; j++) {
			tDeck.addCard(kingdom[i]);
		}

		kingdomDecks.push_back(tDeck);
	}

	//Trash pile remains unaffected
}

Board::Board(vector<Deck> baseCards, vector<Deck> kingdomCards, int players) {
	baseDecks = baseCards;
	kingdomDecks = kingdomCards;

	numPlayers = players;

	//Trash pile also remains unaffected here
}

Card Board::findCardOnBoard(string name) {
	Card retVal;
	bool found = false;
	for (int i = 0; i < baseDecks.size(); i++) {
		if (!baseDecks[i].isEmptyDeck() && baseDecks[i].getSingleCard(0).getName() == name) {
			retVal = baseDecks[i].getSingleCard(0);
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < kingdomDecks.size(); i++) {
			if (!kingdomDecks[i].isEmptyDeck() && kingdomDecks[i].getSingleCard(0).getName() == name) {
				retVal = kingdomDecks[i].getSingleCard(0);
				found = true;
				break;
			}
		}
	}

	return retVal;
}

Card Board::takeCard(string name) {
	Card retVal;
	bool found = false;
	for (int i = 0; i < baseDecks.size(); i++) {
		if (!baseDecks[i].isEmptyDeck() && baseDecks[i].getSingleCard(0).getName() == name) {
			retVal = baseDecks[i].takeCard();
			found = !found;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < kingdomDecks.size(); i++) {
			if (!kingdomDecks[i].isEmptyDeck() && kingdomDecks[i].getSingleCard(0).getName() == name) {
				retVal = kingdomDecks[i].takeCard();
				found = !found;
				break;
			}
		}
	}

	return retVal;
}

bool Board::checkForGameEnd() {
	if (baseDecks[baseDecks.size() - 2].isEmptyDeck()) {
		return true;
	}

	int numEmptyDecks = 0;

	for (int i = 0; i < baseDecks.size(); i++) {
		if (baseDecks[i].isEmptyDeck()) {
			numEmptyDecks++;
		}
	}

	for (int i = 0; i < kingdomDecks.size(); i++) {
		if (kingdomDecks[i].isEmptyDeck()) {
			numEmptyDecks++;
		}
	}

	if (numEmptyDecks >= 3) {
		return true;
	}


	return false;
}

void Board::printBaseInfo() {
	cout << "Cards in the Base decks and their remaining amounts..." << endl;

	for (int i = 0; i < baseDecks.size(); i++) {
		cout << i + 1 << ". " << endl;
		baseDecks[i].getSingleCard(0).printCardInfo();
		cout << '\n' << "Total number of cards remaining in this deck: " << baseDecks[i].totalCards() << endl << endl;
	}

}

void Board::printKingdomInfo() {
	cout << "Cards in the Kingdom decks and their remaining amounts..." << endl;

	for (int i = 0; i < kingdomDecks.size(); i++) {
		cout << i + 1 << ". " << endl;
		kingdomDecks[i].getSingleCard(0).printCardInfo();
		cout << '\n' << "Total number of cards remaining in this deck: " << kingdomDecks[i].totalCards() << endl << endl;
	}

}

void Board::printTrashInfo() {
	cout << "Cards in the the Trash deck..." << endl;

	for (int i = 0; i < trashDeck.totalCards(); i++) {
		cout << i + 1 << ". " << endl;
		trashDeck.getSingleCard(i).printCardInfo();
	}
}

void Board::printCardInfo(string name) {
	bool found = false;
	for (int i = 0; i < baseDecks.size(); i++) {
		if (!baseDecks[i].isEmptyDeck() && baseDecks[i].getSingleCard(0).getName() == name) {
			baseDecks[i].getSingleCard(0).printCardInfo();
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < kingdomDecks.size(); i++) {
			if (!kingdomDecks[i].isEmptyDeck() && kingdomDecks[i].getSingleCard(0).getName() == name) {
				kingdomDecks[i].getSingleCard(0).printCardInfo();
				found = true;
				break;
			}
		}
	}

	if (!found) {
		cout << "Card is either not in this kingdom/base set, or it's supply is fully depleted." << endl;
	}


}