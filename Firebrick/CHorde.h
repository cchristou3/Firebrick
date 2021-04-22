#pragma once
#include "CMinion.h"
class CHorde :
	public CMinion
{
private:
	int mAttackIncrement;
	int mInitialAttackPower;

public:
	// Constructor of the class CHorde, parameters: attack points, health points,amount of incrementing attack points
	// Initializes the name, the attack points, the health points and the amount of incrementing attack points of the minion.
	CHorde(string mName, int mAttack, int mHealth, int mAttackIncrement);

	// Default destructor
	~CHorde() = default;

	// For each Rat on the table, increase the attack of the Rat by 1.
	// Afterwards, it attacks a random enemy minion or the enemy player if there are no minions.
	// Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;

	// Incremenets the attack points of the minion
	void IncreaseAttack();

	// Resets its attack points back to the initial value
	void ResetAttackIncrement();
};

