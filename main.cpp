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
	Card mine("Mine", 5, { "Action" }, { "You may trash a Treasure from your hand. Gain a Treasure to your hand costing up to 3 $ more than it." });
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

	

	string choice;

	cout << "Welcome to Command-Line Dominion! This is still a very early-in-development project with many features yet to come!" << endl << endl;

	do {
		
		cout << "1. How to Play [somewhat W.I.P.]" << endl;
		cout << "2. Set up/Play game" << endl;
		cout << "3. Look at all cards/look at specific cards" << endl;
		cout << "4. View/Change Com-Opponent difficulty [W.I.P.]" << endl;
		cout << "5. ??? [W.I.P.]" << endl;
		cout << "6. Close the App" << endl << endl;

		getline(cin, choice);
		if (stoi(choice) == 1) {
			explainGame();
		}
		else if (stoi(choice) == 2) {

			Game game;

			string choice2 = "";

			cout << "Would you like to choose you kingdom cards, have a randomized set of kingdom cards, or use a base set of kingdom cards? type 'choose', 'random', or 'base' respectivly." << endl << endl;

			



			do {
				getline(cin, choice2);

				if (choice2 == "choose") {
					game.setUpBoard(numOfPlayers);
					choice2 = "base";
				}
				else if (choice2 == "random") {
					game.setUpBoardRandomly(numOfPlayers);
					choice2 = "base";
				}
				else if (choice2 != "base") {
					cout << "Looks like you entered an incorrect choice. enter either 'choose', 'random', or 'base'. " << endl << endl;
				}
				else {
					game.setUpBasicBoard();
				}

			} while (choice2 != "base"); 

			game.Play();
			break;
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

void explainGame() {
	cout << "Dominion is a deck-building card game, collecting different cards from treasure cards that provide money, treasure cards that act as the scoring system, and action cards to perform" << endl;
	cout << "a wide variety of different effects on your own decks and other players decks. This is a recreation of the board game that runs of the command line, where carrying out any kind of actions," << endl;
	cout << "buys, and more require the user to type their requests out. You are able to often view individual cards and their stats, buy, trash, discard, and do more by typing out specific commands. If you" << endl;
	cout << "are familiar with the game, but would like to hear more about this version's specifics, type 'more', if you are unfamiliar with the game entirely, type 'tutorial', and if you want to go back to the" << endl;
	cout << "screen selection, type 'quit'" << endl;

	string choice;

	do {
		getline(cin, choice);
		cout << endl;

		if (choice == "more") {

			cout << "For Command-Line Dominion, there are a few specific disclaimers. For one, you technically do not have as much 'freedom' as you do in the board game, mainly due to the fact" << endl;
			cout << "that the command line requires intructions to carry out every single individual action/buy/etc. Another point of interest is the multiplayer aspect of the board game. For now," << endl;
			cout << "and possibly indefinitly, the game will be singleplayer with bot players as opponents. For specific cards, Moats will automatically block attacks, Bureaucrats will not" << endl;
			cout << "let you choose which exact victory card to show (Similar restriction with which treasure card Bandit trashes), your treasures are automatically 'played' during the buy phase, and" << endl;
			cout << "many different changes for how the AI opponent plays the game. As for specific commands:" << endl << endl;

			cout << "trash [card name] - puts a card from your hand into the trash." << endl;
			cout << "discard [card name] - puts a card from you hand into the discard pile." << endl;
			cout << "buy [card name] - spends money from either your collection of treasure cards in your hand, or from money generated by an action card, putting it into your discard pile a majority of the time." << endl;
			cout << "play [card name] - plays a card from your hand (usually an action card) when it is your turn." << endl;
			cout << "look [card name] - look at more specific information about a card, such as it's name, price, card type, and description of what it does." << endl;
			cout << "skip/pass/no - usually used for not going through with a cards action, skipping an action entirely, skipping a buy entirely, or other negations of game actions, when said game actions are player-choice specific" << endl;
			cout << "yes - keyword used for when card specific effects that are not listed above are described and the player wants to go through with those actions." << endl << endl;

			cout << "NOTE: There are more specific keywords (such as some for the Sentry card), but the game will propmpt you with those specific keywords when you play said cards." << endl;
			cout << "PROGRAMMERS NOTE: some command-line specific differences have not been mentioned here. will come back to include them later." << endl << endl;

			cout << "Would you like to see these instructions again, see Dominion specific instructions, or go back to the main screen? Enter 'more', 'tutorial', or 'quit' respectivly." << endl << endl;
		}
		else if (choice == "tutorial") {

			cout << "Dominion is a game that revolved around the cards you accumulate in you decks. The game is split into a main 'board', shared amongst all the players, and the player specific cards." << endl;
			cout << "The baord is made up of base cards, which are cards you will play every game with that have basic functions, and 'kingdom' cards, 10 specific cards that have greater functionality and influence on how you" << endl;
			cout << "carry out your turn. These cards will not all be the same between games, with different ways to combine and mix different kingdom cards each game. The board also has a 'trash mat', where" << endl;
			cout << "cards can be put via different action cards, and will be unobtainable and unusable by everyone in the game, including the person who trashed said card. All of these parts of the board are considered 'the supply'" << endl;
			cout << "The player cards are divided amongst a hand, normally consisting of 5 cards to play/buy other cards with, a discard deck to put all cards you've played or have in hand once your turn is over," << endl;
			cout << "and a draw deck to draw new hands once a turn has passed. Moving to the cards themselves, there are a few different types. Treasure cards are used as a way to 'create' currency, Victory cards are" << endl;
			cout << "cards that act as 'points' that contribute to who is considered the game's ultimate winner, and action cards are played to cause a variety of effects on the game, whether that is trashing cards to" << endl;
			cout << "get better cards, to increase the number of actions, buys, cards, and money you get, manipulating your draw or discard piles in various ways, and more. Some action cards can be used to directly affect" << endl;
			cout << "other players hand/decks/cards, and have an additional card type - Attack. Finally, the Curse card has the exact same card type as it's name, and acts as the opposite of victory cards, subtracting from your score" << endl;
			cout << "More on the action cards themselves, when you see something like '+1 Action', or '+2 Cards', these haves specific effects. When you see '+Action', you get the ability to play more actions. '+Cards' lets" << endl;
			cout << "you draw more cards from your draw pile into your hand. '+Buy' lets you be able to buy more than one card during your buy phase. '+$' (which has a specific coin symbol in the physical game) give your more" << endl;
			cout << "more money to spend during your buy phase, not necessarily giving you the ability to buy more things. When you play the game, each player goes through 3 specific phases: the Action phase" << endl;
			cout << ", the Buy phase, and the Clean-up phase. The Action phase gives you one action with 5 card in your hand to play. If you have no action cards, you skip this phase. If you want to play more action cards (each one costing" << endl;
			cout << "1 action to play), you must use action cards that give you those '+ actions'. When you do play an action cards, you take it from you hand, put it in front of you for everyone else to see, and play all of its effects from top to bottom." << endl;
			cout << "This card is now considered 'in-play', and you do this with every action card you play. After this phase is over, you enter the buy phase with a specific limit of cards you can buy (usually only one). You can increase this using" << endl;
			cout << "specific action cards, but besides this you also have a speficic amount of money given by the treasure cards in your hand (which can be affected by, again, your actions). Cards have spefific costs, and when you buy" << endl;
			cout << "a card, you take it from it's pile on the board, and put it into your discard pile. The final phase has you taking any cards you have 'in play' and in your hand, putting them into the discard pile, and" << endl;
			cout << "drawing 5 new cards from your draw pile. NOTE: when your draw pile becomes empty, take your discard pile, shuffle it, and set it as the new draw pile, having your discard pile now empty. Every player follows this" << endl;
			cout << "cycle for their own turns, and you keep playing cards, buying cards, and building you deck up over the course of the entire game. The game ends when either the 'Province' card pile in the base cards area is fully depleted," << endl;
			cout << "or three piles from the supply are fully depleted, whether they are base card piles, kingdom card piles, or a mix of both. After this, you count the amount of VP's given by each victory card you have up, and whoever" << endl;
			cout << "has the most VP wins the game. If players tie with VP, you then count the amount of money given by treasure cards up, and the player with the most treasure wins." << endl << endl;

			cout << "PROGRAMMERS NOTE: This description is a bit too wordy and not ordered the best, will come back later to reword it." << endl << endl;

			cout << "Would you like to see these instructions again, see Dominion specific instructions, or go back to the main screen? Enter 'more', 'tutorial', or 'quit' respectivly." << endl << endl;
		}
		else if (choice != "quit") {
			cout << "Looks like you entered in an incorrect choice. Enter either 'more' for more command-line instructions, 'tutorail' for more Dominion instructions, or 'quit' to exit to the main screen." << endl << endl;
		}

	} while (choice != "quit");


}