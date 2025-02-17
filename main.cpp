#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void readCSV();

int main() {
    readCSV();
}

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

    // getline(ss, player.iceTimePerGamePlayed);
    getline(ss, player.iceTimePerGamePlayed, ',');
}

void readCSV() {
    ifstream fin("nhlstats2324.csv");

    if (fin) {
        while (!fin.eof()) {
            string line;
            getline(fin, line);

            Player player;

            if (line.length() > 0) {
                parse(line, player);
                cout << player.name << ", "
                << player.team << ", " << player.position << ", "
                << player.gamesPlayed << ", " << player.goals << ", "
                << player.points << ", " << player.pointsPerGamePlayed << ", "
                << player.iceTimePerGamePlayed
                << endl;
            }
        }
        fin.close();
    }
    else {
        cout << "File not found !" << endl;
    }
}