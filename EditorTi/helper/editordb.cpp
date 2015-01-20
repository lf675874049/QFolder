#include "editordb.h"

EditorDB::EditorDB(QString dbName)
{
    name(dbName);
}

EditorDB::~EditorDB()
{

}

bool EditorDB::_buildUnitModelTable() {
    QSqlQuery query(database);
    // better to give a varchar capacity.
    if (query.exec("CREATE TABLE UnitModel("
                   "[ID] INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "[EditorID] VARCHAR NOT NULL,"
                   "[EditorClass] VARCHAR DEFAULT 'UnitModel',"
                   "[Name] VARCHAR DEFAULT '',"
                   "[EditorName] VARCHAR NOT NULL,"
                   "[ProperName] VARCHAR DEFAULT '',"
                   "[IconFile] VARCHAR DEFAULT '',"
                   "[ModelFile] VARCHAR DEFAULT '',"
                   "[Scaling] SMALLINT DEFAULT 100,"
                   "[Tint] VARCHAR(12) DEFAULT '255|255|255',"
                   "[CollisionRect] VARCHAR DEFAULT '0|0|0|0',"
                   "[Pathing] VARCHAR DEFAULT '0|0',"
                   "[SelectionRadius] INTEGER DEFAULT 32,"
                   "[LabelOffset] INTEGER DEFAULT 64,"
                   "[Cost] VARCHAR DEFAULT '',"
                   "[Product] VARCHAR DEFAULT '',"
                   "[UnitClassification] VARCHAR DEFAULT '',"
                   "[Life] DOUBLE DEFAULT 1,"
                   "[LifeRegen] DOUBLE DEFAULT 0,"
                   "[Leech] DOUBLE DEFAULT 0,"
                   "[LifeIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[LifeRegenIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[LeechIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[Mana] DOUBLE DEFAULT 0,"
                   "[ManaRegen] DOUBLE DEFAULT 0,"
                   "[Imperius] DOUBLE DEFAULT 0,"
                   "[ManaIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[ManaRegenIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[ImperiusIncreasePerLevel] DOUBLE DEFAULT 0,"
                   "[Strength] DOULBLE DEFAULT 0,"
                   "[Dexterity] DOULBLE DEFAULT 0,"
                   "[Intelligence] DOULBLE DEFAULT 0,"
                   "[Vitality] DOULBLE DEFAULT 0,"
                   "[StrengthIncreasePerLevel] DOULBLE DEFAULT 0,"
                   "[DexterityIncreasePerLevel] DOULBLE DEFAULT 0,"
                   "[IntelligenceIncreasePerLevel] DOULBLE DEFAULT 0,"
                   "[VitalityIncreasePerLevel] DOULBLE DEFAULT 0,"
                   "[LastUpdated] TIMESTAMP NOT NULL DEFAULT(datetime('now','localtime')))")) {

        qDebug()<<"create unit table success";
        return true;
    } else {
        qDebug()<<"create unit table error : "<<query.lastError().text();
        return false;
    }
}

bool EditorDB::_buildSkillModelTable() {
    //TODO: in dev.
    return true;
}

bool EditorDB::_buildItemModelTable() {
    //TODO: in dev.
    return true;
}

bool EditorDB::buildTable(QString tablename) {
//    if you are C'er
//    if (tablename.compare(nameUnitModel()) == 0) {

    if (tablename == nameUnitModelTable()) {
        return _buildUnitModelTable();
    }

    if (tablename == nameSkillModelTable()) {
        return _buildSkillModelTable();
    }

    if (tablename == nameItemModelTable()) {
        return _buildItemModelTable();
    }

    return false;
}

QString EditorDB::name(QString dbname) {
    if (dbname.isEmpty()) {
        return this->_db_name;
    }

    if (this->_db_name.isEmpty()) {
        qDebug()<<"new connection name : "<<dbname;
        this->_db_name = dbname;
    }

    return this->_db_name;
}

bool EditorDB::connect() {
    if (name() != nullptr) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(name());
        if (!db.open()) {
            qDebug()<<"ERROR: Open database named "<<name()<<" failed : "<<db.lastError().text();
            return false;
        } else {
            qDebug()<<"database connected, name:"<<name();
            // check table exists.
            database = db;

            bool inited = true;
            QStringList commands;
            commands.append(nameUnitModelTable());
            commands.append(nameSkillModelTable());
            commands.append(nameItemModelTable());

            foreach(QString command, commands) {
                if (inited == false) {
                    break;
                }

                QSqlQuery query(database);
                query.exec(QString("SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME='%1'").arg(command));
                if (query.next()) {
                    if (query.value(0).toInt() == 0) {
                        qDebug()<<"Table "<<command<<" no found. create new table ...";
                        inited = buildTable(command);
                    } else {
                        // table exists. continue
                    }
                } else{
                    qDebug()<<"select table query executed error : "<<query.lastError().text();
                    inited = false;
                }
            }

            if (inited == false) {
                qDebug()<<"EditorDB "<<name()<<" find & build table error : "<<db.lastError().text();
                return false;
            } else {
                return true;
            }
        }
    } else {
        qDebug("nameless EditorDB.");
        return false;
    }
}

