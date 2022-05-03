#include "my_functions.h"

void drop_tables(connection *C) {
    string table_names[4] = {"PLAYER", "TEAM", "STATE", "COLOR"};
    for (int i = 0; i < 4; i++) {
        string sql = "DROP TABLE IF EXISTS " + table_names[i] + " CASCADE;";
        work W(*C);
        W.exec(sql);
        W.commit();
    }
    // cout << "drop successfully" << endl;
}

void create_player(connection *C) {
    string sql = "CREATE TABLE PLAYER(\n";
    sql += "PLAYER_ID SERIAL,\n";
    sql += "TEAM_ID INT,\n";
    sql += "UNIFORM_NUM INT,\n";
    sql += "FIRST_NAME VARCHAR(255),\n";
    sql += "LAST_NAME VARCHAR(255),\n";
    sql += "MPG INT,\n";
    sql += "PPG INT,\n";
    sql += "RPG INT,\n";
    sql += "APG INT,\n";
    sql += "SPG DOUBLE PRECISION,\n";
    sql += "BPG DOUBLE PRECISION,\n";
    sql += "PRIMARY KEY (PLAYER_ID),\n";
    sql += "FOREIGN KEY(TEAM_ID) REFERENCES TEAM (TEAM_ID) ON UPDATE CASCADE\n";
    sql += ");";
    work W(*C);
    W.exec(sql);
    W.commit();
    // cout << "create player successfully" << endl;
}

void create_team(connection *C) {
    string sql = "CREATE TABLE TEAM(\n";
    sql += "TEAM_ID SERIAL,\n";
    sql += "NAME VARCHAR(255),\n";
    sql += "STATE_ID INT,\n";
    sql += "COLOR_ID INT,\n";
    sql += "WINS INT,\n";
    sql += "LOSSES INT,\n";
    sql += "PRIMARY KEY (TEAM_ID),\n";
    sql += "FOREIGN KEY(STATE_ID) REFERENCES STATE (STATE_ID) ON UPDATE CASCADE,\n";
    sql += "FOREIGN KEY(COLOR_ID) REFERENCES COLOR (COLOR_ID) ON UPDATE CASCADE";
    sql += ");";
    work W(*C);
    W.exec(sql);
    W.commit();
    // cout << "create team successfully" << endl;
}

void create_state(connection *C) {
    string sql = "CREATE TABLE STATE(\n";
    sql += "STATE_ID SERIAL,\n";
    sql += "NAME VARCHAR(255),\n";
    sql += "PRIMARY KEY (STATE_ID)";
    sql += ");";
    work W(*C);
    W.exec(sql);
    W.commit();
    // cout << "create state successfully" << endl;
}

void create_color(connection *C) {
    string sql = "CREATE TABLE COLOR(\n";
    sql += "COLOR_ID SERIAL,\n";
    sql += "NAME VARCHAR(255),\n";
    sql += "PRIMARY KEY (COLOR_ID)";
    sql += ");";
    work W(*C);
    W.exec(sql);
    W.commit();
    // cout << "create color successfully" << endl;
}

void create_tables(connection *C) {
    create_state(C);
    create_color(C);
    create_team(C);
    create_player(C);
    // cout << "finish create tables" << endl;
}

void insert_player(connection *C) {
    int player_id, team_id, uniform_num, mpg, ppg, rpg, apg;
    string first_name, last_name;
    double spg, bpg;
    string line;
    ifstream infile("player.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            stringstream ss(line);
            ss >> player_id;
            ss >> team_id;
            ss >> uniform_num;
            ss >> first_name;
            ss >> last_name;
            ss >> mpg;
            ss >> ppg;
            ss >> rpg;
            ss >> apg;
            ss >> spg;
            ss >> bpg;
            add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
        }
        infile.close();
        // cout << "insert player successfully" << endl;
    } else {
        cerr << "Cannot open player file";
        exit(EXIT_FAILURE);
    }
}

void insert_team(connection *C) {
    string name;
    int team_id, state_id, color_id, wins, losses;
    string line;
    ifstream infile("team.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            stringstream ss(line);
            ss >> team_id;
            ss >> name;
            ss >> state_id;
            ss >> color_id;
            ss >> wins;
            ss >> losses;
            add_team(C, name, state_id, color_id, wins, losses);
        }
        infile.close();
        // cout << "insert team successfully" << endl;
    } else {
        cerr << "Cannot open team file";
        exit(EXIT_FAILURE);
    }
}

void insert_state(connection *C) {
    int state_id;
    string name;
    string line;
    ifstream infile("state.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            stringstream ss(line);
            ss >> state_id;
            ss >> name;
            add_state(C, name);
        }
        infile.close();
        // cout << "insert state successfully" << endl;
    } else {
        cerr << "Cannot open state file";
        exit(EXIT_FAILURE);
    }
}

void insert_color(connection *C) {
    int color_id;
    string name;
    string line;
    ifstream infile("color.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            stringstream ss(line);
            ss >> color_id;
            ss >> name;
            add_color(C, name);
        }
        infile.close();
        // cout << "insert color successfully" << endl;
    } else {
        cerr << "Cannot open state file";
        exit(EXIT_FAILURE);
    }
}

void insert_info(connection *C) {
    insert_state(C);
    insert_color(C);
    insert_team(C);
    insert_player(C);
    // cout << "insert finishes" << endl;
}