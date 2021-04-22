#pragma once
#include "CSpell.h"
#include "CPlayer.h"
class CFireball :
	public CSpell
{
public:
	// Constructor of the class CFireball, parameters: name of the card + the attack points
	// Initializes the name and the attack points of the card
	CFireball(string mName,int mAttack);

	// Default destructor
	~CFireball() = default;

	// Causes 3 points of damage.
	// Can be directed at minion or player. Chooses a target at random. Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;

	// Causes damage to the enemy player. Parameter: the enemy player
	void AttackEnemyPlayer(CPlayer* enemyPlayer);
};

