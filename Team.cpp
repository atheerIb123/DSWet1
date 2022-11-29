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
    PlayerByStats newPlayerSt(playerId, this->teamId, gamesPlayed, goals, cards, gk);
    PlayerById newPlayerId(playerId, this->teamId, gamesPlayed, goals, cards, gk);

    if (!teamTreeByStats.insert(newPlayerSt) || !teamTreeById.insert(newPlayerId))
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
    PlayerByStats tempPlayerSt(playerId, this->teamId, 0, 0, 0, false);
    PlayerById tempPlayerId(playerId, this->teamId, 0, 0, 0, false);

    Node<PlayerByStats>* tempSt = teamTreeByStats.find(teamTreeByStats.getRoot(), tempPlayerSt);
    Node<PlayerById>* tempId = teamTreeById.find(teamTreeById.getRoot(), tempPlayerId);

    if (!tempSt || !tempId)
    {
        return false;
    }

    Node<PlayerByStats>* toRemoveSt = teamTreeByStats.remove(*(tempSt->data));
    Node<PlayerById>* toRemoveId = teamTreeById.remove(*(tempId->data));

    if (this->totalPlayers == 1 && (toRemoveId != nullptr || toRemoveSt != nullptr))
    {
        return false;
    }

    this->totalPlayers--;

    if (toRemoveId != nullptr)
    {
        this->totalCards -= toRemoveId->data->getCardsCount();
        this->totalGoals -= toRemoveId->data->getGoalsCount();

        if (toRemoveId->data->isGoalKeeper() == true)
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

int Team::getID() const
{
    return this->teamId;
}

void Team::getPlayersDetails(PlayerByStats* const out)
{
    int index = 0;
    this->teamTreeByStats.inOrder(teamTreeByStats.getRoot(), out, index);
}

bool Team::hasGoalKeeper() const
{
    if (this->goalKeepers[0])
        return true;
    return false;
}

Node<Player>* Team::findPlayer(Player p)
{
    return this->teamTree.find(teamTree.getRoot(), p);
}




bool Team::operator<(const Team& other) const
{
    if (this->teamId < other.teamId)
    {
        return true;
    }
    return false;
}

bool Team::operator>(const Team& other) const
{
    if (this->teamId > other.teamId)
    {
        return true;
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