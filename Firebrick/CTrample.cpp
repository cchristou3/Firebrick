#include "CTrample.h"

CTrample::CTrample(string mName, int mAttack, int mHealth) : CMinion(mName, mAttack, mHealth) {  }

void CTrample::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	Attack(pEnemyPlayer, pCurrentPlayer,GetAttack());	
}

void CTrample::AttackEnemyMinion(CPlayer* pEnemyPlayer, int enemyPosition, int& excessDamage)
{
	CCard* pRandomEnemyCard =
		(pEnemyPlayer->GetSelectedCardFromTable(enemyPosition));
	CMinion* pAttackedMinion = (CMinion*)pRandomEnemyCard;
	cout << pAttackedMinion->GetName() << ": ";
	int allyMinionAttackPower = excessDamage;
	int enemyMinionCurrentHp = pAttackedMinion->GetHealth();
	int enemyMinionUpdatedHp = enemyMinionCurrentHp 
								+ pAttackedMinion->GetDefence()	// adding the protection as well
								- allyMinionAttackPower;
	if (enemyMinionUpdatedHp <= 0) // minion is removed from the table
	{		
		excessDamage = -enemyMinionUpdatedHp;		
		MinionDies(pAttackedMinion, pEnemyPlayer, enemyPosition);
		cout << endl;
	}
	else
	{
		excessDamage = 0;
		UpdateMinionHealth(pAttackedMinion, enemyMinionUpdatedHp);
	}
}

void CTrample::Attack(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer, int excessDamage)
{
	while (excessDamage > 0)
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
				AttackEnemyMinion(pEnemyPlayer, randomPositionOnEnemyTable, excessDamage);
			}
			else
			{
				AttackEnemyMinion(pEnemyPlayer, indexOfEnemyWall, excessDamage);
			}
		}
		else // if there are no enemy minions, it attacks the player's HP
		{
			cout << pEnemyPlayer->GetName() << ": ";
			int enemyPlayerCurrentHp = pEnemyPlayer->GetHealthPoints();
			int minionAttckPower = excessDamage;
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
			excessDamage = 0;
		}
	}	
}

inline void CTrample::ResetToInitialAttackPower()
{
	SetAttack(mInitialAttackPower);
}