#ifndef EDITORDB_H
#define EDITORDB_H

#include <QtSql>
#include <QHash>
#include <QVector>
#include <QString>
#include <QStringList>

#include "../model/unitmodel.h"

class EditorSimpleIndex
{
public:
    // grouped ..
    QString editorClass;

    // index with ..
    QString editorID;
    QString editorName;

    // display with ..
    QString interfaceIcon;
    QString lastUpdatedString;
};

class EditorDB
{
public:
    EditorDB(QString dbName);
    ~EditorDB();

    // db function.
    bool connect();
    bool transaction();
    bool commit();
    bool rollback();

    /*
     * ########################
     *      UnitModel ADUS
     * ########################
     */
    bool addUnit(UnitModel *unit);        // add / update data.
    bool removeUnit(QString editorID);    // del data.

    UnitModel*                      buildUnitModelByEditorID(QString editorID);            // 从数据库中获得角色信息
    QVector<EditorSimpleIndex*>*    buildUnitModelIndex();
    QVector<UnitModel*>*            buildUnitModelFULL();

    /*
     * ########################
     *           common
     * ########################
     */

    QVector<EditorSimpleIndex*>*    buildSubListByKeyword(QString &keyword, QVector<EditorSimpleIndex*> &majorList);     // 从目标分组中按关键字获取子分组
    QString name(QString dbname = nullptr);         // database's name

    // getters.
    QString nameDB() { return name(); }
    QString nameUnitModelTable() { return QString("UnitModel"); }
    QString nameSkillModelTable() { return QString("SkillModel"); }
    QString nameItemModelTable() { return QString("ItemModel"); }

    // ...
    // others.
    // ...

private:
    QSqlDatabase database;
    QString _db_name;

    bool buildTable(QString tablename);
    bool _buildUnitModelTable();
    bool _buildSkillModelTable();
    bool _buildItemModelTable();

    UnitModel* _buildUnitModelByQuery(QSqlQuery query);
};

#endif // EDITORDB_H
