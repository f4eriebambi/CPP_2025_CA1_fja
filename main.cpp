#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <map>

using namespace std;

void headers() {
    cout << left
            << "\n========== NHL PLAYER STATS 23/24 SEASON ==========\n"
    // "\n- NHL PLAYER STATS 23/24 SEASON -\n"
            << setw(24) << "Name"
            << setw(10) << "Team"
            << setw(10) << "Position"
            << setw(15) << "Games Played"
            << setw(10) << "Goals"
            << setw(10) << "Points"
            << setw(20) << "Points Per Game"
            << setw(20) << "Ice Time Per Game"
            << "\n----------------------------------------------------------------------------------------------------------------------"
            << endl;
}

// ---- STAGE 1 ----
void parse(string line, string &name, string &team, char &position,
    int &gamesPlayed, int &goals, int &points, float &pointsPerGamePlayed,
    string &iceTimePerGamePlayed) {
    stringstream ss(line);
    string temp;

    getline(ss, name, ',');
    getline(ss, team, ',');

    getline(ss, temp, ',');
    position = temp[0];

    getline(ss, temp, ',');
    gamesPlayed = stoi(temp);

    getline(ss, temp, ',');
    goals = stoi(temp);

    getline(ss, temp, ',');
    points = stoi(temp);

    getline(ss, temp, ',');
    pointsPerGamePlayed = stof(temp);

    getline(ss, iceTimePerGamePlayed, ',');
}
void readCSV() {
    ifstream fin("nhlstats2324.csv");

    if (fin) {
        headers();
        while (!fin.eof()) {
            string line;
            getline(fin, line);

            string name, team, iceTimePerGamePlayed;
            char position;
            int gamesPlayed, goals,  points;
            float pointsPerGamePlayed;

            if (line.length() > 0) {
                parse(line, name, team, position,
                    gamesPlayed, goals, points, pointsPerGamePlayed,
                    iceTimePerGamePlayed);

                cout << left
                << setw(24) << name
                << setw(10) << team
                << setw(10) << position
                << setw(15) << gamesPlayed
                << setw(10) << goals
                << setw(10) << points
                << setw(20) << fixed << setprecision(2) << pointsPerGamePlayed // https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
                << setw(20) << iceTimePerGamePlayed
                << endl;
            }
        }
        fin.close();
    }
    else {
        cout << "\nFile not found !" << endl;
    }
}

// ---- STAGE 2.1 ----
struct Player {
    string name;
    string team;
    char position;
    int gamesPlayed;
    int goals;
    int points;
    float pointsPerGamePlayed;
    string iceTimePerGamePlayed;
};
// ---- STAGE 2.2 ----
void parse(string line, Player &player) {
    stringstream ss(line);
    string temp;

    getline(ss, player.name, ',');
    getline(ss, player.team, ',');

    getline(ss, temp, ',');
    player.position = temp[0];

    getline(ss, temp, ',');
    player.gamesPlayed = stoi(temp);

    getline(ss, temp, ',');
    player.goals = stoi(temp);

    getline(ss, temp, ',');
    player.points = stoi(temp);

    getline(ss, temp, ',');
    player.pointsPerGamePlayed = stof(temp);

    getline(ss, player.iceTimePerGamePlayed);
}
void load(string fileName, vector<Player> &players) {
    ifstream fin(fileName);
    if (fin) {
        string line;
        while (getline(fin, line)) {
            Player player;
            parse(line, player);
            players.push_back(player);
        }
        fin.close();
    }
    else {
        cout << "\nFile not found !" << endl;
    }
}
void displayPlayer(const Player &player) {
    cout << left
            << setw(24) << player.name
            << setw(10) << player.team
            << setw(10) << player.position
            << setw(15) << player.gamesPlayed
            << setw(10) << player.goals
            << setw(10) << player.points
            << setw(20) << fixed << setprecision(2) << player.pointsPerGamePlayed
            << setw(20) << player.iceTimePerGamePlayed
            << endl;
}

// ---- STAGE 3.1 ----
void display(const vector<Player> &players) {
    vector<Player>::const_iterator iter;
    for (iter = players.cbegin(); iter != players.cend(); iter++) {
        if (iter != players.cbegin()) {
            cout << left
            << setw(24) << iter->name
            << setw(10) << iter->team
            << setw(10) << iter->position
            << setw(15) << iter->gamesPlayed
            << setw(10) << iter->goals
            << setw(10) << iter->points
            << setw(20) << fixed << setprecision(2) << iter->pointsPerGamePlayed
            << setw(20) << iter->iceTimePerGamePlayed
            << endl;
        }
    }
}

// ---- STAGE 3.2 ----
int searchPosition(const vector<Player> &players, char position) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].position == position) {
            return i;
        }
    }
    return -1;
}

// ---- STAGE 3.3 ----
map<string,int> countTeamPlayerRows(const vector<Player> &players) { // https://www.geeksforgeeks.org/map-of-vectors-in-c-stl-with-examples/
    map<string, int> count;
    for (int i = 0; i < players.size(); i++) {
        count[players[i].team]++;
    }
    return count;
}

