#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "splashdialog.h"

#include <QMessageBox>

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
    this->initEditor();


}

EditorWindow::~EditorWindow()
{
    qDebug("Editor destructed.");
    delete ui;
    delete unitEditor;
    delete editorDB;
}

// private functions.
// init controller.
void EditorWindow::initEditor() {
    this->hide();

    SplashDialog splash(editorName(), 0);
    splash.setModal(true);
    splash.show();
    splash.message(tr("Editor ready to run."));

    // data. & controller.
    editorDB = new EditorDB(dbName());
    if (editorDB->connect()) {
        // call editors.
        splash.message(QString(tr("Config Unit-Model-Editor.")));
        unitEditor = new UnitEditor(editorDB, this->centralWidget());
        // entry.
        splash.message(QString(tr("Init Main Window.")));
        configUI();

        splash.message(QString(tr("Config Layout.")));
        splash.message(QString(tr("Starting...")));

        splash.splashFinish();
        this->show();
    } else {
        splash.splashFinish();
        this->show();
        QMessageBox::critical(
                    ui->centralWidget,
                    QString("Error:"),
                    QString("DB connection failed."));
    }
}

void EditorWindow::configUI() {
    connect(ui->actionThis_is_Main, SIGNAL(triggered()), this, SLOT(openSplash()));
    connect(ui->actionGo_to_UnitEditor, SIGNAL(triggered()), this, SLOT(openUnitEditorWindow()));
}

void EditorWindow::openSplash() {
    qDebug("Show Splash Dialog.");
    SplashDialog splash;
    splash.exec();
}

void EditorWindow::openUnitEditorWindow() {
    qDebug("Call UnitEditor.");
    unitEditor->show();
}


// init. // call thread.start()
void EditorInitThread::run() {
    //TODO.
}
