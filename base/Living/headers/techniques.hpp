#ifndef TECHNIQUES_HPP
#define TECHNIQUES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "skills.hpp"
// 1. Enum for type safety and performance

struct TechniqueStats {
    int isMagical = 0; // 0 for physical, 1 for magical
    SkillType skillType;
    std::string skillName;
    std::string techniqueType;
    std::string description;
    double moveSpeed = 0;
    double damage_physical = 0;
    double damage_magic = 0;
    double areaOfAffect = 0;
    double defense_physical = 0;
    double defense_magic = 0;
    double accuracy = 0;
    double evasion = 0;
    double hitChance = 0;
    double criticalChance = 0;
    double criticalDamage = 0;
    double learningMultiplier = 1.0;
    double actionMultiplier = 1.0;
    double strength = 0;
    int level = 0;
    int experience = 0;
};

class Techniques {

public:
    TechniqueStats stats;
    Techniques() {};    

    Techniques(int isMagical, SkillType skillType, std::string skillName, std::string techniqueType, std::string description, double moveSpeed, double damage_physical, 
        double damage_magic, double areaOfAffect, double defense_physical, double defense_magic, double accuracy, 
               double evasion, double hitChance, double criticalChance, double criticalDamage, 
               double learningMultiplier, double actionMultiplier, double strength) {
        stats.isMagical = isMagical;
        stats.skillType = skillType;
        stats.skillName = skillName;
        stats.techniqueType = techniqueType;
        stats.description = description;
        stats.moveSpeed = moveSpeed;
        stats.damage_physical = damage_physical;
        stats.damage_magic = damage_magic;
        stats.areaOfAffect = areaOfAffect;
        stats.defense_physical = defense_physical;
        stats.defense_magic = defense_magic;
        stats.accuracy = accuracy;
        stats.evasion = evasion;
        stats.hitChance = hitChance;
        stats.criticalChance = criticalChance;
        stats.criticalDamage = criticalDamage;
        stats.learningMultiplier = learningMultiplier;
        stats.actionMultiplier = actionMultiplier;
        stats.strength = strength;
    }

    TechniqueStats& getStats() { return stats; }

    void addExperience(int amount) {
        stats.experience += amount * stats.learningMultiplier;
        // Simple level-up logic
        if (stats.experience >= (stats.level + 1) * 10) {
            stats.level++;
            std::cout << "Technique " << stats.skillName << " leveled up to level " << stats.level << "!" << std::endl;
        }
    }
    double calculateDamagePhysical() {
        if (stats.level == 0) return stats.damage_physical * 0.5;
        return stats.damage_physical * stats.learningMultiplier * stats.actionMultiplier * stats.strength;
    }
    double calculateDamageMagical() {
        if (stats.level == 0) return stats.damage_magic * 0.5;
        return stats.damage_magic * stats.learningMultiplier * stats.actionMultiplier * stats.strength;
    }
    double calculateDefensePhysical() {
        if (stats.level == 0) return stats.defense_physical * 0.5;
        return stats.defense_physical * stats.learningMultiplier * stats.actionMultiplier * stats.strength;
    }
    double calculateDefenseMagical() {
        if (stats.level == 0) return stats.defense_magic * 0.5;
        return stats.defense_magic * stats.learningMultiplier * stats.actionMultiplier * stats.strength;
    }

};

#endif