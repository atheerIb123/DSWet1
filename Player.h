#ifndef PLAYER_H_
#define PLAYER_H_


class PlayerStats
{
public:
	PlayerStats(){}
	PlayerStats(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper)
	{
		this->playerId = playerId;
		this->teamId = teamId;
		this->gamesPlayed = gamesPlayed;
		this->goals = goals;
		this->cards = cards;
		this->goalKeeper = goalKeeper;
	}

	int playerId;
	int teamId;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;
};

class Player
{
public:
	Player(){}
	Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
	~Player() = default;
	Player(const Player& other) = default;
	Player& operator=(const Player& other) = default;

	void updateStats(int gamesPlayed, int scoredGoals, int cardsReceieved);
	int getTeamId() const;
	bool operator<(const Player& other) const;
	bool operator>(const Player& other) const;
	bool operator==(const Player& other) const;
	PlayerStats pStats;
private:
	/*int playerId;
	int teamId;
	int gamesPlayed;
	int goals;
	int cards;
	bool goalKeeper;*/
};

#endif