#pragma once
#include "CCard.h"
#include "CPlayer.h"
class CEquipment :
	public CCard
{
private:
	int mEquipmentValue;
	int mHealingAmount = 2; // all equipment sub-classes heal the same portion
public:
	// Constructor of the class CEquipment, parameters: the name of the card + a generic value that all equipement cards have
	// Initializes the name and the equipement points of the card
	CEquipment(string mName, int mEquipmentValue);

	// Default destructor
	~CEquipment() = default;

	// Changes the characteristics of a friendly minion
	// If no friendly minion is on the table then increases the health of the controlling player by 2
	// Parameters: both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override; // all subclasses will override this method

	// Returns true if the controlling player has minions in his/her table, otherwise returns false
	// Parameter: the controlling player
	bool CheckForFriendlyMinions(CPlayer* pCurrentPlayer);

	// Returns the value of the equipement card
	int GetEquipmentValue();

	// Returns the amount of the healing 
	int GetHealingAmount();

	// Increases the health of the controlling player, parameter: the controlling player
	void HealCurrentPlayer(CPlayer* pCurrentPlayer);
};

