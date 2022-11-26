#define ACTIVETEAMS_H_

#include "AVLTree.h"
#include "Team.h"

enum mode{removeFlag, insertFlag, checkFlag};
class ActiveTeams
{
private:
	AVLTree<Team> teams;
	int NumOfActiveTeams;


public:
	AVLTree<Team> updateActiveTeams(Team& currentTeam, mode flag);
};
