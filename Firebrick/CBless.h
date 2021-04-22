#pragma once
#include "CSpell.h"
#include "CBless.h"
class CBless :
	public CSpell
{
private:
public:
	// Constructor of the class CBless, takes as parameters: the name of the card + the attack/healing points	
	CBless(string mName, int mAttack);

	// default destructor
	~CBless() = default; 

	// the card either increases the health points of a friendly minion or the controlling player
	// OR  inflicts damage to an enemy minion or the enemy player
	// parameters: Both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override;

	// inflicts damage to the enemy player, parameter: the enemy player
	void AttackEnemyPlayer(CPlayer* pEnemyPlayer);

	// increases the health points to the controlling player, parameter: the controlling player
	void HealCurrentPlayer(CPlayer* pCurrentPlayer);
};

