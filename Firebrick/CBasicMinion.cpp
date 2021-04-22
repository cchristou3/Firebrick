#include "CBasicMinion.h"

CBasicMinion::CBasicMinion(string mName, int mAttack, int mHealth) : CMinion(mName, mAttack, mHealth) {  }

void CBasicMinion::Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	CMinion::Attack(enemyPlayer,currentPlayer);
}