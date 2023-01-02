// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "worldcup23a1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_players(string cmd, world_cup_t *obj, int teamID);

int main()
{
    cin >> std::boolalpha;
	
    int d1, d2, d3, d4, d5;
    bool b1;

    // Init
	world_cup_t *obj = new world_cup_t();
	
    // Execute all commands in file
	string op;
	while (cin >> op)
    {
        if (!op.compare("add_team")) {
            cin >> d1 >> d2;
            print(op, obj->add_team(d1, d2));
        } else if (!op.compare("remove_team")) {
            cin >> d1;
            print(op, obj->remove_team(d1));
        } else if (!op.compare("add_player")) {
            cin >> d1 >> d2 >> d3 >> d4 >> d5 >> b1;
            print(op, obj->add_player(d1, d2, d3, d4, d5, b1));
        } else if (!op.compare("remove_player")) {
            cin >> d1;
            print(op, obj->remove_player(d1));
        } else if (!op.compare("update_player_stats")) {
            cin >> d1 >> d2 >> d3 >> d4;
            print(op, obj->update_player_stats(d1, d2, d3, d4));
        } else if (!op.compare("play_match")) {
            cin >> d1 >> d2;
            print(op, obj->play_match(d1, d2));
        } else if (!op.compare("get_num_played_games")) {
            cin >> d1;
            print(op, obj->get_num_played_games(d1));
        } else if (!op.compare("get_team_points")) {
            cin >> d1;
            print(op, obj->get_team_points(d1));
        } else if (!op.compare("unite_teams")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->unite_teams(d1, d2, d3));
        } else if (!op.compare("get_top_scorer")) {
            cin >> d1;
            print(op, obj->get_top_scorer(d1));
        } else if (!op.compare("get_all_players_count")) {
            cin >> d1;
            print(op, obj->get_all_players_count(d1));
        } else if (!op.compare("get_all_players")) {
            cin >> d1;
            query_get_all_players(op, obj, d1);
        } else if (!op.compare("get_closest_player")) {
            cin >> d1 >> d2;
            print(op, obj->get_closest_player(d1, d2));
        } else if (!op.compare("knockout_winner")) {
            cin >> d1 >> d2;
            print(op, obj->knockout_winner(d1, d2));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit 
	delete obj;
	return 0;
}

// Helpers
static const char *StatusTypeStr[] =
{
   	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print(string cmd, StatusType res) 
{
	cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_players(string cmd, world_cup_t *obj, int teamID)
{
	output_t<int> count = obj->get_all_players_count(teamID);
    // Allocate if okay
    int *out_mem = nullptr;
	if (count.status() == StatusType::SUCCESS && (count.ans() > 0)) {
        out_mem = new int[count.ans()];
        for (int i = 0; i < count.ans(); ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_players(teamID, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
	    for (int i = 0; i < count.ans(); ++i)
        {
		    cout << out_mem[i] << endl;
	    }
    }
    delete[] out_mem;
}
