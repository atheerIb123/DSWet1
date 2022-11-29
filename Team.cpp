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
    PlayerById tempPlayerId(playerId, this->teamId, 0, 0, 0, false);

    Node<PlayerById>* tempId = teamTreeById.find(teamTreeById.getRoot(), tempPlayerId);
    PlayerByStats tempPlayerSt(playerId, this->teamId, tempId->data->getGamesPlayed(), tempId->data->getGoalsCount(), tempId->data->getCardsCount(), tempId->data->isGoalKeeper());
    Node<PlayerByStats>* tempSt = teamTreeByStats.find(teamTreeByStats.getRoot(), tempPlayerSt);

    if (!tempSt || !tempId)
    {
        return false;
    }

    int goals = tempId->data->getGoalsCount(), cards = tempId->data->getCardsCount();
    bool gk = tempId->data->isGoalKeeper();

    Node<PlayerByStats>* toRemoveSt = teamTreeByStats.remove(*(tempSt->data));
    Node<PlayerById>* toRemoveId = teamTreeById.remove(*(tempId->data));

    if (this->totalPlayers == 1 && (toRemoveId != nullptr || toRemoveSt != nullptr))
    {
        return false;
    }

    this->totalPlayers--;

    if (toRemoveId != nullptr)
    {
        this->totalCards -= cards;
        this->totalGoals -= goals;

        if (gk == true)
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

void Team::updatePlayerStatsInTeam(PlayerByStats& p, int playerId, int gamesToAdd, int goalsToAdd, int cardsToAdd)
{
    PlayerById tempPlayer(playerId, 0, 0, 0, 0, false);
    Node<PlayerById>* currentPlayer = teamTreeById.find(teamTreeById.getRoot(), tempPlayer);
    currentPlayer->data->updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    Node<PlayerByStats>* currentPlayerByStats = teamTreeByStats.find(teamTreeByStats.getRoot(), p);
    currentPlayerByStats->data->updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    this->totalCards += cardsToAdd;
    this->totalGoals += goalsToAdd;

}

void Team::inOrderPlayers(int* output,PlayerByStats* const playersOutPut) const
{
    int index = 0;
    teamTreeByStats.inOrder(teamTreeByStats.getRoot(), playersOutPut, index);
    for (int i = 0; i < teamTreeByStats.getNodesNum(); i++)
    {
        output[i] = playersOutPut[i].getPlayerId();
    }
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