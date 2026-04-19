#include <fight.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>

// Helper function to format double to string with 2 decimal places
std::string to_string_with_precision(double val, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << val;
    return out.str();
}

Fight::Fight(Living* f1, Living* f2) : fighter1(f1), fighter2(f2) {
    log.push_back("A fight starts between " + fighter1->getName() + " and " + fighter2->getName() + "!");
    std::random_device rd;
    gen = std::mt19937(rd());
}

double Fight::Attr_Diff(int who, int attribute_index, double mod1, double mod2) {
    if (who == 2) {
        switch (attribute_index) {
            case 1: return fighter1->getStrength()*mod1 / fighter2->getStrength()*mod2;
            case 2: return fighter1->getDurability()*mod1 / fighter2->getDurability()*mod2;
            case 3: return fighter1->getSpeed()*mod1 / fighter2->getSpeed()*mod2;
            case 4: return fighter1->getReflexes()*mod1 / fighter2->getReflexes()*mod2;
            default: return 0;
        }
    } else {
        switch (attribute_index) {
            case 1: return fighter2->getStrength()*mod1 / fighter1->getStrength()*mod2;
            case 2: return fighter2->getDurability()*mod1 / fighter1->getDurability()*mod2;
            case 3: return fighter2->getSpeed()*mod1 / fighter1->getSpeed()*mod2;
            case 4: return fighter2->getReflexes()*mod1 / fighter1->getReflexes()*mod2;
            default: return 0;
        }
    }
}
int Fight::simulate(int whoAttackFirst, int autoRounds) {

    int whoAttackFirst_r = whoAttackFirst;

    if (fight_done)
    {
        if (lastTurnFighter ==1 )
        {
            log.push_back("Fight is over !" + fighter1->getName() + " wins!");
        }else if (lastTurnFighter == 2)
        {
            log.push_back("Fight is over !" + fighter2->getName() + " wins!");
        }
        
        return 1;
    }

    
    if(autoRounds == 1){
        while(!fight_done){
            if(whoAttackFirst_r == 1){
                Techniques attack = pick_attack_skills(1);
                Techniques defense = pick_defense_skills(2);
                if (clash(1, attack, defense) == 1) {
                    log.push_back(fighter1->getName() + " wins the fight!");
                    fight_done = true;
                }
                whoAttackFirst_r = 2;
            }else if (whoAttackFirst_r == 2)
            {
                Techniques attack = pick_attack_skills(2);
                Techniques defense = pick_defense_skills(1);
                if (clash(2, attack, defense) == 1) {
                    log.push_back(fighter2->getName() + " wins the fight!");
                    fight_done = true;
                }
                whoAttackFirst_r = 1;
            }            
        }
    }else{
        if(whoAttackFirst_r == 1){
            Techniques attack = pick_attack_skills(1);
            Techniques defense = pick_defense_skills(2);
            if (clash(1, attack, defense) == 1) {
                log.push_back(fighter1->getName() + " wins the fight!");
                fight_done = true;
            }
        }else if (whoAttackFirst_r == 2)
        {
            Techniques attack = pick_attack_skills(2);
            Techniques defense = pick_defense_skills(1);
            if (clash(2, attack, defense) == 1) {
                log.push_back(fighter2->getName() + " wins the fight!");
                fight_done = true;
            }
        }           
    }

    return fight_done ? 1 : 0;    
}

int Fight::simulate_nologs(int whoAttackFirst, int autoRounds) {
    int whoAttackFirst_r = whoAttackFirst;
    if (fight_done)
    {
        if (lastTurnFighter ==1 )
        {
            log.push_back("Fight is over !" + fighter1->getName() + " wins!");
        }else if (lastTurnFighter == 2)
        {
            log.push_back("Fight is over !" + fighter2->getName() + " wins!");
        }
        
        return 1;
    }
    if(autoRounds == 1){
        while(!fight_done){
            if(whoAttackFirst_r == 1){
                Techniques attack = pick_attack_skills(1);
                Techniques defense = pick_defense_skills(2);
                if (clash_nologs(1, attack, defense) == 1) {
                    log.push_back(fighter1->getName() + " wins the fight!");
                    fight_done = true;
                }
                whoAttackFirst_r = 2;
            }else if (whoAttackFirst_r == 2)
            {
                Techniques attack = pick_attack_skills(2);
                Techniques defense = pick_defense_skills(1);
                if (clash_nologs(2, attack, defense) == 1) {
                    log.push_back(fighter2->getName() + " wins the fight!");
                    fight_done = true;
                }
                whoAttackFirst_r = 1;
            }            
        }
    }else{
        while(!fight_done){
            if(whoAttackFirst_r == 1){
                Techniques attack = pick_attack_skills(1);
                Techniques defense = pick_defense_skills(2);
                if (clash_nologs(1, attack, defense) == 1) {
                    log.push_back(fighter1->getName() + " wins the fight!");
                    fight_done = true;
                }
            }else if (whoAttackFirst_r == 2)
            {
                Techniques attack = pick_attack_skills(2);
                Techniques defense = pick_defense_skills(1);
                if (clash_nologs(2, attack, defense) == 1) {
                    log.push_back(fighter2->getName() + " wins the fight!");
                    fight_done = true;
                }
            }            
        }        
    }

    return fight_done ? 1 : 0; 

}

