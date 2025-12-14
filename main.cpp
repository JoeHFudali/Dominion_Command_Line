#include "Board.h"
#include <ctime>

using namespace std;

int main() {

	srand(time(0));

	Card village("Village", 3, { "Action" }, { "+1 Card", "+2 Actions" });
	Card market("Market", 5, { "Action" }, { "+1 Card", "+1 Action", "+1 Buy", "+1 o" });
	Card merchant("Merchant", 3, { "Action" }, { "+1 Card", "+1 Action", "The first time you play a Silver this turn, +1 o" });

	Card estate("Estate", 2, { "Victory" }, { "1 VP" });
	Card province("Province", 8, { "Victory" }, { "6 VP" });
	Card curse("Curse", 0, { "Curse" }, { "-1 VP" });

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

	
	Board b;
	b.printCardInfo("Witch");

	

	return 0;
}