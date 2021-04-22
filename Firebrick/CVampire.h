#pragma once
#include "CMinion.h"
class CVampire :
	public CMinion
{
private:
	int mHealAmount;

public:
	// Constructor, parameters: name of the card, its attack points, its health points and healling amount
	// Initializes the name, the attack points, the health points and the healing amount of the card
	CVampire(string mName, int mAttack, int mHealth, int mHealAmount);

	// Default destructor
	~CVampire() = default;
	
	// It attacks and it increases its health by 1. Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override;

	// Getters
	string GetName(); // returns the name of the minion
	int GetHealAmount(); // returns the amount of health that is going to be restored

	// Restores health to itself
	void HealMinionItself();
};

