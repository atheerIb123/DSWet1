#ifndef PLAYER_ID_H_
#define PLAYER_ID_H_

class PlayerById
{
public:
	PlayerById();
	PlayerById(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~PlayerById() = default;
	PlayerById(const PlayerById& other) = default;
	PlayerById& operator=(const PlayerById& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	int getGoalsCount() const;
	int getCardsCount() const;
	bool isGoalKeeper() const;
	bool operator<(const PlayerById& other) const;
	bool operator>(const PlayerById& other) const;
	bool operator==(const PlayerById& other) const;
private:
	int playerId;
	int teamId;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;
};

#endif