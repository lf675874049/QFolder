#include "splashdialog.h"
#include "ui_splashdialog.h"

#include <QTimer>

SplashDialog::SplashDialog(QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashDialog)
{
    ui->setupUi(this);
    ui->label_splash_content->setText(title);
}

SplashDialog::~SplashDialog()
{
    qDebug("SplashDialog destruct.");
    delete ui;
}

void SplashDialog::splashFinish() {
    qDebug("Splash finished!");
    this->accept();
}

void SplashDialog::message(QString msg) {
    ui->label_status->setText(msg);
}
