#include "worldcup23a1.h"

Node<PlayerByStats>* getLeftRightestNode(Node<PlayerByStats>* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->right == nullptr)
	{
		return node;
	}

	return getLeftRightestNode(node->right);
}

Node<PlayerByStats>* getRightLeftestNode(Node<PlayerByStats>* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->left == nullptr)
	{
		return node;
	}

	return getRightLeftestNode(node->left);

}

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

void world_cup_t::updateTeamId(Node<PlayerById>* root, int newTeamId)
{
	if (!root)
	{
		return;
	}

	updateTeamId(root->left, newTeamId);
	root->data->setTeamId(newTeamId);
	updateTeamId(root->right, newTeamId);
}

void world_cup_t::findClosest(Node<PlayerByStats>* player)
{
	Node<PlayerByStats>* current = player;
	
	while (current != nullptr)
	{
		comparePlayers(current->parent, getLeftRightestNode(current), getRightLeftestNode(current), current);
		current = current->parent;
	}
}

int min(int val1, int val2, int val3)
{
	if (val1 < val2)
	{
		return val1;
	}
	else if (val1 > val2)
	{
		return val2;
	}

	return min(min(val1, val2, 0), val3, 0);
}

void world_cup_t::comparePlayers(Node<PlayerByStats>* p1, Node<PlayerByStats>* p2, Node<PlayerByStats>* p3, Node<PlayerByStats>* player)
{
	int goalsDiff[3] = { 0 };
	int cardsDiff[3] = { 0 };

	if (p1 != nullptr)
	{
		goalsDiff[0] = abs(player->data->getGoalsCount() - p1->data->getGoalsCount());
		cardsDiff[0] = abs(player->data->getCardsCount() - p1->data->getCardsCount());

		if (p2 != nullptr)
		{
			goalsDiff[1] = abs(player->data->getGoalsCount() - p2->data->getGoalsCount());
			cardsDiff[1] = abs(player->data->getCardsCount() - p2->data->getCardsCount());
		}
		if (p3 != nullptr)
		{
			goalsDiff[2] = abs(player->data->getGoalsCount() - p3->data->getGoalsCount());
			cardsDiff[2] = abs(player->data->getCardsCount() - p3->data->getCardsCount());
		}

		int minGoals = min(goalsDiff[0], goalsDiff[1], goalsDiff[2]);
		int minCards = min(cardsDiff[0], cardsDiff[1], cardsDiff[2]);
		int goalsCounter = 0;
		int cardsCounter = 0;
		
		for (int i = 0; i < 3; i++)
		{	
			if (minGoals == goalsDiff[0] && goalsDiff[0] == goalsDiff[1])
			{
				if (cardsDiff[0] < cardsDiff[1])
				{

				}
			}
		}
		

	}
}

