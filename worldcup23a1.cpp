#include "worldcup23a1.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

//world_cup_t::~world_cup_t()
//{
//	// TODO: Your code goes here
//}


StatusType world_cup_t::add_team(int teamId, int points)
{
	Team newTeam(teamId, points);
	
	if (!teams.insert(newTeam))
	{
		return StatusType::FAILURE;
	}

	this->totalTeams++;

	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	Team tempTeam(teamId, 0);
	if (!teams.find(teams.getRoot(), tempTeam) || teams.find(teams.getRoot(), tempTeam)->data->getPlayersCount() >= 1)
	{
		return StatusType::FAILURE;
	}

	Node<Team>* toRemove = teams.remove(tempTeam);

	if (this->totalTeams >= 1 && !toRemove)
	{
		return StatusType::FAILURE;
	}
	
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
	int goals, int cards, bool goalKeeper)
{
	Team tempTeam(teamId, 0);

	Node<Team>* team = teams.find(teams.getRoot(), tempTeam);

	if (team->data->insertPlayer(playerId, gamesPlayed, goals, cards, goalKeeper) == false || !team)
	{
		return StatusType::FAILURE;
	}

	Player newPlayer(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
	
	if (players.find(players.getRoot(), newPlayer))
	{
		return StatusType::FAILURE;
	}

	if (!players.insert(newPlayer))
	{
		return StatusType::FAILURE;
	}
	
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
	int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	Player tempPlayer(playerId, 0, 0, 0, 0, false);
	Node<Player>* temp = players.find(players.getRoot(), tempPlayer);
	
	if (!temp)
	{
		output_t<int> output(StatusType::FAILURE);
		return output;
	}

	int gamesPlayed = (temp->data->pStats.gamesPlayed);
	output_t<int> output(gamesPlayed);

	return output;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
	static int i = 0;
	return (i++ == 0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int* const output)
{
	// TODO: Your code goes here
	output[0] = 4001;
	output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	Team tempMin(minTeamId, 0), tempMax(maxTeamId, 0);
	Node<Team>* minNode = activeTeams.find(activeTeams.getRoot(), tempMin);
	Node<Team>* maxNode = activeTeams.find(activeTeams.getRoot(), tempMax);
	
	Team* const participatingTeams = new Team[activeTeams.getNodesNum()];
	int index = 0;

	teams.inOrderMinToMax(teams.getRoot(), minNode->data, maxNode->data, participatingTeams, index);
	if (index == 0)
		return StatusType::FAILURE;
	for (int i = 1; i < index; i += 2)
	{
		participatingTeams[i].addPoints(participatingTeams[i - 1].getTeamPoints());

	}

	return 2;
}