int Fight::clash(int who, Techniques attack, Techniques defense){
    int landHit = 0;
    int dodgeHit = 0;

    double strength_diff = Attr_Diff(who, 1, 1, 1);
    double durability_diff = Attr_Diff(who, 2, 1, 1);    
    double speed_diff = Attr_Diff(who, 3, attack.stats.moveSpeed, defense.stats.moveSpeed);
    double reflexes_diff = Attr_Diff(who, 4, attack.stats.moveSpeed, defense.stats.moveSpeed);

    
    std::uniform_real_distribution<double> dis(0.0, 1.0); 
    if(dis(gen) < speed_diff) landHit = 1;
    if(dis(gen) < reflexes_diff) dodgeHit = 1;

    if (landHit && dodgeHit)
    {
        if (dis(gen) > 0.3)
        {
            landHit = 0;dodgeHit = 1;
        }
        
    }else if (!landHit && !dodgeHit)
    {
        if (dis(gen) > 0.3)
        {
            landHit = 1;dodgeHit = 0;
        }
        
    }
    
std::cout << "\n\nstrength_diff: " << strength_diff << " durability_diff: " << durability_diff << " landHit: " << landHit << " dodgeHit: " << dodgeHit << " who: " << who << std::endl;


    if (who == 1)
    {
        double damage_physical = attack.calculateDamagePhysical()*strength_diff - defense.calculateDefensePhysical()*durability_diff;
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();

        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;

std::cout << "damage_physical: " << damage_physical << " damage_magical: " << damage_magical << std::endl;

        if(landHit == 1){
            log.push_back("Fight turn: " + fighter1->getName() + " vs " + fighter2->getName());
            log.push_back("   "+fighter1->getName() + " attacks with " + attack.stats.skillName + " dealing " + to_string_with_precision(damage_physical) + " physical damage and " + to_string_with_precision(damage_magical) + " magical damage!");
            log.push_back("     "+fighter2->getName() + " defends with " + defense.stats.skillName + "!");
            fighter2->takeDamage(damage_physical, damage_magical);
        }else if (dodgeHit == 1)
        {
            if ( (defense.stats.skillName).find("Dodge") == std::string::npos )
            {
                damage_magical = damage_magical * 0.5;
                damage_physical = damage_physical * 0.5;
                log.push_back("Fight turn: " + fighter1->getName() + " vs " + fighter2->getName());
                log.push_back("   "+fighter1->getName() + " attacks with " + attack.stats.skillName + " dealing " + to_string_with_precision(damage_physical) + " physical damage and " + to_string_with_precision(damage_magical) + " magical damage!");
                log.push_back("     "+fighter2->getName() + " defends well and halved the damages with " + defense.stats.skillName + "!");
                fighter2->takeDamage(damage_physical, damage_magical);
            }else{
                log.push_back("Fight turn: " + fighter1->getName() + " vs " + fighter2->getName());
                log.push_back("     "+fighter2->getName() + " dogdges with " + defense.stats.skillName + "!");
            }
            
        }
        
        return (fighter2->getHealth() <= 0) ? 1 : 0; // Return 1 if fighter2 is defeated, otherwise return 0
    }
    else if (who == 2)
    {


        double damage_physical = attack.calculateDamagePhysical()*strength_diff - defense.calculateDefensePhysical()*durability_diff;
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();

        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;

std::cout << "damage_physical: " << damage_physical << " damage_magical: " << damage_magical << std::endl;

        if(landHit == 1){
            log.push_back("Fight turn: " + fighter2->getName() + " vs " + fighter1->getName());
            log.push_back("   "+fighter2->getName() + " attacks with " + attack.stats.skillName + " dealing " + to_string_with_precision(damage_physical) + " physical damage and " + to_string_with_precision(damage_magical) + " magical damage!");
            log.push_back("     "+fighter1->getName() + " defends with " + defense.stats.skillName + "!");
            fighter1->takeDamage(damage_physical, damage_magical);
        }else if (dodgeHit == 1)
        {
            if ( (defense.stats.skillName).find("Dodge") == std::string::npos )
            {
                damage_magical = damage_magical * 0.5;
                damage_physical = damage_physical * 0.5;
                log.push_back("Fight turn: " + fighter2->getName() + " vs " + fighter1->getName());
                log.push_back("   "+fighter2->getName() + " attacks with " + attack.stats.skillName + " dealing " + to_string_with_precision(damage_physical) + " physical damage and " + to_string_with_precision(damage_magical) + " magical damage!");
                log.push_back("     "+fighter1->getName() + " defends well and halved the damages with " + defense.stats.skillName + "!");
                fighter1->takeDamage(damage_physical, damage_magical);
            }else{
                log.push_back("Fight turn: " + fighter1->getName() + " vs " + fighter2->getName());
                log.push_back("     "+fighter1->getName() + " dogdges with " + defense.stats.skillName + "!");
            }
            
        }

        return (fighter1->getHealth() <= 0) ? 1 : 0;
    }
    else
    {
        std::cout << "Error: Invalid who parameter in clash function." << std::endl;
        return 0;
    }
}

