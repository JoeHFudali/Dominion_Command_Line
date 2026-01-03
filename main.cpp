#include "Board.h"
#include "Turn.h"
#include "Player.h"
#include "Game.h"
#include <ctime>

using namespace std;

int main() {

	srand(time(0));

	
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

	game.Play();

	
	Board b;
	b.printCardInfo("Moat");

	

	return 0;
}