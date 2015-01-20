#ifndef UNITMODEL_H
#define UNITMODEL_H

#include <QString>
#include <QStringList>

class LifeComplex
{
public:
    LifeComplex(
            float vLife = 0, float vLifeRegen = 0, float vLeech = 0,
            float vLifeIPL = 0, float vLifeRegenIPL = 0, float vLeechIPL = 0);
    LifeComplex(LifeComplex *complex);

    ~LifeComplex();

    bool initWithComplex(LifeComplex *complex);
    bool initWithArgs( float vLife = 0, float vLifeRegen = 0, float vLeech = 0,
                  float vLifeIPL = 0, float vLifeRegenIPL = 0, float vLeechIPL = 0);

    float life;
    float lifeRegen;
    float leech;

    float lifeIncreasePerLevel;
    float lifeRegenIncreasePerLevel;
    float leechIncreasePerLevel;
};

class ManaComplex
{
public:
    ManaComplex(
            float vMana = 0, float vManaRegen = 0, float vImperius = 0,
            float vManaIPL = 0, float vManaRegenIPL = 0, float vImperiusIPL = 0);
    ManaComplex(ManaComplex *complex);

    ~ManaComplex();

    bool initWithComplex(ManaComplex* complex);
    bool initWithArgs( float vMana = 0, float vManaRegen = 0, float vImperius = 0,
                  float vManaIPL = 0, float vManaRegenIPL = 0, float vImperiusIPL = 0);

    float mana;
    float manaRegen;
    float imperius;

    float manaIncreasePerLevel;
    float manaRegenIncreasePerLevel;
    float imperiusIncreasePerLevel;
};

class PropertiesComplex
{
public:
    PropertiesComplex(
            float vStrength = 0, float vDexterity = 0, float vIntelligence = 0, float vVitality = 0,
            float vStrIPL = 0, float vDexIPL = 0, float vIntIPL = 0, float vVitIPL = 0);
    PropertiesComplex(PropertiesComplex *complex);

    ~PropertiesComplex();

    bool initWithComplex(PropertiesComplex* complex);
    bool initWithArgs( float vStrength = 0, float vDexterity = 0, float vIntelligence = 0, float vVitality = 0,
                  float vStrIPL = 0, float vDexIPL = 0, float vIntIPL = 0, float vVitIPL = 0);

    float strength;
    float dexterity;
    float intelligence;
    float vitality;

    float strengthIncreasePerLevel;
    float dexterityIncreasePerLevel;
    float intelligenceIncreasePerLevel;
    float vitalityIncreasePerLevel;
};

class UnitModel
{
public:
    UnitModel();
    UnitModel(UnitModel* model);

    ~UnitModel();

private:
    int _db_id;
public:
    // Display info.
    QString editorID;
    // ***
    QString editorClass;
    QString name;
    QString editorName;
    QString properName;
    QString interfaceIcon;
    QString modelFile;
    float scaling;
    // tint color.
    int tint_r;
    int tint_g;
    int tint_b;
    // collider box.
    int collision_x;
    int collision_y;
    int collision_w;
    int collision_h;
    // pathing map size.
    int pathing_x;
    int pathing_y;
    int selection_radius;
    int labelOffset;

    // Property info
    int cost;
    int product;
    QStringList unitClassList;

    LifeComplex* life;     // hp.
    ManaComplex* mana;     // mp.
    PropertiesComplex* properties;   // base properties.

    int id(int dbid = -1);

    QString tintString();
    QString collisionString();
    QString pathString();
    QString unitClassificationString();
    int scalingInt();
    QString costString();
    QString productString();

    bool setTintByString(QString str);
    bool setCollisionByString(QString str);
    bool setPathingByString(QString str);
    bool setUnitClassificationByString(QString str);
    bool setScalingByInteger(int scale100);
    bool setCostByString(QString str);
    bool setProductByString(QString str);
};

#endif // UNITMODEL_H
