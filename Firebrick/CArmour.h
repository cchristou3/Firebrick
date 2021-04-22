#pragma once
#include "CEquipment.h"
#include "CMinion.h"
class CArmour :
	public CEquipment
{
public:
	// Constructor of the class CArmour, takes as parameters: the name of the card + the defence points.
	// Initializes the name of the card and the defence points it offers when activated.
	CArmour(string mName, int mDefenceValue);

	// Default destructor
	~CArmour() = default;

	// The card increases the defence points of a friendly minion.
	// The more defence points a minion has the less damage it takes.	
	// If there are no minions on the controlling player's table it heals the controlling player.
	// Parameters: Both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override;

	// Increases the defence points of the minion, parameter: A pointer that points to the address of a friendly minion
	// The effect stays until the minion dies
	// Parameter: the chosen friendly minion
	void IncreaseDefence(unique_ptr<CMinion> pChosenFriendlyMinion);
};

