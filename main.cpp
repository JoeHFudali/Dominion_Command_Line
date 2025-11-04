#include "Card.h"

using namespace std;

int main() {

	Card village("Village", 3, { "Action" }, { "+1 Card", "+2 Actions" });
	Card market("Market", 5, { "Action" }, { "+1 Card", "+1 Action", "+1 Buy", "+1 o" });


	village.printCardInfo();

	market.printCardInfo();

	return 0;
}