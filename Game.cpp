#include "Game.h"

Game::Game() {



	b = new Board();

	Player p1("Joe");

	Player p2("Bot 1");

	personPlayer = p1;
	otherPlayers.push_back(p2);

	currentTurnCount = 0;
	isGameSet = true;
}

Game::Game(Player you, vector<Player> players) {

	personPlayer = you;
	otherPlayers = players;

	currentTurnCount = 0;
	isGameSet = false;
}

Game::~Game() {
	delete b;
	b = 0;

	personPlayer.deletePlayer();

	for (int i = 0; i < otherPlayers.size(); i++) {
		otherPlayers[i].deletePlayer();
	}
	
}

void Game::Play() {
	//We will make a simple 2 player game, will try to include more bots laters, this is just the simplest thing to do right now



	vector<Player> personContainer = { personPlayer };
	char yOrN = 'y';

	do {
		while (!b->checkForGameEnd()) {
			currentTurnCount++;



			personPlayer.takeTurn(b, otherPlayers);

			if (b->checkForGameEnd()) {
				break;
			}

			otherPlayers[0].ComputerTurn(b, personContainer);


			personPlayer = personContainer[0];
		}

		personPlayer.discardHand();
		otherPlayers[0].discardHand();

		gameEnd();

		cout << "Would you like to play again? - type 'n' for no, and anything else for yes" << endl << endl;
		cin >> yOrN;

		//Need to reset board and players here, will do that later
		currentTurnCount = 0;

	} while (yOrN != 'n');

}

void Game::setUpBoard(int numPlayers) {

	

	vector<Card> kingdomCards;


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
	Card artisan("Artisan", 6, { "Action" }, { "Gain a card to your hand costing up to 5$. Put a card from your hand onto your deck." });
	Card bandit("Bandit", 5, { "Action", "Attack" }, { "Gain a Gold. Each other player reveals the top 2 cards of their deck, trashes a revealed Treasure other than Copper, and discards the rest." });
	Card bureaucrat("Bureaucrat", 4, { "Action", "Attack" }, { "Gain a Silver onto your deck. Each other player reveals a Victory card from their hand and puts it onto their deck (or reveals a hand with no Victory cards)." });
	Card chapel("Chapel", 2, { "Action" }, { "Trash up to 4 cards from your hand." });
	Card councilRoom("Council Room", 5, { "Action" }, { "+4 Cards", "+1 Buy", "Each other player draws a card." });
	Card festival("Festival", 5, { "Action" }, { "+2 Actions", "+1 Buy", "+2 $" });
	Card harbinger("Harbinger", 3, { "Action" }, { "+1 Card", "+1 Action", "Look through your discard pile. You may put a card from it onto your deck." });
	Card laboratory("Laboratory", 5, { "Action" }, { "+2 Cards", "+1 Action" });
	Card library("Library", 5, { "Action" }, { "Draw until you have 7 cards in hand, skipping any Action cards you choose to; set those aside, discarding them afterwards." });
	Card moneylender("Moneylender", 4, { "Action" }, { "You may trash a Copper from your hand for +3 $." });
	Card poacher("Poacher", 4, { "Action" }, { "+1 Card", "+1 Action", "+1 $", "Discard a card per empty Supply pile." });
	Card sentry("Sentry", 5, { "Action" }, { "+1 Card", "+1 Action", "Look at the top 2 cards of your deck. Trash and/or discard any number of them. Put the rest back on top in any order." });
	Card throneRoom("Throne Room", 4, { "Action" }, { "You may play an Action card from your hand twice." });
	Card vassal("Vassal", 3, { "Action" }, { "+2 $", "Discard the top card of your deck. if it's an Action card, you ay play it." });
	Card witch("Witch", 5, { "Action", "Attack" }, { "+2 Cards", "Each other player gains a Curse. " });
	Card gardens("Gardens", 4, { "Victory" }, { "Worth 1 VP per 10 cards you have (round down)." });

	vector<Card> avaliableKingdomCards = { artisan, bandit, bureaucrat, cellar, chapel, councilRoom, festival, harbinger, laboratory, library, market, merchant, militia, mine, moat,
	moneylender, poacher, remodel, sentry, smithy, throneRoom, vassal, village, witch, workshop, gardens };

	vector<bool> selected(26, false);
	int numSelected = 0;

	cout << "Choose 10 cards from these cards (type their name to select them as part of your kingdom set): " << endl << endl;
	//Replace the yes and no with special charadcters later.
	do {
		string cName;
		bool found = false;
		for (int i = 0; i < avaliableKingdomCards.size(); i++) {
			if (selected[i]) {
				cout << i + 1 << "1. " << avaliableKingdomCards[i].getName() << " - [yes]" << endl;
			}
			else {
				cout << i + 1 << ". " << avaliableKingdomCards[i].getName() << " - [no]" << endl;
			}
		}

		getline(cin, cName);

		for (int i = 0; i < avaliableKingdomCards.size(); i++) {
			if (cName == avaliableKingdomCards[i].getName()) {
				kingdomCards.push_back(avaliableKingdomCards[i]);
				selected[i] = !selected[i];
				numSelected++;
				found = !found;
				break;
			}
			
		}

		if (!found) {
			cout << "Error, card not found. Try typing the name of a card found above!" << endl << endl;
		}


	} while (numSelected < 10);

	cout << "Kingdom decks assembled!" << endl << endl;

	b = new Board(kingdomCards, numPlayers);
	isGameSet = true;
}

void Game::gameEnd() {
	cout << "Game Over!" << endl << endl;
	cout << setfill('=') << setw(15) << "" << setfill(' ') << endl;
	

	if (personPlayer.totalVP() > otherPlayers[0].totalVP()) {
		cout << "The winner is the Player!!" << endl << endl;
	}
	else {
		cout << "The winner is the Program!!" << endl << endl;
	}

	cout << personPlayer.getName() << "'s score: " << personPlayer.totalVP() << endl;
	cout << otherPlayers[0].getName() << "'s score: " << otherPlayers[0].totalVP() << endl << endl;
	
	cout << "It took " << currentTurnCount << " turns to play this game!" << endl << endl;
}

bool Game::isGameReady() {
	return isGameSet;
}