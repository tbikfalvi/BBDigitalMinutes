#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include <QTranslator>

#include "mainwindow.h"

extern QTranslator     *poTransApp;
extern QTranslator     *poTransQT;
extern QApplication    *apMainApp;

namespace Ui { class dlgSettings; }

class dlgSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSettings(QWidget *parent = 0, cSettings *p_poSettings = NULL );
    ~dlgSettings();

private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();
    void on_pbRetranslate_clicked();
    void on_cmbLang_currentIndexChanged(const QString &arg1);
    void on_pbReset_clicked();

private:
    Ui::dlgSettings     *ui;
    cSettings           *poSettings;

    QString              m_qsLang;
    bool                 m_bReloadLanguage;
};

#endif // DLGSETTINGS_H
