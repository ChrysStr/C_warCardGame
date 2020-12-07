//Chrys December 2020
/*
Code example in C
Example of Card Game War
Played with two mini-deck of single suit of 13 cards.
Manual mode were player prompts for each play .
Automatic mode where play and winner are determined without input as game is entirely luck based and requires no skill.
Output in standard output.
limitations:
	no external libraries.
	single text file only.	
can be compiled and run in online C compiler
ex: https://www.onlinegdb.com/online_c_compiler or https://www.tutorialspoint.com/compile_c_online.php
*/

#include <stdio.h>
#include <stdlib.h>

//Max size of deck.
int deckSize = 13;

//Struct for deck stack object.
struct cardDeck 
{
	int deckArr[13];
	int deckTop;
	char deckOwner;
	int points;
};

//Method to determine card play result.
//Determine win condition, either Win, Lose, or Draw.
char cardWin(int playercard, int systemcard)
{
	//
	if (playercard > systemcard)
	{
		return 'W';
	}
	else if (playercard < systemcard)
	{
		return 'L';
	}
	else
	{
		return 'D';
	}
}


//Method to popCard on top of the deck stack.
//Pops the int card value from the top of the deck stack and increments stack top value down.
int popCard(struct cardDeck *deck)
{
	if (emptyDeck(deck))
	{
		return 0;
	}
	else
	{
		int card = deck->deckArr[deck->deckTop];
		deck->deckTop = deck->deckTop - 1;
		return card;
	}
	
}

