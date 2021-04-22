#include "CMinion.h"
CMinion::CMinion(string mName, int mAttack, int mHealth) :
	CCard(mName), mAttackPoints(mAttack), mHealthPoints(mHealth), 
	mDefencePoints(0) // zero is the default value in defence
{  }

CMinion::~CMinion()
{

}

void CMinion::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{

}

void CMinion::Attack(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	int numOfCardsOnEnemyTable = pEnemyPlayer->GetNumberOfCardsOnTable();
	cout << GetName() << " attacks ";
	if (numOfCardsOnEnemyTable > 0) // if enemy has minions
	{
		// make a quick check whether a wall exist in the enemy minions on the table
		int indexOfEnemyWall = FindMinion("Wall", pEnemyPlayer);
		if (indexOfEnemyWall == -1)
		{
			// no "wall" in enemy table
			int randomPositionOnEnemyTable = Random(numOfCardsOnEnemyTable - 1); // starting from 0
			AttackEnemyMinion(pEnemyPlayer, randomPositionOnEnemyTable);
		}
		else
		{
			AttackEnemyMinion(pEnemyPlayer, indexOfEnemyWall);
		}
	}
	else // if there are no enemy minions, it attacks the player's HP
	{
		cout << pEnemyPlayer->GetName() << ": ";
		int enemyPlayerCurrentHp = pEnemyPlayer->GetHealthPoints();
		int minionAttckPower = GetAttack();
		int enemyPlayerUpdatedHp = enemyPlayerCurrentHp - minionAttckPower;
		if (enemyPlayerUpdatedHp <= 0)
		{
			pEnemyPlayer->SetHealthPoints(enemyPlayerUpdatedHp);
			cout << pEnemyPlayer->GetName() << " killed" << endl;
		}
		else
		{
			pEnemyPlayer->SetHealthPoints(enemyPlayerUpdatedHp);
			cout << pEnemyPlayer->GetName() << " health now " << pEnemyPlayer->GetHealthPoints() << endl;
		}
	}
}

void CMinion::AttackEnemyMinion(CPlayer* pEnemyPlayer, int enemyPosition)
{
	CCard* pRandomEnemyCard =
		(pEnemyPlayer->GetSelectedCardFromTable(enemyPosition));
	CMinion* pAttackedMinion = (CMinion*)pRandomEnemyCard;
	cout << pAttackedMinion->GetName() << ": ";
	int allyMinionAttackPower = GetAttack();
	int enemyMinionCurrentHp = pAttackedMinion->GetHealth();
	int enemyMinionUpdatedHp = enemyMinionCurrentHp
		+ pAttackedMinion->GetDefence()	// adding the protection as well
		- allyMinionAttackPower;
	if (enemyMinionUpdatedHp <= 0) // minion is removed from the table
	{
		MinionDies(pAttackedMinion, pEnemyPlayer, enemyPosition);
		cout << endl;
	}
	else
	{
		UpdateMinionHealth(pAttackedMinion, enemyMinionUpdatedHp);
	}
}

int CMinion::FindMinion(string minionName, CPlayer* pEnemyPlayer)
{
	container::iterator pCardPtr;
	container* mpCardsOnTable = pEnemyPlayer->GetCardsOnTable();
	for (unsigned i = 0; i < mpCardsOnTable->size(); i++)
	{
		if ((*mpCardsOnTable)[i]->GetName() == minionName)
		{
			return i;
		}
	}
	return -1;
}

int CMinion::GetOccurancesOfCard(string minionName, CPlayer* pCurrentPlayer)
{
	int sum = -1;	// begin from -1, as we do not include the attacking rat
					// only one rat in the game -> no bonus attack damage given
	container::iterator pCardPtrCurrentPlayer;
	container* mpCardsOnTableCurrentPlayer = pCurrentPlayer->GetCardsOnTable();
	for (unsigned i = 0; i < mpCardsOnTableCurrentPlayer->size(); i++)
	{
		if ((*mpCardsOnTableCurrentPlayer)[i]->GetName() == minionName)
		{
			sum++;
		}
	}
	return sum;
}

void CMinion::MinionDies(CMinion* pAttackedMinion, CPlayer* pEnemyPlayer, int enemyPosition)
{
	cout << pAttackedMinion->GetName() << " killed";
	// find the minion's position on the table
	unique_ptr<container> cardsOnTableOfEnemyPlayer =
		unique_ptr<container>(pEnemyPlayer->GetCardsOnTable());
	// and after remove the card from the player's hand
	(cardsOnTableOfEnemyPlayer.get())->erase
	((*cardsOnTableOfEnemyPlayer.get()).begin() + enemyPosition);
	cardsOnTableOfEnemyPlayer.release(); // release the ownership
}

void CMinion::UpdateMinionHealth(CMinion* pAttackedMinion, int enemyMinionUpdatedHp)
{
	pAttackedMinion->SetHealth(enemyMinionUpdatedHp);
	cout << pAttackedMinion->GetName() << " health now " << pAttackedMinion->GetHealth() << endl;
}

// getters
int CMinion::GetAttack() { return mAttackPoints; }
int CMinion::GetHealth() { return mHealthPoints; }
int CMinion::GetDefence() { return mDefencePoints; }
string CMinion::GetName() { return CCard::GetName(); }

// setters
void CMinion::SetAttack(int mAttackPoints) { this->mAttackPoints = mAttackPoints; }
void CMinion::SetHealth(int mHealthPoints) { this->mHealthPoints = mHealthPoints; }
void CMinion::SetDefence(int mDefencePoints) { this->mDefencePoints = mDefencePoints; }

