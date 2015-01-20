#include "subdialog.h"

SubDialog::SubDialog(QWidget *parent) : QDialog(parent)
{
    // init.
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName(""))
    QLabel *usrLabel = new QLabel(tr("UserName:"));
    QLabel *pwdLabel = new QLabel(tr("Password:"));

    QVBoxLayout *layoutTxt = new QVBoxLayout;
    layoutTxt->addWidget(usrLabel);
    layoutTxt->addWidget(pwdLabel);

    QPushButton *confirmBtn = new QPushButton(tr("Login"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));

    QHBoxLayout *layoutBtn = new QHBoxLayout;
    layoutBtn->setSpacing(60);
    layoutBtn->addWidget(confirmBtn);
    layoutBtn->addWidget(cancelBtn);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(40);
    layout->addLayout(layoutTxt);
    layout->addLayout(layoutBtn);
    setLayout(layout);

    connect(confirmBtn, SIGNAL(clicked()), this, SLOT(confirmed()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelled()));

    setWindowTitle(tr("Login"));
    resize(640, 480);
}

SubDialog::~SubDialog()
{

}

void SubDialog::confirmed() {
    QDialog::accept();
}

void SubDialog::cancelled() {
    QDialog::reject();
}










