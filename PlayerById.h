#ifndef PLAYER_ID_H_
#define PLAYER_ID_H_

#include <iostream>
#include <memory>

class Team;

class PlayerById
{
public:
	PlayerById();
	PlayerById(int playerId, std::shared_ptr<int>& teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~PlayerById() = default;
	PlayerById(const PlayerById& other) = default;
	PlayerById& operator=(const PlayerById& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	void setTeamId(int newId);
    void setTeamPtr(std::shared_ptr<int>& id);
	int getGoalsCount() const;
	int getCardsCount() const;
	int getGamesPlayed() const;
	bool isGoalKeeper() const;
	void setGamesPlayedWithTeam(std::shared_ptr<int>& games);
    void setPlayerTeam(std::shared_ptr<Team>& t);
    void changeTeam(Team& t);
    std::shared_ptr<Team>& getPlayerTeam();
    void decGames(int amount);
    int getGamesPlayedWTeam();
    void setGamesPlayedWhenJoined(int amount);
    int getGamesPlayedNon() const
    {
        return this->gamesPlayed;
    }
    int getPlayerId() const
	{
		return this->playerId;
	}
	bool operator<(const PlayerById& other) const;
	bool operator>(const PlayerById& other) const;
	bool operator==(const PlayerById& other) const;
private:
	int playerId;
	std::shared_ptr<int> teamId;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;
	std::shared_ptr<int> gamesPlayedWithTeam;
    std::shared_ptr<Team> playerTeam;
    int gamesPlayedWhenJoinedTeam;
};

#endif