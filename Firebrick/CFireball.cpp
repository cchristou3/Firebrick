#include "CFireball.h"
#include "CMinion.h"

CFireball::CFireball(string mName, int mAttackValue): CSpell(mName,mAttackValue) {}

void CFireball::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	cout << "Fireball attacks ";
	int numOfCardsOnEnemyTable = pEnemyPlayer->GetNumberOfCardsOnTable();
	int randomEnemyPosition = Random(numOfCardsOnEnemyTable - 1 + 1);	// -1 because we start from 0
																// and +1 because we add 
																//the enemy Player as well
	if (pEnemyPlayer->GetNumberOfCardsOnTable() > 0)
	{
		if (randomEnemyPosition < numOfCardsOnEnemyTable)
		{
			CCard* pRandomEnemyCard =
				(pEnemyPlayer->GetSelectedCardFromTable(randomEnemyPosition));
			CMinion* pAttackedMinion = (CMinion*)pRandomEnemyCard;
			cout << pAttackedMinion->GetName() << ". ";
			int enemyMinionCurrentHp = pAttackedMinion->GetHealth();
			int fireballAttackPower = GetAttack();
			int enemyMinionUpdatedHp = enemyMinionCurrentHp
										+ pAttackedMinion->GetDefence()	// adding the protection as well
										- fireballAttackPower;
			if (enemyMinionUpdatedHp <= 0)
			{
				cout << pAttackedMinion->GetName() << " killed" << endl;
				// minion is removed from the table
				// find the minion's position on the table
				unique_ptr<container> cardsOnTableOfEnemyPlayer =
					unique_ptr<container>(pEnemyPlayer->GetCardsOnTable());
				// and after remove the card from the player's hand				
				(cardsOnTableOfEnemyPlayer.get())->erase
				((*cardsOnTableOfEnemyPlayer.get()).begin() + randomEnemyPosition);
				cardsOnTableOfEnemyPlayer.release();
			}
			else
			{
				// minions hp is updated
				pAttackedMinion->SetHealth(enemyMinionUpdatedHp);
				cout << pAttackedMinion->GetName() << " health now " << pAttackedMinion->GetHealth() << endl;				
			}			
		}
		else
		{// attack the enemy player by randomness
			AttackEnemyPlayer(pEnemyPlayer);
		}
	}
	else
	{// attack the enemy player because there are no minions of his side of the table
		AttackEnemyPlayer(pEnemyPlayer);
	}
}

void CFireball::AttackEnemyPlayer(CPlayer* pEnemyPlayer)
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

