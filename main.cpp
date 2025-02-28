#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <map>
#include <cctype>

using namespace std;

void headers() {
    cout << left
            << "\n========== NHL PLAYER STATS 23/24 SEASON ==========\n"
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
void load(const string fileName, vector<Player> &players) {
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

// ---- STAGE 3.2 ----
// int searchPosition(const vector<Player> &players, char position) { // ONLY GETTING FIRST INDEX MATCH OF SEARCHED HOCKEY POSITION ::old code
//     for (int i = 0; i < players.size(); i++) {
//         if (players[i].position == position) {
//             return i;
//         }
//     }
//     return -1;
// }
// ---- STAGE 3.2 ----
vector<int> searchPosition(const vector<Player> &players, char position) { // GETTING ALL INDEX MATCHES OF SEARCHED HOCKEY POSITION
    vector<int> positionMatches;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].position == position) {
            positionMatches.push_back(i);
        }
    }
    return positionMatches;
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
            if (!found) {
                cout << "- Player(s) of " << team << " ::";
                headers();
                found = true;
            }
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

    cout << "\n========== NHL PLAYER STATS 23/24 SEASON ==========\n";
    cout << "Highest Number of Goals :: " << max << " goals made by "
    << highestScorer.name << endl;
    cout << "Lowest Number of Goals :: " << min << " goal(s) made by "
    << lowestScorer.name << endl;
    cout << "Average Goals Scored :: " << averageGoal << endl;

    return averageGoal;
}

// ---- STAGE 3.6 ----
list<Player> searchPlayerName(const vector<Player> &players, const string &search) {
    list<Player> pList;
    string searchUpper;
    for (char c : search) {
        if (!isspace(c)) { // https://www.scaler.com/topics/removing-whitespace-from-a-string-in-cpp/
            searchUpper.push_back(toupper(c));
        }
    }

    vector<Player>::const_iterator iter;
    for (iter = players.cbegin(); iter != players.cend(); iter++) {
        string nameUpper;
        for (char c : iter->name) {
            if (!isspace(c)) {
                nameUpper.push_back(toupper(c));
            }
        }

        if (nameUpper.find(searchUpper) != string::npos) { // https://stackoverflow.com/questions/29461786/partial-string-search-in-c
            pList.push_back(*iter);
        }
    }
    return pList;
}

// ---- STAGE 3.7 ----
int descendingPointsPerGame(const Player &x, const Player &y) {
    return x.pointsPerGamePlayed > y.pointsPerGamePlayed;
}

