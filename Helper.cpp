#include "Helper.h"

using namespace std;

Helper::Helper() {
	//do nothing for now
}

//At this moment, this function takes care of non-alpha characters, extra spaces, and capitilization. WIll include functionality for mispellings like one-off letters, too many letters, switched letters, and other issues.
void Helper::cleanseInput(string& input) {
	bool spaceFound = false;
	//string firstWord = "";

	

	for (int i = 0; i < input.size(); i++) {

		if (input[i] == ' ' && i >= 7 && isalpha(input[i + 1]) && input.substr(i - 6, 6) == "Throne") {
			input[i + 1] = toupper(input[i + 1]);
			i++;
		}
		else if (input[i] == ' ' && i >= 8 && isalpha(input[i + 1]) && input.substr(i - 7, 7) == "Council") {
			input[i + 1] = toupper(input[i + 1]);
			i++;
		}
		else if (input[i] == ' ' && isalpha(input[i + 1]) && (input.substr(0, i) == "buy" || input.substr(0, i) == "trash" || input.substr(0, i) == "discard" || input.substr(0, i) == "look" || input.substr(0, i) == "play") && !spaceFound && i + 1 < input.size()) {
			input[i + 1] = toupper(input[i + 1]);
			i++;
			spaceFound = !spaceFound;
		}
		else if (input[i] != ' ' && isalpha(input[i])) {
			input[i] = tolower(input[i]);
		}
		else if (input[i] == ' ' || !isalpha(input[i])) {
			if (i + 1 < input.size()) {
				input = input.substr(0, i) + input.substr(i + 1);
			}
			else {
				input = input.substr(0, i);
			}
			i--;
		}

		
	}
	//cout << input << endl;

	cout << endl;
}