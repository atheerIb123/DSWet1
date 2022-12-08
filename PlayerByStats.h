#ifndef PLAYER_STATS_H_
#define PLAYER_STATS_H_

#include <iostream>

class PlayerByStats
{
public:
	PlayerByStats();
	PlayerByStats(int playerId, std::shared_ptr<int> teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~PlayerByStats() = default;
	PlayerByStats(const PlayerByStats& other) = default;
	PlayerByStats& operator=(const PlayerByStats& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	int* getTeamIdPtr() const { return this->teamId.get(); };
	int getPlayerId() const;
	void setTeamId(int newId);
	int getGamesPlayed() const;
	int getGoalsCount() const;
	int getCardsCount() const;
	void setGamesPlayedWithTeam(std::shared_ptr<int> games);
	void setClosest(int playerId);
	void setClosestPtr(std::shared_ptr<int> ptr);
	int getClosest() const;
	bool isGk() const;
	virtual bool operator<(const PlayerByStats& other) const;
	virtual bool operator>(const PlayerByStats& other) const;
	bool operator==(const PlayerByStats& other) const;

private:
	int playerId;
	std::shared_ptr<int> teamId;
	std::shared_ptr<int> gamesPlayedWithTeam;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;
	std::shared_ptr<int> closestId;
};

#endif