
//Black Jack Game
//Holland Sersen

#include <stdio.h>
#include <iostream>
#include "dealer.hpp"

Dealer gameSpace;

using namespace std;

int main(){
	gameSpace.initSeed();
	for (int i = 0; i < 100; i++){	
		gameSpace.playGame();
	}

	gameSpace.showWins(true);
	gameSpace.showWins(false);
	return 0;
}