// transaction actions.
bool EditorDB::transaction() {
    if (!database.transaction()) {
        qDebug()<<"database transaction error : "<<database.lastError().text();
        return false;
    }

    return true;
}

bool EditorDB::commit() {
    if (!database.commit()) {
        qDebug()<<"database commit error : "<<database.lastError().text();
        return false;
    }

    return true;
}

bool EditorDB::rollback() {
    if (!database.rollback()) {
        qDebug()<<"database rollback error : " << database.lastError().text();
        return false;
    }

    return true;
}

/*
 * ########################
 *      UnitModel ADUS
 * ########################
 */
bool EditorDB::addUnit(UnitModel *unit) {
    QSqlQuery query(database);
    if (unit->id() != -1) {
        // update.
        qDebug()<<"add unit -> update.";
        // id is auto-increasement value, and editorclass is a final value.
        query.prepare("UPDATE UnitModel SET "
                      "[ID]=NULL,"
                      "[EditorID]=:editor_id,"
                      "[Name]=:name,"
                      "[EditorName]=:editor_name,"
                      "[ProperName]=:proper_name,"
                      "[IconFile]=:icon_file,"
                      "[ModelFile]=:model_file,"
                      "[Scaling]=:scaling_int,"
                      "[Tint]=:tint_str,"
                      "[CollisionRect]=:rect_str,"
                      "[Pathing]=:pathing_str,"
                      "[SelectionRadius]=:selection_radius,"
                      "[LabelOffset]=:label_offset,"
                      "[Cost]=:cost_str,"
                      "[Product]=:product_str,"
                      "[UnitClassification]=:unit_class_str,"
                      "[Life]=:life,"
                      "[LifeRegen]=:life_regen,"
                      "[Leech]=:leech,"
                      "[LifeIncreasePerLevel]=:life_ipl,"
                      "[LifeRegenIncreasePerLevel]=:life_regen_ipl,"
                      "[LeechIncreasePerLevel]=:leech_ipl,"
                      "[Mana]=:mana,"
                      "[ManaRegen]=:mana_regen,"
                      "[Imperius]=:imperius,"
                      "[ManaIncreasePerLevel]=:mana_ipl,"
                      "[ManaRegenIncreasePerLevel]=:mana_regen_ipl,"
                      "[ImperiusIncreasePerLevel]=:imperius_ipl,"
                      "[Strength]=:pstr,"
                      "[Dexterity]=:pdex,"
                      "[Intelligence]=:pint,"
                      "[Vitality]=:pvit,"
                      "[StrengthIncreasePerLevel]=:pstr_ipl,"
                      "[DexterityIncreasePerLevel]=:pdex_ipl,"
                      "[IntelligenceIncreasePerLevel]=:pint_ipl,"
                      "[VitalityIncreasePerLevel]=:pvit_ipl,"
                      "[LastUpdated]=datetime('now','localtime')"
                      "WHERE [ID]=:id");

        query.bindValue(":id",              QVariant(unit->id()));
    } else {
        // insert.
        qDebug()<<"add unit -> insert.";
        query.prepare("INSERT INTO UnitModel ([EditorID],[Name],[EditorName],[ProperName],[IconFile],[ModelFile],[Scaling],[Tint],[CollisionRect],[Pathing],[SelectionRadius],[LabelOffset],"
                                           "[Cost],[Product],[UnitClassification],"
                                           "[Life],[LifeRegen],[Leech],[LifeIncreasePerLevel],[LifeRegenIncreasePerLevel],[LeechIncreasePerLevel],"
                                           "[Mana],[ManaRegen],[Imperius],[ManaIncreasePerLevel],[ManaRegenIncreasePerLevel],[ImperiusIncreasePerLevel],"
                                           "[Strength],[Dexterity],[Intelligence],[Vitality],[StrengthIncreasePerLevel],[DexterityIncreasePerLevel],[IntelligenceIncreasePerLevel],[VitalityIncreasePerLevel]"
                                           ")"
                                  " VALUES (:editor_id,:name,:editor_name,:proper_name,:icon_file,:model_file,:scaling_int,:tint_str,:rect_str,:pathing_str,:selection_radius,:label_offset,"
                                           ":cost_str,:product_str,:unit_class_str,"
                                           ":life,:life_regen,:leech,:life_ipl,:life_regen_ipl,:leech_ipl,"
                                           ":mana,:mana_regen,:imperius,:mana_ipl,:mana_regen_ipl,:imperius_ipl,"
                                           ":pstr,:pdex,:pint,:pvit,:pstr_ipl,:pdex_ipl,:pint_ipl,:pvit_ipl)");
    }

    // string.

    query.bindValue(":editor_id"            ,QVariant(unit->editorID));
    query.bindValue(":name"                 ,QVariant(unit->name));
    query.bindValue(":editor_name"          ,QVariant(unit->editorName));
    query.bindValue(":proper_name"          ,QVariant(unit->properName));
    query.bindValue(":icon_file"            ,QVariant(unit->interfaceIcon));
    query.bindValue(":model_file"           ,QVariant(unit->modelFile));

    query.bindValue(":tint_str"             ,QVariant(unit->tintString()));
    query.bindValue(":rect_str"             ,QVariant(unit->collisionString()));
    query.bindValue(":pathing_str"          ,QVariant(unit->pathString()));

    query.bindValue(":cost_str"             ,QVariant(unit->costString()));
    query.bindValue(":product_str"          ,QVariant(unit->productString()));
    query.bindValue(":unit_class_str"       ,QVariant(unit->unitClassificationString()));

    // numberic.
    query.bindValue(":scaling_int"          ,QVariant(unit->scalingInt()));
    query.bindValue(":selection_radius"     ,QVariant(unit->selection_radius));
    query.bindValue(":label_offset"         ,QVariant(unit->labelOffset));

    query.bindValue(":life"                 ,QVariant(unit->life->life));
    query.bindValue(":life_regen"           ,QVariant(unit->life->lifeRegen));
    query.bindValue(":leech"                ,QVariant(unit->life->leech));
    query.bindValue(":life_ipl"             ,QVariant(unit->life->lifeIncreasePerLevel));
    query.bindValue(":life_regen_ipl"       ,QVariant(unit->life->lifeRegenIncreasePerLevel));
    query.bindValue(":leech_ipl"            ,QVariant(unit->life->leechIncreasePerLevel));
    query.bindValue(":mana"                 ,QVariant(unit->mana->mana));
    query.bindValue(":mana_regen"           ,QVariant(unit->mana->manaRegen));
    query.bindValue(":imperius"             ,QVariant(unit->mana->imperius));
    query.bindValue(":mana_ipl"             ,QVariant(unit->mana->manaIncreasePerLevel));
    query.bindValue(":mana_regen_ipl"       ,QVariant(unit->mana->manaRegenIncreasePerLevel));
    query.bindValue(":imperius_ipl"         ,QVariant(unit->mana->imperiusIncreasePerLevel));
    query.bindValue(":pstr"                 ,QVariant(unit->properties->strength));
    query.bindValue(":pdex"                 ,QVariant(unit->properties->dexterity));
    query.bindValue(":pint"                 ,QVariant(unit->properties->intelligence));
    query.bindValue(":pvit"                 ,QVariant(unit->properties->vitality));
    query.bindValue(":pstr_ipl"             ,QVariant(unit->properties->strengthIncreasePerLevel));
    query.bindValue(":pdex_ipl"             ,QVariant(unit->properties->dexterityIncreasePerLevel));
    query.bindValue(":pint_ipl"             ,QVariant(unit->properties->intelligenceIncreasePerLevel));
    query.bindValue(":pvit_ipl"             ,QVariant(unit->properties->vitalityIncreasePerLevel));

    if (!query.exec()) {
        //insert / update error.
        qDebug()<<"add unit error : "<<query.lastError().text();
    }

    return true;
}

