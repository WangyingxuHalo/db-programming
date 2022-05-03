#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include "query_funcs.h"

using namespace std;

void drop_tables(connection *C);
void create_player(connection *C);
void create_team(connection *C);
void create_state(connection *C);
void create_color(connection *C);
void create_tables(connection *C);
void insert_player(connection *C);
void insert_team(connection *C);
void insert_state(connection *C);
void insert_color(connection *C);
void insert_info(connection *C);
