#include "Team.h"

Team::Team()
{
    this->teamId = std::make_shared<int>(-1);
}
Team::Team(int teamId, int points) : points(points)
{
    this->teamId = std::make_shared<int>(teamId);
    this->goalKeepers[0] = 0;
    this->goalKeepers[1] = 0;
    this->topScorer[0] = 0;
    this->topScorer[1] = -1;
    this->topScorer[2] = 0;
    this->totalCards = 0;
    this->totalGamesPlayed = std::make_shared<int>(0);
    this->totalGoals = 0;
    this->totalPlayers = 0;
}

bool Team::insertPlayer(int playerId, int gamesPlayed, int goals, int cards, bool goalKeeper, std::shared_ptr<int>& teamIdPtr, std::shared_ptr<int>& closest)
{
    teamIdPtr = this->teamId;

    PlayerById p1(playerId, teamIdPtr, gamesPlayed, goals, cards, goalKeeper);
    PlayerByStats p2(playerId, teamIdPtr, gamesPlayed, goals, cards, goalKeeper, closest);
    p1.setGamesPlayedWithTeam(this->totalGamesPlayed);
    p2.setGamesPlayedWithTeam(this->totalGamesPlayed);

    teamTreeById.insert(&p1, false);
    teamTreeByStats.insert(&p2, false);
    /*if (!teamTreeByStats.insert(&p2) || !teamTreeById.insert(&p1))
    {
        return false;
    }*/

    if (p1.isGoalKeeper() == true)
    {
        this->goalKeepers[0] = 1;
        this->goalKeepers[1]++;
    }

    this->totalPlayers++;
    this->totalCards += p1.getCardsCount();
    this->totalGoals += goals;



    if (topScorer[1] <= p2.getGoalsCount())
    {
        if (topScorer[1] == p2.getGoalsCount())
        {
            if(topScorer[2] == p2.getCardsCount())
            {
                if (topScorer[0] < p2.getPlayerId())
                {
                    topScorer[0] = p2.getPlayerId();
                }
            }
            else if(topScorer[2] > p2.getCardsCount())
            {
                topScorer[0] = p2.getPlayerId();
                topScorer[2] = p2.getCardsCount();
            }
        }
        else if (topScorer[1] < p2.getGoalsCount())
        {
            topScorer[0] = p2.getPlayerId();
            topScorer[1] = p2.getGoalsCount();
            topScorer[2] = p2.getCardsCount();
        }
    }

    return true;
}

bool Team::removePlayer(int playerId)
{
    std::shared_ptr<int> x = std::make_shared<int>(0);
    PlayerById tempPlayerId(playerId, x, 0, 0, 0, false);

    Node<PlayerById>* tempId = teamTreeById.find(teamTreeById.getRoot(), tempPlayerId);
    PlayerByStats tempPlayerSt(playerId, x, tempId->data->getGamesPlayed(), tempId->data->getGoalsCount(), tempId->data->getCardsCount(), tempId->data->isGoalKeeper(), x);
    Node<PlayerByStats>* tempSt = teamTreeByStats.find(teamTreeByStats.getRoot(), tempPlayerSt);

    if (!tempSt || !tempId)
    {
        return false;
    }

    int goals = tempId->data->getGoalsCount(), cards = tempId->data->getCardsCount();
    bool gk = tempId->data->isGoalKeeper();

    teamTreeByStats.remove(tempSt->data, false);
    teamTreeById.remove(tempId->data, false);


    this->totalPlayers--;


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


    if (topScorer[0] == playerId)
    {
        PlayerByStats* top = teamTreeByStats.findMax(teamTreeByStats.getRoot());
        if (top != nullptr)
        {
            topScorer[0] = top->getPlayerId();
            topScorer[1] = top->getGoalsCount();
            topScorer[2] = top->getCardsCount();
        }
        else
        {
            topScorer[0] = -1;
            topScorer[1] = -1;
            topScorer[2] = -1;
        }
    }

    return true;
}

