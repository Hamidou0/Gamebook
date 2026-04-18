#include <fight.hpp>
#include <iostream>

Fight::Fight(Living f1, Living f2) : fighter1(f1), fighter2(f2) {
    log.push_back("A fight starts between " + fighter1.getName() + " and " + fighter2.getName() + "!");
}

void Fight::simulate(int whoAttackFirst) {

    if(whoAttackFirst == 1){
        Techniques attack = pick_attack_skills(1);
        Techniques defense = pick_defense_skills(2);
        if (clash(1, attack, defense) == 1) {
            log.push_back(fighter1.getName() + " wins the fight!");
            return;
        }
    }else if (whoAttackFirst == 2)
    {
        Techniques attack = pick_attack_skills(2);
        Techniques defense = pick_defense_skills(1);
        if (clash(2, attack, defense) == 1) {
            log.push_back(fighter2.getName() + " wins the fight!");
            return;
        }
    }
    
}

int Fight::clash(int who, Techniques attack, Techniques defense){
    if (who == 1)
    {
        double damage_physical = attack.calculateDamagePhysical() - defense.calculateDefensePhysical();
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();
        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;
        log.push_back(fighter1.getName() + " attacks with " + attack.stats.skillName + " dealing " + std::to_string(damage_physical) + " physical damage and " + std::to_string(damage_magical) + " magical damage!");
        fighter2.takeDamage(damage_physical, damage_magical);
        return (fighter2.getHealth() <= 0) ? 1 : 0; // Return 1 if fighter2 is defeated, otherwise return 0
    }
    else if (who == 2)
    {
        double damage_physical = attack.calculateDamagePhysical() - defense.calculateDefensePhysical();
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();
        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;
        log.push_back(fighter2.getName() + " attacks with " + attack.stats.skillName + " dealing " + std::to_string(damage_physical) + " physical damage and " + std::to_string(damage_magical) + " magical damage!");
        fighter1.takeDamage(damage_physical, damage_magical);
        return (fighter1.getHealth() <= 0) ? 1 : 0;
    }
}

Techniques Fight::pick_defense_skills(int who){
    if(who == 1){
        return fighter1.getRandomTechnique(3);
    } else {
        return fighter2.getRandomTechnique(3);
    }
}

Techniques Fight::pick_attack_skills(int who){
    if(who == 1){
        return fighter1.getRandomTechnique(2);
    } else {
        return fighter2.getRandomTechnique(2);
    }
}

std::string Fight::getLog() const {
    std::string fullLog;
    for (const auto& entry : log) {
        fullLog += entry + "\n";
    }
    return fullLog;
}

void Fight::printResult() const {
    std::cout << getLog();
}
