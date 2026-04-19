#include <living.hpp>
#include <fight.hpp>
#include <techniques_list.hpp>

#include <chrono>
#include <thread>
int main(){
    NameGenerator generator;
    static Living character = Living();
    static Living character2 = Living();
    static bool initialized = false;

    if (!initialized) {
        NameGenerator generator;
        character.setName(generator.getRandomName());
        character2.setName(generator.getRandomName());
        character.genAll();
        character2.genAll();
        character.addTechnique(2, fistPunch);
       // character.addTechnique(2, legKick);
        character.addTechnique(3, twoHandBlock);
        character.addTechnique(3, oneHandBlock);

        character2.addTechnique(2, fistPunch);
        character2.addTechnique(2, legKick);
       // character2.addTechnique(2, twoHandBlock);
        character2.addTechnique(3, oneHandBlock);

        character2.print_stat();
        std::cout << "--------------------- NEXT WARRIORSS !!!!" << std::endl;
        character.print_char();
        std::cout << "\n--------------------- NOW THE FIGHT !!!!" << std::endl;
        Fight fight = Fight(&character, &character2);
        fight.simulate(1,0);
        std::cout << fight.getLog_clear() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        while(fight.nextTurn() == 0){
            std::cout << fight.getLog_clear() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        
     
        initialized = true;
    }

}
