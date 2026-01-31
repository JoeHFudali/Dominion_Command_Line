#include "Board.h"
#include "Turn.h"
#include "Player.h"
#include "Game.h"
#include <ctime>

using namespace std;



void viewAllCards();
void viewSpecificCard(string cardNmae, vector<Card> searchList);
void explainGame();

int main() {


	Card copper;
	Card silver("Silver", 3, { "Treasure" }, { "2 $" });
	Card gold("Gold", 6, { "Treasure" }, { "3 $" });
	Card estate("Estate", 2, { "Victory" }, { "1 VP" });
	Card duchy("Duchy", 5, { "Victory" }, { "3 VP" });
	Card province("Province", 8, { "Victory" }, { "6 VP" });
	Card curse("Curse", 0, { "Curse" }, { "-1 VP" });
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

	vector<Card> baseGameCards = { copper, silver, gold, estate, duchy, province, curse, artisan, bandit, bureaucrat, chapel, councilRoom, festival, harbinger, laboratory, library, moneylender, poacher,
	sentry, throneRoom, vassal, witch, gardens, cellar, moat, village, merchant, workshop, smithy, remodel, militia, market, mine };

	srand(time(0));

	int numOfPlayers = 2;

	
	//Testing the card/deck class below

	/*village.printCardInfo();

	market.printCardInfo();

	estate.printCardInfo();

	province.printCardInfo();

	Deck d;

	d.addCard(estate);
	d.addCard(village);
	d.addCard(province);
	d.addCard(merchant);

	cout << d.sumVP() << endl;

	d.printDeck();*/

	//Testing the Board class below

	Game game;

	string choice;

	cout << "Welcome to Command-Line Dominion! This is still a very early-in-development project with many features yet to come!" << endl << endl;

	do {
		
		cout << "1. How to Play [W.I.P.]" << endl;
		cout << "2. Set up/Play game" << endl;
		cout << "3. Look at all cards/look at specific cards" << endl;
		cout << "4. View/Change Com-Opponent difficulty [W.I.P.]" << endl;
		cout << "5. View instructions/general tutorial [W.I.P.]" << endl;
		cout << "6. Close the App" << endl << endl;

		getline(cin, choice);

		if (stoi(choice) == 2) {

			if (!game.isGameReady()) {
				game.setUpBoard(numOfPlayers);
			}

			game.Play();
		}
		else if (stoi(choice) == 3) {
			string choice2 = "all";

			do {
				if (choice2 == "all") {
					viewAllCards();
				}
				else if (choice2.find("view ") != string::npos) {
					//Need to add which cardd to view here as a parameter later
					viewSpecificCard(choice2.substr(5), baseGameCards);
				}
				else if (choice2 != "quit") {
					cout << "Oops, looks like you didn't enter a correct choice." << endl << endl;
				}
				else {
					break;
				}

				cout << "Would you like to view this again, look at a specific card, or quit. type 'all', 'view [card name]', or 'quit' respectively" << endl << endl;

				getline(cin, choice2);


			} while (choice2 != "quit");

			//choice = "";
			//cout << "Type 'look [card name]' to look at a specific card, or 'quit' to go back" << endl;

		}
		else if (stoi(choice) == 6) {
			break;
		}

		if (stoi(choice) != 2 && stoi(choice) != 3 && stoi(choice) != 6 && choice != "") {
			cout << "Oops, you entered a choice that is either not one of the selected ones, or is not implemented yet. Please choose again!" << endl << endl;
		}
		
	} while (true);

	

	
	Board b;
	b.printCardInfo("Moat");

	

	return 0;
}

void viewAllCards() {
	cout << "Base Deck Cards: " << endl;
	cout << "Copper - Silver - Gold - Estate - Duchy - Province - Curse" << endl << endl;

	cout << "Kingdom Cards: " << endl;
	cout << "Artisan - Bandit - Bureaucrat - Cellar - Chapel" << endl;
	cout << "Council Room - Festival - Harbinger - Laboratory - Library" << endl;
	cout << "Market - Merchant - Militia - Mine - Moat" << endl;
	cout << "Moneylender - Poacher - Remodel - Sentry - Smithy" << endl;
	cout << "Throne Room - Vassal - Village - Witch - Workshop - Gardens" << endl << endl;


}

void viewSpecificCard(string cardName, vector<Card> searchList) {
	bool found = false;
	for (int i = 0; i < searchList.size(); i++) {
		if (searchList[i].getName() == cardName) {
			searchList[i].printCardInfo();
			found = !found;
			break;
		}
	}

	if (!found) {
		cout << "Looks like the card you are looking for is not in the base game of Dominion." << endl << endl;
	}


}