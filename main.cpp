#include "Board.h"
#include "Turn.h"
#include "Player.h"
#include "Game.h"
#include <ctime>

using namespace std;

void viewAllCards();
void viewSpecificCard();
void explainGame();

int main() {

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
	cout << "1. How to Play [W.I.P.]" << endl;
	cout << "2. Set up/Play game" << endl;
	cout << "3. Look at all cards/look at specific cards [W.I.P.]" << endl;
	cout << "4. View/Change Com-Opponent difficulty [W.I.P.]" << endl;
	cout << "5. View instructions/general tutorial [W.I.P.]" << endl;

	do {
		getline(cin, choice);

		if (stoi(choice) != 2 && stoi(choice) != 3) {
			cout << "Oops, you entered a choice that is either not one of the selected ones, or is not implemented yet. Please choose again!" << endl << endl;
		}

	} while (stoi(choice) != 2 && stoi(choice) != 3);

	if (stoi(choice) == 2) {

		if (!game.isGameReady()) {
			game.setUpBoard(numOfPlayers);
		}

		game.Play();
	}
	else if (stoi(choice) == 3) {
		viewAllCards();

		//cout << "Type 'look [card name]' to look at a specific card, or 'quit' to go back" << endl;


	}
	

	
	Board b;
	b.printCardInfo("Moat");

	

	return 0;
}

void viewAllCards() {

}