void printMenu() {
    cout << "\n--------------------------------------------------\n";
    cout << " ============ NHL PLayer Stats Menu =============\n";
    cout << "--------------------------------------------------\n";
    cout << "1. Display All Players____.\n";
    cout << "2. Search Players by Position____.\n";
    cout << "3. Count Players on Teams____.\n";
    cout << "4. Display Players of Team____.\n";
    cout << "5. Highest+Lowest Number of Goals & Average Goals of 23/24____.\n";
    cout << "6. Search Players by Name____.\n";
    cout << "7. Sort Players by Points Per Game in Descending Order____.\n";
    cout << "8. Exit.\n";
    cout << "--------------------------------------------------\n";
    cout << " ============ SELECT AN OPTION =============\n";
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


    // ---- MENU ----
    int choice = 0;
    while (choice != 8) {
        printMenu();
        // cin >> choice;

        if (!(cin >> choice)) { // https://cplusplus.com/forum/beginner/142433/
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "INVALID OPTION - Try again ><" << endl;
            continue;
        }
        cin.ignore();

        switch (choice) {
            // ---- STAGE 3.1 ----
            case 1: {
                cout << "\n[ ..DISPLAYING ALL PLAYERS ]";
                headers();
                display(p);
                break;
            }
            // ---- STAGE 3.2 ----
            case 2: {
                cout << "\n[ .. SEARCH PLAYER BY POSITION ]\n";
                cout << "Enter the hockey position you would like to see players of - Enter C, D, L or R : \n";
                char position;
                cin >> position;
                cin.ignore(1000, '\n');
                position = toupper(position); // https://www.programiz.com/cpp-programming/library-function/cctype/toupper
                // int index = searchPosition(p, position); // ONLY GETTING FIRST INDEX MATCH OF SEARCHED HOCKEY POSITION ::old code
                // if (index != -1) {
                //     cout << "- Player(s) found with position '" << position << "'";
                //     headers();
                //     cout << "index " << index << " ::\n";
                //     cout << left
                //     << setw(24) << p[index].name
                //     << setw(10) << p[index].team
                //     << setw(10) << p[index].position
                //     << setw(15) << p[index].gamesPlayed
                //     << setw(10) << p[index].goals
                //     << setw(10) << p[index].points
                //     << setw(20) << fixed << setprecision(2) << p[index].pointsPerGamePlayed
                //     << setw(20) << p[index].iceTimePerGamePlayed
                //     << endl;
                // }
                // else {
                //     cout << "!! NO INDEX(ES) OF PLAYER(S) WITH POSITION '" << position << "' !!" << endl;
                // }
                // break;

                vector<int> positionMatches = searchPosition(p, position); // GETTING ALL INDEX MATCHES OF SEARCHED HOCKEY POSITION
                if (!positionMatches.empty()) {
                    cout << left
                    << "- Player(s) found with position '" << position << "'";
                    headers();
                    for (int index: positionMatches) {
                        cout << left
                        << "index " << index << " ::\n"
                        << setw(24) << p[index].name
                        << setw(10) << p[index].team
                        << setw(10) << p[index].position
                        << setw(15) << p[index].gamesPlayed
                        << setw(10) << p[index].goals
                        << setw(10) << p[index].points
                        << setw(20) << fixed << setprecision(2) << p[index].pointsPerGamePlayed
                        << setw(20) << p[index].iceTimePerGamePlayed
                        << "\n" << endl;
                    }
                }
                else {
                    cout << "!! NO INDEX(ES) OF PLAYER(S) WITH POSITION '" << position << "' !!" << endl;
                }
                break;
            }
            // ---- STAGE 3.3 ----
            case 3: {
                cout << "\n[ ..COUNT PLAYERS ON TEAMS ]";
                cout << left
                << "\n========== NHL PLAYER STATS 23/24 SEASON ==========\n"
                << setw(24) << "Team"
                << setw(10) << "Player Count"
                << "\n----------------------------------------------------------------------------------------------------------------------"
                << endl;
                map<string,int> countPlayers = countTeamPlayerRows(p);
                for (const auto &teamCount : countPlayers) {
                    cout << left
                    // https://www.geeksforgeeks.org/pair-in-cpp-stl/
                    << setw(24) << teamCount.first
                    << setw(10) << teamCount.second
                    << endl;
                }
                break;
            }
            // ---- STAGE 3.4 ----
            case 4: {
                cout << "\n[ ..DISPLAY PLAYERS OF TEAM ]\n";
                cout << "Enter a team name (3 letter format) : \n";
                string team;
                cin >> team;
                for (char &c : team) {
                    c = toupper(c);
                }
                displayPlayerByTeam(p, team);
                break;
            }
            // ---- STAGE 3.5 ----
            case 5: {
                cout << "\n[ ..HIGHEST, LOWEST GOAL SCORERS & AVERAGE GOALS OF 23/24 ]\n";
                Player highestScorer;
                Player lowestScorer;
                highLowAvgGoals(p, highestScorer, lowestScorer);
                break;
            }
            // ---- STAGE 3.6 ----
            case 6: {
                cout << "\n[ ..SEARCH PLAYER BY NAME ]\n";
                cout << "Enter name to search player(s) : \n";
                string search;
                getline(cin, search);

                list<Player> searchNames = searchPlayerName(p, search);
                if (!searchNames.empty()) {
                    cout << "- Player(s) found with name containing '" << search << "' ::";
                    headers();
                    for (const Player &player : searchNames) {
                        displayPlayer(player);
                    }
                }
                else {
                    cout << "!! NO PLAYER(S) FOUND WITH A NAME CONTAINING '" << search << "' !!" << endl;
                }
                break;
            }
            // ---- STAGE 3.7 ----
            case 7: {
                cout << "\n[ ..PLAYERS SORTED BY 'Points Per Game' IN DESCENDING ORDER ]\n";
                vector <Player> pDesc = p;
                sort(pDesc.begin(), pDesc.end(), descendingPointsPerGame);
                cout << "\n- Players sorted by 'Points Per Game' in descending order ::";
                headers();
                display(pDesc);
                break;
            }
            case 8: {
                cout << "[ ..EXITING ] Thank you for using this program~" << endl;
                break;
            }
            default: {
                cout << "INVALID OPTION - Please enter a valid option :1" << endl;
                break;
            }
        }
    }
    return 0;
}