#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <living.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>

class Fight {

public:
    // Initialize the generator engine (Mersenne Twister) with the seed
    std::mt19937 gen; 
    bool fight_done = false;
    int lastTurnFighter = 1; // 1 for fighter1, 2 for fighter2

    std::unordered_map <SkillType, std::pair<SkillType, double>> weak_skills_map = {
        {SkillType::Magic_Fire, {SkillType::Magic_Water, 0.8}},
        {SkillType::Magic_Water, {SkillType::Magic_Earth, 0.9}},
        {SkillType::Magic_Wind, {SkillType::Magic_Earth, 0.9}},
        {SkillType::Magic_Earth, {SkillType::Magic_Thunder, 0.95}},
        {SkillType::Magic_Blood, {SkillType::Magic_Light, 0.8}},
        {SkillType::Magic_Darkness, {SkillType::Magic_Light, 0.8}},
    };

    Living* fighter1;
    Living* fighter2;

    std::vector<std::string> log;

    Fight ();
    Fight(Living* f1, Living* f2);

    /**
     * Simulates a simple turn-based fight until one's stamina or health (simulated) drops.
     * For now, it just logs a basic interaction based on speed/strength.
     */
    int simulate(int whoAttackFirst, int autoRounds);

    /**
     * Simulates a fight without detailed logging, only logs the winner at the end.
    */
    int simulate_nologs(int whoAttackFirst, int autoRounds);

    Techniques pick_defense_skills(int who);
    Techniques pick_attack_skills(int who);

    int clash(int who,Techniques attack, Techniques defense);
    int clash_nologs(int who,Techniques attack, Techniques defense);
    int nextTurn();

    /**
     * Returns the diff between attributes
     * 1 for strength, 2 for durability, 3 for speed, 4 for reflexes
     */
    double Attr_Diff(int who, int attribute_index, double mod1, double mod2);

    /**
     * Returns the full log of the fight
     */
    std::string getLog() const;

    /**
     * Returns the full log of the fight and then clears it
     */
    std::string getLog_clear();
    
    /**
     * Prints the result to console
     */
    void printResult() const;
};

#endif
