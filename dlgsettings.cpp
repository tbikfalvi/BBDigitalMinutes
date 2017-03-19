
#include <QTranslator>
#include <QDir>

#include "dlgsettings.h"
#include "ui_dlgsettings.h"

dlgSettings::dlgSettings(QWidget *parent, cSettings *p_poSettings) : QDialog(parent), ui(new Ui::dlgSettings)
{
    ui->setupUi(this);

    poSettings          = p_poSettings;
    m_bReloadLanguage   = false;

    m_qsLang = poSettings->language();
    int nCurrentIndex   = ui->cmbLang->findText( QString("%1 (").arg( m_qsLang ), Qt::MatchContains );
    ui->cmbLang->setCurrentIndex( nCurrentIndex );
    ui->chkReloadSizePos->setChecked( poSettings->isreloadsizepos() );
    ui->chkReloadLastMinute->setChecked( poSettings->isreloadminute() );
    ui->ledCountQuarter->setText( QString::number( poSettings->countquarters() ) );
    ui->ledLengthPeriod->setText( QString::number( poSettings->timeQuarter() ) );
    ui->chkAllowExtendedTime->setChecked( poSettings->isovertimeenabled() );
    ui->ledLengthOvertime->setText( QString::number( poSettings->timeovertime() ) );
    ui->chkOffensTimeUsed->setChecked( poSettings->istimeoffenseused() );
    ui->ledLengthOffense->setText( QString::number( poSettings->timeOffense() ) );
    ui->ledLengthOffenseExtended->setText( QString::number( poSettings->timeOffenseExt() ) );
    ui->ledLengthTimeout->setText( QString::number( poSettings->timeout() ) );
    ui->chkAutoSaveMinute->setChecked( poSettings->autoSaveMinute() );
    ui->ledAutoSaveMinute->setText( QString::number( poSettings->autoSaveMinuteMin() ) );
    ui->chkTimeStopAtScore->setChecked( poSettings->timerStopAfterScore() );
}

dlgSettings::~dlgSettings()
{
    delete ui;
}

void dlgSettings::on_pbRetranslate_clicked()
{
    m_bReloadLanguage = true;

    apMainApp->removeTranslator( poTransApp );
    apMainApp->removeTranslator( poTransQT );

    poTransApp->load( QString("%1\\BBDigitalMinutes_%2.qm").arg( QDir::currentPath() ).arg(m_qsLang) );
    poTransQT->load( QString("%1\\qt_%2.qm").arg( QDir::currentPath() ).arg(m_qsLang) );

    apMainApp->installTranslator( poTransApp );
    apMainApp->installTranslator( poTransQT );

    ui->retranslateUi( this );

    int nCurrentIndex   = ui->cmbLang->findText( QString("%1 (").arg(m_qsLang), Qt::MatchContains );

    ui->cmbLang->setCurrentIndex( nCurrentIndex );

    m_bReloadLanguage = false;
}

void dlgSettings::on_cmbLang_currentIndexChanged(const QString &arg1)
{
    if( !m_bReloadLanguage )
    {
        m_qsLang = arg1.left(2);
    }
}

void dlgSettings::on_pbOk_clicked()
{
    poSettings->setAppLang( m_qsLang );
    poSettings->setReloadSizePos( ui->chkReloadSizePos->isChecked() );
    poSettings->setReloadMinute( ui->chkReloadLastMinute->isChecked() );
    poSettings->setCountQuarters( ui->ledCountQuarter->text().toInt() );
    poSettings->setTimeQuarter( ui->ledLengthPeriod->text().toInt() );
    poSettings->setOvertimeEnabled( ui->chkAllowExtendedTime->isChecked() );
    poSettings->setTimeOvertime( ui->ledLengthOvertime->text().toInt() );
    poSettings->setTimeOffenseUsed( ui->chkOffensTimeUsed->isChecked() );
    poSettings->setTimeOffense( ui->ledLengthOffense->text().toInt() );
    poSettings->setTimeOffenseExt( ui->ledLengthOffenseExtended->text().toInt() );
    poSettings->setTimeout( ui->ledLengthTimeout->text().toInt() );
    poSettings->setAutoSaveMinute( ui->chkAutoSaveMinute->isChecked() );
    poSettings->setAutoSaveMinuteMin( ui->ledAutoSaveMinute->text().toInt() );
    poSettings->setTimerAutoStopOnScore( ui->chkTimeStopAtScore->isChecked() );

    QDialog::accept();
}

void dlgSettings::on_pbCancel_clicked()
{
    QDialog::reject();
}

void dlgSettings::on_pbReset_clicked()
{
    ui->cmbLang->setCurrentIndex( 0 );
    ui->chkReloadSizePos->setChecked( false );
    ui->chkReloadLastMinute->setChecked( false );
    ui->ledCountQuarter->setText( "4" );
    ui->ledLengthPeriod->setText( "10" );
    ui->chkAllowExtendedTime->setChecked( false );
    ui->ledLengthOvertime->setText( 0 );
    ui->ledLengthOffense->setText( "24" );
    ui->chkOffensTimeUsed->setChecked( false );
    ui->ledLengthOffenseExtended->setText( "14" );
    ui->ledLengthTimeout->setText( "60" );
    ui->chkTimeStopAtScore->setChecked( true );
}

void dlgSettings::on_chkAutoSaveMinute_clicked(bool checked)
{
    ui->ledAutoSaveMinute->setEnabled( checked );
}
