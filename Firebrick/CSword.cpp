#include "CSword.h"
#include "CMinion.h"

CSword::CSword(string mName, int mAttackValue): CEquipment(mName,mAttackValue){}

void CSword::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	cout << "Sword activated " << endl;
	bool anyFriendlyMinions = CheckForFriendlyMinions(pCurrentPlayer);
	if (anyFriendlyMinions)
	{
		
		int numOfCardsOnCurrentTable = pCurrentPlayer->GetNumberOfCardsOnTable();
		int randomFriendlyMinionPosition = Random(numOfCardsOnCurrentTable - 1); // -1 because we start from 0
		// pick the random friendly minion
		unique_ptr<CCard> pRandomFriendlyCard = 
			unique_ptr<CCard>(pCurrentPlayer->GetSelectedCardFromTable(randomFriendlyMinionPosition));
		// down-casting it to an object of type CMinion
		CMinion* pChosenFriendlyMinionCard = dynamic_cast<CMinion*>(pRandomFriendlyCard.get());
		unique_ptr<CMinion> pChosenFriendlyMinion;
		if (pChosenFriendlyMinionCard != nullptr)
		{
			pRandomFriendlyCard.release();
			pChosenFriendlyMinion.reset(pChosenFriendlyMinionCard);
		}
		// increase its attack by  an amount
		IncreaseAttackValue(std::move(pChosenFriendlyMinion));		
	}
	else
	{
		HealCurrentPlayer(pCurrentPlayer);
		cout << "Sword heals " << pCurrentPlayer->GetName() << ". " << pCurrentPlayer->GetName() << " health now "
			<< pCurrentPlayer->GetHealthPoints() << endl;
	}
}

void CSword::IncreaseAttackValue(unique_ptr<CMinion> pChosenFriendlyMinion)
{
	int chosenMinionCurrentAttackValue = pChosenFriendlyMinion->GetAttack();
	int attackValue = GetEquipmentValue();
	int chosenMinionUpdatedAttackValue = chosenMinionCurrentAttackValue + attackValue;
	pChosenFriendlyMinion->SetAttack(chosenMinionUpdatedAttackValue);
	cout << "Sword increases attack value of "
		<< pChosenFriendlyMinion->GetName() << ".  " << pChosenFriendlyMinion->GetName() << "'s attack value now "
		<< pChosenFriendlyMinion->GetAttack() << endl;
	pChosenFriendlyMinion.release(); // release the ownership
}


