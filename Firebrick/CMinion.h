#pragma once
#include <vector>
#include "CCard.h"
#include "CPlayer.h"
class CMinion :
	public CCard
{
private:
	int mAttackPoints;
	int mHealthPoints;
	int mDefencePoints;	

public:
	// Default constructor
	CMinion() = default;

	// 2nd constructor, parameters: name, attack points and health points of the minion
	// Initializes the name, the attack points, the health points of the card
	CMinion(string mName, int mAttack, int mHealth);

	// Destructor
	~CMinion();	

	// Minion get removed from the game. Parameters: both players and the position of the enemy minion on the table
	void MinionDies(CMinion* pAttackedMinion, CPlayer* pEnemyPlayer, int enemyPosition);

	// Minion's health gets updated. Parameters: the attacked minion and its updated health points
	void UpdateMinionHealth(CMinion* pAttackedMinion, int enemyMinionUpdatedHp);

	// Getters for attack points, health points, defence points and the name of a minion
	int GetAttack();
	int GetHealth();
	int GetDefence();
	string GetName();

	// Setters for the attack points, health points and defence points of a minion
	void SetAttack(int mAttackPoints);
	void SetHealth(int mHealthPoints);
	void SetDefence(int mDefencePoints);

	// This method gets overriden by its subclasses, the body is empty in this class
	// Parameters: both players
	void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer)override;

	// The minion chooses a random enemy minion to attack.
	// If there are no enemy minions, it attacks the player. Parameters: both players
	void Attack(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer);

	// Minion atttacks an enemy minion. Parameters: the enemy player and the position of an enemy in the game
	void AttackEnemyMinion(CPlayer* pEnemyPlayer, int enemyPosition);

	// Returns the index of the minion in the table if found. Otherwise returns -1
	// Parameters: the enemy player and the name of the minion
	int FindMinion(string minionName, CPlayer* pEnemyPlayer);

	// Counts how many times a minion name exists within the controlling player's table.
	// Parameters: the controlling player and the name of a minion card
	int GetOccurancesOfCard(string minionName, CPlayer* pCurrentPlayer);
};