// ---- STAGE 3.4 ----
void displayPlayerByTeam(const vector<Player> &players, const string &team) {
    bool found = false;
    for (const Player &player : players) {
        if (player.team == team) {
            cout << left
            << setw(24) << player.name
            << setw(10) << player.team
            << setw(10) << player.position
            << setw(15) << player.gamesPlayed
            << setw(10) << player.goals
            << setw(10) << player.points
            << setw(20) << fixed << setprecision(2) << player.pointsPerGamePlayed
            << setw(20) << player.iceTimePerGamePlayed
            << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "!! NO PLAYERS FOUND ON THE TEAM '" << team << "' !!" << endl;
    }
}

// ---- STAGE 3.5 ----
int highLowAvgGoals(const vector<Player> &players, Player &highestScorer, Player &lowestScorer) {
    int max = INT_MIN;
    int min = INT_MAX;
    double total = 0;
    // Player highestScorer;
    // Player lowestScorer;

    for (const Player &player : players) {
        if (player.goals > max) {
            max = player.goals;
            highestScorer = player;
        }
        if (player.goals < min) {
            min = player.goals;
            lowestScorer = player;
        }
        total += player.goals;
    }
    double average = total / players.size();
    int averageGoal = (int)round(average);

    cout << "Highest Number of Goals made in 23/24 Season :: " << max<< ", made by "
    << highestScorer.name << endl;
    cout << "Lowest Number of Goals made in 23/24 Season :: " << min << ", made by "
    << lowestScorer.name << endl;
    cout << "Average Goals Scored in 23/24 Season :: " << averageGoal << endl;

    return averageGoal;
}

// ---- STAGE 3.6 ----
list<Player> searchPlayerName(const vector<Player> &players, const string &search) {
    list<Player> pList;
    vector<Player>::const_iterator iter;
    for (iter = players.cbegin(); iter != players.cend(); iter++) {
        if (iter->name.find(search) != string::npos) { // https://stackoverflow.com/questions/29461786/partial-string-search-in-c
            pList.push_back(*iter);
        }
    }
    return pList;
}

// ---- STAGE 3.7 ----
int descendingPointsPerGame(const Player &x, const Player &y) {
    return x.pointsPerGamePlayed > y.pointsPerGamePlayed;
}

int main() {
    // ---- STAGE 1 ----
    cout << "[ ..READING FROM CSV FILE ]";
    readCSV();


    // ---- STAGE 2 ----
    cout << "\n[ ..READING CSV FILE WITH VECTOR OF STRUCTS ]";
    vector<Player> p;
    load("nhlstats2324.csv", p);
    headers();
    for (int i = 0; i < p.size(); i++) {
        displayPlayer(p[i]);
    }


    // ---- STAGE 3.1 ----
    cout << "\n[ ..testing display func ]";
    headers();
    display(p);
    // ---- STAGE 3.2 ----
    cout << "\n[ ..testing searchPosition ]\n";
    cout << "ENTER THE HOCKEY POSITION YOU WOULD LIKE TO SEE PLAYER OF (C/D/L/R) : \n";
    char position;
    cin >> position;
    int index = searchPosition(p, position);
    if (index == -1) {
        cout << "!! NO PLAYER(S) FOUND AT THE INDEX !!" << endl;
    }
    else {
        headers();
        cout << "- PLAYER FOUND AT INDEX " << index << " ::\n" << endl;
        cout << left
        << setw(24) << p[index].name
        << setw(10) << p[index].team
        << setw(10) << p[index].position
        << setw(15) << p[index].gamesPlayed
        << setw(10) << p[index].goals
        << setw(10) << p[index].points
        << setw(20) << fixed << setprecision(2) << p[index].pointsPerGamePlayed
        << setw(20) << p[index].iceTimePerGamePlayed
        << endl;
    }
    // ---- STAGE 3.3 ----
    cout << "\n[ ..testing countTeamPlayerRows ]";
    cout << left
    << "\n========== NHL PLAYER STATS 23/24 SEASON ==========\n"
    << setw(24) << "Team"
    << setw(10) << "Player Count"
    << "\n----------------------------------------------------------------------------------------------------------------------"
    << endl;

    map<string,int> countPlayers = countTeamPlayerRows(p);
    for (const auto &teamCount : countPlayers) {
        cout << left
            << setw(24) << teamCount.first << setw(10) << teamCount.second << endl; // https://www.geeksforgeeks.org/pair-in-cpp-stl/
    }
    // ---- STAGE 3.4 ----
    cout << "\n[ ..testing displayPlayerByTeam ]\n";
    cout << "ENTER A TEAM NAME (case-sensitive only UPPERCASE and in 3 letter format) : \n";
    string team;
    cin >> team;
    headers();
    cout << "- PLAYER(S) OF " << team << " ::\n\n";
    displayPlayerByTeam(p, team);
    // ---- STAGE 3.5 ----
    cout << "\n[ ..testing highLowAvgGoals ]\n";
    Player highestScorer;
    Player lowestScorer;
    highLowAvgGoals(p, highestScorer, lowestScorer);
    // ---- STAGE 3.6 ----
    cout << "\n[ ..testing searchPlayerName ]\n";
    cout << "ENTER NAME TO SEARCH PLAYER(S) : \n";
    string search;
    cin >> search;
    list<Player> searchNames = searchPlayerName(p, search);
    if (!searchNames.empty()) {
        headers();
        cout << "- PLAYER(S) FOUND WITH A NAME CONTAINING '" << search << "' ::\n" << endl;
        for (const Player &player : searchNames) {
            displayPlayer(player);
        }
    }
    else {
        cout << "!! NO PLAYER(S) FOUND WITH A NAME CONTAINING '" << search << "' !!" << endl;
    }
    // ---- STAGE 3.7 ----
    cout << "\n[ ..testing descendingPointsPerGame ]";
    vector <Player> pDesc = p;
    sort(pDesc.begin(), pDesc.end(), descendingPointsPerGame);
    headers();
    cout << "- PLAYERS SORTED BY 'Points Per Game' IN DESCENDING ORDER ::\n" << endl;
    display(pDesc);
}