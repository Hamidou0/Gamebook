#include <living.hpp>

int main(){
    NameGenerator generator;
    Living first_dude;
    first_dude.setName(generator.getRandomName());

    first_dude.print_stat();

}
