#ifndef DLGPLAYEREDIT_H
#define DLGPLAYEREDIT_H

#include <QDialog>

namespace Ui {
class dlgPlayerEdit;
}

class dlgPlayerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit dlgPlayerEdit(QWidget *parent = 0, int p_nNumber = 0, QString p_qsName = "" );
    ~dlgPlayerEdit();

    void        clear();
    int         playerNumber();
    QString     playerName();

private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();

private:
    Ui::dlgPlayerEdit *ui;
};

#endif // DLGPLAYEREDIT_H
