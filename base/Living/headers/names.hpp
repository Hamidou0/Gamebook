#include <iostream>
#include <vector>
#include <string>
#include <random> // Essential for modern randomness
#include <ctime>

class NameGenerator {
private:
    std::mt19937 gen; // The random number engine
    std::vector<std::string> maleFirstNames = {
        "Liam", "Hiroshi", "Kwame", "Arjun", "Mateo", "Chidi", "Kenji", "Alexander", "Babatunde", "Wei", 
        "Santiago", "Haruto", "Olumide", "Sebastian", "Zane", "Kofi", "Aarav", "Dimitri", "Chen", "Jabari", 
        "Bjorn", "Tariq", "Sora", "Malik", "Lukas", "Youssef", "Min-ho", "Rahul", "Luvuyo", "Aleksei", 
        "Dante", "Ibrahim", "Thabo", "Hassan", "Finnegan", "Kaito", "Zuberi", "Ravi", "Hugo", "Mustafa",
        "Juma", "Kenji", "Arlo", "Takeshi", "Musa", "Ethan", "Dev", "Oskar", "Kwesi", "Ren",
        "Samuel", "Akira", "Bakari", "Leo", "Bodhi", "Amir", "Sven", "Tenzin", "Femi", "Hiro",
        "Felix", "Kenta", "Zaid", "Tobias", "Chinua", "Jaxon", "Daiki", "Bayo", "Julian", "Koji",
        "Idris", "Soren", "Mikael", "Elijah", "Sunil", "Nkosana", "Luca", "Ryota", "Omar", "Kaleb",
        "Daisuke", "Gideon", "Moussa", "Oscar", "Siddharth", "Amani", "Silas", "Jun", "Kwaku", "Casper",
        "Titus", "Hiroki", "Sekani", "Arthur", "Rohan", "Desta", "Jasper", "Naoki", "Chinonso", "Anders",
        "Marek", "Jiro", "Zaki", "Gabriel", "Vihaan", "Kayode", "Hugo", "Ren", "Solomon", "Kento"
    };

    // Female First Names (100+)
    std::vector<std::string> femaleFirstNames = {
        "Aisha", "Mei", "Elena", "Zahra", "Yuki", "Olivia", "Amara", "Priya", "Fatima", "Chloe", 
        "Ximena", "Sakura", "Zenzile", "Isabella", "Nia", "Ananya", "Svetlana", "Ji-woo", "Elowen", "Imani", 
        "Freja", "Noor", "Hina", "Saanvi", "Inaya", "Astrid", "Lin", "Khadija", "Nandi", "Valentina", 
        "Ayanda", "Mariam", "Indira", "Sofia", "Thandiwe", "Leila", "Yara", "Aarohi", "Siobhan", "Zoya",
        "Mina", "Adanya", "Elara", "Kaori", "Zola", "Aurora", "Anika", "Emi", "Kizzy", "Tara",
        "Maya", "Akiko", "Laila", "Seraphina", "Nisha", "Malaika", "Freya", "Sana", "Keiko", "Esme",
        "Chiamaka", "Rumi", "Selina", "Ada", "Kiara", "Kiran", "Yumi", "Abena", "Clara", "Sarai",
        "Hana", "Zuwena", "Iris", "Jia", "Lindiwe", "Elena", "Natsuki", "Amal", "Sasha", "Dalia",
        "Eshe", "Mio", "Thea", "Sunita", "Tia", "Ayumi", "Jada", "Katia", "Yejide", "Nola",
        "Suki", "Mirembe", "Kaia", "Asha", "Aiko", "Kiana", "Muna", "Beatrix", "Himani", "Zola",
        "Elodie", "Narumi", "Zainab", "Nina", "Leila", "Anya", "Teni", "Emiko", "Farrah", "Veda"
    };

    // Last Names (100+)
    std::vector<std::string> lastNames = {
        "Smith", "Tanaka", "Okonkwo", "Patel", "Garcia", "Muller", "Nguyen", "Mensah", "Kim", "Diallo", 
        "Murphy", "Sato", "Keita", "Singh", "Rodriguez", "Abara", "Choi", "Ivanov", "Tadesse", "Wong", 
        "Eriksson", "Al-Sayed", "Park", "Kulkarni", "Ono", "Dube", "Hernandez", "Bibi", "Nkosi", "Lebedev", 
        "O'Sullivan", "Wang", "Mbeki", "Gomez", "Kozlov", "Zhu", "Traore", "Iyer", "Hansen", "Agrawal",
        "Brown", "Yamamoto", "Osei", "Gupta", "Martinez", "Schmidt", "Pham", "Banda", "Lee", "Camara",
        "Wilson", "Suzuki", "Diop", "Reddy", "Lopez", "Jansen", "Tran", "Molefe", "Zhang", "Touré",
        "Taylor", "Watanabe", "Yeboah", "Das", "Perez", "Weber", "Huang", "Moyo", "Cho", "Sow",
        "Anderson", "Ito", "Adeyemi", "Shah", "Gonzalez", "Fischer", "Lin", "Zuma", "Jung", "Keita",
        "Thomas", "Kobayashi", "Okafor", "Nair", "Sanchez", "Hoffman", "Chen", "Dlamini", "Yoon", "Traoré",
        "White", "Nakamura", "Suleiman", "Joshi", "Ramirez", "Wagner", "Liu", "Tsotetsi", "Kang", "Koné",
        "Harris", "Kato", "Bangura", "Mehta", "Torres", "Richter", "Wu", "Sibanda", "Shin", "Sylla"
    };



public:
    NameGenerator() {
        // Seed the engine with the current time
        std::random_device rd;
        gen.seed(rd());
    }

    std::string getRandomName() {
        
        // 1. Randomly decide if we want a male or female first name (50/50)
        std::uniform_int_distribution<> genderDist(0, 1);
        bool isMale = genderDist(gen);

        // 2. Select the first name based on gender choice
        const std::vector<std::string>& chosenFirstList = isMale ? maleFirstNames : femaleFirstNames;
        std::uniform_int_distribution<> firstDist(0, chosenFirstList.size() - 1);
        std::string firstName = chosenFirstList[firstDist(gen)];

        // 3. Select the last name
        std::uniform_int_distribution<> lastDist(0, lastNames.size() - 1);
        std::string lastName = lastNames[lastDist(gen)];

        return firstName + " " + lastName;
    }
};