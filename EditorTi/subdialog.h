#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QtGui>
#include <QTextCodec>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
    class SubDialog;
}

class SubDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SubDialog(QWidget *parent = 0);
    ~SubDialog();

public slots:
    virtual void confirmed();
    virtual void cancelled();
private:
    // TODO.
};

#endif // SUBDIALOG_H
