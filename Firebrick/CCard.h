#pragma once
#include <string>
#include <vector>
using namespace std;
class CPlayer;
class CCard
{
private:
	string mName;
public:
	// Constructor of the class CCard, takes as parameters: the name of the card
	// Initializes the name of the card
	CCard(string mName);

	// Default contructor
	CCard() = default;

	// Virtual destructor, in order to recurively call all destructors of the subclasses
	virtual ~CCard();

	// Sets the name of the card, parameter: the name of the card
	void SetName(string mName);

	// Returns the name of the card
	string GetName();

	// Returns a random number in the range 0 ..n, inclusive.
	// Paramater: a constant integer.
	int Random(const int n);
	
	// This method will get overriden by all the subclasses.
	// Each of one has different implementation.
	// Parapeters: both players
	virtual void Activate(CPlayer* pEnemyPlayer, CPlayer* pCurrentPlayer);
};