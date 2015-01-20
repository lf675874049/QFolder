#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "splashdialog.h"

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
    delete _sub_window;
}

// private functions.
void EditorWindow::initEditor() {
    this->hide();

    SplashDialog splash(editorName(), 0);
    splash.setModal(true);
    splash.show();

    // model.
    splash.message(QString("加载数据模型 ..."));

    // view.
    splash.message(QString("初始化界面元素 ..."));
    _unit_editor = new UnitEditor(this->centralWidget());

    connect(ui->actionThis_is_Main, SIGNAL(triggered()), this, SLOT(openSplash()));
    connect(ui->actionGo_to_UnitEditor, SIGNAL(triggered()), this, SLOT(openUnitEditorWindow()));

    // read a layout file.
    splash.message(QString("调整界面配置 ..."));
    splash.message(QString("准备开始"));
    // open views ..

    splash.splashFinish();
    this->show();
}

void EditorWindow::openSplash(bool only) {
    qDebug("Show Splash Dialog.");
    if (only) {
        this->hide();
    }

    SplashDialog splash;
    splash.exec();

    if (only) {
        this->show();
    }
}

void EditorWindow::openUnitEditorWindow() {
    qDebug("Call UnitEditor.");
    _unit_editor->show();
}


// init. // call thread.start()
void EditorInitThread::run() {
    //TODO.
}