void Team::updatePlayerStatsInTeam(PlayerByStats& p, int playerId, int gamesToAdd, int goalsToAdd, int cardsToAdd)
{
    std::shared_ptr<int> x = std::make_shared<int>(0);
    PlayerById tempPlayer(playerId, x, 0, 0, 0, false);
    Node<PlayerById>* currentPlayer = teamTreeById.find(teamTreeById.getRoot(), tempPlayer);

    PlayerById tempId(*currentPlayer->data);
    teamTreeById.remove(currentPlayer->data, false);
    tempId.updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    teamTreeById.insert(&tempId, false);

    Node<PlayerByStats>* currentPlayerByStats = teamTreeByStats.find(teamTreeByStats.getRoot(), p);

    PlayerByStats tempSt(*currentPlayerByStats->data);
    teamTreeByStats.remove(currentPlayerByStats->data, false);
    tempSt.updateStats(gamesToAdd, goalsToAdd, cardsToAdd);
    teamTreeByStats.insert(&tempSt, false);

    teamTreeById.find(teamTreeById.getRoot(), tempId)->data->setGamesPlayedWithTeam(this->totalGamesPlayed);
    teamTreeByStats.find(teamTreeByStats.getRoot(), tempSt)->data->setGamesPlayedWithTeam(this->totalGamesPlayed);

    this->totalCards += cardsToAdd;
    this->totalGoals += goalsToAdd;

    if (topScorer[1] <= tempSt.getGoalsCount())
    {
        if (topScorer[1] == tempSt.getGoalsCount())
        {
            if(topScorer[2] == tempSt.getCardsCount())
            {
                if (topScorer[0] < tempSt.getPlayerId())
                {
                    topScorer[0] = tempSt.getPlayerId();
                }
            }
            else if(topScorer[2] > tempSt.getCardsCount())
            {
                topScorer[0] = tempSt.getPlayerId();
                topScorer[2] = tempSt.getCardsCount();
            }
        }
        else if (topScorer[1] < tempSt.getGoalsCount())
        {
            topScorer[0] = tempSt.getPlayerId();
            topScorer[1] = tempSt.getGoalsCount();
            topScorer[2] = tempSt.getCardsCount();
        }
    }

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

    for(int i = 0 ; i < other.getPlayersCount() ; i++)
    {
        this->totalGoals += second[i].getGoalsCount();
        this->totalCards += second[i].getCardsCount();
        second[i].setGamesPlayedWithTeam(this->totalGamesPlayed);
    }
    teamTreeByStats.mergeTrees(first, this->totalPlayers, second, other.getPlayersCount(), mergedTeam);

    this->totalPlayers = teamTreeById.getNodesNum();
    this->addPoints(other.getTeamPoints());
    this->goalKeepers[0] += other.goalKeepers[0];
    this->goalKeepers[1] += other.goalKeepers[1];

    if (this->topScorer[1] <= other.getTopScorerGoalsAmount())
    {
        if (topScorer[1] == other.getTopScorerGoalsAmount())
        {
            if(topScorer[2] == other.topScorer[2])
            {
                if (topScorer[0] < other.getTopScorer())
                {
                    topScorer[0] = other.getTopScorer();
                }
            }
            else if(topScorer[2] > other.topScorer[2])
            {
                topScorer[0] = other.getTopScorer();
                topScorer[2] = other.topScorer[2];
            }
        }
        else
        {
            topScorer[0] = other.getTopScorer();
            topScorer[1] = other.getTopScorerGoalsAmount();
            topScorer[2] = other.topScorer[2];
        }
    }

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


Node<PlayerByStats>* Team::findPlayerById(int playerId)
{
    std::shared_ptr<int> x = std::make_shared<int>(0);
    PlayerById tempPlayer(playerId, x, 0, 0, 0, 0);
    Node<PlayerById>* currentPlayer = teamTreeById.find(teamTreeById.getRoot(), tempPlayer);
    PlayerByStats tempStats(currentPlayer->data->getPlayerId(), x, currentPlayer->data->getGamesPlayed(), currentPlayer->data->getGoalsCount(), currentPlayer->data->getCardsCount(), currentPlayer->data->isGoalKeeper(), x);
 
    return teamTreeByStats.find(teamTreeByStats.getRoot(), tempStats);
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
    return this->topScorer[0];
}

int Team::getTopScorerGoalsAmount() const
{
    return this->topScorer[1];
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
    return *this->teamId;
}

void Team::setNewId(std::shared_ptr<int>& id)
{
    this->teamId = id;
    if(this->teamTreeById.getRoot() != nullptr)
    {
        this->teamTreeById.getRoot()->data->setTeamId(*id);
        this->teamTreeByStats.getRoot()->data->setTeamId(*id);
    }
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
    if (*this->teamId < *other.teamId)
    {
        return true;
    }
    return false;
}

bool Team::operator>(const Team& other) const
{
    if (*this->teamId > *other.teamId)
    {
        return true;
    }
    return false;
}

bool Team::operator==(const Team& other) const
{
    if (*this->teamId == *other.teamId)
    {
        return true;
    }

    return false;
}

std::shared_ptr<int>& Team::teamIdPtr()
{
    return this->teamId;
}

void Team::updateTeamIdPlayers(int newTeamID) {
    PlayerById* const firstTeamPlayers = new PlayerById[this->totalPlayers];
    PlayerByStats* const first = new PlayerByStats[this->totalPlayers];

    int index = 0;
    this->teamTreeById.inOrder(teamTreeById.getRoot(), firstTeamPlayers, index);
    index =0;
    this->teamTreeByStats.inOrder(teamTreeByStats.getRoot(), first, index);

    for(int i = 0 ; i < this->totalPlayers ; i++)
    {
        firstTeamPlayers[i].setTeamId(newTeamID);
        first[i].setTeamId(newTeamID);
    }
    delete[] firstTeamPlayers;
    delete[] first;
}

void Team::setTeamPoints(int amount) {
    this->points = amount;
}

std::shared_ptr<int> &Team::gamesPlayedPtr() {
    return this->totalGamesPlayed;
}

void Team::setGamesPlayed(std::shared_ptr<int> &games)
{
    this->totalGamesPlayed = games;
}