bool EditorDB::removeUnit(QString editorID) {
    QSqlQuery query(database);
    query.prepare("DELETE FROM :table WHERE :key=:value");
    query.bindValue(":table", QVariant("UnitModel"));
    query.bindValue(":key", QVariant("EditorID"));
    query.bindValue(":value", QVariant(editorID));

    if (!query.exec()) {
        qDebug()<<"remove unit error : "<<query.lastError().text();
    }

    return true;
}

UnitModel* EditorDB::buildUnitModelByEditorID(QString editorID) {
    QSqlQuery query(database);
    if (!query.exec(QString("SELECT * FROM UnitModel WHERE EditorID=%1").arg(editorID))) {
        qDebug()<<"find unit by editor id error : "<<query.lastError().text();
        return NULL;
    }

    if (query.next()) {
        UnitModel* unit = _buildUnitModelByQuery(query);
        return unit;
    } else {
        qDebug()<<"find unit by editor id error : found nobody ...";
        return NULL;
    }
}

QVector<EditorSimpleIndex*>* EditorDB::buildUnitModelIndex() {
    QSqlQuery query(database);
    QVector<EditorSimpleIndex*> *vec = new QVector<EditorSimpleIndex*>;

    if (query.exec("SELECT EditorID,EditorClass,EditorName,IconFile,LastUpdated FROM UnitModel")) {
        while (query.next()) {
            EditorSimpleIndex* index = new EditorSimpleIndex;
            index->editorID             = query.value(0).toString();
            index->editorClass          = query.value(1).toString();
            index->editorName           = query.value(2).toString();
            index->interfaceIcon        = query.value(3).toString();
            index->lastUpdatedString    = query.value(4).toString();

            vec->append(index);
        }
    } else {
        qDebug()<<"select unitmodel index error : "<<query.lastError().text();
    }

    return vec;
}

