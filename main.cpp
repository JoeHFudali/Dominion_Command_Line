#include "Card.h"

using namespace std;

int main() {

	Card village("village", 3, { "action" }, "+1 Card\n+2 Actions");


	village.printCardInfo();

	return 0;
}