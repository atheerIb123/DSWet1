#ifndef PLAYER_ID_H_
#define PLAYER_ID_H_

#include <iostream>
#include <memory>

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
};

#endif