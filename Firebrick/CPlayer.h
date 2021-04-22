#pragma once
#include "CDeck.h"
#include <vector>
typedef vector<unique_ptr<CCard>> container;
class CCard;
class CPlayer
{
private:
	unique_ptr<container> mpCardsInHand;
	unique_ptr<container> mpCardsOnTable;
	unique_ptr<CDeck> mpDeck;
	string mName;
	int mHealthPoints;

public:
	int static PLAYER_STARTING_HP;

public:
	// Constructor, parameters: the pathway of the text file which contains the deck + the player's name
	// Initializes the name of the player and also the pathway of the file that contains the player's cards (deck).
	CPlayer(string mTextFile, string mName);

	// Destructor
	~CPlayer();

	// Displays all cards in the deck
	void DisplayDeck();

	// Displays all cards in the hand
	void DisplayHand();

	// Displays all cards on the table
	void DisplayTable();

	// Player draws a card. The top card of the deck/stack is removed and placed in the player's hand
	void DrawCard(bool startingRound); // if it is the starting round print the name of the starting card

	// Player pick a random card to play
	// Parameters: both players + the random position of the card is going to be played
	void PlayCard(int randomNumber, CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer);

	// Sets the health points of the player. Parameter: the health points of the player
	void SetHealthPoints(int hp);

	// Getters
	int GetHealthPoints(); // returns the health points
	int GetNumberOfCardsOnTable(); // returns  the number of cards on the table
	string GetName(); // returns the name of the player
	CCard* GetSelectedCardFromTable(int position); // returns a pointer of the card in that position from the table
	CCard* GetSelectedCardFromHand(int position); // returns a pointer of the card in that position from the hand
	int GetSize(CDeck* mpDeck); // returns the size of the deck
	container* GetCardsInHand(); // returns a pointer to the cards in the player's hand
	container* GetCardsOnTable(); // returns a pointer to the cards in the player's table
	CDeck* GetDeck(); // returns a pointer to the cards in the player's deck
};

