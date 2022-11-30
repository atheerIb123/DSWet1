#include "PlayerByStats.h"

PlayerByStats::PlayerByStats()
{
	playerId = 0;
	teamId = nullptr;
	gamesPlayed = 0;
	goals = 0;
	cards = 0;
	goalKeeper = 0;
	gamesPlayedWithTeam = nullptr;
}

PlayerByStats::PlayerByStats(int playerId, std::shared_ptr<int> teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) :
	playerId(playerId), teamId(std::move(teamId)), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper), gamesPlayedWithTeam(nullptr)
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
	return *(this->teamId);
}

int PlayerByStats::getPlayerId() const
{
	return this->playerId;
}

void PlayerByStats::setTeamId(int newId)
{
	*(this->teamId) = newId;
}

int PlayerByStats::getGamesPlayed() const
{
	if (gamesPlayedWithTeam != nullptr)
	{
		return gamesPlayed + *gamesPlayedWithTeam;
	}

	return gamesPlayed;
}

void PlayerByStats::setGamesPlayedWithTeam(std::shared_ptr<int> games)
{
	gamesPlayedWithTeam = games;
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