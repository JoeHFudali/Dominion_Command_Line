#pragma once
#include "Player.h"
#include "Turn.h"
#include "Board.h"

using namespace std;

class Game {
public:

	Game();
	~Game();
	Game(Player you, vector<Player> players, Board board);

	void Play();

	

private:

	void gameEnd();

	int currentTurnCount;

	Player personPlayer;

	vector<Player> otherPlayers;
	Board* b;

};