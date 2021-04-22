#pragma once
#include <vector>
#include "CMinion.h"
class CBasicMinion :
	public CMinion
{
private:

public:
	// Constructor, parameters: name of the card, its attack points and its health points.
	// Initializes the name, the attack points and the health points  of the minion.
	CBasicMinion(string mName, int mAttack, int mHealth);

	// Default destructor
	~CBasicMinion() = default;

	// The friendly minion attacks a random enemy minion. If there are no enemy minions, it attacks the enemy player instead.
	// Parameters: both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override;
};

