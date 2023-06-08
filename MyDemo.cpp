#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;

#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"

using namespace ariel;

int random_int(int min = 0, int max = 100)
{
    std::default_random_engine generator(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
double random_float(double min = -50, double max = 50)
{
    std::default_random_engine generator(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}
string random_name(int type = 0)
{
    string name;
    if (type == 0)
        return "Cowboy No. " + to_string(random_int());
    else if (type == 1)
        return "Young Ninja No. " + to_string(random_int());
    else if (type == 2)
        return "Trained Ninja No. " + to_string(random_int());
    else
        return "Old Ninja No. " + to_string(random_int());
    return "not valid";
};

auto create_cowboy = [](double x = random_float(), double y = random_float())
{
    return new Cowboy{random_name(0), Point{x, y}};
};
auto create_yninja = [](double x = random_float(), double y = random_float())
{
    return new YoungNinja{random_name(1), Point{x, y}};
};
auto create_tninja = [](double x = random_float(), double y = random_float())
{
    return new TrainedNinja{random_name(2), Point{x, y}};
};
auto create_oninja = [](double x = random_float(), double y = random_float())
{
    return new OldNinja{random_name(3), Point{x, y}};
};

auto random_char(double x = random_float(), double y = random_float()) -> Character *
{
    int flag = static_cast<int>(random_float()) % 4;
    if (flag == 0)
        return create_cowboy(x, y);
    if (flag == 1)
        return create_yninja(x, y);
    if (flag == 2)
        return create_tninja(x, y);
    return create_oninja(x, y);
}

auto start_battle = [](Team &team, Team &team2)
{
    int i = 0;
    int rounds = 1;
    while (team.stillAlive() && team2.stillAlive())
    {
        cout << "Round " << rounds++ << ":" << endl;
        cout << "Team 1:" << endl;
        team.print();
        cout << "Team 2:" << endl;
        team2.print();
        if (i % 2 == 0)
        {
            cout << "Team 1 attacks Team 2:" << endl;
            team.attack(&team2);
        }
        else
        {
            cout << "Team 2 attacks Team 1:" << endl;
            team2.attack(&team);
        }
        i++;
    }
    cout << "Team " << (team.stillAlive() ? "1" : "2") << " won!" << endl;
    cout << "Total rounds: " << rounds << endl;
};

auto create_team = [](char type, Character *leader)
{
    Team *team;
    if (type == '1')
        team = new Team{leader};
    else if (type == '2')
        team = new Team2{leader};
    else
        team = new SmartTeam{leader};

    return team;
};

int main(void)
{
    char team1_choice, team2_choice;
    int team1_size = 0, team2_size = 0;
    cout << "Choose team 1 type:" << endl;
    cout << "1. Team" << endl;
    cout << "2. Team2" << endl;
    cout << "3. SmartTeam" << endl;
    cin >> team1_choice;
    if (team1_choice != '1' && team1_choice != '2' && team1_choice != '3')
    {
        cout << "Invalid choice." << endl;
        return 1;
    }
    cout << "Choose team 2 type:" << endl;
    cout << "1. Team" << endl;
    cout << "2. Team2" << endl;
    cout << "3. SmartTeam" << endl;
    cin >> team2_choice;
    if (team2_choice != '1' && team2_choice != '2' && team2_choice != '3')
    {
        cout << "Invalid choice." << endl;
        return 1;
    }

    cout << "Choose team sizes (10 max):" << endl;
    cout << "Team 1: ";
    cin >> team1_size;
    cout << "Team 2: ";
    cin >> team2_size;
    if (team1_size < 1 || team2_size < 1 || team1_size > 10 || team2_size > 10)
    {
        cout << "Invalid team size." << endl;
        return 1;
    }

    // Create teams
    Team *team1, *team2;
    team1 = create_team(team1_choice, random_char());
    team2 = create_team(team2_choice, random_char());
    for(int i = 0; i < team1_size; i++){
        team1->add(random_char());
    }
    for(int i = 0; i < team2_size; i++){
        team2->add(random_char());
    }
    start_battle(*team1, *team2);

    // Delete teams
    delete team1;
    delete team2;
    
    return 0;
}