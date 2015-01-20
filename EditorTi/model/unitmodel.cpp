#include "unitmodel.h"
#include <QVariant>

UnitModel::UnitModel()
{
    this->_db_id = -1;

    // .str values.

    this->scaling = 1;

    this->tint_r = 255;
    this->tint_g = 255;
    this->tint_b = 255;

    this->collision_x = 0;
    this->collision_y = 0;
    this->collision_w = 0;
    this->collision_h = 0;

    this->pathing_x = 0;
    this->pathing_y = 0;

    this->selection_radius = 0;
    this->labelOffset = 0;

    this->cost = 0;
    this->product = 0;

    this->unitClassList = QStringList();

    this->life = new LifeComplex();
    this->mana = new ManaComplex();
    this->properties = new PropertiesComplex();
}

UnitModel::~UnitModel()
{
    delete this->life;
    delete this->mana;
    delete this->properties;
}

int UnitModel::id(int dbid) {
    if (dbid == -1) {
        return this->_db_id;
    } else if (this->_db_id == -1) {
        this->_db_id = dbid;
    }

    return this->_db_id;
}

QString UnitModel::tintString() {
    return QString("%1|%2|%3").arg(tint_r).arg(tint_g).arg(tint_b);
}

QString UnitModel::collisionString() {
    return QString("%1|%2|%3|%4").arg(collision_x).arg(collision_y).arg(collision_w).arg(collision_h);
}

QString UnitModel::pathString() {
    return QString("%1|%2").arg(pathing_x).arg(pathing_y);
}

QString UnitModel::unitClassificationString() {
    QString ret = "";
    foreach (QString classification, unitClassList) {
        ret += classification;
    }

    return ret;
}

QString UnitModel::costString() {
    return QString("");
}

QString UnitModel::productString() {
    return QString("");
}

int UnitModel::scalingInt() {
    return QVariant(scaling * 100).toInt();
}

// write with content.
bool UnitModel::setTintByString(QString str) {
    if ( !str.isEmpty() ) {
        tint_r = str.section('|', 0, 0).toInt();
        tint_g = str.section('|', 1, 1).toInt();
        tint_b = str.section('|', 2, 2).toInt();
        return true;
    }

    return false;
}

bool UnitModel::setCollisionByString(QString str) {
    if ( !str.isEmpty() ) {
        collision_x = str.section('|', 0, 0).toFloat();
        collision_y = str.section('|', 1, 1).toFloat();
        collision_w = str.section('|', 2, 2).toFloat();
        collision_h = str.section('|', 3, 3).toFloat();
        return true;
    }

    return false;
}

bool UnitModel::setPathingByString(QString str) {
    if ( !str.isEmpty() ) {
        collision_x = str.section('|', 0, 0).toFloat();
        collision_y = str.section('|', 1, 1).toFloat();
        collision_w = str.section('|', 2, 2).toFloat();
        collision_h = str.section('|', 3, 3).toFloat();
        return true;
    }

    return false;
}

bool UnitModel::setUnitClassificationByString(QString str) {
    unitClassList.clear();
    int step = 0;
    while (!str.section('|', step, step).isEmpty()) {
        unitClassList << str.section('|', step, step);
        step += 1;
    }

    return true;
}

bool UnitModel::setScalingByInteger(int scale100) {
    if ( scale100 < 0) {
        return false;
    }

    scaling = scale100 / 100.0f;
    return true;
}

bool UnitModel::setCostByString(QString str) {
    cost = 0;
    return true;
}

bool UnitModel::setProductByString(QString str) {
    product = 0;
    return true;
}









LifeComplex::LifeComplex(
        float vLife, float vLifeRegen, float vLeech,
        float vLifeIPL, float vLifeRegenIPL, float vLeechIPL) {
    life = vLife;
    lifeRegen = vLifeRegen;
    leech = vLeech;

    lifeIncreasePerLevel = vLifeIPL;
    lifeRegenIncreasePerLevel = vLifeRegenIPL;
    leechIncreasePerLevel = vLeechIPL;
}

LifeComplex::~LifeComplex() {

}

ManaComplex::ManaComplex(
        float vMana, float vManaRegen, float vImperius,
        float vManaIPL, float vManaRegenIPL, float vImperiusIPL) {
    mana = vMana;
    manaRegen = vManaRegen;
    imperius = vImperius;

    manaIncreasePerLevel = vManaIPL;
    manaRegenIncreasePerLevel = vManaRegenIPL;
    imperiusIncreasePerLevel = vImperiusIPL;
}

ManaComplex::~ManaComplex() {

}

PropertiesComplex::PropertiesComplex(
        float vStrength, float vDexterity, float vIntelligence, float vVitality,
        float vStrIPL, float vDexIPL, float vIntIPL, float vVitIPL) {
    strength = vStrength;
    dexterity = vDexterity;
    intelligence = vIntelligence;
    vitality = vVitality;

    strengthIncreasePerLevel = vStrIPL;
    dexterityIncreasePerLevel = vDexIPL;
    intelligenceIncreasePerLevel = vIntIPL;
    vitalityIncreasePerLevel = vVitIPL;
}

PropertiesComplex::~PropertiesComplex() {

}






















