#include "Team.h"

Team::Team(int teamId, int points) : points(points)
{
    this->teamId = teamId;
    this->goalKeepers[0] = 0;
    this->goalKeepers[1] = 0;
    this->topScorerId = 0;
    this->totalCards = 0;
    this->totalGamesPlayed = std::make_shared<int>(0);
    this->totalGoals = 0;
    this->totalPlayers = 0;
}

Team::~Team()
{
}

bool Team::insertPlayer(PlayerByStats* newPlayerSt, PlayerById* newPlayerId)
{
    if (!teamTreeByStats.insert(newPlayerSt) || !teamTreeById.insert(newPlayerId))
    {
        return false;
    }
    
    if (newPlayerId->isGoalKeeper() == true)
    {
        this->goalKeepers[0] = 1;
        this->goalKeepers[1]++;
    }

    this->totalPlayers++;
    this->totalCards += newPlayerId->getCardsCount();
    this->totalGoals += newPlayerId->getGoalsCount();
    
    newPlayerSt->setGamesPlayedWithTeam(this->totalGamesPlayed);
    newPlayerId->setGamesPlayedWithTeam(this->totalGamesPlayed);

    return true;
}

bool Team::removePlayer(int playerId)
{
    PlayerById tempPlayerId(playerId, nullptr, 0, 0, 0, false);

    Node<PlayerById>* tempId = teamTreeById.find(teamTreeById.getRoot(), tempPlayerId);
    PlayerByStats tempPlayerSt(playerId, nullptr, tempId->data->getGamesPlayed(), tempId->data->getGoalsCount(), tempId->data->getCardsCount(), tempId->data->isGoalKeeper());
    Node<PlayerByStats>* tempSt = teamTreeByStats.find(teamTreeByStats.getRoot(), tempPlayerSt);

    if (!tempSt || !tempId)
    {
        return false;
    }

    int goals = tempId->data->getGoalsCount(), cards = tempId->data->getCardsCount();
    bool gk = tempId->data->isGoalKeeper();

    Node<PlayerByStats>* toRemoveSt = teamTreeByStats.remove(tempSt->data);
    Node<PlayerById>* toRemoveId = teamTreeById.remove(tempId->data);

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

    PlayerById tempId(*currentPlayer->data);
    teamTreeById.remove(currentPlayer->data);
    tempId.updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    teamTreeById.insert(&tempId);

    Node<PlayerByStats>* currentPlayerByStats = teamTreeByStats.find(teamTreeByStats.getRoot(), p);
    
    PlayerByStats tempSt(*currentPlayerByStats->data);
    teamTreeByStats.remove(currentPlayerByStats->data);
    tempSt.updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    teamTreeByStats.insert(&tempSt);

    teamTreeById.find(teamTreeById.getRoot(), tempId)->data->setGamesPlayedWithTeam(this->totalGamesPlayed);
    teamTreeByStats.find(teamTreeByStats.getRoot(), tempSt)->data->setGamesPlayedWithTeam(this->totalGamesPlayed);

    this->totalCards += cardsToAdd;
    this->totalGoals += goalsToAdd;
}

void Team::inOrderPlayers(int* output, PlayerByStats* const playersOutPut) const
{
    int index = 0;
    teamTreeByStats.inOrder(teamTreeByStats.getRoot(), playersOutPut, index);
    
    if (output != nullptr)
    {
        for (int i = 0; i < teamTreeByStats.getNodesNum(); i++)
        {
            output[i] = playersOutPut[i].getPlayerId();
        }
    }
}

void Team::inOrderPlayers(PlayerById* const output) const
{
    int index = 0;
    teamTreeById.inOrder(teamTreeById.getRoot(), output, index);
}

Node<PlayerById>* Team::getRootOfIds() const
{
    return this->teamTreeById.getRoot();
}

void Team::mergeTeams(Team& other)
{
    PlayerById* const firstTeamPlayers = new PlayerById[this->totalPlayers];
    PlayerById* const secondTeamPlayers = new PlayerById[other.getPlayersCount()];
    PlayerById* const mergedTeamArr = new PlayerById[this->totalPlayers + other.getPlayersCount()];

    int index = 0;
    this->teamTreeById.inOrder(teamTreeById.getRoot(), firstTeamPlayers, index);
    other.inOrderPlayers(secondTeamPlayers);
    teamTreeById.mergeTrees(firstTeamPlayers, this->totalPlayers, secondTeamPlayers, other.getPlayersCount(), mergedTeamArr);
    
    PlayerByStats* const first = new PlayerByStats[this->totalPlayers];
    PlayerByStats* const second = new PlayerByStats[other.getPlayersCount()];
    PlayerByStats* const mergedTeam = new PlayerByStats[this->totalPlayers + other.getPlayersCount()];
    index = 0;
    this->teamTreeByStats.inOrder(teamTreeByStats.getRoot(), first, index);
    other.inOrderPlayers(nullptr, second);
    teamTreeByStats.mergeTrees(first, this->totalPlayers, second, other.getPlayersCount(), mergedTeam);

    this->totalPlayers = teamTreeById.getNodesNum();

    delete[] firstTeamPlayers;
    delete[] secondTeamPlayers;
    delete[] mergedTeamArr;
    delete[] first;
    delete[] second;
    delete[] mergedTeam;
}

void Team::incrementGamesPlayed()
{
    totalGamesPlayed.operator*()++;
}

void Team::setGamesPlayed()
{
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

void Team::setNewId(int id)
{
    this->teamId = id;
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