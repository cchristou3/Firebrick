#include "CSpell.h"

CSpell::CSpell(string mName, int mAttack): CCard(mName), mAttack(mAttack) {}

void CSpell::Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	// all subclasses will override this method
}

int CSpell::GetAttack() { return this->mAttack; }
void CSpell::SetAttack(int mAttack) { this->mAttack = mAttack; }