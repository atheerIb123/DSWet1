#include "worldcup23a1.h"

Node<Team>* world_cup_t::findTeam(int teamId, bool emptyFlag)
{
	Team tempTeam(teamId, 0);
	Node<Team>* team;

	if (emptyFlag == true)
	{
		team = teamsInSystem.find(teamsInSystem.getRoot(), tempTeam);
	}
	else
	{
		team = nonEmptyTeams.find(nonEmptyTeams.getRoot(), tempTeam);

	}

	return team;
}

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
	if (teamId <= 0 || points < 0)
	{
		return StatusType::INVALID_INPUT;
	}

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
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

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
	if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0)
	{
		return StatusType::FAILURE;
	}

	if (gamesPlayed == 0 && (goals > 0 || cards > 0))
	{
		return StatusType::FAILURE;
	}

	Node<Team>* team = findTeam(teamId, true);

	if (team == nullptr)
	{
		return StatusType::FAILURE;
	}

	if (nonEmptyTeams.find(nonEmptyTeams.getRoot(), *(team->data)) == nullptr)
	{
		if (team->data->insertPlayer(playerId, gamesPlayed, goals, cards, goalKeeper) == false)
		{
			return StatusType::FAILURE;
		}

		nonEmptyTeams.insert(*(team->data));
	}
	else
	{
		Node<Team>* tempTeam = findTeam(teamId, false); //Find it in the nonEmptyTeams tree

		if (tempTeam->data->insertPlayer(playerId, gamesPlayed, goals, cards, goalKeeper) == false)
		{
			return StatusType::FAILURE;
		}
	}

	//Adding the player to the players' trees
	PlayerById newPlayerId(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
	PlayerByStats newPlayerSt(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);

	if (playersById.find(playersById.getRoot(), newPlayerId) || playersByStats.find(playersByStats.getRoot(), newPlayerSt))
	{
		return StatusType::FAILURE;
	}

	if (!playersByStats.insert(newPlayerSt) || !playersById.insert(newPlayerId))
	{
		return StatusType::FAILURE;
	}

	
	//Checking if the team is fit to join the active teams tree
	Node<Team>* tempTeam = findTeam(teamId, false);
	if (tempTeam->data->getPlayersCount() >= 11 && tempTeam->data->hasGoalKeeper())
	{
		Node<Team>* currentTeam = activeTeams.find(activeTeams.getRoot(), *team->data);
		if (currentTeam == nullptr)
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
	if (playerId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	PlayerById temp(playerId, 0, 0, 0, 0, false);
	Node<PlayerById>* tempPlayer = playersById.find(playersById.getRoot(), temp);

	if (tempPlayer == nullptr)
	{
		return StatusType::FAILURE;
	}

	PlayerByStats tempSt(playerId, tempPlayer->data->getTeamId(), tempPlayer->data->getGamesPlayed(), tempPlayer->data->getGoalsCount(), tempPlayer->data->getCardsCount(), tempPlayer->data->isGoalKeeper());
	
	int amountOfPlayers[2] = { 0 };
	amountOfPlayers[0] = playersById.getNodesNum();
	amountOfPlayers[1] = playersByStats.getNodesNum();

	playersById.remove(*tempPlayer->data);
	playersByStats.remove(tempSt);

	if (playersById.getNodesNum() == amountOfPlayers[0] || playersByStats.getNodesNum() == amountOfPlayers[1])
	{
		return StatusType::FAILURE;
	}

	Node<Team>* currentTeam = findTeam(tempPlayer->data->getTeamId(), false);
	
	if (currentTeam->data->removePlayer(playerId) == false)
	{
		return StatusType::FAILURE;
	}

	if (currentTeam != nullptr && currentTeam->data->getPlayersCount() == 0)
	{
		nonEmptyTeams.remove(*currentTeam->data);
	}


	currentTeam = activeTeams.find(activeTeams.getRoot(), *(currentTeam->data));

	if (currentTeam != nullptr)
	{
		currentTeam->data->removePlayer(playerId);
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

	PlayerById tempPlayer(playerId, 0, gamesPlayed, scoredGoals, cardsReceived, false);
	Node<PlayerById>* currentPlayer = playersById.find(playersById.getRoot(), tempPlayer);
	if (currentPlayer == nullptr)
	{
		return StatusType::FAILURE;
	}

	PlayerByStats p(playerId, currentPlayer->data->getTeamId(), currentPlayer->data->getGamesPlayed(), currentPlayer->data->getGoalsCount(), currentPlayer->data->getCardsCount(), currentPlayer->data->isGoalKeeper());
	currentPlayer->data->updateStats(gamesPlayed, scoredGoals, cardsReceived);


	Node<PlayerByStats>* playerToUpdate = playersByStats.find(playersByStats.getRoot(), p);
	playerToUpdate->data->updateStats(gamesPlayed, scoredGoals, cardsReceived);


	Node<Team>* currentTeam = findTeam(currentPlayer->data->getTeamId(), false);
	currentTeam->data->updatePlayerStatsInTeam(p, playerId, gamesPlayed, scoredGoals, cardsReceived);



	Team tempTeam(currentTeam->data->getID(), 0);
	currentTeam = activeTeams.find(activeTeams.getRoot(), tempTeam);
	currentTeam->data->updatePlayerStatsInTeam(p, playerId, gamesPlayed, scoredGoals, cardsReceived);



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

	Team* remainingTeams = new Team[size / 2 + size % 2];

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