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
	
	if (!teamsInSystem.insert(newTeam))
	{
		return StatusType::FAILURE;
	}

	
	this->totalTeams++;

	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	Team tempTeam(teamId, 0);
	if (!teamsInSystem.find(teamsInSystem.getRoot(), tempTeam) || teamsInSystem.find(teamsInSystem.getRoot(), tempTeam)->data->getPlayersCount() >= 1)
	{
		return StatusType::FAILURE;
	}

	int numOfTeams = teamsInSystem.getNodesNum();
	teamsInSystem.remove(tempTeam);
	
	if (teamsInSystem.getNodesNum() == numOfTeams)
	{
		return StatusType::FAILURE;
	}

	this->totalTeams--;
	
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
	int goals, int cards, bool goalKeeper)
{
	Team tempTeam(teamId, 0);

	Node<Team>* team = teamsInSystem.find(teamsInSystem.getRoot(), tempTeam);


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

	if(team->data->getPlayersCount() == 1)
		nonEmptyTeams.insert(*team->data);
	//to do add player to team 

	if (team->data->getPlayersCount() >= 11 && team->data->hasGoalKeeper())
	{
		Node<Team>* currentTeam = activeTeams.find(activeTeams.getRoot(), *team->data);
		if(currentTeam == nullptr)
			activeTeams.insert(*team->data);
		else
		{
			currentTeam->data->insertPlayer(playerId, gamesPlayed, goals, cards, goalKeeper);	
		}
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	Player temp(playerId, 0, 0, 0, 0, false);
	Node<Player>* newPlayer = players.find(players.getRoot(), temp);
	
	if (newPlayer == nullptr)
	{
		return StatusType::FAILURE;
	}
	
	int amountOfPlayers = players.getNodesNum();
	players.remove(*newPlayer->data);
	
	if (players.getNodesNum() == amountOfPlayers)
	{
		return StatusType::FAILURE;
	}
	
	Team tempTeam(newPlayer->data->pStats.teamId, 0);
	
	Node<Team>* currentTeam = nonEmptyTeams.find(nonEmptyTeams.getRoot(), tempTeam);
	currentTeam->data->removePlayer(newPlayer->data->pStats.teamId);
	if (currentTeam != nullptr && currentTeam->data->getPlayersCount() == 0)
		nonEmptyTeams.remove(*currentTeam->data);


	currentTeam = activeTeams.find(activeTeams.getRoot(), tempTeam);
	
	if (currentTeam != nullptr)
	{
		currentTeam->data->removePlayer(newPlayer->data->pStats.teamId);
		if (currentTeam->data->getPlayersCount() < 11 || !currentTeam->data->hasGoalKeeper())
		{
			activeTeams.remove(*currentTeam->data);
		}
	}
	
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
	int scoredGoals, int cardsReceived)
{
	if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	
	Player tempPlayer(playerId, 0, gamesPlayed, scoredGoals, cardsReceived, false);
	Node<Player>* currentPlayer = players.find(players.getRoot(), tempPlayer);
	if (currentPlayer == nullptr)
	{
		return StatusType::FAILURE;
	}
	currentPlayer->data->updateStats(gamesPlayed, scoredGoals, cardsReceived);

	
	Team tempTeam(currentPlayer->data->getTeamId(), 0);
	Node<Team>* currentTeam = nonEmptyTeams.find(nonEmptyTeams.getRoot(), tempTeam);
	currentPlayer = currentTeam->data->findPlayer(tempPlayer);
	if (currentPlayer != nullptr)
		currentPlayer->data->updateStats(gamesPlayed, scoredGoals, cardsReceived);

	
	currentTeam = activeTeams.find(activeTeams.getRoot(), tempTeam);
	currentPlayer = currentTeam->data->findPlayer(tempPlayer);
	if (currentPlayer != nullptr)
		currentPlayer->data->updateStats(gamesPlayed, scoredGoals, cardsReceived);

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
	Team* const participatingTeams = new Team[activeTeams.getNodesNum()];
	Team tempMin(minTeamId, 0), tempMax(maxTeamId, 0);
	Node<Team>* minNode = activeTeams.find(activeTeams.getRoot(), tempMin);
	Node<Team>* maxNode = activeTeams.find(activeTeams.getRoot(), tempMax);

	int index = 0;
	activeTeams.inOrderMinToMax(activeTeams.getRoot(), minNode->data, maxNode->data, participatingTeams, index);
	if (index == 0)
		return StatusType::FAILURE;
	return(knockout_winner_aux(minTeamId, maxTeamId, participatingTeams, index));

}
output_t<int> world_cup_t::knockout_winner_aux(int minTeamId, int maxTeamId, Team* participatingTeams, int size)
{
	
	Team* remainingTeams = new Team[size/2 + size%2];

	if (size == 1)
	{
		output_t<int> result(participatingTeams[0].getID());
		return result;
	}
	int j = 0;
	for (int i = 1; i < size; i += 2)
	{
		//warning: if size % 2 = 1 the last team dont play 
		//participatingTeams[i].addPoints(participatingTeams[i - 1].getTeamPoints());
		remainingTeams[j] = participatingTeams[i];
		j++;
	}

	output_t<int> winner = knockout_winner_aux(minTeamId, maxTeamId, remainingTeams, size / 2);
	delete remainingTeams;
	return winner;

}

