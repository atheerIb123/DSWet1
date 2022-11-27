#include "Team.h"

Team::Team(int teamId, int points) : teamId(teamId), points(points)
{
    this->goalKeepers[0] = 0;
    this->goalKeepers[1] = 0;
    this->topScorerId = 0;
    this->totalCards = 0;
    this->totalGamesPlayed = new int(0);
    this->totalGoals = 0;
    this->totalPlayers = 0;
}

bool Team::insertPlayer(int playerId, int gamesPlayed, int goals, int cards, bool gk)
{
    Player newPlayer(playerId, this->teamId, gamesPlayed, goals, cards, gk);
    
    if (!teamTree.insert(newPlayer))
    {
        return false;
    }

    if (gk == true)
    {
        this->goalKeepers[0] = 1;
        this->goalKeepers[1]++;
    }

    this->totalPlayers++;
    this->totalCards += cards;
    this->totalGoals += goals;

    return true;
}

bool Team::removePlayer(int playerId)
{
    Player tempPlayer(playerId, 0, 0, 0, 0, false);
    Node<Player>* temp = teamTree.find(teamTree.getRoot(), tempPlayer);

    if (!temp)
    {
        return false;
    }

    Node<Player>* toRemove = teamTree.remove(*(temp->data));
    
    if (this->totalPlayers == 1 && toRemove != nullptr)
    {
        return false;
    }

    this->totalPlayers--;

    if (toRemove != nullptr)
    {
        this->totalCards -= toRemove->data->pStats.cards;
        this->totalGoals -= toRemove->data->pStats.goals;

        if (toRemove->data->pStats.goalKeeper == true)
        {
            if (this->goalKeepers[1] == 1)
            {
                this->goalKeepers[0] = 0;
            }
            if (this->goalKeepers[1] >= 1)
            {
                this->goalKeepers[1]--;
            }
        }
    }

    return true;
}

int Team::getTeamPoints() const
{
    return this->points;
}

void Team::addPoints(int points)
{
    this->points += points;
}

int Team::getTopScorer() const
{
    return this->topScorerId;
}

int Team::getTeamPower() const
{
    int power = this->points + (this->totalGoals - this->totalCards);
    return power;
}

int Team::getPlayersCount() const
{
    return this->totalPlayers;
}

void Team::getPlayerDetails(Player* const out)
{
    int index = 0;
    this->teamTree.inOrder(teamTree.getRoot(), out, index);
}


bool Team::operator<(const Team& other) const
{
    if (this->getTeamPower() < other.getTeamPower())
    {
        return true;
    }
    else if (this->getTeamPower() == other.getTeamPower())
    {
        if (this->teamId < other.teamId)
        {
            return true;
        }
    }

    return false;
}

bool Team::operator>(const Team& other) const
{
    if (this->getTeamPower() > other.getTeamPower())
    {
        return true;
    }
    else if (this->getTeamPower() == other.getTeamPower())
    {
        if (this->teamId > other.teamId)
        {
            return true;
        }
    }

    return false;
}

bool Team::operator==(const Team& other) const
{
    if (this->teamId == other.teamId)
    {
        return true;
    }

    return false;
}

