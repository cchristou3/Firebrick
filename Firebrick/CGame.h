#pragma once
#include "CPlayer.h"
#include"CMinion.h"
#include "CBasicMinion.h"
#include <ctime>
class CGame
{
private:
	const string SORCERESS_FILE = "..\\Debug\\sorceress.txt";
	const string WIZARD_FILE = "..\\Debug\\wizard.txt";
	const int MAXIMUM_ROUND = 30;
	const int STARTING_ROUND = 1;
	bool mShuffleDecks;
	int mRoundNumber;
	unique_ptr<CPlayer> mpSorceress;
	unique_ptr<CPlayer> mpWizard;

public:
	// Constructor of the class CGame. Creates the players objects as well.
	// Also initializes the number of rounds to 0
	CGame();

	// Destructor of the class CGame
	~CGame() = default;

	// Starts the game
	void Start();

	// A round is played, within a round each player draws a card, plays a card and attacks with his/her minions
	// Returns true if any of the two player's health has reached zero, otherwise returns false
	bool PlayRound();

	// Returns a random number in the range 0 .. n, inclusive.
	int Random(const int n);

	// Increments the number of rounds by one
	void NextRound();

	// Returns the number of rounds played
	int GetNumberOfRounds();

	// A player draws a card.
	// In the first round each player draws two cards. One starting as a starting hand
	// and the other which signifies the the round started. Parameters: The controlling player and a boolean value,
	// indicating whether it is the starting round or not.
	void PlayerDrawsCard(CPlayer* pPlayer, bool startingRound);

	// A player picks a card from his hand and plays it on the table
	// if its a spell/equipment card, he / she activates it immediately. Parameters: both players
	void PlayerPlaysCard(CPlayer* pCurrentPlayer, CPlayer* pEnemyPlayer);

	// A player draws a card, plays a card and attacks with his/her minions
	// parameters: both players
	bool PlayerPlaysRound(CPlayer* pCurrentPlayer,CPlayer* pEnemyPlayer);

	// Returns true if any of the two player's health has reached zero, otherwise returns false. Paramters: both players
	bool CheckPlayersHeahlth(CPlayer* pCurrentPlayer, CPlayer* pEnemyPlayer);

	// Asks the user if he/she would like to shuffle the decks before the game starts.
	// Returns true if answered positively, otherwise returns false
	bool AskUserToShuffleTheDecks();

	// Shuffles the player's deck. Paramter: the controlling player
	void ShufflePlayerDeck(CPlayer* pPlayer);

	// Prints the results. Paramters: both players
	void ShowResults(CPlayer* pPlayerOne, CPlayer* pPlayerTwo);

	// Handles everything that has to do with shuffling process. Paramters: both players
	void HandleShuffle(CPlayer* pPlayerOne, CPlayer* pPlayerTwo);

	// Each player draws their starting hand, parameters: both players
	void DrawStartingHand(CPlayer* mpSorceress, CPlayer* mpWizard);

	// The player plays a random card form his/her hand. The card is placed on the player's table. Paramters: both players
	void PlayRandomCardFromHand(CPlayer* pCurrentPlayer, CPlayer* pEnemyPlayer);
	
};

