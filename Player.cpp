#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) : 
		pStats(playerId, teamId, gamesPlayed, goals, cards, goalKeeper) 
{
}

void Player::updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved)
{
	pStats.goals += scoredGoals;
	pStats.gamesPlayed += gamesPlayed;
	pStats.cards += cardsReceieved;
}

bool Player::operator<(const Player& other) const
{
	if (this->pStats.goals < other.pStats.goals)
	{
		return true;
	}
	else if (this->pStats.goals == other.pStats.goals)
	{
		if (this->pStats.cards > other.pStats.cards)
		{
			return true;
		}
		else if (this->pStats.cards == other.pStats.cards)
		{
			if (this->pStats.playerId < other.pStats.playerId)
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::operator>(const Player& other) const
{
	if (this->pStats.goals > other.pStats.goals)
	{
		return true;
	}
	else if (this->pStats.goals == other.pStats.goals)
	{
		if (this->pStats.cards < other.pStats.cards)
		{
			return true;
		}
		else if (this->pStats.cards == other.pStats.cards)
		{
			if (this->pStats.playerId > other.pStats.playerId)
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::operator==(const Player& other) const
{
	if (this->pStats.playerId == other.pStats.playerId)
	{
		return true;
	}

	return false;
}

