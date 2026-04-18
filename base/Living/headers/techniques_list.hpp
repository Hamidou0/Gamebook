#pragma once

extern Techniques fistPunch(
    0,                          // isMagical (0 for physical)
    SkillType::Hands,           // skillType
    "Fist Punch",               // skillName
    "Physical Attack",          // techniqueType
    "A standard forward strike with a clenched fist.", // description
    1.0,                        // moveSpeed
    15.0,                       // damage_physical
    0.0,                        // damage_magic
    1.0,                        // areaOfAffect (Single target)
    5.0,                        // defense_physical
    0.0,                        // defense_magic
    95.0,                       // accuracy
    5.0,                        // evasion
    90.0,                       // hitChance
    10.0,                       // criticalChance
    1.5,                        // criticalDamage (50% extra)
    1.1,                        // learningMultiplier
    1.0,                        // actionMultiplier
    10.0                        // strength
);

extern Techniques legKick(
    0,                          // isMagical
    SkillType::Legs,            // skillType
    "Leg Kick",                 // skillName
    "Physical Strike",          // techniqueType
    "A powerful low sweep targeting the opponent's lead leg.", // description
    0.8,                        // moveSpeed (Slightly slower than a punch)
    25.0,                       // damage_physical
    0.0,                        // damage_magic
    1.0,                        // areaOfAffect
    2.0,                        // defense_physical
    0.0,                        // defense_magic
    85.0,                       // accuracy
    10.0,                       // evasion
    80.0,                       // hitChance
    15.0,                       // criticalChance
    2.0,                        // criticalDamage (Double damage)
    1.2,                        // learningMultiplier
    1.1,                        // actionMultiplier
    15.0                        // strength
);

extern Techniques twoHandBlock(
    0,                          // isMagical
    SkillType::Hands,           // skillType
    "Two Hand Block",           // skillName
    "Defensive Guard",          // techniqueType
    "Bracing both arms to absorb significant physical impact.", // description
    0.5,                        // moveSpeed (Slowed while bracing)
    0.0,                        // damage_physical
    0.0,                        // damage_magic
    1.0,                        // areaOfAffect
    50.0,                       // defense_physical (High protection)
    10.0,                       // defense_magic
    100.0,                      // accuracy (Always succeeds in bracing)
    0.0,                        // evasion (You are standing your ground)
    100.0,                      // hitChance
    0.0,                        // criticalChance
    0.0,                        // criticalDamage
    1.0,                        // learningMultiplier
    1.5,                        // actionMultiplier (Higher reward for defense)
    20.0                        // strength (Requires effort to hold)
);

extern Techniques oneHandBlock(
    0,                          // isMagical
    SkillType::Hands,           // skillType
    "One Hand Block",           // skillName
    "Parry/Guard",              // techniqueType
    "Deflecting an incoming attack with a single arm.", // description
    1.2,                        // moveSpeed (Faster/Mobile)
    2.0,                        // damage_physical (Small 'bump' damage)
    0.0,                        // damage_magic
    1.0,                        // areaOfAffect
    20.0,                       // defense_physical
    5.0,                        // defense_magic
    90.0,                       // accuracy
    25.0,                       // evasion (Easier to dodge while one-handing)
    90.0,                       // hitChance
    5.0,                        // criticalChance
    1.2,                        // criticalDamage
    1.1,                        // learningMultiplier
    1.2,                        // actionMultiplier
    8.0                         // strength
);