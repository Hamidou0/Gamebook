#include <living.hpp>


void Living::generateLiving(double strengthIndex, double intelligenceIndex, double reflexeIndex){
    this->strengthIndex = strengthIndex;
    this->intelligenceIndex = intelligenceIndex;
    this->reflexeIndex = reflexeIndex;
    srand(time(NULL));
//===============================
    durabilityPercentage = this->strengthIndex*0.7;
    recoveryPercentage = this->strengthIndex*0.7;
    speedPercentage = this->strengthIndex*0.7;
//===============================
    physical.strength = 20 + (rand()%20+1) + this->strengthIndex ;
    physical.durability = physical.strength * durabilityPercentage*0.1;
    physical.recovery = physical.strength * recoveryPercentage*0.1;
    physical.stamina = (physical.strength * recoveryPercentage*0.1) +(rand()%20+1) + this->strengthIndex ;
    physical.speed = physical.strength * speedPercentage*0.1;
//==============================
    physical.reflexes = 20 + (rand()%30+1) + this->reflexeIndex ;
//==============================
    physical.thinking = 20 + (rand()%40+1) + this->intelligenceIndex ;

}

void Living::generateLiving(){
    this->strengthIndex = randomIndex();
    this->intelligenceIndex = randomIndex();
    this->reflexeIndex = randomIndex();
    srand(time(NULL));
//===============================
    durabilityPercentage = this->strengthIndex*0.7;
    recoveryPercentage = this->strengthIndex*0.7;
    speedPercentage = this->strengthIndex*0.7;
    
//===============================
    physical.strength = 20 + (rand()%20+1) + this->strengthIndex ;
    physical.durability = physical.strength * durabilityPercentage*0.1;
    physical.recovery = physical.strength * recoveryPercentage*0.1;
    physical.stamina = (physical.strength * recoveryPercentage*0.1) +(rand()%20+1) + this->strengthIndex ;
    physical.speed = physical.strength * speedPercentage*0.1;
//==============================
    physical.reflexes = 20 + (rand()%30+1) + this->reflexeIndex ;
//==============================
    physical.thinking = 20 + (rand()%40+1) + this->intelligenceIndex ;   
}

void Living::generateMagic(double magicIndex){
    srand(time(NULL));
    this->magicIndex = magicIndex;
    magical.magic_class = 0;
    for(int i = 0; i<magicIndex*10; i++){
        int magic_class_tmp = randomMagicClass();
        if(magic_class_tmp >magical.magic_class ) magical.magic_class = magic_class_tmp;
    }

    for(int i = 0; i<10; i++){
        magical.affinities[i] = (rand()%40)*0.01;
    }
    magicMultiplier(magical.magic_class);
    affinitiesSelection(magical.magic_class);
    

    magical.magicalstrength = 20 + (rand()%20+1) + this->strengthIndex ;

}

void Living::generateMagic(){
    srand(time(NULL));
    this->magicIndex = randomIndexMagic();
    magical.magic_class = 0;
    for(int i = 0; i<magicIndex*10; i++){
        int magic_class_tmp = randomMagicClass();
        if(magic_class_tmp >magical.magic_class ) magical.magic_class = magic_class_tmp;
    }

    for(int i = 0; i<10; i++){
        magical.affinities[i] = (rand()%40)*0.01;
    }
    magicMultiplier(magical.magic_class);
    affinitiesSelection(magical.magic_class);

    magical.magicalstrength = 20 + (rand()%20+1) + this->strengthIndex ;

}

void Living::magicMultiplier(int magic_class){
    switch (magic_class)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    {
        int i = rand()%4+1;
        magical.affinities[i]=1;
        break;
    }break;
    case 5:
    {
        for(int x = 0; x<2;x++){
            int i = rand()%4+1;
            magical.affinities[i]=1; 
        }
        break;
    }break;
    case 6:
    {
        for(int x = 0; x<2;x++){
            int i = rand()%4+1;
            magical.affinities[i]=1; 
        }
        for(int x = 0; x<1;x++){
            int i = rand()%3+4;
            magical.affinities[i]=1; 
        }
        break;
    }break;
    case 7:
    {
        for(int x = 0; x<3;x++){
            int i = rand()%4+1;
            magical.affinities[i]=1; 
        }
        for(int x = 0; x<2;x++){
            int i = rand()%3+4;
            magical.affinities[i]=1; 
        }
        break;
    }break;
    case 8:
    {
        for(int x = 0; x<3;x++){
            int i = rand()%4+1;
            magical.affinities[i]=1; 
        }
        for(int x = 0; x<2;x++){
            int i = rand()%3+4;
            magical.affinities[i]=1; 
        }
        break;
    }break;
    case 9:
    {
        for(int x = 0; x<5;x++){
            int i = rand()%4+1;
            magical.affinities[i]=1; 
        }
        for(int x = 0; x<2;x++){
            int i = rand()%3+4;
            magical.affinities[i]=1; 
        }
        for(int x = 0; x<1;x++){
            int i = rand()%2+8;
            magical.affinities[i]=1; 
        }
    
        break;
    }break;
    default:
        break;
    }
}

void Living::setName(std::string name){
    this->name = name;
}

Living::Living(){
    generateLiving();
    generateMagic();
}

Living::Living(double strengthIndex, double intelligenceIndex, double reflexeIndex, double magicIndex){
    generateLiving(strengthIndex, intelligenceIndex, reflexeIndex);
    generateMagic( magicIndex);
}