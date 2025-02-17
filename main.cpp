#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

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
            << setw(20) << player.pointsPerGamePlayed
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
        cout << "File not found !" << endl;
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
        cout << "File not found !" << endl;
    }
}

int main() {
    cout << "[ ..READING FROM CSV FILE ]";
    readCSV();

    vector<Player> p;
    load("nhlstats2324.csv", p);

    cout << "\n[ ..READING CSV FILE FROM VECTOR OF STRUCTS ]";
    headers();
    for (int i = 0; i < p.size(); i++) {
        displayPlayer(p[i]);
    }
}