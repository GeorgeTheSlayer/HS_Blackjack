#pragma once
#include "dealer.hpp"
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

extern int deck[];

void tester(){
	cout << "Loser" << endl;

}

int Dealer::endDia(bool isPlayer){
	string winner;
	
	if (isPlayer){
		winner = "Player";
		playerWins += 1;
		confidenceLevel += 2;
	}
	else{
		winner = "Dealer";
		dealerWins += 1;
		confidenceLevel -= 2;
	}
		
	cout << winner << " Wins! " << "Player Score: " << playerScore << " Dealer Score: " << dealerScore << endl;
	
	return 1;

}

//Shuffle the Cards. Make them all 3 so there is an equal chance of getting them
void Dealer::shuffleDeck(){
	for (int i = 0; i < 13; i++){
		deck[i] = 3;
	}
}


void Dealer::shuffleDeck(int val){
	for (int i = 0; i < 13; i++){
		deck[i] = val;
	}
}

void Dealer::hit(bool isPlayer){
	int drawnCard = rand() % 13;
	
	bool isValid = true;

	//If that Card has been drawn too many times then draw again
	while(isValid){
		if (deck[drawnCard] < 0)
			drawnCard = rand() % 13;	

		else 
			isValid = false;
	}

	//Get rid of one card from the deck
	deck[drawnCard] -= 1;
	
	//Find The Value of the Card	
	int cardScore = 1;
	if(drawnCard >= 11)
		cardScore = 10;
	else if (drawnCard == 0){
		playerAces += 1;
		cardScore = 1;
	}
	else
		cardScore += 1;

	if (isPlayer == true)
		playerScore += drawnCard;
	else 
		dealerScore += drawnCard;
	
}

int Dealer::checkPlayerWin(){
	const int newPS = trueValue(true);

	if (newPS == 21){
		return endDia(true);
	}
	
	if (newPS > 21 && playerBust == false){
		playerBust = true;
		return endDia(false);
	}
	
	if (playerDone == true && dealerDone == true){
		if (newPS > trueValue(false) && playerBust == false){
			return endDia(true);
		}

		else {
			return endDia(false);
		}
	}
	
	
	return 0;
}

int Dealer::checkDealerWin() {
	const int newDS = trueValue(false);
	
	if (newDS == 21){
		return endDia(false);
	}


	if (newDS > 21 && dealerBust == false){
		dealerBust = true;
		return endDia(true);
	}
	
	if (playerDone == true && dealerDone == true){
		if (trueValue(true) > newDS && playerBust == false){
			return endDia(true);
		}

		else {
			return endDia(false);
		}
	}
	
	return 0;
}



//Higher Rez Time
void Dealer::initSeed(){
	unsigned int time_ui = time(NULL) ;
	srand( time_ui );
}

void Dealer::resetGame(){
	playerScore = 0;
	dealerScore = 0;
	playerAces = 0;
	dealerAces = 0;
	playerBust = false;
	dealerBust = false;
	playerDone = false;
	dealerDone = false;
}



void Dealer::showWins(bool isPlayer){
		if (isPlayer)
			std::cout << "Player Wins: " << playerWins << std::endl;
		else
			std::cout << "Dealer Wins: " << dealerWins << std::endl;
	}

//Play game, can be looped
void Dealer::playGame(){
	bool gamePlay = true;

	while(gamePlay){
		shuffleDeck();

		if (!dealerBust && dealerScore <= 16)
			hit(false);
		
		if (dealerScore > 16)
			dealerDone = true;

		const int d_outcome = checkDealerWin();
		
		if (d_outcome == 1 ){
			gamePlay = false;
		}
		
		if (gamePlay){
			//Determine if the player should hit again
			const int hitChance = rand() % 100;		

			if (playerScore <= 0 || playerAces > 0 )
				hit(true);
			else if (!playerBust && hitChance <= confidenceLevel)
				hit(true);
			else 
				playerDone = true;
			
			const int p_outcome = checkPlayerWin();

			if (p_outcome == 1 ){
				gamePlay = false;
			}
		}
	}

	//Reset the Game
	resetGame();
}

int Dealer::trueValue(bool isPlayer){
	int newSum = 0;
	if (isPlayer)
	{
		newSum = playerScore;
		if (playerAces > 0){
			for (int i = 0; i < playerAces; i++)
			{
				if (newSum + playerAces - 1 <= 10)
				{
					newSum += 11;
				}
				else{
					newSum += 1;
				}
			}
			
			return newSum;
			
		}
		
		return playerScore;
	}
	
	else if (!isPlayer)
	{
		newSum = dealerScore;
			if (dealerAces > 0){
				for (int i = 0; i < dealerAces; i++)
				{
					if (newSum + dealerAces - 1 <= 10)
					{
						newSum += 11;
					}
					else{
						newSum += 1;
					}
				}
				
				return newSum;
				
			}
			
			return dealerScore;
		}
}

