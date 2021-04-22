// CGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <memory>
#include "CGame.h"
#define _CRTDBG_MAP_ALLOC
CGame::CGame():
	mpSorceress(make_unique<CPlayer>(SORCERESS_FILE, "Sorceress")),
	mpWizard(make_unique<CPlayer>(WIZARD_FILE, "Wizard")),
	mRoundNumber(STARTING_ROUND)
{
	// Print my name + Program name
	cout << "Charalambos Christou. Firebrick" << endl;
}

bool CGame::PlayRound()
{
	cout << "Round " << GetNumberOfRounds() << endl;

	//~~~~~~~~~~~~~~~~~~~~~~~// a round plays //~~~~~~~~~~~~~~~~~~~~~~~//

	bool isAnyPlayerDead = PlayerPlaysRound(this->mpSorceress.get(), this->mpWizard.get());
	if (isAnyPlayerDead)
	{
		return true;
	}
	cout << endl;
	
	isAnyPlayerDead = PlayerPlaysRound(this->mpWizard.get(), this->mpSorceress.get());
	if (isAnyPlayerDead)
	{
		return true;
	}

	// going to the next round
	NextRound();
	cout << endl;
	return false;
}

int CGame::Random(const int n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}

inline void CGame::NextRound()
{
	this->mRoundNumber++;
}

int CGame::GetNumberOfRounds() { return this->mRoundNumber; }

void CGame::PlayerDrawsCard(CPlayer* pPlayer, bool startingRound)
{
	// check whether the player has cards in his deck
	if (pPlayer->GetDeck()->GetTop() != 0)
	{
		if (!startingRound)
		{
			cout << pPlayer->GetName() << " draws ";
		}
		pPlayer->DrawCard(startingRound);
	}
	else
	{
		cout << pPlayer->GetName() << " is out of cards to draw!" << endl;
	}
	
}

void CGame::PlayerPlaysCard(CPlayer* pCurrentPlayer, CPlayer* pEnemyPlayer)
{
	if (pCurrentPlayer->GetCardsInHand()->size() != 0)
	{
		PlayRandomCardFromHand(pCurrentPlayer, pEnemyPlayer);
	}
	else
	{
		cout << pCurrentPlayer->GetName() << " is out of cards to play!" << endl;
	}
}

bool CGame::PlayerPlaysRound(CPlayer* pCurrentPlayer, CPlayer* pEnemyPlayer)
{
	//  player draws a card
	PlayerDrawsCard(pCurrentPlayer, false);
	//  player plays a card
	PlayerPlaysCard(pCurrentPlayer, pEnemyPlayer);
	// check whether a spell killed a player
	if (CheckPlayersHeahlth(pCurrentPlayer, pEnemyPlayer))
	{
		return true;
	}
	cout << "Cards on table: ";
	if (pCurrentPlayer->GetNumberOfCardsOnTable() != 0)
	{
		pCurrentPlayer->DisplayTable();
	}
	else
	{
		cout << "none" << endl;
	}
	
	// get the number of cards on each player table, after both players played a card each
	int numofCardsOnTableForSorceress = pCurrentPlayer->GetNumberOfCardsOnTable();
	
	//~~~~~~~~~~~~~~~~~~~~~~~// Player's minions activate //~~~~~~~~~~~~~~~~~~~~~~~//
	// traverse through all minions each player's table
	for (int i = 0; i < numofCardsOnTableForSorceress; i++)
	{
		unique_ptr<CCard> attackingMinion = unique_ptr<CCard>(pCurrentPlayer->GetSelectedCardFromTable(i));		
		// each minion gets activated
		attackingMinion->Activate(pEnemyPlayer, pCurrentPlayer);
		attackingMinion.release();		
		if (CheckPlayersHeahlth(pCurrentPlayer, pEnemyPlayer))
		{
			return true;
		}
	}
	return false; // no player died in this player's turn
}

bool CGame::CheckPlayersHeahlth(CPlayer* pCurrentPlayer,CPlayer* pEnemyPlayer)
{
	if (pCurrentPlayer->GetHealthPoints() <= 0 || pEnemyPlayer->GetHealthPoints() <= 0)
	{
		// finish game
		cout << "\n" << ((pCurrentPlayer->GetHealthPoints() <= 0) ? pCurrentPlayer->GetName() : pEnemyPlayer->GetName())
			<< " lost the game!" << endl;
		return true;
	}
	return false;
}

