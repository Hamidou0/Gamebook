#include <stdlib.h> 
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <names.hpp>
#include <skills.hpp>
#include <vector>
#include <random> // Essential for modern randomness
#include <ctime>
#include <sstream>

class Living {
private:

    std::string name = "blank_name";
    Skills skills;
    double strengthIndex; ///define the growth rate and chance to have a good start (strength wise)
    double intelligenceIndex;
    double reflexeIndex;
    double magicIndex; 
    //================
    double durabilityPercentage, recoveryPercentage, speedPercentage;

    std::string magic_class_name[10] = {"None","Noneexistant","Useless","Weak","Magico","Mage",
                                    "High Mage", "Highlord", "Emperor"};
    std::string affinities_class_name[10] = {"Fire","Water","Earth", "Wind","Thunder",
                                    "Blood","Light","Darkness","Space","Time"};
    //int weight_magical_class[9] = {30000,30000,20000,5000,2000,1000,500,100,30}; 
    int weight_magical_class[9] = {300,200,100,50,20,10,5,3,1}; 
    int index_weight[10] = {10,20,50,100,100,130,100,50,20,10};
    int index_magical_weight[10] = {100,20,50,100,10,130,10,5,2,10};

    struct physical_att
    {
        double strength, durability, speed;
        double stamina, recovery;
        double reflexes, thinking;
    } physical;

    struct magical_att
    {
        int magic_class;
        double magicalstrength, magicalcastingspeed, magicalrecovery;
        /**
         * affinity 1 - fire 
         * affinity 2 - water
         * affinity 3 - earth
         * affinity 4 - wind
         * affinity 5 - thunder
         * affinity 6 - blood
         * affinity 7 - light
         * affinity 8 - darkness
         * affinity 9 - space
         * affinity 10- time
        */
        double global_growth;
        double global_output;
        double affinities[10] = {0.1,0.1,0.1,0.1,0.01,0.01,0.01,0.01,0.001,0.001};
    } magical;



    /**
     * This will call other functions to generate a character
     * Generate a global strength index, strengthIndex
     * Generate a global intelligence, reflexe index
     */
    void generateLiving( double strengthIndex, double intelligenceIndex, double reflexeIndex);
    void generateLiving();

    /**
     * Generate the magic of a character
     *
     * @param magicIndex define the growth rate and chance to have a good start (magic wise)
     */
    void generateMagic( double magicIndex);
    void generateMagic();


    /**
     * Generate a random wieghted number for a magic class, the weights 
     * are defined in weight_magical_class[]
    */
    int randomMagicClass(){
        srand(time(NULL));
        int weight; for(int i :weight_magical_class) weight += i;
        int rand_num = rand() % weight + 1;
        int i = 0;
        while ( weight_magical_class[i] < rand_num){
            rand_num = rand_num - weight_magical_class[i];
            i++;
            i = i % 9; 
        }
        return i;
    }

    /**
     * Generate a random weighted number for an index, the weights 
     * are defined in index_weight[] 
    */
    int randomIndex(){
        srand(time(NULL));
        int weight; for(int i :index_weight) weight += i;
        int rand_num = rand() % weight + 1;
        int i = 0;
        while ( index_weight[i] < rand_num){
            rand_num = rand_num - index_weight[i]; 
            i++;
            i = i % 10;
        }
        return i;
    }

    int randomIndexMagic(){
        srand(time(NULL));
        int weight; for(int i :index_magical_weight) weight += i;
        int rand_num = rand() % weight + 1;
        int i = 0;
        while ( index_magical_weight[i] < rand_num){
            rand_num = rand_num - index_magical_weight[i]; 
            i++;
            i = i % 10;
        }
        return i;
    }

    /**
     * This function sets the magical affinities for the magic
     * 
     * @param magic_class The magic class to be used for the selection
    */
    void affinitiesSelection(int magic_class){
        switch (magic_class)
        {
        case 0:
            magical.global_growth = 0.01;
            magical.global_output = 0.01;
            break;
        case 1:
            magical.global_growth = 0.05;
            magical.global_output = 0.05;
            break;
        case 2:
            magical.global_growth = 0.1;
            magical.global_output = 0.85;
            break;
        case 3:
            magical.global_growth = 0.40;
            magical.global_output = 0.88;
            break;
        case 4:
            magical.global_growth = 0.85;
            magical.global_output = 0.90;
            break;
        case 5:
            magical.global_growth = 0.95;
            magical.global_output = 0.95;
            break;
        case 6:
            magical.global_growth = 1;
            magical.global_output = 1;
            break;
        case 7:
            magical.global_growth = 1;
            magical.global_output = 1;
            break;
        case 8:
            magical.global_growth = 1.05;
            magical.global_output = 1.05;
            break;
        case 9:
            magical.global_growth = 1.1;
            magical.global_output = 1.1;
            break;
        
        default:
            break;
        }
    }