QVector<UnitModel*>* EditorDB::buildUnitModelFULL() {
    QSqlQuery query(database);
    QVector<UnitModel*>* vec = new QVector<UnitModel*>;
    if (query.exec("SELECT * FROM UnitModel")) {
        while (query.next()) {
            UnitModel* unit = _buildUnitModelByQuery(query);
            vec->append(unit);
        }
    } else {
        qDebug()<<"select unitmodel index error : "<<query.lastError().text();
    }

    return vec;
}

QVector<EditorSimpleIndex*>* EditorDB::buildSubListByKeyword(QString &keyword, QVector<EditorSimpleIndex*> &majorList) {
    QVector<EditorSimpleIndex*> *vec = new QVector<EditorSimpleIndex*>;
    foreach(EditorSimpleIndex* index, majorList) {
        if (index->editorName.indexOf(keyword) != -1) {
            vec->append(index);
        }
    }

    return vec;
}

// private.
UnitModel* EditorDB::_buildUnitModelByQuery(QSqlQuery query) {
    UnitModel *unit = new UnitModel;
    unit->id(query.value(0).toInt());
    unit->editorID                                       = query.value(1).toString();
    unit->editorClass                                    = query.value(2).toString();
    unit->name                                           = query.value(3).toString();
    unit->editorName                                     = query.value(4).toString();
    unit->properName                                     = query.value(5).toString();
    unit->interfaceIcon                                  = query.value(6).toString();
    unit->modelFile                                      = query.value(7).toString();
    unit->setScalingByInteger(query.value(8).toInt());
    unit->setTintByString(query.value(9).toString());
    unit->setCollisionByString(query.value(10).toString());
    unit->setPathingByString(query.value(11).toString());
    unit->selection_radius                               = query.value(12).toInt();
    unit->labelOffset                                    = query.value(13).toInt();

    unit->setCostByString(query.value(14).toString());
    unit->setProductByString(query.value(15).toString());
    unit->setUnitClassificationByString(query.value(16).toString());

    unit->life->life                                     = query.value(17).toDouble();
    unit->life->lifeRegen                                = query.value(18).toDouble();
    unit->life->leech                                    = query.value(19).toDouble();
    unit->life->lifeIncreasePerLevel                     = query.value(20).toDouble();
    unit->life->lifeRegenIncreasePerLevel                = query.value(21).toDouble();
    unit->life->leechIncreasePerLevel                    = query.value(22).toDouble();

    unit->mana->mana                                     = query.value(23).toDouble();
    unit->mana->manaRegen                                = query.value(24).toDouble();
    unit->mana->imperius                                 = query.value(25).toDouble();
    unit->mana->manaIncreasePerLevel                     = query.value(26).toDouble();
    unit->mana->manaRegenIncreasePerLevel                = query.value(27).toDouble();
    unit->mana->imperiusIncreasePerLevel                 = query.value(28).toDouble();

    unit->properties->strength                           = query.value("Strength").toDouble();
    unit->properties->dexterity                          = query.value("Dexterity").toDouble();
    unit->properties->intelligence                       = query.value("Intelligence").toDouble();
    unit->properties->vitality                           = query.value("Vitality").toDouble();
    unit->properties->strengthIncreasePerLevel           = query.value("StrengthIncreasePerLevel").toDouble();
    unit->properties->dexterityIncreasePerLevel          = query.value("DexterityIncreasePerLevel").toDouble();
    unit->properties->intelligenceIncreasePerLevel       = query.value("IntelligenceIncreasePerLevel").toDouble();
    unit->properties->vitalityIncreasePerLevel           = query.value("VitalityIncreasePerLevel").toDouble();

    return unit;
}

/*
 * ########################
 *      ItemModel ADUS
 * ########################
 */
//TODO


/*
 * ########################
 *      SkillModel ADUS
 * ########################
 */
//TODO









