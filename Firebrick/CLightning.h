#pragma once
#include "CSpell.h"
class CLightning :
	public CSpell
{
public:
	// Constructor of the class CLightning, parameters: name of the card + its attack points
	// Initializes the name and the attack points of the card
	CLightning(string mName, int mAttack);

	// Default destructor
	~CLightning() = default;

	// Causes 1 point of damage to all enemies, including the enemy player. Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;

	// Causes damage to the enemy player. Parameter: the enemy players
	void AttackEnemyPlayer(CPlayer* enemyPlayer);
};

