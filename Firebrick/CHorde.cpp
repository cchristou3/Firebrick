#include "CHorde.h"
CHorde::CHorde(string mName, int mAttack, int mHealth, int mAttackIncrement) :
	CMinion(mName, mAttack, mHealth), mAttackIncrement(mAttackIncrement),
	mInitialAttackPower(mAttack) {}

void CHorde::Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	ResetAttackIncrement(); // reset the minions attack power
	// check how many rats exist in the current player's table.
	int numberOfHordeMinionsOnCurrentPlayerTable = GetOccurancesOfCard(GetName(), currentPlayer);
	// i = 0 -> no other rats | 1 <= 0 -> not going inside the for loop
	for(int i = 1; i <= numberOfHordeMinionsOnCurrentPlayerTable; i++)
	{
		IncreaseAttack();
	}
	CMinion::Attack(enemyPlayer, currentPlayer);
}

inline void CHorde::IncreaseAttack()
{
	SetAttack(GetAttack() + mAttackIncrement);
}

inline void CHorde::ResetAttackIncrement()
{
	SetAttack(mInitialAttackPower);
}