int Fight::clash_nologs(int who, Techniques attack, Techniques defense){


    int landHit = 0;
    int dodgeHit = 0;

    double strength_diff = Attr_Diff(who, 1, 1, 1);
    double durability_diff = Attr_Diff(who, 2, 1, 1);    
    double speed_diff = Attr_Diff(who, 3, attack.stats.moveSpeed, defense.stats.moveSpeed);
    double reflexes_diff = Attr_Diff(who, 4, attack.stats.moveSpeed, defense.stats.moveSpeed);

    
    std::uniform_real_distribution<double> dis(0.0, 1.0); 
    if(dis(gen) < speed_diff) landHit = 1;
    if(dis(gen) < reflexes_diff) dodgeHit = 1;

    if (landHit && dodgeHit)
    {
        if (dis(gen) > 0.3)
        {
            landHit = 0;dodgeHit = 1;
        }
        
    }else if (!landHit && !dodgeHit)
    {
        if (dis(gen) > 0.3)
        {
            landHit = 1;dodgeHit = 0;
        }
        
    }



    if (who == 1)
    {
        double damage_physical = attack.calculateDamagePhysical()*strength_diff - defense.calculateDefensePhysical()*durability_diff;
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();

        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;

        if(landHit == 1){
            fighter2->takeDamage(damage_physical, damage_magical);
        }else if (dodgeHit == 1)
        {
            if ( (defense.stats.skillName).find("Dodge") == std::string::npos )
            {
                damage_magical = damage_magical * 0.5;
                damage_physical = damage_physical * 0.5;
                fighter2->takeDamage(damage_physical, damage_magical);
            }
        }  
        return (fighter2->getHealth() <= 0) ? 1 : 0; // Return 1 if fighter2 is defeated, otherwise return 0
    }
    else if (who == 2)
    {

        double damage_physical = attack.calculateDamagePhysical()*strength_diff - defense.calculateDefensePhysical()*durability_diff;
        double damage_magical = attack.calculateDamageMagical() - defense.calculateDefenseMagical();

        if(damage_physical < 0) damage_physical = 0;
        if(damage_magical < 0) damage_magical = 0;

        if(landHit == 1){
            fighter1->takeDamage(damage_physical, damage_magical);
        }else if (dodgeHit == 1)
        {
            if ( (defense.stats.skillName).find("Dodge") == std::string::npos )
            {
                damage_magical = damage_magical * 0.5;
                damage_physical = damage_physical * 0.5;
                fighter1->takeDamage(damage_physical, damage_magical);
            }
        }
        return (fighter1->getHealth() <= 0) ? 1 : 0;
    }
    return 0;
}

int Fight::nextTurn(){ 
    if (fight_done)
    {
        if (lastTurnFighter ==1 )
        {
            log.push_back("Fight is over !" + fighter1->getName() + " wins!");
        }else if (lastTurnFighter == 2)
        {
            log.push_back("Fight is over !" + fighter2->getName() + " wins!");
        }
        
        return 1;
    }
    
    if(lastTurnFighter == 1){
        lastTurnFighter = 2;
        return simulate(lastTurnFighter,0);
    }else if(lastTurnFighter == 2){
        lastTurnFighter = 1;
        return simulate(lastTurnFighter,0);
    }else{
        std::cout << "Error: Invalid lastTurnFighter value in nextTurn function." << std::endl;
        return 1;
    }
}

Techniques Fight::pick_defense_skills(int who){
    if(who == 1){
        return fighter1->getRandomTechnique(3);
    } else {
        return fighter2->getRandomTechnique(3);
    }
}

Techniques Fight::pick_attack_skills(int who){
    if(who == 1){
        return fighter1->getRandomTechnique(2);
    } else {
        return fighter2->getRandomTechnique(2);
    }
}

std::string Fight::getLog() const {
    std::string fullLog;
    for (const auto& entry : log) {
        fullLog += entry + "\n";
    }
    return fullLog;
}

std::string Fight::getLog_clear() {
    std::string fullLog;
    for (const auto& entry : log) {
        fullLog += entry + "\n";
    }
    log.clear(); // Clear the log after retrieving
    return fullLog;
}

void Fight::printResult() const {
    std::cout << getLog();
}
