#pragma once
// Test Function
#include <stdio.h>
void tester();

//Init All Objects

class Dealer {	
	//Create and Array that hols all the values of the card
	int deck[13] = {3};

	//Re shuffle the Deck
	void shuffleDeck();
	void shuffleDeck(int val);
	
	//Chances player hits or Stands
	int confidenceLevel = 50;
	
	//Current Dealer and Player Score
	int playerScore, dealerScore = 0;
	int playerAces, dealerAces = 0;
	int playerBust, dealerBust = false;
	bool playerDone, dealerDone = false;
	int SEED = 0;

	//Initial Two Card Draw
	void hit(bool isPlayer);

	//Check if anyone has won
	int checkPlayerWin();
	int checkDealerWin();
	
	int trueValue(bool isPlayer);

	//Reset to defaults
	void resetGame();
	
	//End of game Dialogue
	int endDia(bool isPlayer);

public:
	
	//Init Seed
	void initSeed();

	void showWins(bool isPlayer);

	//Play the Game. Can Be looped
	void playGame();

	//Wins and Losses for each Player
	int playerWins, dealerWins = 0;
};

//Clip: Check if value is too high or low
template <typename T> T  clip(T value, T min, T max){

	if (value < min){
		return min;
	}
	
	else if (value > max){
		return max;
	}

	return value;
}


