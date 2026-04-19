#ifndef SKILLS_HPP
#define SKILLS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

// 1. Enum for type safety and performance
enum class SkillType {
    Magic_Fire, Magic_Water, Magic_Earth, Magic_Wind, Magic_Thunder,
    Magic_Blood, Magic_Light, Magic_Darkness, Magic_Space, Magic_Time,
    Hands, Legs, Running, Swimming, Stealth, Speech
};

struct SkillStats {
    int experience = 0;
    double learningMultiplier = 1.0;
    double actionMultiplier = 1.0;
    double strength = 0;
    int level = 0;
    int combat_IQ_level = 0;
};

class Skills {
private:
    std::map<SkillType, SkillStats> skillMap;

public:
    Skills() {
        // Initialize all skills defined in the enum
        for (int i = static_cast<int>(SkillType::Magic_Fire); 
                 i <= static_cast<int>(SkillType::Speech); ++i) {
            skillMap[static_cast<SkillType>(i)] = SkillStats();
        }
    }

    // 2. Encapsulated Logic for adding experience
    void addExperience(SkillType skill, double amount) {
        SkillStats& s = skillMap[skill];
        
        // Apply multipliers
        double finalGain = amount * s.learningMultiplier;
        s.experience += finalGain;

        // Simple level-up check
        if ( (s.experience % 10) > s.level ) {
            s.level++;
            std::cout << "Skill leveled up! New level: " << s.level << std::endl;
        }
    }

    SkillStats& getSkill(SkillType skill) {
        return skillMap[skill];
    }
};

#endif