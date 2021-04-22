#pragma once
#include "CMinion.h"
class CLeech :
	public CMinion
{
private:
	int mHealAmount;

public:
	// Constructor of the class CLeech, parameters: attack points, health points, amount of the healing points of the minion
	// Initializes the name, the attack points, the health points and the healing amount of the card
	CLeech(string mName, int mAttack, int mHealth, int mHealAmount);

	// Default destructor
	~CLeech() = default;

	// Returns the healing amount
	int GetHealAmount();

	// It attacks and 2 points of health are restored to its controlling player. Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;	

	// Restores health points to its controlling player. Parameter: controlling player
	void HealOwner(CPlayer* currentPlayer);
};

