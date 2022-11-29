#ifndef PLAYER_STATS_H_
#define PLAYER_STATS_H_

class PlayerByStats
{
public:
	PlayerByStats();
	PlayerByStats(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~PlayerByStats() = default;
	PlayerByStats(const PlayerByStats& other) = default;
	PlayerByStats& operator=(const PlayerByStats& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	int getPlayerId() const;

	int getGamesPlayed() const;
	virtual bool operator<(const PlayerByStats& other) const;
	virtual bool operator>(const PlayerByStats& other) const;
	bool operator==(const PlayerByStats& other) const;
private:
	int playerId;
	int teamId;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;
};

#endif