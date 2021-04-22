#include "CEquipment.h"

CEquipment::CEquipment(string mName, int mEquipmentValue):
	CCard(mName), mEquipmentValue(mEquipmentValue) {}

void CEquipment::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	// subclasses will override this method
}

bool CEquipment::CheckForFriendlyMinions(CPlayer* pCurrentPlayer)
{
	if (pCurrentPlayer->GetCardsOnTable()->size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CEquipment::HealCurrentPlayer(CPlayer* pCurrentPlayer)
{
	int playerCurrentHp = pCurrentPlayer->GetHealthPoints();
	int healingAmount = GetHealingAmount();
	int playerUpdatedHp = playerCurrentHp + healingAmount;
	pCurrentPlayer->SetHealthPoints(playerUpdatedHp);
}

int CEquipment::GetEquipmentValue() { return this->mEquipmentValue; }

int CEquipment::GetHealingAmount() { return this->mHealingAmount; }
