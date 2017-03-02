#include "dlgedit.h"
#include "ui_dlgedit.h"

dlgEdit::dlgEdit(QWidget *parent) : QDialog(parent), ui(new Ui::dlgEdit)
{
    ui->setupUi(this);
}

dlgEdit::~dlgEdit()
{
    delete ui;
}

void dlgEdit::clear()
{
    ui->ledName->setText("");
}

QString dlgEdit::name()
{
    return ui->ledName->text();
}

void dlgEdit::setName(QString qsName)
{
    ui->ledName->setText( qsName );
}

void dlgEdit::on_pbOk_clicked()
{
    QDialog::accept();
}

void dlgEdit::on_pbCancel_clicked()
{
    QDialog::reject();
}
