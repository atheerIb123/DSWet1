// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_

#include "wet1util.h"
#include "AVLTree.h"
#include "Team.h"

class world_cup_t {
private:
	AVLTree<PlayerByStats> playersByStats;
	AVLTree<PlayerById> playersById;
	AVLTree<Team> teamsInSystem;
	AVLTree<Team> activeTeams;
	AVLTree<Team> nonEmptyTeams;

	int topScorer[2];//Index[0] = playerId, Index[1] = totalGoals that playerId scored
	int totalTeams;

	Node<Team>* findTeam(int teamId, bool emptyFlag);
	void updateTeamId(Node<PlayerById>* root, int newTeamId);
	void findClosest(Node<PlayerByStats>* player);
	int findActiveTeams(int minTeamId, int maxTeamId, Team* partcipatingTeams, int size);
public:
	// <DO-NOT-MODIFY> {
	world_cup_t();
	virtual ~world_cup_t() = default;
	StatusType add_team(int teamId, int points);

	StatusType remove_team(int teamId);

	StatusType add_player(int playerId, int teamId, int gamesPlayed,
		int goals, int cards, bool goalKeeper);

	StatusType remove_player(int playerId);

	StatusType update_player_stats(int playerId, int gamesPlayed,
		int scoredGoals, int cardsReceived);

	StatusType play_match(int teamId1, int teamId2);

	output_t<int> get_num_played_games(int playerId);

	output_t<int> get_team_points(int teamId);

	StatusType unite_teams(int teamId1, int teamId2, int newTeamId);

	output_t<int> get_top_scorer(int teamId);

	output_t<int> get_all_players_count(int teamId);

	StatusType get_all_players(int teamId, int* const output);

	output_t<int> get_closest_player(int playerId, int teamId);

	output_t<int> knockout_winner(int minTeamId, int maxTeamId);

	output_t<int> knockout_winner_aux(int minTeamId, int maxTeamId, Team* participatingTeams, int size);

	Node<PlayerByStats>* getRootOfS() const
	{
		return playersByStats.getRoot();
	}

	Node<PlayerByStats>* getHead() const
	{
		return playersByStats.listOfNodes.head;
	}
	
	Node<PlayerById>* getH() const
	{
		return playersById.listOfNodes.head;
	}
	int totalPlayers() const
	{
		return this->playersByStats.getNodesNum();
	}
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_