bool CGame::AskUserToShuffleTheDecks()
{
	cout << "Would you like to shuffle the decks? Answer with  Y or N (Y/N)" << endl;
	string answer;
	cin >> answer;
	while (true)
	{
		if (answer == "Y")
		{
			cout << endl;
			return true;
		}
		else if (answer == "N")
		{
			cout << endl;
			return false;
		}
		else
		{
			cout << "Need to write either 'Y' or 'N'!" << endl;
			cin >> answer;
		}
	}
}

void CGame::Start()
{
	srand(static_cast<unsigned int> (0));
	if (this->mpSorceress->GetDeck()->IsEmpty() || this->mpWizard->GetDeck()->IsEmpty())
	{
		cout << "Game couldn't get started, one of the player's has no deck!" << endl;
	}
	else
	{
		HandleShuffle(mpSorceress.get(), mpWizard.get());

		// Both Players draw their starting hand
		DrawStartingHand(this->mpSorceress.get(), this->mpWizard.get());

		while (this->GetNumberOfRounds() <= MAXIMUM_ROUND)
		{
			bool gameFinished = this->PlayRound();
			if (gameFinished)
			{
				cout << "Game finished" << endl;
				break;
			}
		}
		ShowResults(mpSorceress.get(), mpWizard.get());
	}		
}

void CGame::ShufflePlayerDeck(CPlayer* pPlayer)
{
	pPlayer->GetDeck()->Shuffle();
}

void CGame::ShowResults(CPlayer* pPlayerOne, CPlayer* pPlayerTwo)
{
	int currentPlayerHp = pPlayerOne->GetHealthPoints();
	int enemyPlayerHp = pPlayerTwo->GetHealthPoints();
	if (this->GetNumberOfRounds() == MAXIMUM_ROUND + 1
		&& currentPlayerHp > 0 && enemyPlayerHp > 0)
	{

		if (currentPlayerHp == enemyPlayerHp)
		{
			cout << "It's a draw!" << endl;
		}
		else if (currentPlayerHp < enemyPlayerHp)
		{
			cout << pPlayerOne->GetName() << " won the game!" << endl;
		}
		else if ((currentPlayerHp > enemyPlayerHp))
		{
			cout << pPlayerTwo->GetName() << " won the game!" << endl;
		}
	}
}

void CGame::HandleShuffle(CPlayer* pPlayerOne, CPlayer* pPlayerTwo)
{
	bool shuffleDecks = AskUserToShuffleTheDecks();
	if (shuffleDecks)
	{
		ShufflePlayerDeck(pPlayerOne);
		ShufflePlayerDeck(pPlayerTwo);
	}
}

void CGame::DrawStartingHand(CPlayer* mpSorceress, CPlayer* mpWizard)
{
	// this single card is the starting hand
	PlayerDrawsCard(mpSorceress, true);
	cout << mpSorceress->GetName() << " begins with " << mpSorceress->GetSelectedCardFromHand(0)->GetName() << endl;
	PlayerDrawsCard(mpWizard, true);
	cout << mpWizard->GetName() << " begins with " << mpWizard->GetSelectedCardFromHand(0)->GetName() << endl;
	cout << endl;
	/*	Sorceress begins with Dwarf
		Wizard begins with Orc	*/
}

void CGame::PlayRandomCardFromHand(CPlayer* pCurrentplayer, CPlayer* pEnemyPlayer)
{
	// get the amount of cards the each user is holding
	int numofCardsInHandOfPlayer = pCurrentplayer->GetCardsInHand()->size() - 1; // -1 as we always start from 0
	// choose a random integer between 0..handSize
	int positionOfCardInHand = Random(numofCardsInHandOfPlayer); // this card will be placed on the table
	cout << pCurrentplayer->GetName() << " plays ";
	pCurrentplayer->PlayCard(positionOfCardInHand, pEnemyPlayer, pCurrentplayer);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void MemoryLeakDetection()
{
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}
void StartGame()
{
	unique_ptr<CGame> pGame = make_unique<CGame>();
	pGame->Start();
}
int main()
{
	_crtBreakAlloc = -1;

	StartGame();

	MemoryLeakDetection();
}