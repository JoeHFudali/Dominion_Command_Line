#pragma once
#include "Player.h"
#include "Turn.h"
#include "Board.h"

using namespace std;

class Game {
public:

	Game();
	~Game();
	Game(Player you, vector<Player> players);

	void setUpBoard(int numPlayers);
	void Play();

	bool isGameReady();

private:
	
	void gameEnd();

	int currentTurnCount;

	Player personPlayer;

	vector<Player> otherPlayers;
	Board* b;

	bool isGameSet;

};