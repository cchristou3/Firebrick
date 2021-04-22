#pragma once
#include "CCard.h"
class CSpell :
	public CCard
{	
private:
	int mAttack;
public:
	// Constructor, parameters: name of the card + its attack points
	// Initializes the name and the attack points of the card
	CSpell(string mName, int mAttack);

	// Default constructor
	CSpell() = default;

	// Virtual default destructor, recursively calls the destructors of all its subclasses
	virtual ~CSpell() = default;

	// Changes the health points of minions + players, either heals or damages, depending on spell card
	// Parameters: both players
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)override; // all subclasses will override this method

	// Returns the attack points of the spell
	int GetAttack();

	// Sets the attack points of the spell. Parameter: the attack points
	void SetAttack(int mAttack);
};

