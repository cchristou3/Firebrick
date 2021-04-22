#pragma once
#include "CMinion.h"
class CTrample :
	public CMinion
{
private:
	int mInitialAttackPower;

public:
	// Constructor, parameters: name of the card, its attack points and its health points
	// Initializes the name, the attack points and the health points of the card
	CTrample(string mName, int mAttack, int mHealth);

	// Default destructor
	~CTrample() = default;

	// If a minion with the trample ability kills an enemy minion,
	// then it selects a new target at random and inflicts any excess damage on the new target.
	// This process continues until the minion has no excess damage left to apply
	// Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;

	// Attacks a random enemy minion. Parameters: the enemy player, the position of the enemy minion on the table
	// and the exccessive damage that is left after the attack.
	void AttackEnemyMinion(CPlayer* enemyPlayer, int enemyPosition, int& excessDamage);

	// Resets it attack power to the initial one
	void ResetToInitialAttackPower();

	// Contains all the statements for the attack
	void Attack(CPlayer* enemyPlayer, CPlayer* currentPlayer, int excessDamage);
};

