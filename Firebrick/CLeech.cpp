#include "CLeech.h"

CLeech::CLeech(string mName, int mAttack, int mHealth, int mHealAmount) :
	CMinion(mName, mAttack, mHealth), mHealAmount(mHealAmount) {}

void CLeech::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	CMinion::Attack(pEnemyPlayer, pCurrentPlayer);

	// heal the owner of this minion
	HealOwner(pCurrentPlayer);
}

void CLeech::HealOwner(CPlayer* pCurrentPlayer)
{
	int healthOfCurrentPlayer = pCurrentPlayer->GetHealthPoints();
	int heallingAmount = GetHealAmount();
	int healthOfUpdatedPlayer = healthOfCurrentPlayer + heallingAmount;
	pCurrentPlayer->SetHealthPoints(healthOfUpdatedPlayer);
}

int CLeech::GetHealAmount() { return this->mHealAmount; }

