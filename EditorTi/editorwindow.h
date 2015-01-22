#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "subwindow.h"

#include "helper/editordb.h"
#include "editor/uniteditor.h"

#include <QThread>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

    QString editorName() { return "Ti Editor QT"; }
    QString dbName() { return "Ti.db"; }
private:
    // M
    EditorDB *editorDB;

    // V
    Ui::EditorWindow *ui;
    UnitEditor *unitEditor;

    void initEditor();
    void configUI();
private slots:
    void openSplash();
    void openUnitEditorWindow();
};



// if need..
class EditorInitThread : public QThread
{
protected:
    void run();
};

#endif // EDITORWINDOW_H
