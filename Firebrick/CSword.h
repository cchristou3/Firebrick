#pragma once
#include "CEquipment.h"
#include "CMinion.h"
class CSword :
	public CEquipment
{
public:
	// Constructor, parameters: name of the card + its attack points
	// Initializes the name and the attack value of the card
	CSword(string mName, int mAttackValue);

	// Default constructor
	~CSword() = default;

	// Increases the attack value of a friendly minion by 2
	// If there are no friendly minions on the table, then increases the health of the player by 2.
	// Parameters: both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override; // all subclasses will override this method

	// Increases the attack value of a friendly minion. Parameter: the chosen friendly minion
	void IncreaseAttackValue(unique_ptr<CMinion> pChosenFriendlyMinion);
};