world_cup_t::world_cup_t()
{
	topScorer[0] = -1;
	topScorer[1] = -1;
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

	if (!teamsInSystem.insert(&newTeam))
	{
		return StatusType::FAILURE;
	}

	teamsInSystem.find(teamsInSystem.getRoot(), newTeam)->data->setGamesPlayed();

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

	if (!teamsInSystem.find(teamsInSystem.getRoot(), tempTeam) || nonEmptyTeams.find(teamsInSystem.getRoot(), tempTeam)->data->getPlayersCount() >= 1)
	{
		return StatusType::FAILURE;
	}

	int numOfTeams = teamsInSystem.getNodesNum();
	teamsInSystem.remove(&tempTeam);

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
		return StatusType::INVALID_INPUT;
	}

	if (gamesPlayed == 0 && (goals > 0 || cards > 0))
	{
		return StatusType::INVALID_INPUT;
	}
	
	std::shared_ptr<int> team_id = std::make_shared<int>();
	*team_id = teamId;
	
	PlayerById newPlayerId(playerId, team_id, gamesPlayed, goals, cards, goalKeeper);
	PlayerByStats newPlayerSt(playerId, team_id, gamesPlayed, goals, cards, goalKeeper);

	Node<Team>* team = findTeam(teamId, true);

	if (team == nullptr)
	{
		return StatusType::FAILURE;
	}

	if (nonEmptyTeams.find(nonEmptyTeams.getRoot(), *(team->data)) == nullptr)
	{
		if (team->data->insertPlayer(&newPlayerSt, &newPlayerId) == false)
		{
			return StatusType::FAILURE;
		}

		nonEmptyTeams.insert(team->data);
		findTeam(teamId, true)->data->removePlayer(playerId);
	}
	else
	{
		Node<Team>* tempTeam = findTeam(teamId, false); //Find it in the nonEmptyTeams tree

		if (tempTeam->data->insertPlayer(&newPlayerSt, &newPlayerId) == false)
		{
			return StatusType::FAILURE;
		}
	}

	//Adding the player to the players' trees
	if (playersById.find(playersById.getRoot(), newPlayerId) || playersByStats.find(playersByStats.getRoot(), newPlayerSt))
	{
		return StatusType::FAILURE;
	}

	if (!playersByStats.insert(&newPlayerSt) || !playersById.insert(&newPlayerId))
	{
		return StatusType::FAILURE;
	}

	
	//Checking if the team is fit to join the active teams tree
	Node<Team>* tempTeam = findTeam(teamId, false);
	if (tempTeam->data->getPlayersCount() >= 11 && tempTeam->data->hasGoalKeeper())
	{
		Node<Team>* currentTeam = activeTeams.find(activeTeams.getRoot(), *team->data);
		if (currentTeam == nullptr)
			activeTeams.insert(tempTeam->data);
		else
		{
			currentTeam->data->insertPlayer(&newPlayerSt, &newPlayerId);
		}
	}

	if (topScorer[1] <= goals)
	{
		if (topScorer[1] == goals)
		{
			if (topScorer[0] < playerId)
			{
				topScorer[0] = playerId;
			}
		}
		else if (topScorer[1] < goals)
		{
			topScorer[0] = playerId;
			topScorer[1] = goals;
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

	int teamIdOfPlayer = tempPlayer->data->getTeamId();

	PlayerByStats pStats(playerId, nullptr, tempPlayer->data->getGamesPlayed(), tempPlayer->data->getGoalsCount(), tempPlayer->data->getCardsCount(), tempPlayer->data->isGoalKeeper());
	Node<PlayerByStats>* tempSt = playersByStats.find(playersByStats.getRoot(), pStats);
	
	int amountOfPlayers[2] = { 0 };
	
	amountOfPlayers[0] = playersById.getNodesNum();
	amountOfPlayers[1] = playersByStats.getNodesNum();

	playersById.remove(tempPlayer->data);
	playersByStats.remove(tempSt->data);

	if (playersById.getNodesNum() == amountOfPlayers[0] || playersByStats.getNodesNum() == amountOfPlayers[1])
	{
		return StatusType::FAILURE;
	}

	Node<Team>* currentTeam = findTeam(teamIdOfPlayer, false);
	
	if (currentTeam->data->removePlayer(playerId) == false)
	{
		return StatusType::FAILURE;
	}

	if (currentTeam != nullptr && currentTeam->data->getPlayersCount() == 0)
	{
		nonEmptyTeams.remove(currentTeam->data);
	}

	if (currentTeam != nullptr)
	{
		currentTeam = activeTeams.find(activeTeams.getRoot(), *(currentTeam->data));
	}

	if (currentTeam != nullptr)
	{
		currentTeam->data->removePlayer(playerId);
		if (currentTeam->data->getPlayersCount() < 11 || !currentTeam->data->hasGoalKeeper())
		{
			activeTeams.remove(currentTeam->data);
		}
	}

	if (topScorer[0] == playerId)
	{
		PlayerByStats* top = playersByStats.findMax(playersByStats.getRoot());

		if (top != nullptr)
		{
			topScorer[0] = top->getPlayerId();
			topScorer[1] = top->getGoalsCount();
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

	PlayerById tempId(*currentPlayer->data);

	PlayerByStats p(playerId, nullptr, currentPlayer->data->getGamesPlayed(), currentPlayer->data->getGoalsCount(), currentPlayer->data->getCardsCount(), currentPlayer->data->isGoalKeeper());
	Node<PlayerByStats>* playerToUpdate = playersByStats.find(playersByStats.getRoot(), p);


	if (playerToUpdate == nullptr)
	{
		return StatusType::FAILURE;
	}

	PlayerByStats tempSt(*playerToUpdate->data);

	Node<Team>* currentTeam = findTeam(tempSt.getTeamId(), false);
	currentTeam->data->updatePlayerStatsInTeam(*playerToUpdate->data, playerId, gamesPlayed, scoredGoals, cardsReceived);

	Team tempTeam(currentTeam->data->getID(), 0);
	currentTeam = activeTeams.find(activeTeams.getRoot(), tempTeam);
	if (currentTeam != nullptr)
	{
		currentTeam->data->updatePlayerStatsInTeam(*playerToUpdate->data, playerId, gamesPlayed, scoredGoals, cardsReceived);
	}

	playersById.remove(currentPlayer->data);
	tempId.updateStats(gamesPlayed, scoredGoals, cardsReceived);
	playersById.insert(&tempId);

	playersByStats.remove(playerToUpdate->data);
	tempSt.updateStats(gamesPlayed, scoredGoals, cardsReceived);
	playersByStats.insert(&tempSt);

	if (topScorer[1] <= tempSt.getGoalsCount())
	{
		if (topScorer[1] == tempSt.getGoalsCount())
		{
			if (topScorer[0] < tempSt.getPlayerId())
			{
				topScorer[0] = tempSt.getPlayerId();
			}
		}
		else if (topScorer[1] < tempSt.getGoalsCount())
		{
			topScorer[0] = tempSt.getPlayerId();
			topScorer[1] = tempSt.getGoalsCount();
		}
	}

	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
	{
		return StatusType::INVALID_INPUT;
	}
	
	Team temp1(teamId1, 0);
	Team temp2(teamId2, 0);
	Node<Team>* activeTeam1 = activeTeams.find(activeTeams.getRoot(), temp1);
	Node<Team>* activeTeam2 = activeTeams.find(activeTeams.getRoot(), temp2);
	
	if (!activeTeam1 || !activeTeam2)
	{
		return StatusType::FAILURE;
	}
	
	if (activeTeam1->data->getTeamPower() < activeTeam2->data->getTeamPower())
	{
		activeTeam2->data->addPoints(3);
		findTeam(teamId2, false)->data->addPoints(3);
	}
	else if (activeTeam1->data->getTeamPower() > activeTeam2->data->getTeamPower())
	{
		activeTeam1->data->addPoints(3);
		findTeam(teamId1, false)->data->addPoints(3);
	}
	else
	{
		activeTeam1->data->addPoints(1);
		activeTeam2->data->addPoints(1);
		findTeam(teamId1, false)->data->addPoints(1);
		findTeam(teamId2, false)->data->addPoints(1);
	}

	activeTeam1->data->incrementGamesPlayed();
	activeTeam2->data->incrementGamesPlayed();
	
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	PlayerById tempPlayer(playerId, 0, 0, 0, 0, false);
	Node<PlayerById>* temp = playersById.find(playersById.getRoot(), tempPlayer);

	if (!temp)
	{
		output_t<int> output(StatusType::FAILURE);
		return output;
	}

	int gamesPlayed = (temp->data->getGamesPlayed());
	output_t<int> output(gamesPlayed);

	return output;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0)
	{
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	Node<Team>* team = findTeam(teamId, true);
	int points = 0;

	if (!team && !(findTeam(teamId, true)))
	{
		return output_t<int>(StatusType::FAILURE);
	}

	if (findTeam(teamId, true) != nullptr)
	{
		points = findTeam(teamId, true)->data->getTeamPoints();
	}
	else if (team != nullptr)
	{
		points = team->data->getTeamPoints();
	}
	
	output_t<int> res(points);
	
	return res;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	if (newTeamId <= 0 || teamId1 <= 0 || teamId2 <= 0)
	{
		return StatusType::FAILURE;
	}
	if (teamId1 == teamId2)
	{
		return StatusType::FAILURE;
	}

	if (!findTeam(teamId1, true) || !findTeam(teamId2, true))
	{
		return StatusType::FAILURE;
	}

	if (findTeam(newTeamId, true))
	{
		if (findTeam(newTeamId, true)->data->getID() != teamId1 && findTeam(newTeamId, true)->data->getID() != teamId2)
		{
			return StatusType::FAILURE;
		}
	}

	Node<Team>* team1 = findTeam(teamId1, false);
	Node<Team>* team2 = findTeam(teamId2, false);

	if (team2 == nullptr)
	{
		if (team1 != nullptr)
		{
			team1->data->setNewId(newTeamId);

			Team activeTeamTemp(teamId1, 0);
			Node<Team>* activeTeam1 = activeTeams.find(activeTeams.getRoot(), activeTeamTemp);
			
			updateTeamId(team1->data->getRootOfIds(), newTeamId);

			teamsInSystem.find(teamsInSystem.getRoot(), activeTeamTemp)->data->setNewId(newTeamId);
			if (activeTeam1 != nullptr)
			{
				activeTeam1->data->setNewId(newTeamId);
			}

		}
		else
		{
			findTeam(teamId1, false)->data->setNewId(teamId1);
		}
		remove_team(teamId2);
	}
	else
	{
		Team activeTeamTemp2(teamId2, 0);
		Node<Team>* activeTeam2 = activeTeams.find(activeTeams.getRoot(), activeTeamTemp2);
		
		if (team1 == nullptr)
		{
			team2->data->setNewId(newTeamId);
			updateTeamId(team2->data->getRootOfIds(), newTeamId);
			findTeam(teamId2, true)->data->setNewId(newTeamId);

			if (activeTeam2 != nullptr)
			{
				activeTeam2->data->setNewId(newTeamId);
			}

			remove_team(teamId1);
		}
		else
		{
			Node<Team>* activeTeam = activeTeams.find(activeTeams.getRoot(), *team1->data);

			team1->data->mergeTeams(*team2->data);
			team1->data->setNewId(newTeamId);
			
			updateTeamId(team1->data->getRootOfIds(), newTeamId);

			findTeam(teamId1, true)->data->setNewId(newTeamId);

			if (activeTeam == nullptr && team1->data->getPlayersCount() >= 11 && team1->data->hasGoalKeeper())
			{
				activeTeams.insert(team1->data);
			}
			else if (activeTeam != nullptr)
			{
				activeTeams.remove(activeTeam->data);
				activeTeams.insert(team1->data);

			}

			if (activeTeam2 != nullptr)
			{
				activeTeams.remove(activeTeam2->data);
			}

			nonEmptyTeams.remove(team2->data);
			teamsInSystem.remove(findTeam(teamId2, true)->data);
			this->totalTeams--;
		}
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0)
		return StatusType::INVALID_INPUT;
	if (teamId < 0)
	{
		if (playersById.getNodesNum() == 0)
			return StatusType::FAILURE;
		return output_t<int>(topScorer[0]);
	}
	else //teamId > 0
	{
		Node<Team>* currentTeam = findTeam(teamId, false);
		if (currentTeam == nullptr || currentTeam->data->getPlayersCount() == 0)
		{
			return StatusType::FAILURE;
		}
		return output_t<int>(currentTeam->data->getTopScorer());
	}
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0)
	{
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	else if (teamId < 0)
	{
		int totalPlayers = playersById.getNodesNum();
		return output_t<int>(totalPlayers);
	}
	else //teamId > 0
	{
		Node<Team>* team = findTeam(teamId, false);
		int totalPlayersInTeam = 0;

		if (team == nullptr && findTeam(teamId, true) == nullptr)
		{
			return output_t<int>(StatusType::FAILURE);
		}
		else if (team != nullptr)
		{
			totalPlayersInTeam = team->data->getPlayersCount();
		}
		
		return output_t<int>(totalPlayersInTeam);
	}
}

StatusType world_cup_t::get_all_players(int teamId, int* const output)
{
	if (teamId == 0 || output == nullptr)
	{
		return StatusType::INVALID_INPUT;
	}
	else if (teamId < 0)
	{
		if (playersById.getNodesNum() == 0)
			return StatusType::FAILURE;
		int index = 0;
		PlayerByStats* const playersOutput = new PlayerByStats[playersByStats.getNodesNum()];
		playersByStats.inOrder(playersByStats.getRoot(), playersOutput, index);
		for (int i = 0; i < playersByStats.getNodesNum(); i++)
		{
			output[i] = playersOutput[i].getPlayerId();
		}
		delete[] playersOutput;
	}
	else //teamId > 0
	{
		Node<Team>* currentTeam = findTeam(teamId, true);
		if (currentTeam == nullptr || currentTeam->data->getPlayersCount() == 0)
		{
			return StatusType::FAILURE;
		}
		PlayerByStats* const playersOutput = new PlayerByStats[currentTeam->data->getPlayersCount()];
		currentTeam->data->inOrderPlayers(output, playersOutput);
		delete[] playersOutput;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	//take care of statusTypes
	if (minTeamId < 0 || maxTeamId < 0 || minTeamId > maxTeamId)
		return StatusType::INVALID_INPUT;

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
	int firstResult = 0;
	int secondResult = 0;

	for (int i = 0; i < size; i += 2)
	{
		if (i % 2 == 0 && i == size - 1)
		{
			remainingTeams[j] = participatingTeams[i];
			break;
		}

		firstResult = participatingTeams[i].getTeamPower();
		secondResult = participatingTeams[i + 1].getTeamPower();

		if (firstResult > secondResult)
		{
			participatingTeams[i].addPoints(3 + participatingTeams[i + 1].getTeamPoints());
			remainingTeams[j] = participatingTeams[i];
		}
		else //draw or second team won
		{
			participatingTeams[i + 1].addPoints(3 + participatingTeams[i].getTeamPoints());
			remainingTeams[j] = participatingTeams[i + 1];
		}
		j++;
	}
	int winnerId;
	if (size % 2 == 0)
	{
		output_t<int> winner = knockout_winner_aux(minTeamId, maxTeamId, remainingTeams, j);
		winnerId = winner.ans();
	}
	else
	{
		output_t<int> winner = knockout_winner_aux(minTeamId, maxTeamId, remainingTeams, j + 1);
		winnerId = winner.ans();
	}
	delete[] remainingTeams;
	return output_t<int>(winnerId);
}