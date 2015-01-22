#include "unitmodel.h"


/*
    LifeComplex
    ####
*/
LifeComplex::LifeComplex(
        float vLife, float vLifeRegen, float vLeech,
        float vLifeIPL, float vLifeRegenIPL, float vLeechIPL)
{
    initWithArgs(
                vLife,
                vLifeRegen,
                vLeech,

                vLifeIPL,
                vLifeRegenIPL,
                vLeechIPL
                );
}

LifeComplex::LifeComplex(LifeComplex* complex)
{
    initWithComplex(complex);
}


bool LifeComplex::initWithComplex(LifeComplex *complex)
{
    return initWithArgs(
                complex->life,
                complex->lifeRegen,
                complex->leech,

                complex->lifeIncreasePerLevel,
                complex->lifeRegenIncreasePerLevel,
                complex->leechIncreasePerLevel
                );
}

bool LifeComplex::initWithArgs(float vLife, float vLifeRegen, float vLeech,
                          float vLifeIPL, float vLifeRegenIPL, float vLeechIPL)
{
    life = vLife;
    lifeRegen = vLifeRegen;
    leech = vLeech;

    lifeIncreasePerLevel = vLifeIPL;
    lifeRegenIncreasePerLevel = vLifeRegenIPL;
    leechIncreasePerLevel = vLeechIPL;

    return true;
}

LifeComplex::~LifeComplex() {

}





/*
    ManaComplex
    ####
*/
ManaComplex::ManaComplex(
        float vMana, float vManaRegen, float vImperius,
        float vManaIPL, float vManaRegenIPL, float vImperiusIPL)
{
    initWithArgs(
                vMana,
                vManaRegen,
                vImperius,

                vManaIPL,
                vManaRegenIPL,
                vImperiusIPL
                );
}

ManaComplex::ManaComplex(ManaComplex *complex)
{
    initWithComplex(complex);
}

bool ManaComplex::initWithComplex(ManaComplex *complex)
{
    return initWithArgs(
                complex->mana,
                complex->manaRegen,
                complex->imperius,

                complex->manaIncreasePerLevel,
                complex->manaRegenIncreasePerLevel,
                complex->imperiusIncreasePerLevel
                );
}

bool ManaComplex::initWithArgs(
        float vMana, float vManaRegen, float vImperius,
        float vManaIPL, float vManaRegenIPL, float vImperiusIPL)
{
    mana = vMana;
    manaRegen = vManaRegen;
    imperius = vImperius;

    manaIncreasePerLevel = vManaIPL;
    manaRegenIncreasePerLevel = vManaRegenIPL;
    imperiusIncreasePerLevel = vImperiusIPL;

    return true;
}

ManaComplex::~ManaComplex() {

}





/*
    PropertiesComplex
    ####
*/
PropertiesComplex::PropertiesComplex(
        float vStrength, float vDexterity, float vIntelligence, float vVitality,
        float vStrIPL, float vDexIPL, float vIntIPL, float vVitIPL)
{
    initWithArgs(
                vStrength,
                vDexterity,
                vIntelligence,
                vVitality,

                vStrIPL,
                vDexIPL,
                vIntIPL,
                vVitIPL
                );
}

PropertiesComplex::PropertiesComplex(PropertiesComplex *complex)
{
    initWithComplex(complex);
}

bool PropertiesComplex::initWithComplex(PropertiesComplex* complex) {
    return initWithArgs(
                complex->strength,
                complex->dexterity,
                complex->intelligence,
                complex->vitality,

                complex->strengthIncreasePerLevel,
                complex->dexterityIncreasePerLevel,
                complex->intelligenceIncreasePerLevel,
                complex->vitalityIncreasePerLevel
                );
}

bool PropertiesComplex::initWithArgs(
        float vStrength, float vDexterity, float vIntelligence, float vVitality,
        float vStrIPL, float vDexIPL, float vIntIPL, float vVitIPL)
{
    strength = vStrength;
    dexterity = vDexterity;
    intelligence = vIntelligence;
    vitality = vVitality;

    strengthIncreasePerLevel = vStrIPL;
    dexterityIncreasePerLevel = vDexIPL;
    intelligenceIncreasePerLevel = vIntIPL;
    vitalityIncreasePerLevel = vVitIPL;

    return true;
}

PropertiesComplex::~PropertiesComplex() {

}
