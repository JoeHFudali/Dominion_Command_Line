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

	//All Other cards in the base game

	Card artisan("Artisan", 6, { "Action" }, { "Gain a card to your hand costing up to 5$. Put a card from your hand onto your deck." });
	Card bandit("Bandit", 5, { "Action", "Attack" }, { "Gain a Gold. Each other player reveals the top 2 cards of their deck, trashes a revealed Treasure other than Copper, and discards the rest." });
	Card bureaucrat("Bureaucrat", 4, { "Action", "Attack" }, { "Gain a Silver onto your deck. Each other player reveals a Victory card from their hand and puts it onto their deck (or reveals a hand with no Victory cards)." });
	Card chapel("Chapel", 2, { "Action" }, { "Trash up to 4 cards from your hand." });
	Card councilRoom("Council Room", 5, { "Action" }, { "+4 Cards", "+1 Buy", "Each other player draws a card." });
	Card festival("Festival", 5, { "Action" }, { "+2 Actions", "+1 Buy", "+2 $" });
	Card harbinger("Harbinger", 3, { "Action" }, { "+1 Card", "+1 Action", "Look through your discard pile. You may put a card from it onto your deck." });
	Card laboratory("Laboratory", 5, { "Action" }, { "+2 Cards", "+1 Action" });
	Card library("Library", 5, { "Action" }, { "Draw until you have 7 cards in hand, skipping any Action cards you choose to; set those aside, discarding them afterwards."});
	Card moneylender("Moneylender", 4, { "Action" }, { "You may trash a Copper from your hand for +3 $." });
	Card poacher("Poacher", 4, { "Action" }, {"+1 Card", "+1 Action", "+1 $", "Discard a card per empty Supply pile."});
	Card sentry("Sentry", 5, { "Action" }, { "+1 Card", "+1 Action", "Look at the top 2 cards of your deck. Trash and/or discard any number of them. Put the rest back on top in any order." });
	Card throneRoom("Throne Room", 4, { "Action" }, { "You may play an Action card from your hand twice." });
	Card vassal("Vassal", 3, { "Action" }, { "+2 $", "Discard the top card of your deck. if it's an Action card, you ay play it." });
	Card witch("Witch", 5, { "Action", "Attack" }, { "+2 Cards", "Each other player gains a Curse. " });
	Card gardens("Gardens", 4, { "Victory" }, { "Worth 1 VP per 10 cards you have (round down)." });

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

void Board::addToTrash(Card c) {
	trashDeck.addCard(c);
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

bool Board::isCardAvaliable(string name) {
	bool retVal = false;
	for (int i = 0; i < baseDecks.size(); i++) {
		if (baseDecks[i].getSingleCard(0).getName() == name && !baseDecks[i].isEmptyDeck()) {
			retVal = !retVal;
			break;
		}
	}

	if (!retVal) {
		for (int i = 0; i < kingdomDecks.size(); i++) {
			if (kingdomDecks[i].getSingleCard(0).getName() == name && !kingdomDecks[i].isEmptyDeck()) {
				retVal = !retVal;
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

int Board::numEmptyDecks() {
	int retVal = 0;
	for (int i = 0; i < baseDecks.size(); i++) {
		if (baseDecks[i].totalCards() == 0) {
			retVal++;
		}
	}

	for (int i = 0; i < kingdomDecks.size(); i++) {
		if (kingdomDecks[i].totalCards() == 0) {
			retVal++;
		}
	}

	return retVal;
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
			cout << "Num of cards in deck: " << baseDecks[i].totalCards() << endl << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < kingdomDecks.size(); i++) {
			if (!kingdomDecks[i].isEmptyDeck() && kingdomDecks[i].getSingleCard(0).getName() == name) {
				kingdomDecks[i].getSingleCard(0).printCardInfo();
				cout << "Num of cards in deck: " << kingdomDecks[i].totalCards() << endl << endl;
				found = true;
				break;
			}
		}
	}

	if (!found) {
		cout << "Card is either not in this kingdom/base set, or it's supply is fully depleted." << endl;
	}


}

Deck Board::getBase(int index) {
	return baseDecks[index];
}

Deck Board::getKingdom(int index) {
	return kingdomDecks[index];
}