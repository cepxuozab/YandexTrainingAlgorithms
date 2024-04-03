#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

unordered_map<string, unordered_map<string, vector<int>>> teamScore;
unordered_map<string, unordered_map<string, vector<int>>> playerScore;
unordered_map<string, map<int, int>> playerTime;
unordered_map<string, int> teamFirst;
unordered_map<string, int> playersFirst;
unordered_map<string, set<string>> teamToPlayer;
unordered_map<string, string> playerToTeam;

auto readGoals(const string &team, const string &rival, int goals) -> pair<int, string> {
    string line;
    bool first = true;
    int firstTime = 100;
    string firstPlayer = "";
    unordered_map<string, int> playerGoalsOnMatch;
    for (int i = 0; i < goals; ++i) {
        getline(cin, line);
        size_t pos = line.find_first_of("1234567890");
        string player = line.substr(0, pos - 1);
        stringstream ss(line.substr(pos));
        int time;
        ss >> time;
        if (first) {
            firstTime = time;
            firstPlayer = player;
            first = false;
        }
        if (time > 90) {
            time = 90;
        }
        ++playerGoalsOnMatch[player];
        ++playerTime[player][time];
        teamToPlayer[team].insert(player);
        playerToTeam[player] = team;
    }
    for (auto &[player, go]: playerGoalsOnMatch) {
        playerScore[player][rival].push_back(go);
    }
    return make_pair(firstTime, firstPlayer);
}

void readInfo(const string &line) {
    size_t st = 1;
    size_t pos = line.find('\"', st);
    string team1 = line.substr(1, pos - 1);
    st = line.find('\"', pos + 1);
    pos = line.find('\"', st + 1);
    string team2 = line.substr(st + 1, pos - st - 1);
    stringstream ss(line.substr(pos + 1));
    int goals1, goals2;
    char c;
    ss >> goals1 >> c >> goals2;
    teamScore[team1][team2].push_back(goals1);
    teamScore[team2][team1].push_back(goals2);
    auto [t1, p1] = readGoals(team1, team2, goals1);
    auto [t2, p2] = readGoals(team2, team1, goals2);
    if (t1 < t2) {
        ++teamFirst[team1];
        ++playersFirst[p1];
    } else if (t2 < t1) {
        ++teamFirst[team2];
        ++playersFirst[p2];
    }
}

auto getTotalGoalsForTeam(const string &team) -> int {
    int result = 0;
    for (auto &[rival, vec]: teamScore[team]) {
        for (auto score: vec) {
            result += score;
        }
    }
    return result;
}

auto getTeamName(const string &line) -> string {
    size_t st = line.find('\"', 0);
    size_t pos = line.find('\"', st + 1);
    string team = line.substr(st + 1, pos - st - 1);
    return team;
}

auto getMeanGoalsPerGameForTeam(const string &team) -> float {
    if (teamScore.count(team) == 0) {
        return 0;
    }

    int total = getTotalGoalsForTeam(team);
    size_t gamesCount = 0;
    for (auto &[r, vec]: teamScore[team]) {
        gamesCount += vec.size();
    }
    return float(total) / float(gamesCount);
}

auto getTotalGoalsByPlayer(const string &player) -> int {
    int result = 0;
    for (auto &[rival, vec]: playerScore[player]) {
        for (auto score: vec) {
            result += score;
        }
    }
    return result;
}

auto getMeanGoalsPerGameByPlayer(const string &player) -> float {
    if (playerToTeam.count(player) == 0) {
        return 0;
    }

    string team = playerToTeam[player];

    if (teamScore.count(team) == 0) {
        return 0;
    }

    size_t gamesCount = 0;
    for (auto &[r, vec]: teamScore[team]) {
        gamesCount += vec.size();
    }
    int total = getTotalGoalsByPlayer(player);
    return float(total) / float(gamesCount);
}

auto getGoalsOnMinuteForPlayer(int minute, const string &player) -> int {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    if (playerTime[player].count(minute) == 0) {
        return 0;
    }
    return playerTime[player][minute];
}

auto getGoalsOnFirstMinutesForPlayer(int minutes, const string &player) -> int {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    int result = 0;
    for (auto &[time, goals]: playerTime[player]) {
        if (time <= minutes) {
            result += goals;
        } else {
            break;
        }
    }
    return result;
}

auto getGoalsOnLastMinutesForPlayer(int minutes, const string &player) -> int {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    int result = 0;
    for (auto it = playerTime[player].rbegin(); it != playerTime[player].rend(); ++it) {
        int time = it->first;
        if (time >= 91 - minutes) {
            result += it->second;
        } else {
            break;
        }
    }
    return result;
}

auto getScoreOpensForPlayer(const string &player) -> int {
    if (playersFirst.count(player) == 0) {
        return 0;
    }
    return playersFirst[player];
}

auto getScoreOpensForTeam(const string &team) -> int {
    if (teamFirst.count(team) == 0) {
        return 0;
    }
    return teamFirst[team];
}

auto main() -> int {
    string line;
    getline(cin, line);


    while (!line.empty()) {
        if (line.find("Total goals for ") == 0) {
            string team = getTeamName(line);
            cout << getTotalGoalsForTeam(team) << '\n';
        } else if (line.find("Mean goals per game for ") == 0) {
            string team = getTeamName(line);
            cout << setprecision(17) << getMeanGoalsPerGameForTeam(team) << '\n';
        } else if (line.find("Total goals by ") == 0) {
            string player = line.substr(string("Total goals by ").length());
            cout << getTotalGoalsByPlayer(player) << '\n';
        } else if (line.find("Mean goals per game by ") == 0) {
            string player = line.substr(string("Mean goals per game by ").length());
            cout << setprecision(17) << getMeanGoalsPerGameByPlayer(player) << '\n';
        } else if (line.find("Goals on minute ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minute;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minute;
            pos = line.find("by ");
            string player = line.substr(pos + string("by ").length());
            cout << getGoalsOnMinuteForPlayer(minute, player) << '\n';
        } else if (line.find("Goals on first ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minutes;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minutes;
            pos = line.find("minutes by ");
            string player = line.substr(pos + string("minutes by ").length());
            cout << getGoalsOnFirstMinutesForPlayer(minutes, player) << '\n';
        } else if (line.find("Goals on last ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minutes;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minutes;
            pos = line.find("minutes by ");
            string player = line.substr(pos + string("minutes by ").length());
            cout << getGoalsOnLastMinutesForPlayer(minutes, player) << '\n';
        } else if (line.find("Score opens by ") == 0) {
            size_t st = line.find('\"', 0);
            int result;
            if (st == string::npos) { // player
                string player = line.substr(string("Score opens by ").length());
                result = getScoreOpensForPlayer(player);
            } else {
                size_t pos = line.find('\"', st + 1);
                string team = line.substr(st + 1, pos - st - 1);
                result = getScoreOpensForTeam(team);
            }
            cout << result << '\n';
        } else if (line.at(0) == '"') {
            readInfo(line);
        }

        getline(cin, line);
    }

}

