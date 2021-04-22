#pragma once
#include "CMinion.h"
class CWall :
	public CMinion
{
public:
	// Default constructor
	CWall() = default;

	// 2nd constructor, parameters: name of the card, its attack points and its health points
	// Initializes the name, the attack points and the health points of the card
	CWall(string mName, int mAttack, int mHealth);

	// Default destructor
	~CWall() = default;

	// If it has attack power it attacks, otherwise it does nothing
	void Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer);
};

