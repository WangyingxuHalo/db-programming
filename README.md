# Database Programming with C++
For this project, I use C++ to operate Postgres database <br>

## Database Layout
There are 5 tables for this project: <br>
1: PLAYER <br>
PLAYER (PLAYER_ID, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) <br>
2: TEAM <br>
TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES) <br>
3: STATE <br>
STATE (STATE_ID, NAME)
4: COLOR <br>
COLOR (COLOR_ID, NAME)

## Implemented Functions
1) show all attributes of each player with average statistics that fall between the min and max (inclusive) for each enabled statistic <br>
2) show the name of each team with the indicated uniform color <br>
3) show the first and last name of each player that plays for the indicated team, ordered from highest to lowest ppg (points per game) <br>
4) show first name, last name, and jersey number of each player that plays in the indicated state and wears the indicated uniform color <br>
5) show first name and last name of each player, and team name and number of wins for each team that has won more than the indicated number of games <br>
