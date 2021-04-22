#include "CBless.h"
#include "CMinion.h"
CBless::CBless(string mName, int mAttack): CSpell(mName,mAttack){}

void CBless::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	cout << "Bless activated " << endl;
	//enemy minions, enemy player, friendly minions, friendly player.
	int numOfCardsOnEnemyTable = pEnemyPlayer->GetNumberOfCardsOnTable();	
	int numOfCardsOnCurrentTable = pCurrentPlayer->GetNumberOfCardsOnTable();
	int numberOfAllPositionsInTheGame = numOfCardsOnEnemyTable + numOfCardsOnCurrentTable;
	// no need to add 2 for the positions of the players as we start from 0. 
	// E.g numOfCardsOnEnemyTable = 2, indexes -> dwarf [0], orc [1]. The last position is reserved for the player -> [2]
	int randomPositionInTheGame = Random(numberOfAllPositionsInTheGame - 1);

	if (randomPositionInTheGame <= (numberOfAllPositionsInTheGame - numOfCardsOnCurrentTable))
	{		
		// if the position is inside the enemy's side, inflict damge
		cout << "Bless inflicts damage to ";
		if (numOfCardsOnEnemyTable != 0)
		{
			// calculating who will get hit from enemy player + his minions combined
			// if generated number is the last one in this range, then it's the enemy player
			// orc dwarf wall ePlayer swordswinger spearcarrier Player = 7 positions
			// 0     1    2		3			4			5			6  = 6 indexes
			// orc dwarf wall = get size -> 3 | +1 player | swordswinger spearcarrier = get size -> 2 | +1 player
			// 
			if (randomPositionInTheGame == (numOfCardsOnEnemyTable))
			{
				// player's position
				AttackEnemyPlayer(pEnemyPlayer);
			}
			else
			{
				// the target is a minion
				CCard* pRandomEnemyCard =
					(pEnemyPlayer->GetSelectedCardFromTable(randomPositionInTheGame));
				CMinion* pAttackedMinion = (CMinion*)pRandomEnemyCard;
				cout << pAttackedMinion->GetName() << ". ";
				int enemyMinionCurrentHp = pAttackedMinion->GetHealth();
				int blessAttackPower = GetAttack();
				int enemyMinionUpdatedHp = enemyMinionCurrentHp
											+ pAttackedMinion->GetDefence()	// adding the protection as well
											- blessAttackPower;
				if (enemyMinionUpdatedHp <= 0)
				{
					cout << pAttackedMinion->GetName() << " killed" << endl;
					// minion is removed from the table
					// find the minion's position on the table
					unique_ptr<container> cardsOnTableOfEnemyPlayer =
						unique_ptr<container>(pEnemyPlayer->GetCardsOnTable());
					// and after remove the card from the player's hand					
					(cardsOnTableOfEnemyPlayer.get())->erase
					((*cardsOnTableOfEnemyPlayer.get()).begin() + randomPositionInTheGame);
					cardsOnTableOfEnemyPlayer.release();
				}
				else
				{
					// minions hp is updated
					pAttackedMinion->SetHealth(enemyMinionUpdatedHp);
					cout << pAttackedMinion->GetName() << " health now " << pAttackedMinion->GetHealth() << endl;				
				}				
			}
		}
		else
		{
			AttackEnemyPlayer(pEnemyPlayer);
		}
	}
	else
	{
		// if the position is inside the current player's side, heal
		cout << "Bless heals  ";
		if (numOfCardsOnCurrentTable != 0)
		{
			if (randomPositionInTheGame == numberOfAllPositionsInTheGame)
			{
				// player's position
				HealCurrentPlayer(pCurrentPlayer);
			}
			else
			{
				// the target is a minion
				unique_ptr<CCard> pRandomCurrentPlayerCard =
					unique_ptr<CCard>
					(pCurrentPlayer->GetSelectedCardFromTable(randomPositionInTheGame - (numOfCardsOnEnemyTable + 1)));
				// down-casting it to an object of type CMinion
				CMinion* pHealedMinion = dynamic_cast<CMinion*>(pRandomCurrentPlayerCard.get());
				unique_ptr<CMinion> pFriendlyHealedMinion;
				if (pHealedMinion != nullptr)
				{
					pRandomCurrentPlayerCard.release();
					pFriendlyHealedMinion.reset(pHealedMinion);
				}
				cout << pFriendlyHealedMinion->GetName() << ". ";
				int friendlyMinionCurrentHp = pFriendlyHealedMinion->GetHealth();
				int blessHealingPower = GetAttack();
				int friendlyMinionUpdatedHp = friendlyMinionCurrentHp + blessHealingPower;
				// minion's hp is updated
				pFriendlyHealedMinion->SetHealth(friendlyMinionUpdatedHp);
				cout << pFriendlyHealedMinion->GetName() << " health now " << pFriendlyHealedMinion->GetHealth() << endl;
				pFriendlyHealedMinion.release();
			}			
		}
		else
		{
			HealCurrentPlayer(pCurrentPlayer);
		}
	}
}

void CBless::AttackEnemyPlayer(CPlayer* pEnemyPlayer)
{
	cout <<  pEnemyPlayer->GetName() << ". ";
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

void CBless::HealCurrentPlayer(CPlayer* pCurrentPlayer)
{
	cout << pCurrentPlayer->GetName() << ". ";
	int currentPlayerCurrentHp = pCurrentPlayer->GetHealthPoints();
	int spellHealingPower = GetAttack(); // access the amount of attack/healing power of the spell
	int currentPlayerUpdatedHp = currentPlayerCurrentHp + spellHealingPower;

	pCurrentPlayer->SetHealthPoints(currentPlayerUpdatedHp);
	cout << pCurrentPlayer->GetName() << " health now " << pCurrentPlayer->GetHealthPoints() << endl;
	
}
