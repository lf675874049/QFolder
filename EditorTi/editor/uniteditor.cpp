#include "uniteditor.h"
#include "ui_uniteditor.h"

UnitEditor::UnitEditor(EditorDB *editorDB, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitEditor)
{
    ui->setupUi(this);
    this->editorDB = editorDB;

    // ezzzz
}

UnitEditor::~UnitEditor()
{
    delete ui;
}
