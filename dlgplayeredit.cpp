#include "dlgplayeredit.h"
#include "ui_dlgplayeredit.h"

dlgPlayerEdit::dlgPlayerEdit(QWidget *parent, int p_nNumber, QString p_qsName) :
    QDialog(parent),
    ui(new Ui::dlgPlayerEdit)
{
    ui->setupUi(this);

    if( p_nNumber > -1 )
        ui->ledNumber->setText( QString::number( p_nNumber ) );
    ui->ledName->setText( p_qsName );
}

dlgPlayerEdit::~dlgPlayerEdit()
{
    delete ui;
}

void dlgPlayerEdit::clear()
{
    ui->ledNumber->setText("");
    ui->ledName->setText("");
    ui->ledNumber->setFocus();
}

int dlgPlayerEdit::playerNumber()
{
    return ui->ledNumber->text().toInt();
}

QString dlgPlayerEdit::playerName()
{
    return ui->ledName->text();
}

void dlgPlayerEdit::on_pbOk_clicked()
{
    QDialog::accept();
}

void dlgPlayerEdit::on_pbCancel_clicked()
{
    QDialog::reject();
}