    /**
     * This function select the appropriate multiplier for the selected magic class
     * 
     * @param magic_class The magic class to be used for the selection
    */
    void magicMultiplier(int magic_class);

public:
    // Getters for attributes
    std::string getName() const { return name; }
    double getStrength() const { return physical.strength; }
    double getDurability() const { return physical.durability; }
    double getSpeed() const { return physical.speed; }
    double getStamina() const { return physical.stamina; }
    double getRecovery() const { return physical.recovery; }
    double getReflexes() const { return physical.reflexes; }
    double getThinking() const { return physical.thinking; }

    std::string getMagicClassName() const { return magic_class_name[magical.magic_class]; }
    double getMagicalStrength() const { return magical.magicalstrength; }
    double getMagicalCastingSpeed() const { return magical.magicalcastingspeed; }
    double getMagicalRecovery() const { return magical.magicalrecovery; }
    double getGlobalGrowth() const { return magical.global_growth; }
    double getGlobalOutput() const { return magical.global_output; }
    double getAffinity(int index) const { 
        if (index >= 0 && index < 10) return magical.affinities[index];
        return 0.0;
    }
    std::string getAffinityName(int index) const {
        if (index >= 0 && index < 10) return affinities_class_name[index];
        return "Unknown";
    }

    double getStrengthIndex() const { return strengthIndex; }
    double getIntelligenceIndex() const { return intelligenceIndex; }
    double getReflexeIndex() const { return reflexeIndex; }
    double getMagicIndex() const { return magicIndex; }

    /**
     * default constructor, uses random number
    */
    Living();

    /**
        * constructor with define values
    */
    Living(double strengthIndex, double intelligenceIndex, double reflexeIndex, double magicIndex);

    void setName(std::string name);

    /**
     * Randomly generate it all,
     * See generateLiving and generateMagic
    */
    void genAll();

    /**
     * This function prints the statistic of the living being
    */
    void print_stat(){
        std::cout << "Statistic of " << name;
        std::cout << "\n|== Physical Attribute ===|" ;
        std::cout << "\nStrength : " << physical.strength; 
        std::cout << "\nDurability : " << physical.durability; 
        std::cout << "\nSpeed : " << physical.speed; 
        std::cout << "\nStamina : " << physical.stamina; 
        std::cout << "\nRecovery : " << physical.recovery; 
        std::cout << "\nReflexes : " << physical.reflexes; 
        std::cout << "\nThinking : " << physical.thinking;
        std::cout << "\n|== Magical Attribute ===|";
        std::cout << "\nMagic Class : " << magic_class_name[magical.magic_class];
        std::cout << "\nMagical Strength : " << magical.magicalstrength;
        std::cout << "\nMagical Casting Speed : " << magical.magicalcastingspeed;
        std::cout << "\nMagical Recovery : " << magical.magicalrecovery;
        std::cout << "\nGlobal Growth : "<< magical.global_growth;
        std::cout << "\nGlobal Ouput : " << magical.global_output;
        std::cout << "\n == Affinities";
        for(int i = 0; i<10;i++){
            std::cout << "\n --"<<affinities_class_name[i]<<" : "<<magical.affinities[i];
        } 
        std::cout << "\nStrength Index : " << strengthIndex;
        std::cout << "\nIntelligence Index : " << intelligenceIndex;
        std::cout << "\nReflexes Index : " << reflexeIndex;
        std::cout << "\nMagic Index : " << magicIndex;
        std::cout << "\n|==========";

    }

    std::string return_stat(){
        std::stringstream ss;
        ss << "Statistic of " << name;
        ss << "\n|== Physical Attribute ===|" ;
        ss << "\nStrength : " << physical.strength; 
        ss << "\nDurability : " << physical.durability; 
        ss << "\nSpeed : " << physical.speed; 
        ss << "\nStamina : " << physical.stamina; 
        ss << "\nRecovery : " << physical.recovery; 
        ss << "\nReflexes : " << physical.reflexes; 
        ss << "\nThinking : " << physical.thinking;
        ss << "\n|== Magical Attribute ===|";
        ss << "\nMagic Class : " << magic_class_name[magical.magic_class];
        ss << "\nMagical Strength : " << magical.magicalstrength;
        ss << "\nMagical Casting Speed : " << magical.magicalcastingspeed;
        ss << "\nMagical Recovery : " << magical.magicalrecovery;
        ss << "\nGlobal Growth : "<< magical.global_growth;
        ss << "\nGlobal Ouput : " << magical.global_output;
        ss << "\n == Affinities";
        for(int i = 0; i<10;i++){
            ss << "\n --"<<affinities_class_name[i]<<" : "<<magical.affinities[i];
        } 
        ss << "\nStrength Index : " << strengthIndex;
        ss << "\nIntelligence Index : " << intelligenceIndex;
        ss << "\nReflexes Index : " << reflexeIndex;
        ss << "\nMagic Index : " << magicIndex;
        ss << "\n|==========";
        return ss.str();
    }
};