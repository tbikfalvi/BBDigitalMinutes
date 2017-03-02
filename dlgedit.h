#ifndef DLGEDIT_H
#define DLGEDIT_H

#include <QDialog>

namespace Ui {
class dlgEdit;
}

class dlgEdit : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEdit(QWidget *parent = 0);
    ~dlgEdit();

    void        clear();
    QString     name();
    void        setName( QString qsName );

private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();

private:
    Ui::dlgEdit *ui;
};

#endif // DLGEDIT_H
