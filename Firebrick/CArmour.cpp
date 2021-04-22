#include "CArmour.h"
#include "CMinion.h"

CArmour::CArmour(string mName, int mDefenceValue):CEquipment(mName, mDefenceValue) {}


void CArmour::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	cout << "Armour activated" << endl;
	bool anyFriendlyMinions = CheckForFriendlyMinions(pCurrentPlayer);
	if (anyFriendlyMinions) // add defence points to a friendly minion
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
		IncreaseDefence(std::move(pChosenFriendlyMinion));
	}
	else
	{
		HealCurrentPlayer(pCurrentPlayer);
		cout << "Armour heals " << pCurrentPlayer->GetName() << ". " << pCurrentPlayer->GetName() << " health now "
			<< pCurrentPlayer->GetHealthPoints() << endl;
	}
}

void CArmour::IncreaseDefence(unique_ptr<CMinion> pChosenFriendlyMinion)
{
	int minionInitialDefencePoints = pChosenFriendlyMinion->GetDefence();
	int additionalDefencePoints = this->GetEquipmentValue();
	int minionUpdatedDefencePoints = minionInitialDefencePoints + additionalDefencePoints;
	pChosenFriendlyMinion->SetDefence(minionUpdatedDefencePoints);
	cout << "Armour increases defence points of "
		<< pChosenFriendlyMinion->GetName() << ".  " << pChosenFriendlyMinion->GetName() << "'s defence points now "
		<< pChosenFriendlyMinion->GetDefence() << endl;
	pChosenFriendlyMinion.release();	// releasing the ownership
}