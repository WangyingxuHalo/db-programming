#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
    work W(*C);
    stringstream ss;
    ss << "INSERT INTO PLAYER(TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG)VALUES(" <<
    team_id << "," << jersey_num << "," << W.quote(first_name) << "," << W.quote(last_name) << "," << mpg << "," <<
    ppg << "," << rpg << "," << apg << "," << spg << "," << bpg << ");";
    string sql = ss.str();
    W.exec(sql);
    W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    work W(*C);
    stringstream ss;
    ss << "INSERT INTO TEAM(NAME, STATE_ID, COLOR_ID, WINS, LOSSES)VALUES(" <<
    W.quote(name) << "," << state_id << "," << color_id << "," << wins << "," << losses << ");";
    string sql = ss.str();
    W.exec(sql);
    W.commit();
}


void add_state(connection *C, string name)
{
    work W(*C);
    stringstream ss;
    ss << "INSERT INTO STATE(NAME)VALUES(" <<
    W.quote(name) << ");";
    string sql = ss.str();
    W.exec(sql);
    W.commit();
}


void add_color(connection *C, string name)
{
    work W(*C);
    stringstream ss;
    ss << "INSERT INTO COLOR(NAME)VALUES(" <<
    W.quote(name) << ");";
    string sql = ss.str();
    W.exec(sql);
    W.commit();
}

// Show all attributes of each player with average statistics that fall between teh min and max for each enabled statistics
void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
    string sql = "SELECT * FROM PLAYER";
    string points[6] = {"MPG", "PPG", "RPG", "APG", "SPG", "BPG"};
    int uses[6] = {use_mpg, use_ppg, use_rpg, use_apg, use_spg, use_bpg};
    int min_data_int[4] = {min_mpg, min_ppg, min_rpg, min_apg};
    int max_data_int[4] = {max_mpg, max_ppg, max_rpg, max_apg};
    double min_data_double[2] = {min_spg, min_bpg};
    double max_data_double[2] = {max_spg, max_bpg};
    bool is_first = true;
    int last_one = 0;
    for (int i = 0 ; i < 6; i++) {
        if (uses[i] != 0) {
            last_one = i;
        }
    }
    for (int i = 0 ; i < 6; i++) {
        if (uses[i] != 0) {
            if (is_first) {
                sql += " WHERE ";
                is_first = false;
            }
            // int
            if (i <= 3) {
                sql += points[i] + " >= " + to_string(min_data_int[i]) + " AND " + points[i] + " <= " + to_string(max_data_int[i]);
            } else {
            // double
                sql +=  points[i] + " >= " + to_string(min_data_double[i - 4]) + " AND " + points[i] + " <= " + to_string(max_data_double[i - 4]);
            }
            if ( i != last_one) {
                sql += " AND ";
            } else {
                sql += ";";
            }
        }
    }
    // cout << sql << endl;
    nontransaction N(*C);
    result R( N.exec( sql ));
    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << fixed << setprecision(1) << c[0].as<int>() << " " << c[1].as<int>() << " " << c[2].as<int>() << " " << c[3].as<string>() << " " << c[4].as<string>() << " " << c[5].as<int>() << " " << c[6].as<int>() << " " << c[7].as<int>() << " " << c[8].as<int>() << " " << c[9].as<double>() << " " << c[10].as<double>() << endl;
    }
}

// Show the name of each team with the indicated uniform color
void query2(connection *C, string team_color)
{
    string sql = "SELECT TEAM.NAME FROM TEAM, COLOR WHERE COLOR.NAME = \'" + team_color + "\' AND TEAM.COLOR_ID = COLOR.COLOR_ID;";
    // cout << sql << endl;
    nontransaction N(*C);
    result R( N.exec( sql ));
    cout << "NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << endl;
    }
}

// Show the first and last name of each player that plays for the indicated team, ordered from highest to lowest ppg
void query3(connection *C, string team_name)
{
    string sql = "SELECT FIRST_NAME,LAST_NAME FROM PLAYER,TEAM WHERE TEAM.NAME = \'" + team_name + "\' AND PLAYER.TEAM_ID = TEAM.TEAM_ID ORDER BY PPG DESC;";
    // cout << sql << endl;
    nontransaction N(*C);
    result R( N.exec( sql ));
    cout << "FIRST_NAME LAST_NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << " " << c[1].as<string>() << endl;
    }
}

// Show tfirst name, last name, and jersey number of each player that plays in the indicated state and wears the indicated uniform color
void query4(connection *C, string team_state, string team_color)
{
    string sql = "SELECT UNIFORM_NUM,FIRST_NAME,LAST_NAME FROM PLAYER,TEAM,STATE,COLOR WHERE STATE.NAME = \'" + team_state + "\' AND COLOR.NAME = \'" + team_color + "\' AND PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.STATE_ID = STATE.STATE_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID;";
    // cout << sql << endl;
    nontransaction N(*C);
    result R( N.exec( sql ));
    cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<int>() << " " << c[1].as<string>() << " " << c[2].as<string>() << endl;
    }
}

// Show first name and last name of eeach player, and team name and number of wins for each team that has won more than the indicated number of games
void query5(connection *C, int num_wins)
{
    string sql = "SELECT FIRST_NAME,LAST_NAME,NAME,WINS FROM PLAYER,TEAM WHERE WINS > " + to_string(num_wins) + " AND PLAYER.TEAM_ID = TEAM.TEAM_ID;";
    // cout << sql << endl;
    nontransaction N(*C);
    result R( N.exec( sql ));
    cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << " " << c[1].as<string>() << " " << c[2].as<string>() << " " << c[3].as<int>() << endl;
    }
}