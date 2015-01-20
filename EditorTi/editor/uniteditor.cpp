#include "uniteditor.h"
#include "ui_uniteditor.h"

UnitEditor::UnitEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitEditor)
{
    ui->setupUi(this);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(ui->formLayoutWidget);
//    setLayout(mainLayout);
}

UnitEditor::~UnitEditor()
{
    delete ui;
}
