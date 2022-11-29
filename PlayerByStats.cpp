#include "PlayerByStats.h"

PlayerByStats::PlayerByStats()
{
	playerId = 0;
	teamId = 0;
	gamesPlayed = 0;
	goals = 0;
	cards = 0;
	goalKeeper = 0;
}

PlayerByStats::PlayerByStats(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) :
	playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper)
{
}

void PlayerByStats::updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved)
{
	this->goals += scoredGoals;
	this->gamesPlayed += gamesPlayed;
	this->cards += cardsReceieved;
}

int PlayerByStats::getTeamId() const
{
	return this->teamId;
}

bool PlayerByStats::operator<(const PlayerByStats& other) const
{
	if (this->goals < other.goals)
	{
		return true;
	}
	else if (this->goals == other.goals)
	{
		if (this->cards > other.cards)
		{
			return true;
		}
		else if (this->cards == other.cards)
		{
			if (this->playerId < other.playerId)
			{
				return true;
			}
		}
	}

	return false;
}

bool PlayerByStats::operator>(const PlayerByStats& other) const
{
	if (this->goals > other.goals)
	{
		return true;
	}
	else if (this->goals == other.goals)
	{
		if (this->cards < other.cards)
		{
			return true;
		}
		else if (this->cards == other.cards)
		{
			if (this->playerId > other.playerId)
			{
				return true;
			}
		}
	}

	return false;
}

bool PlayerByStats::operator==(const PlayerByStats& other) const
{
	if (this->playerId == other.playerId)
	{
		return true;
	}

	return false;
}