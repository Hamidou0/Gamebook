#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
#include <vector>

enum class ItemType {
    Consumable,
    Weapon,
    Armor,
    Accessory,
    QuestItem,
    Material
};

enum class BodyPart {
    None,
    Head,
    Chest,
    Legs,
    Feet,
    Hands,
    Neck,
    Finger,
    MainHand,
    OffHand
};

struct ItemStats {
    // Current combat stats
    double physicalAttack = 0;
    double magicalAttack = 0;
    double physicalDefense = 0;
    double magicalDefense = 0;
    
    // Bonus percentages or flat values for Living attributes
    double healthBonus = 0;
    double manaBonus = 0;
    double strengthBonus = 0;
    double durabilityBonus = 0;
    double speedBonus = 0;
    double staminaBonus = 0;
    double recoveryBonus = 0;
    double reflexesBonus = 0;
    double thinkingBonus = 0;

    // Permanent increase (if edible/consumable)
    bool isPermanent = false;
    double permStrength = 0;
    double permIntelligence = 0;
    double permReflexes = 0;
    double permMagic = 0;
};

class Items {
private:
    std::string name;
    std::string description;
    ItemType type;
    ItemStats stats;
    
    bool isWearable;
    BodyPart slot;
    bool isEdible;
    bool isWeapon;

    double weight;
    int value; // Price/Gold value
    int quantity;

public:
    Items() : name("Unknown Item"), type(ItemType::Material), isWearable(false), slot(BodyPart::None), isEdible(false), isWeapon(false), weight(0.1), value(0), quantity(1) {}

    Items(std::string name, std::string description, ItemType type, ItemStats stats, bool isWearable, BodyPart slot, bool isEdible, bool isWeapon, double weight, int value, int quantity = 1)
        : name(name), description(description), type(type), stats(stats), isWearable(isWearable), slot(slot), isEdible(isEdible), isWeapon(isWeapon), weight(weight), value(value), quantity(quantity) {}

    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getType() const { return type; }
    ItemStats getStats() const { return stats; }
    bool getIsWearable() const { return isWearable; }
    BodyPart getSlot() const { return slot; }
    bool getIsEdible() const { return isEdible; }
    bool getIsWeapon() const { return isWeapon; }
    double getWeight() const { return weight; }
    int getValue() const { return value; }
    int getQuantity() const { return quantity; }

    std::string getSlotName() const {
        switch (slot) {
            case BodyPart::Head:     return "Head";
            case BodyPart::Chest:    return "Chest";
            case BodyPart::Legs:     return "Legs";
            case BodyPart::Feet:     return "Feet";
            case BodyPart::Hands:    return "Hands";
            case BodyPart::Neck:     return "Neck";
            case BodyPart::Finger:   return "Finger";
            case BodyPart::MainHand: return "Main Hand";
            case BodyPart::OffHand:  return "Off Hand";
            default:                 return "None";
        }
    }

    // Setters
    void setName(std::string n) { name = n; }
    void setDescription(std::string d) { description = d; }
    void setType(ItemType t) { type = t; }
    void setStats(ItemStats s) { stats = s; }
    void setIsWearable(bool w) { isWearable = w; }
    void setSlot(BodyPart s) { slot = s; }
    void setIsEdible(bool e) { isEdible = e; }
    void setIsWeapon(bool w) { isWeapon = w; }
    void setWeight(double w) { weight = w; }
    void setValue(int v) { value = v; }
    void setQuantity(int q) { quantity = q; }

    void addQuantity(int amount) { quantity += amount; }
    void removeQuantity(int amount) { 
        quantity -= amount; 
        if (quantity < 0) quantity = 0;
    }
};

#endif
