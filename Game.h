#pragma once
#include "Player.h"
#include "Turn.h"
#include "Board.h"

using namespace std;

class Game {
public:

	Game();
	Game(vector<Player> players, Board board);

	void Play();

private:

	int currentPlayerTurn;

	vector<Player> gamePlayers;
	Board b;

};