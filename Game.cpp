#include "Game.h"

Game::Game() {
	b = new Board();

	Player p1("Joe");

	Player p2("Bot 1");

	personPlayer = p1;
	otherPlayers.push_back(p2);

	currentTurnCount = 0;

}

Game::Game(Player you, vector<Player> players, Board board) {
	*b = board;

	personPlayer = you;
	otherPlayers = players;

	currentTurnCount = 0;
}

Game::~Game() {
	delete b;
	b = 0;
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
	
}

