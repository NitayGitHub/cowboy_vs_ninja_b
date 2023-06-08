#include "doctest.h"
#include "Team.hpp"
#include <iostream>
#include <cmath>
#include <memory>
using namespace std;
using namespace ariel;

TEST_CASE("Point Tests")
{
    Point poss1 = Point(15, 23);
    Point poss2 = Point(32, 45);
    CHECK(poss1.distance(poss2) == sqrt(773));
    CHECK(poss1.toString() == "(15.000000,23.000000)");
    CHECK(poss1.moveTowards(poss1, poss2, 2) == Point(16.222895, 24.582570));
    double BeyondDis = poss1.distance(poss2) + 1;
    CHECK_THROWS(poss1.moveTowards(poss1, poss2, BeyondDis));
}

TEST_CASE("Attacking a dead character")
{
    Point p1(0, 0);
    Character *target = new Cowboy("c1", p1);
    Character *c1 = new Cowboy("c2", p1);
    Character *c2 = new YoungNinja("c3", p1);
    YoungNinja c3 = YoungNinja("c4", p1);
    Cowboy c4 = Cowboy("c5", p1);

    target->hit(120);
    CHECK_THROWS(c1->attack(target));
    CHECK_THROWS(c2->attack(target));
    CHECK_THROWS(target->hit(10));
    CHECK_THROWS(c3.slash(target));
    CHECK_THROWS(c4.shoot(target));

    delete c1;
    delete target;
    delete c2;
}

TEST_CASE("Attacking when you're dead")
{
    Point p1(0, 0);
    Character *c1 = new Cowboy("c1", p1);
    Character *c2 = new OldNinja("c2", p1);
    YoungNinja *c3 = new YoungNinja("c4", p1);
    Cowboy *c4 = new Cowboy("c5", p1);

    c1->hit(120);
    c2->hit(150);
    c3->hit(100);
    c4->hit(110);

    CHECK_THROWS(c1->attack(c2));
    CHECK_THROWS(c2->attack(c1));
    CHECK_THROWS(c3->slash(c4));
    CHECK_THROWS(c4->shoot(c3));

    delete c1;
    delete c2;
    delete c3;
    delete c4;
}

TEST_CASE("Initiation Checks"){
    Point p1(0, 0);
    Cowboy *c1 = new Cowboy("c1", p1);
    OldNinja *c2 = new OldNinja("c2", p1);
    YoungNinja *c3 = new YoungNinja("c4", p1);
    TrainedNinja *c4 = new TrainedNinja("c5", p1);

    CHECK(c1->getHP() == 110);
    CHECK(c2->getHP() == 150);
    CHECK(c3->getHP() == 100);
    CHECK(c4->getHP() == 120);

    CHECK(c1->getBullets() == 6);
    CHECK(c2->getSpeed() == 8);
    CHECK(c3->getSpeed() == 14);
    CHECK(c4->getSpeed() == 12);

    delete c1;
    delete c2;
    delete c3;
    delete c4;
}

TEST_CASE("Team Checks"){

    // Add more than 10 characters
    Point p1(0, 0);
    Cowboy *c1 = new Cowboy("c1", p1);
    Team t1 (c1);
    for(int i = 0; i < 9; i++){
        t1.add(new Cowboy("c" + to_string(i+2), p1));
    }
    CHECK_THROWS(t1.add(new Cowboy("c11", p1)));

    // Leader in another team
    CHECK_THROWS_AS(Team t3 (c1), std::runtime_error);

    // Add a character that is already in a team
    CHECK_THROWS(t1.add(c1));
    
}