//Method to determine if deckArr stack is empty.
//Returns 1 if empty, 0 if not.
int emptyDeck(struct cardDeck deck, int size)
{
	if(deck.deckTop < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Method add a point to deck provided as a parameter.
void addPoint(struct cardDeck *deck)
{
	deck->points = deck->points + 1;
}

//method initializes a deck struct and fills it with integer values for cards.
//then produces a pseudo-random shuffle of the integers in the array to produce a randomized deck.
struct cardDeck shuffleDeck(char owner, int numb)
{
	struct cardDeck deck;
	time_t t;

	deck.deckOwner = owner;
	deck.points = 0;
	
	int startnum = 2;
	
	for (int i = 0; i < 14; i++)
	{
		deck.deckArr[i] = startnum;
		startnum = startnum + 1;
	}
	
	deck.deckTop = 12;
	
	srand((unsigned) time(&t));
	int swapa;
	int swapb;
	int rnum;
	
	for (int i = 0; i < 13; i++)
	{
		rnum = (rand() % numb);
		swapa = deck.deckArr[i];
		swapb = deck.deckArr[rnum];
		deck.deckArr[i] = swapb;
		deck.deckArr[rnum] = swapa;
	}
	
	return deck;
}

//Method to determine if player is the winner of point total
//returns 0 if loss, 1 if Win, 2 if otherwise;
int winLose(struct cardDeck playerDeck, struct cardDeck systemDeck)
{
	if (playerDeck.points > systemDeck.points)
	{
		printf("Player Wins.\n");
		return 1;
	}
	else if (playerDeck.points < systemDeck.points)
	{
		printf("Player Loses.\n");
		return 0;
	}
	else
	{
		printf("No winner determined.\n");
		return 2;
	}
}

//Automatic Play implementation of the game.
//Produces decks and runs each stack index in array against each other.
//Tabulates points an prints out resulting decks and points totals as well as winner.
void playWarAuto ()
{
    printf("Playing War Automatically...\n");
	struct cardDeck playerDeck = shuffleDeck('p',10);
	struct cardDeck systemDeck = shuffleDeck('s',9);
	do {
		int playerCard = popCard(&playerDeck);
		int systemCard = popCard(&systemDeck);
		char result = cardWin(playerCard, systemCard);
		switch(result)
		{
			case 'W' :
				addPoint(&playerDeck);
				break;
			case 'L' :
				addPoint(&systemDeck);
				break;
			case 'D' :
				break;
			default :
				printf("error, draw inconclusive\n");
		}
	}while(playerDeck.deckTop > -1);
	
	deckPrint(playerDeck, 13);
	deckPrint(systemDeck, 13);
	int final = winLose(playerDeck, systemDeck);
	
}

//Manual Play Method
//requires user input to continue and plays each card set individually.
//prints deck and result if player opts not to continue.
void playWarManual ()
{
	int state = 1;
	struct cardDeck playerDeck = shuffleDeck('p',10);
	struct cardDeck systemDeck = shuffleDeck('s',11);
	
	int playerCard;
	int systemCard;
	char result;
	do{
		printf ("1) play\n2) quit\n");
		scanf ("%d", &state);
		switch(state)
		{
			case 1 :
				playerCard = popCard(&playerDeck);
				systemCard = popCard(&systemDeck);
				result = cardWin(playerCard, systemCard);
				switch(result)
				{
					case 'W' :
						addPoint(&playerDeck);
						cardPrint(playerCard);
						printf(" Win\n");
						cardPrint(systemCard);
						printf(" Lose\n");
						break;
					case 'L' :
						addPoint(&systemDeck);
						cardPrint(playerCard);
						printf(" Lose\n");
						cardPrint(systemCard);
						printf(" Win\n");
						break;
					default :
						cardPrint(playerCard);
						printf(" Draw\n");
						cardPrint(systemCard);
						printf(" Draw\n");
				}
				break;
			case 2 :
				state = 2;
				break;
			default :
				printf ("Invalid entry, please try again \n");
			
		}
		if (emptyDeck(playerDeck, 13))
		{
			state = 2;
			printf("End of deck\n");
		}				
	}while(!(state == 2));
	deckPrint(playerDeck, 13);
	deckPrint(systemDeck, 13);
	int final = winLose(playerDeck, systemDeck);	
}

//Method to print out all cards in the deck.
//Prints out the owner of the deck.
//Increments through deck and prints out cards integer values one by one, substituting character values for face cards.
//Prints out the point total.
void deckPrint(struct cardDeck deckx, int size)
{
	if ( deckx.deckOwner == 's' )
	{
		printf("System : ");
	}else
	{
		printf("Player : ");
	}
	//substitute character values for face cards
	for (int i = size - 1; i > -1; i--)
	{
		switch(deckx.deckArr[i])
		{
			case 11 :
				printf("[J] ");
				break;
			case 12 :
				printf("[Q] ");
				break;
			case 13 :
				printf("[K] ");
				break;
			case 14 :
				printf("[A] ");
				break;
			default :
				printf("[%d] ", deckx.deckArr[i]);
		}
	}
	printf("%d points \n", deckx.points);
}

//method prints text representation of card integer.
//substitutes a char value for face cards.
void cardPrint(int card)
{
	switch(card)
	{
			case 11 :
				printf("[J] ");
				break;
			case 12 :
				printf("[Q] ");
				break;
			case 13 :
				printf("[K] ");
				break;
			case 14 :
				printf("[A] ");
				break;
			default :
				printf("[%d] ", card);	
	}
}

//TDD package 
//Add tests for functions as completed.
int TDDtestingPackage ()
{
	//testing cardWin
	printf("%c \n", cardWin(10,2));
	printf("%c \n", cardWin(2,10));
	printf("%c \n", cardWin(10,10));
	
	//testing card shuffle
    struct cardDeck testDeckP = shuffleDeck ('p', 9);
    struct cardDeck testDeckS = shuffleDeck ('s', 10);
	
	//testing deck print
    deckPrint(testDeckP, 13);
    deckPrint(testDeckS, 13);
	
	//testing emptyDeck;
	struct cardDeck testDeckE;
	testDeckE.deckTop = -1;
	printf("%d \n", emptyDeck(testDeckE, 13));
	printf("%d \n", emptyDeck(testDeckP, 13));
	
	//testing popCard and cardPrint
	printf("%d \n", testDeckS.deckTop);
    int card1 = popCard(&testDeckS);
	cardPrint(card1);
	printf("%d \n", testDeckS.deckTop);
    int card2 = popCard(&testDeckS);
    cardPrint(card2);
    printf("%d \n", testDeckS.deckTop);
	
	//testing winLose
	testDeckP.points = 8;
	testDeckS.points = 5;
	int final = winLose(testDeckP, testDeckS);
	printf("%d \n", final);
	testDeckP.points = 5;
	testDeckS.points = 8;
	final = winLose(testDeckP, testDeckS);
	printf("%d \n", final);
	testDeckP.points = 8;
	testDeckS.points = 8;
	final = winLose(testDeckP, testDeckS);
	printf("%d \n", final);
	
	
    
	return 0;
}


int main()
{
	//testing
	//int runTest = TDDtestingPackage();
	
	int inputSelect;
	printf("Game of War : select game mode : \n1) Automatic\n2) Manual\n");
	scanf("%d", &inputSelect);
	switch(inputSelect)
	{
		case 1 :
			playWarAuto();
			break;
		case 2 :
			playWarManual();
			break;
		default :
			printf("Exit");
	}
	return 0;
}