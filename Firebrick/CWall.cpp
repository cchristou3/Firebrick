#include "CWall.h"

CWall::CWall(string mName, int mAttack, int mHealth): CMinion(mName,mAttack,mHealth){}

void CWall::Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	if (GetAttack() <= 0)
	{
		cout << GetName() <<" does not attack, it has no attack points" << endl;
	}
	else
	{ 
		// scenario: Card Sword was used on it
		CMinion::Attack(enemyPlayer, currentPlayer);
	}
}
