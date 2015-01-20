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
    // 分组
    QString editorClass;

    // 索引凭据
    QString editorID;
    QString editorName;

    // 展示
    QString interfaceIcon;

    // check.
    QString lastUpdatedString;
};

class EditorDB
{
public:
    EditorDB(QString dbName);
    ~EditorDB();

    // 数据库操作
    bool connect();
    bool transaction();
    bool commit();
    bool rollback();

    /*
     * ########################
     *      UnitModel ADUS
     * ########################
     */
    bool addUnit(UnitModel *unit);        // 增加 / 更新数据
    bool removeUnit(QString editorID);    // 删除数据

    UnitModel*                      buildUnitModelByEditorID(QString editorID);            // 从数据库中获得角色信息
    QVector<EditorSimpleIndex*>*    buildUnitModelIndex();
    QVector<UnitModel*>*            buildUnitModelFULL();

    /*
     * ########################
     *           通用
     * ########################
     */

    QVector<EditorSimpleIndex*>*    buildSubListByKeyword(QString &keyword, QVector<EditorSimpleIndex*> &majorList);     // 从目标分组中按关键字获取子分组
    QString name(QString dbname = nullptr);         // 数据库(连接)名称

    // getters.
    QString nameDB() { return name(); }
    QString nameUnitModelTable() { return QString("UnitModel"); }
    QString nameSkillModelTable() { return QString("SkillModel"); }
    QString nameItemModelTable() { return QString("ItemModel"); }

    // ...
    // 其它
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
