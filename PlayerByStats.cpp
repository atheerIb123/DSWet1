#include "PlayerByStats.h"

PlayerByStats::PlayerByStats()
{
    playerId = 0;
    teamId = nullptr;
    gamesPlayed = 0;
    goals = -1;
    cards = 0;
    goalKeeper = 0;
    gamesPlayedWithTeam = nullptr;
}

PlayerByStats::PlayerByStats(int playerId, std::shared_ptr<int>& teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, std::shared_ptr<int>& closest)
{
    this->playerId = playerId;
    this->teamId = teamId;
    this->gamesPlayed = gamesPlayed;
    this->goals = goals;
    this->cards = cards;
    this->goalKeeper = goalKeeper;
    this->gamesPlayedWithTeam = nullptr;
    this->closestId = closest;
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


int PlayerByStats::getGamesPlayed() const
{
	if (gamesPlayedWithTeam.get() != nullptr)
	{
		return gamesPlayed + *gamesPlayedWithTeam;
	}

	return gamesPlayed;
}

int PlayerByStats::getGoalsCount() const
{
	return goals;
}

int PlayerByStats::getCardsCount() const
{
	return this->cards;
}

void PlayerByStats::setGamesPlayedWithTeam(std::shared_ptr<int>& games)
{
	gamesPlayedWithTeam = games;
}

void PlayerByStats::setClosest(int playerId)
{
	*this->closestId = playerId;
}

/*void PlayerByStats::setClosestPtr(std::shared_ptr<int>& ptr)
{
	this->closestId = ptr;
}*/

int PlayerByStats::getClosest() const
{
    if(this->closestId.get() == nullptr)
    {
        return -1;
    }

	return *this->closestId;
}

bool PlayerByStats::isGk() const
{
	return this->goalKeeper;
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

void PlayerByStats::setTeamId(int newId)
{
    *this->teamId = newId;
}
