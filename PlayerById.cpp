#include "PlayerById.h"
#include "Team.h"

PlayerById::PlayerById()
{
	playerId = 0;
	teamId = nullptr;
	gamesPlayed = 0;
	goals = 0;
	cards = 0;
	goalKeeper = 0;
	gamesPlayedWithTeam = nullptr;
}

PlayerById::PlayerById(int playerId, std::shared_ptr<int>& teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) :
	playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper), gamesPlayedWithTeam(nullptr)
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
	return *(this->teamId);
}

void PlayerById::setTeamId(int newId)
{
	*(this->teamId) = newId;
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
	if (gamesPlayedWithTeam.get() != nullptr)
	{
		return gamesPlayed + *this->playerTeam->gamesPlayedPtr();
	}

	return gamesPlayed;
}

bool PlayerById::isGoalKeeper() const
{
	return this->goalKeeper;
}

void PlayerById::setGamesPlayedWithTeam(std::shared_ptr<int>& games)
{
	this->gamesPlayedWithTeam = games;
}

bool PlayerById::operator<(const PlayerById& other) const
{   if (this->playerId < other.playerId)
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

void PlayerById::setTeamPtr(std::shared_ptr<int> &id)
{
    this->teamId = id;
}

void PlayerById::setPlayerTeam(std::shared_ptr<Team>& t)
{
    this->playerTeam = t;
}
std::shared_ptr<Team>& PlayerById::getPlayerTeam()
{
    return this->playerTeam;
}

void PlayerById::changeTeam(Team &t)
{
    *this->playerTeam = t;
}

void PlayerById::decGames(int amount)
{
    this->gamesPlayed -= amount;
}

int PlayerById::getGamesPlayedWTeam() {
    return *this->gamesPlayedWithTeam;
}

void PlayerById::setGamesPlayedWhenJoined(int amount)
{
    this->gamesPlayedWhenJoinedTeam = amount;
}

