#include "ActiveTeams.h"

ActiveTeams::ActiveTeams() = default;
AVLTree<Team> ActiveTeams::updateActiveTeams(Team& currentTeam, mode flag)
{
	if (flag == insertFlag)
	{
		if (currentTeam.getPlayersCount() >= 11 && currentTeam.hasGoalKeaper())
		{
			teams.insert(currentTeam);
			NumOfActiveTeams++;
		}
	}
	else if (flag == removeFlag)
	{
		teams.remove(currentTeam);
		NumOfActiveTeams--;
	}
	else if (flag == checkFlag)
	{
		if (currentTeam.getPlayersCount() < 11 || !currentTeam.hasGoalKeaper())
		{
			teams.remove(currentTeam);
			NumOfActiveTeams--;
		}
	}
}
