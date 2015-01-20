#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "subwindow.h"
#include "editor/uniteditor.h"

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

private:
    Ui::EditorWindow *ui;
    UnitEditor *_unit_editor;

    void initEditor();
private slots:
    void openSubDialog();
    void openSplash(bool only);

    void openUnitEditorWindow();
};



// if need..
class EditorInitThread : public QThread
{
protected:
    void run();
};

#endif // EDITORWINDOW_H
