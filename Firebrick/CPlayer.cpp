#include "CPlayer.h"
#include "CCard.h"
#include "CMinion.h"
#include "CBasicMinion.h"
CPlayer::CPlayer(string mTextFile, string mName):
mName(mName),mHealthPoints(PLAYER_STARTING_HP), mpCardsInHand(make_unique<container>(0)), 
mpCardsOnTable(make_unique<container>(0)), mpDeck(make_unique<CDeck>(mTextFile))
{}

CPlayer::~CPlayer()
{
	mpCardsOnTable->clear();
	mpCardsInHand->clear();
}

void CPlayer::DisplayTable()
{
	container::iterator pCardPtr = (*mpCardsOnTable).begin();
	for (pCardPtr = (*mpCardsOnTable).begin(); pCardPtr != mpCardsOnTable->end(); pCardPtr++)
	{
		cout << (*pCardPtr)->GetName() << "(";
		// down-casting, in order to accedss the minions health points
		CMinion* minion = (CMinion*)(*pCardPtr).get();
		cout << minion->GetHealth() << ") ";
	}
	cout << endl;
}

void CPlayer::DisplayHand()
{
	container::iterator pCardPtr;

	for (pCardPtr = mpCardsInHand->begin(); pCardPtr != mpCardsInHand->end(); pCardPtr++)
	{
		cout << (*pCardPtr)->GetName() << endl;
	}
	
}

void CPlayer::DisplayDeck()
{
	this->mpDeck->DisplayDeck();
}

void CPlayer::DrawCard(bool startingRound)
{
	// Removing the top card of the deck
	// and putting it in our hand	
	unique_ptr<CCard> drawnCard = move(mpDeck->Pop());
	if (!startingRound)
	{
		cout << drawnCard->GetName() << endl;
	}
	mpCardsInHand->push_back(move(drawnCard));
	drawnCard.release();

}

void CPlayer::PlayCard(int randomNumber, CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	container::iterator pCardPtr = (*mpCardsInHand).begin();

	// storing the pointer that points to the card that is about to get popped		
	unique_ptr<CCard> pTempo = move((mpCardsInHand.get())->at(randomNumber));
	
	cout << pTempo->GetName() << endl;

	// and putting it into the table first
	// if it is a spell card activate it
	if (pTempo->GetName() == "Fireball" || pTempo->GetName() == "Lightning"
		|| pTempo->GetName() == "Bless" || pTempo->GetName() == "Sword"
		|| pTempo->GetName() == "Armour")
	{
		pTempo->Activate(enemyPlayer, currentPlayer);
	}
	else
	{
		// else put oit on the table 
		mpCardsOnTable->push_back(move(pTempo));
	}
	// and after remove the card from the player's hand
	mpCardsInHand->erase((*mpCardsInHand).begin() +randomNumber);	
}

// setters
void CPlayer::SetHealthPoints(int hp) { this->mHealthPoints = hp; }

// getters
int CPlayer::GetNumberOfCardsOnTable() { return GetCardsOnTable()->size(); }
int CPlayer::GetHealthPoints() { return this->mHealthPoints; }
string CPlayer::GetName() { return mName; }
int CPlayer::GetSize(CDeck* mpDeck) { return mpDeck->GetTop(); }
CCard* CPlayer::GetSelectedCardFromTable(int position) 
{ 
	return (*mpCardsOnTable).at(position).get();
}
CCard* CPlayer::GetSelectedCardFromHand(int position)
{
	return (*mpCardsInHand).at(position).get();
}
container* CPlayer::GetCardsInHand() { return mpCardsInHand.get(); }
container* CPlayer::GetCardsOnTable() { return mpCardsOnTable.get(); }
CDeck* CPlayer::GetDeck() { return this->mpDeck.get(); }

// Initialize static members of class CGame
int CPlayer::PLAYER_STARTING_HP = 30;