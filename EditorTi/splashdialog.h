#ifndef SPLASHDIALOG_H
#define SPLASHDIALOG_H

#include <QDialog>

namespace Ui {
class SplashDialog;
}

class SplashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SplashDialog(QString title = QString("The Splash."), QWidget *parent = 0);
    ~SplashDialog();

private:
    Ui::SplashDialog *ui;
private slots:
    void splashFinish();
    void message(QString msg);
};

#endif // SPLASHDIALOG_H
