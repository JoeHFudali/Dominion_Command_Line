#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Card
{
public:

	Card();
	Card(string nm, int cst, vector<string> tps, vector<string> desc);

	void printCardInfo();

private:

	string name;
	int cost;
	vector<string> types;
	vector<string> description;



};

