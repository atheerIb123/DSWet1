#ifndef PLAYER_ID_H_
#define PLAYER_ID_H_

#include <iostream>

class PlayerById
{
public:
	PlayerById();
	PlayerById(int playerId, std::shared_ptr<int> teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~PlayerById() = default;
	PlayerById(const PlayerById& other) = default;
	PlayerById& operator=(const PlayerById& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	void setTeamId(int newId);
	int getGoalsCount() const;
	int getCardsCount() const;
	int getGamesPlayed() const;
	bool isGoalKeeper() const;
	void setGamesPlayedWithTeam(std::shared_ptr<int> games);

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