#include "Card.h"
#include "Deck.h"
#include <ctime>

using namespace std;

int main() {

	srand(time(0));

	Card village("Village", 3, { "Action" }, { "+1 Card", "+2 Actions" });
	Card market("Market", 5, { "Action" }, { "+1 Card", "+1 Action", "+1 Buy", "+1 o" });

	Card estate("Estate", 2, { "Victory" }, { "1 VP" });
	Card province("Province", 8, { "Victory" }, { "6 VP" });


	village.printCardInfo();

	market.printCardInfo();

	estate.printCardInfo();

	province.printCardInfo();

	Deck d;

	d.addCard(estate);
	d.addCard(village);
	d.addCard(province);

	cout << d.sumVP() << endl;

	Card tCard;

	if (d.takeCard("Estate", tCard))
	{
		cout << "estate taken out!" << endl;
	}

	cout << d.sumVP() << endl;

	

	return 0;
}