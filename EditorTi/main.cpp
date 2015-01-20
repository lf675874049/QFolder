#include "editorwindow.h"
#include "splashdialog.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QStringList>

#define TEST_MODE false
//#include "helper/editordb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if ( TEST_MODE ) {
//        QString src = "155";
//        int r = src.section('|', 0, 0).toInt();
//        int g = src.section('|', 1, 1).toInt();
//        int b = src.section('|', 2, 2).toInt();
//        qDebug()<<"r ="<<r<<" g="<<g<<" b ="<<b;

//        QString str = "";
//        QStringList ret;

//        int step = 0;
//        while (!str.section('|', step, step).isEmpty()) {
//            ret << str.section('|', step, step);
//            step += 1;
//        }

//        foreach (QString classification, ret) {
//            qDebug()<<classification;
//        }

//        UnitModel model;
//        model.name = "Lada.Juda";
//        model.unitClassList.append("Godness");

//        qDebug()<<"class";
//        qDebug()<<"\tname:"<<model.name;
//        qDebug()<<"\tlist:"<<model.unitClassList.at(0);

        EditorDB editorDB("hello.db");
        if (editorDB.connect()) {
            UnitModel* unit0 = new UnitModel;
            unit0->editorID = "10001";
            unit0->editorName = "Sample 00";
            unit0->name = "Kanneya";

            UnitModel* unit1 = new UnitModel;
            unit1->editorID = "10002";
            unit1->editorName = "zSample 00";
            unit1->name = "Muteppou Tora";

            UnitModel* unit2 = new UnitModel;
            unit2->editorID = "10009";
            unit2->editorName = "Sample 09";
            unit2->name = "Bakamidai";

            QVector<UnitModel*> vec;
            vec.append(unit0);
            vec.append(unit1);
            vec.append(unit2);

            for(int i = 0; i < vec.length(); i ++) {
                UnitModel *unit = vec.at(i);
                if (editorDB.buildUnitModelByEditorID(unit->editorID)) {
                    qDebug()<<QString("unit %1:%2 has already exist.").arg(unit->editorID).arg(unit->editorName);
                } else {
                    editorDB.addUnit(unit);

                    QVector<EditorSimpleIndex*>* indexList = editorDB.buildUnitModelIndex();
                    for (int i = 0; i < indexList->size(); i ++ ) {
                        EditorSimpleIndex* index = indexList->at(i);
                        qDebug()<<QString("Index message:<editor_id=%1,editor_name=%2,data=%3>").arg(index->editorID).arg(index->editorName).arg(index->lastUpdatedString);

                        UnitModel* result = editorDB.buildUnitModelByEditorID(index->editorID);
                        if (result) {
                            qDebug()<<QString("Result : id=%1, eid=%2, name=%3").arg(result->id()).arg(result->editorID).arg(result->editorName);
                        } else {
                            qDebug("result is nil.");
                        }

                        qDebug("");
                    }
                }
            }
        }


        return a.exec();
    }

    qDebug()<<"Available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers) {
        qDebug()<<"\t"<<driver;
    }
    qDebug("");

    // MainWindow.
    EditorWindow w;
    w.show();

    return a.exec();
}
