#include "PlayerById.h"
#include "PlayerById.h"

PlayerById::PlayerById()
{
	playerId = 0;
	teamId = 0;
	gamesPlayed = 0;
	goals = 0;
	cards = 0;
	goalKeeper = 0;
}

PlayerById::PlayerById(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) :
	playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper)
{
}

void PlayerById::updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved)
{
	this->goals += scoredGoals;
	this->gamesPlayed += gamesPlayed;
	this->cards += cardsReceieved;
}

int PlayerById::getTeamId() const
{
	return this->teamId;
}

int PlayerById::getGoalsCount() const
{
	return this->goals;
}

int PlayerById::getCardsCount() const
{
	return this->cards;
}

int PlayerById::getGamesPlayed() const
{
	return this->gamesPlayed;
}

bool PlayerById::isGoalKeeper() const
{
	return this->goalKeeper;
}

bool PlayerById::operator<(const PlayerById& other) const
{
	if (this->playerId < other.playerId)
	{
		return true;
	}

	return false;
}

bool PlayerById::operator>(const PlayerById& other) const
{
	if (this->playerId > other.playerId)
	{
		return true;
	}

	return false;
}

bool PlayerById::operator==(const PlayerById& other) const
{
	if (this->playerId == other.playerId)
	{
		return true;
	}

	return false;
}

