#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <living.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include "techniques.hpp"
class Fight {

public:

    std::unordered_map <SkillType, std::pair<SkillType, double>> weak_skills_map = {
        {SkillType::Magic_Fire, {SkillType::Magic_Water, 0.8}},
        {SkillType::Magic_Water, {SkillType::Magic_Earth, 0.9}},
        {SkillType::Magic_Wind, {SkillType::Magic_Earth, 0.9}},
        {SkillType::Magic_Earth, {SkillType::Magic_Thunder, 0.95}},
        {SkillType::Magic_Blood, {SkillType::Magic_Light, 0.8}},
        {SkillType::Magic_Darkness, {SkillType::Magic_Light, 0.8}},
    };

    Living fighter1;
    Living fighter2;

    std::vector<std::string> log;
    Fight(Living f1, Living f2){
        this->fighter1 = f1;
        this->fighter2 = f2;
    }

    /**
     * Simulates a simple turn-based fight until one's stamina or health (simulated) drops.
     * For now, it just logs a basic interaction based on speed/strength.
     */
    void simulate(int whoAttackFirst);

    Techniques pick_defense_skills(int who);
    Techniques pick_attack_skills(int who);

    int clash(int who,Techniques attack, Techniques defense);

    /**
     * Returns the full log of the fight
     */
    std::string getLog() const;
    
    /**
     * Prints the result to console
     */
    void printResult() const;
};

#endif
