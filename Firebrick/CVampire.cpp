#include "CVampire.h"

CVampire::CVampire(string mName, int mAttack, int mHealth, int mHealAmount):
	CMinion(mName, mAttack, mHealth), mHealAmount(mHealAmount) {}

void CVampire::Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)
{
	CMinion::Attack(pEnemyPlayer, pCurrentPlayer);

	//increase health points of the minion itself
	HealMinionItself();
}

void CVampire::HealMinionItself()
{
	int healthOfCurrentMinion = GetHealth();
	int heallingAmount = GetHealAmount();
	int healthOfUpdatedMinion = healthOfCurrentMinion + heallingAmount;
	SetHealth(healthOfUpdatedMinion);
}

string CVampire::GetName() 
{
	// accessing the base class data member through one of its methods
	return CCard::GetName();
}

int CVampire::GetHealAmount() { return this->mHealAmount; }
