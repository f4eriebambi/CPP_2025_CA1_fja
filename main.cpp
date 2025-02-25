#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

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

void headers() {
    cout << left
            << "\n- NHL PLAYER STATS 23/24 SEASON -\n\n"
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

void displayPlayer(const Player &player) {
    cout << left
            << setw(24) << player.name
            << setw(10) << player.team
            << setw(10) << player.position
            << setw(15) << player.gamesPlayed
            << setw(10) << player.goals
            << setw(10) << player.points
            << setw(20) << fixed << setprecision(2) << player.pointsPerGamePlayed // https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
            << setw(20) << player.iceTimePerGamePlayed
            << endl;
}

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

void readCSV() {
    ifstream fin("nhlstats2324.csv");

    if (fin) {
        headers();
        while (!fin.eof()) {
            string line;
            getline(fin, line);

            Player player;

            if (line.length() > 0) {
                parse(line, player);
                // cout << player.name << ", "
                // << player.team << ", " << player.position << ", "
                // << player.gamesPlayed << ", " << player.goals << ", "
                // << player.points << ", " << player.pointsPerGamePlayed << ", "
                // << player.iceTimePerGamePlayed
                // << endl;

                displayPlayer(player);
            }
        }
        fin.close();
    }
    else {
        cout << "\nFile not found !" << endl;
    }
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

int searchPosition(const vector<Player> &players, char position = 'p') {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].position == position) {
            return i;
        }
    }
    return -1;
}

int countRows(const vector<Player> &players) {
    vector<Player>::const_iterator iter;
}

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
        cout << "No players found on the team " << team << endl;
    }
}

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

int main() {
    // STAGE 1
    cout << "[ ..READING FROM CSV FILE ]";
    readCSV();


    //STAGE 2
    cout << "\n[ ..READING CSV FILE WITH VECTOR OF STRUCTS ]";
    vector<Player> p;
    load("nhlstats2324.csv", p);
    headers();
    for (int i = 0; i < p.size(); i++) {
        displayPlayer(p[i]);
    }


    // STAGE 3
    cout << "\n[testing display func]";
    headers();
    display(p);
    cout << "\n[testing searchPosition]\n";
    int index = searchPosition(p, 'D');
    if (index == -1) {
        cout << "No player(s) found at the index" << endl;
    }
    else {
        headers();
        cout << "Player found at Index " << index << " ::\n" << endl;
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
    cout << "\n[testing displayPlayerByTeam]\n";
    cout << "Enter a team name : \n";
    string team;
    cin >> team;
    headers();
    cout << "PLayer(s) of " << team << " ::\n\n";
    displayPlayerByTeam(p, team);
    cout << "\n[testing highLowAvgGoals]\n";
    Player highestScorer;
    Player lowestScorer;
    highLowAvgGoals(p, highestScorer, lowestScorer);
}