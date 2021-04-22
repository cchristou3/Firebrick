#include "CLightning.h"
#include "CMinion.h"

CLightning::CLightning(string mName, int mAttackValue) : CSpell(mName, mAttackValue) {}

void CLightning::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	cout << "Lightning activated " << endl;
	int NumberOfCardsOnEnemyTable = pEnemyPlayer->GetNumberOfCardsOnTable();	
	// if the opponent has minions on his side of the table 
	if (NumberOfCardsOnEnemyTable > 0)
	{		
		for (int i = 0; i <= NumberOfCardsOnEnemyTable - 1; i++) // -1 because we start from 0	
		{
			CCard* pRandomEnemyCard =
				(pEnemyPlayer->GetSelectedCardFromTable(i));
			CMinion* pAttackedMinion = (CMinion*)pRandomEnemyCard;
			cout << "Lightning attacks " << pAttackedMinion->GetName() << ". ";
			int enemyMinionCurrentHp = pAttackedMinion->GetHealth();
			int lightningAttackPower = GetAttack();
			int enemyMinionUpdatedHp = enemyMinionCurrentHp
										+ pAttackedMinion->GetDefence()	// adding the protection as well
										- lightningAttackPower;
			if (enemyMinionUpdatedHp <= 0)
			{
				cout << pAttackedMinion->GetName() << " killed" << endl;
				// minion is removed from the table
				// find the minion's position on the table
				unique_ptr<container> cardsOnTableOfEnemyPlayer =
					unique_ptr<container>(pEnemyPlayer->GetCardsOnTable());
				// and after remove the card from the player's hand				
				(cardsOnTableOfEnemyPlayer.get())->erase
				((*cardsOnTableOfEnemyPlayer.get()).begin() + i);
				cardsOnTableOfEnemyPlayer.release();
				// update the number of enemies on the table + all available positions
				NumberOfCardsOnEnemyTable--; 
				i--;
			}
			else
			{
				// minions hp is updated
				pAttackedMinion->SetHealth(enemyMinionUpdatedHp);
				cout << pAttackedMinion->GetName() << " health now " << pAttackedMinion->GetHealth() << endl;				
			}			
		}
		// attack enemy player as well
		AttackEnemyPlayer(pEnemyPlayer);
	}
	else
	{
		// attack only the enemy player
		AttackEnemyPlayer(pEnemyPlayer);
	}
}

void CLightning::AttackEnemyPlayer(CPlayer* pEnemyPlayer)
{
	cout << "Lightning attacks " << pEnemyPlayer->GetName() << ". ";
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

