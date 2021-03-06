//===========================================================================================================
//
//===========================================================================================================

#include <QMessageBox>
#include <QTimer>
#include <QMenu>
#include <QFileDialog>
#include <QList>
#include <QVBoxLayout>
#include <QToolTip>
#include <QSettings>
#include <QTranslator>

//===========================================================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgplayeredit.h"
#include "dlgedit.h"
#include "dlgsettings.h"
#include "csettings.h"
#include "dlglineedit.h"

//===========================================================================================================

QString qsVersion = "1.0.0";

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Main window
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

//===========================================================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stIcon = new QSystemTrayIcon( parent );

    m_stIcon->setIcon( QIcon(":/resources/basketball.png") );
    m_stIcon->show();

    setWindowTitle( QString( "%1 - v.%2" ).arg( windowTitle() ).arg( qsVersion ) );

    poSettings              = new cSettings();
    poMinute                = new cMinute();

    nTimerMainPlayTime      = 0;
    nTimeMainMiliSec        = poSettings->timeQuarter() * 60000;
    nTimeMinuteMiliSec      = 0;

    nTimerTimeDead          = 0;
    nTimeDeadSecond         = poSettings->timeout() + 1;

    bTeamHomePlay           = false;
    bTeamGuestPlay          = false;
    nTimerTeamPlayTime      = 0;
    nTimeOffense            = poSettings->timeOffense();

    nCountPlayerFieldHome   = 0;
    nCountPlayerFieldGuest  = 0;

    bSubstituteInProgress   = false;

    nScoreHome              = 0;
    nScoreGuest             = 0;

    m_bMinuteInProgress     = false;
    m_bSelectPlayersToField = false;
    m_bGameInProgress       = false;

    m_nMinuteRowCount       = 0;

    m_nTimerAutoSaveMinute  = 0;

    m_nPlayerId             = 0;

    m_nQuarterScoreHome     = 0;
    m_nQuarterScoreGuest    = 0;

    pSoundWhistle = new QSound( QString( "%1/referee_whistle.wav" ).arg( QDir::currentPath() ) );

    _updateMainPlayTime();

    if( poSettings->isreloadsizepos() )
    {
        move( poSettings->left(), poSettings->top() );
        resize( poSettings->width(), poSettings->height() );
    }

//    ui->tbMinute->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbMinute->horizontalHeader()->setVisible( false );
    ui->tbMinute->setColumnWidth( 0, 100 );
    ui->tbMinute->setColumnWidth( 1, 100 );
    ui->tbMinute->setColumnWidth( 2, 100 );

    QStringList qslHeader = QStringList() << ui->lblTeamHome->text() << tr("Minute") << ui->lblTeamGuest->text();

    ui->tbMinute->setHorizontalHeaderLabels( qslHeader );

    _updateTeamName( true, tr("Team HOME") );
    _updateTeamName( false, tr("Team GUEST") );

    _enableControls();

    ui->frmEventsHome->setEnabled( false );
    ui->frmEventsHome->setVisible( false );
    ui->frmEventsGuest->setEnabled( false );
    ui->frmEventsGuest->setVisible( false );

    ui->pb_3->setVisible( false );
    ui->pb_4->setVisible( false );
    ui->pb_5->setVisible( false );
    ui->pb_6->setVisible( false );
}

//===========================================================================================================
MainWindow::~MainWindow()
{
    poSettings->setWindowPosSize( x(), y(), width(), height() );

    m_stIcon->hide();

    delete ui;
    delete pSoundWhistle;
    delete poSettings;
}

//===========================================================================================================
void MainWindow::timerEvent(QTimerEvent *p_poEvent)
{
    if( p_poEvent->timerId() == nTimerMainPlayTime )
    {
        nTimeMainMiliSec   -= 10;
        nTimeMinuteMiliSec += 10;
        _updateMainPlayTime();
    }
    else if( p_poEvent->timerId() == nTimerTimeDead )
    {
        nTimeDeadSecond --;
        _updateDeadTime();
    }
    else if( p_poEvent->timerId() == nTimerTeamPlayTime )
    {
        nTimeOffense --;
        if( bTeamHomePlay )         _updateTeamHomeOffenseTime();
        else if( bTeamGuestPlay )   _updateTeamGuestOffenseTime();
    }
    else if( p_poEvent->timerId() == m_nTimerAutoSaveMinute )
    {
        on_pbMinuteSave_clicked();
    }
}

//===========================================================================================================
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    ui->tbMinute->setColumnWidth( 0, (ui->tbMinute->width()-140)/2 );
    ui->tbMinute->setColumnWidth( 1, 100 );
    ui->tbMinute->setColumnWidth( 2, (ui->tbMinute->width()-140)/2 );
}

//===========================================================================================================
void MainWindow::slotPlayerPanelHomeClicked( cPanelPlayer *poPlayerPanel )
{
    if( m_bSelectPlayersToField && nCountPlayerFieldHome < 5 )
    {
        _setPlayerToField( poPlayerPanel, true );

        if( nCountPlayerFieldHome == 5 )
        {
            m_bSelectPlayersToField = false;
        }
        _savePlayers( true );
    }
    else
    {
        _processPlayerPopupMenu( poPlayerPanel, true );
    }
}

//===========================================================================================================
void MainWindow::slotPlayerPanelGuestClicked( cPanelPlayer *poPlayerPanel )
{
    if( m_bSelectPlayersToField && nCountPlayerFieldGuest < 5 )
    {
        _setPlayerToField( poPlayerPanel, false );

        if( nCountPlayerFieldGuest == 5 )
        {
            m_bSelectPlayersToField = false;
        }
        _savePlayers( false );
    }
    else
    {
        _processPlayerPopupMenu( poPlayerPanel, false );
    }
}

//===========================================================================================================
void MainWindow::slotPlayerHomeDisqualified()
{
    on_pbSignalReferee_clicked();
    nCountPlayerFieldHome--;
    _enableControls();
}

//===========================================================================================================
void MainWindow::slotPlayerGuestDisqualified()
{
    on_pbSignalReferee_clicked();
    nCountPlayerFieldGuest--;
    _enableControls();
}

//===========================================================================================================
// GUI control management procedures
//===========================================================================================================

//===========================================================================================================
void MainWindow::on_pbContinueMainTimer_clicked()
{
    m_bGameInProgress = true;
    if( nCountPlayerFieldHome < 5 || nCountPlayerFieldGuest < 5 )
    {
        QMessageBox::warning( this, tr("Warning"),
                              tr("5 members from both teams has to be selected!") );
        return;
    }
    if( nTimeMinuteMiliSec == 0 )
    {
        QTableWidgetItem *newItem = new QTableWidgetItem( tr( "Minute 1" ) );

        ui->tbMinute->setRowCount( ++m_nMinuteRowCount );
        newItem->setTextAlignment( Qt::AlignHCenter|Qt::AlignCenter );
        ui->tbMinute->setItem( m_nMinuteRowCount-1, 1, newItem );
        ui->tbMinute->scrollToBottom();
    }
    nTimerMainPlayTime = startTimer( 10 );
    if( poSettings->istimeoffenseused() ) nTimerTeamPlayTime = startTimer( 1000 );
    _resetDeadTime();
    _showTrayInfo( tr( "Play continued, timer is live!" ) );
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbSignalReferee_clicked()
{
    killTimer( nTimerMainPlayTime );
    nTimerMainPlayTime = 0;
    if( poSettings->istimeoffenseused() )
    {
        killTimer( nTimerTeamPlayTime );
        nTimerTeamPlayTime = 0;
    }
    if( poSettings->issoundenabled() ) pSoundWhistle->play();
    _showTrayInfo( tr( "Play halted, timer stopped!" ) );
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbEditMainTime_clicked()
{
    ui->ledTimeMainMinute->setEnabled( true );
    ui->ledTimeMainSecond->setEnabled( true );
    ui->ledTimeMainMiliSecond->setEnabled( true );

    ui->ledTimeMainMinute->setStyleSheet( "color: rgb(255, 255, 0);" );
    ui->ledTimeMainSeparator1->setStyleSheet( "color: rgb(255, 255, 0);" );
    ui->ledTimeMainSecond->setStyleSheet( "color: rgb(255, 255, 0);" );
    ui->ledTimeMainSeparator2->setStyleSheet( "color: rgb(255, 255, 0);" );
    ui->ledTimeMainMiliSecond->setStyleSheet( "color: rgb(255, 255, 0);" );

    ui->pbEditMainTime->setEnabled( false );
    ui->pbSaveMainTime->setEnabled( true );
    ui->pbCancelSaveMainTime->setEnabled( true );

    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbSaveMainTime_clicked()
{
    ui->ledTimeMainMinute->setEnabled( false );
    ui->ledTimeMainSecond->setEnabled( false );
    ui->ledTimeMainMiliSecond->setEnabled( false );

    ui->ledTimeMainMinute->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainSeparator1->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainSecond->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainSeparator2->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainMiliSecond->setStyleSheet( "color: rgb(255, 0, 0);" );

    ui->pbEditMainTime->setEnabled( true );
    ui->pbSaveMainTime->setEnabled( false );
    ui->pbCancelSaveMainTime->setEnabled( false );

    nTimeMainMiliSec = ui->ledTimeMainMinute->text().toInt()*60000 +
                       ui->ledTimeMainSecond->text().toInt()*1000 +
                       ui->ledTimeMainMiliSecond->text().toInt()*10;

    _updateMainPlayTime();
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbCancelSaveMainTime_clicked()
{
    ui->ledTimeMainMinute->setEnabled( false );
    ui->ledTimeMainSecond->setEnabled( false );
    ui->ledTimeMainMiliSecond->setEnabled( false );

    ui->ledTimeMainMinute->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainSecond->setStyleSheet( "color: rgb(255, 0, 0);" );
    ui->ledTimeMainMiliSecond->setStyleSheet( "color: rgb(255, 0, 0);" );

    ui->pbEditMainTime->setEnabled( true );
    ui->pbSaveMainTime->setEnabled( false );
    ui->pbCancelSaveMainTime->setEnabled( false );

    _updateMainPlayTime();
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbRequestTime_clicked()
{
    QMenu   qmMenu;
    QString qsTitle = tr( "Timeout request" );

    QAction qaTitle( qsTitle, &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qfTitle.setPointSize( 11 );
    qaTitle.setFont( qfTitle );

    QFont   qfItems;
    qfItems.setPointSize( 10 );

    QAction qaRequestHome( QIcon( ":/resources/basketball_clock_start.png" ), tr("Team HOME request timeout"), &qmMenu );
    qaRequestHome.setFont( qfItems );
    QAction qaRequestGuest( QIcon( ":/resources/basketball_clock_start.png" ), tr("Team GUEST request timeout"), &qmMenu );
    qaRequestGuest.setFont( qfItems );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaRequestHome );
    qmMenu.addAction( &qaRequestGuest );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    nTimeDeadSecond = 61;
    nTimerTimeDead = startTimer( 1000 );
    _enableControls();

    if( qaRet == &qaRequestHome )
    {
        _showTrayInfo( tr( "Home team requested timeout!" ) );
        _addMinuteAction( cMinActionType::MAT_TEAM_TIMEOUT, ui->lblTeamHome->text(), true );
    }
    else
    {
        _showTrayInfo( tr( "Guest team requested timeout!" ) );
        _addMinuteAction( cMinActionType::MAT_TEAM_TIMEOUT, ui->lblTeamGuest->text(), false );
    }
}

//===========================================================================================================
void MainWindow::on_pbHomePlay_clicked()
{
    if( !bTeamHomePlay && poSettings->istimeoffenseused() )
    {
        ui->pbHomePlay->setIcon( QIcon(":/resources/basketball.png") );
        ui->pbGuestPlay->setIcon( QIcon(":/resources/basketball_inactive.png") );
        bTeamHomePlay = true;
        bTeamGuestPlay = false;
        nTimeOffense = poSettings->timeOffense();
        if( nTimerMainPlayTime > 0 && nTimerTeamPlayTime == 0 ) nTimerTeamPlayTime = startTimer( 1000 );
        _updateTeamHomeOffenseTime();
    }
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbGuestPlay_clicked()
{
    if( !bTeamGuestPlay && poSettings->istimeoffenseused() )
    {
        ui->pbHomePlay->setIcon( QIcon(":/resources/basketball_inactive.png") );
        ui->pbGuestPlay->setIcon( QIcon(":/resources/basketball.png") );
        bTeamHomePlay = false;
        bTeamGuestPlay = true;
        nTimeOffense = poSettings->timeOffense();
        if( nTimerMainPlayTime > 0 && nTimerTeamPlayTime == 0 ) nTimerTeamPlayTime = startTimer( 1000 );
        _updateTeamGuestOffenseTime();
    }
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pnIncreaseQuarter_clicked()
{
    int nCountQuarter = poSettings->countquarters();

    if( poSettings->isovertimeenabled() )
    {
        nCountQuarter++;
    }

    if( ui->ledCountQuarter->text().toInt() < nCountQuarter )
    {
        if( QMessageBox::question( this, tr("Question"),
                                   tr( "Are you sure to jump to the next quarter?\n"
                                       "The minutes will be updated with the closure of the quarter."),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            ui->ledCountQuarter->setText( QString::number( ui->ledCountQuarter->text().toInt()+1 ) );
            if( ui->ledCountQuarter->text().toInt() < poSettings->countquarters()+1 )
            {
                nTimeMainMiliSec = poSettings->timeQuarter() * 60000;
                _updateMainPlayTime();
            }
            else
            {
                nTimeMainMiliSec = poSettings->timeovertime() * 60000;
                _updateMainPlayTime();
            }
            m_nQuarterScoreHome     = poMinute->getQuarterScore( cTeamType::HOME, ui->ledCountQuarter->text().toInt() );
            m_nQuarterScoreGuest    = poMinute->getQuarterScore( cTeamType::GUEST, ui->ledCountQuarter->text().toInt() );
        }
    }
    _enableControls();
    poSettings->setQuarter( ui->ledCountQuarter->text().toInt() );
}

//===========================================================================================================
void MainWindow::on_pnDecreaseQuarter_clicked()
{
    if( ui->ledCountQuarter->text().toInt() > 1 )
    {
        if( QMessageBox::question( this, tr("Question"),
                                   tr( "Are you sure to jump back to the previous quarter?\n"
                                       "The minutes will be updated with the reopen of the previous quarter."),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            ui->ledCountQuarter->setText( QString::number( ui->ledCountQuarter->text().toInt()-1 ) );
            m_nQuarterScoreHome     = poMinute->getQuarterScore( cTeamType::HOME, ui->ledCountQuarter->text().toInt() );
            m_nQuarterScoreGuest    = poMinute->getQuarterScore( cTeamType::GUEST, ui->ledCountQuarter->text().toInt() );
        }
    }
    _enableControls();
    poSettings->setQuarter( ui->ledCountQuarter->text().toInt() );
}

//===========================================================================================================
void MainWindow::on_pbTeamHome_clicked()
{
    _processTeamPopupMenu( true );
}

//===========================================================================================================
void MainWindow::on_pbTeamGuest_clicked()
{
    _processTeamPopupMenu( false );
}

//===========================================================================================================
void MainWindow::on_pbEditTeamHome_clicked()
{
    _processTeamNamePopupMenu( true );
    poSettings->setTeamName( true, ui->lblTeamHome->text() );
}

//===========================================================================================================
void MainWindow::on_pbEditTeamGuest_clicked()
{
    _processTeamNamePopupMenu( false );
    poSettings->setTeamName( true, ui->lblTeamGuest->text() );
}

//===========================================================================================================
void MainWindow::on_pbPlayerChangeHome_clicked()
{
    if( nCountPlayerFieldHome > 0 )
    {
        posMenu.setX( QCursor::pos().x() );
        posMenu.setY( QCursor::pos().y() );

        _selectPlayerFromField( true );
        if( pPlayerToSubstitute != NULL )
        {
            _selectPlayerFromSubstitute( true );
            if( pPlayerToField != NULL )
            {
                pPlayerToSubstitute->setPlayerToSubstitute();
                pPlayerToField->setPlayerToField();
                QString qsTemp = QString( "%1 <-> %2" )
                                        .arg( pPlayerToSubstitute->playerAndNumber() )
                                        .arg( pPlayerToField->playerAndNumber() );
                _addMinuteAction( cMinActionType::MAT_PLAYER_SUBSTITUTE, qsTemp, true );
            }
        }
    }
    _enableControls();
    _savePlayers( true );
}

//===========================================================================================================
void MainWindow::on_pbPlayerChangeGuest_clicked()
{
    if( nCountPlayerFieldGuest > 0 )
    {
        posMenu.setX( QCursor::pos().x() );
        posMenu.setY( QCursor::pos().y() );

        _selectPlayerFromField( false );
        if( pPlayerToSubstitute != NULL )
        {
            _selectPlayerFromSubstitute( false );
            if( pPlayerToField != NULL )
            {
                pPlayerToSubstitute->setPlayerToSubstitute();
                pPlayerToField->setPlayerToField();
                QString qsTemp = QString( "%1 <-> %2" )
                                        .arg( pPlayerToSubstitute->playerAndNumber() )
                                        .arg( pPlayerToField->playerAndNumber() );
                _addMinuteAction( cMinActionType::MAT_PLAYER_SUBSTITUTE, qsTemp, false );
            }
        }
    }
    _enableControls();
    _savePlayers( false );
}

//===========================================================================================================
/*
void MainWindow::on_pbScore1Home_clicked()  {   _increaseTeamScoreFault( true );    }
void MainWindow::on_pbScore2Home_clicked()  {   _increaseTeamScore( 2, true );      }
void MainWindow::on_pbScore3Home_clicked()  {   _increaseTeamScore( 3, true );      }
void MainWindow::on_pbScore1Guest_clicked() {   _increaseTeamScoreFault( false  );  }
void MainWindow::on_pbScore2Guest_clicked() {   _increaseTeamScore( 2, false );     }
void MainWindow::on_pbScore3Guest_clicked() {   _increaseTeamScore( 3, false );     }
*/

//===========================================================================================================
void MainWindow::on_pbFaultHome_clicked()
{
    _setPlayerFault( true );
}

//===========================================================================================================
void MainWindow::on_pbFaultGuest_clicked()
{
    _setPlayerFault( false );
}

//===========================================================================================================
void MainWindow::on_pbSettings_clicked()
{
    dlgSettings obDlgSettings( this, poSettings );

    if( obDlgSettings.exec() == QDialog::Accepted )
    {
        bool bTeamTranslateHome  = false;
        bool bTeamTranslateGuest = false;

        if( ui->lblTeamHome->text().compare( tr("Team HOME") ) == 0 )   bTeamTranslateHome  = true;
        if( ui->lblTeamGuest->text().compare( tr("Team GUEST") ) == 0 ) bTeamTranslateGuest = true;

        ui->retranslateUi( this );

        if( bTeamTranslateHome )  _updateTeamName( true, tr("Team HOME") );
        if( bTeamTranslateGuest ) _updateTeamName( false, tr("Team GUEST") );

        poSettings->saveAppSettings();

        if( !m_bMinuteInProgress )
        {
            if( ui->ledCountQuarter->text().toInt() < poSettings->countquarters()+1 )
            {
                nTimeMainMiliSec = poSettings->timeQuarter() * 60000;
                _updateMainPlayTime();
            }
            else
            {
                nTimeMainMiliSec = poSettings->timeovertime() * 60000;
                _updateMainPlayTime();
            }

        }
    }
}

//===========================================================================================================
void MainWindow::on_pbMinuteNew_clicked()
{
    dlgLineEdit obLineEdit( this );

    obLineEdit.setTitle( tr("Enter name of Minute") );
    if( obLineEdit.exec() == QDialog::Accepted )
    {
        ui->tbMinute->setColumnWidth( 0, (ui->tbMinute->width()-140)/2 );
        ui->tbMinute->setColumnWidth( 1, 100 );
        ui->tbMinute->setColumnWidth( 2, (ui->tbMinute->width()-140)/2 );
        ui->tbMinute->horizontalHeader()->setVisible( true );

        if( poMinute->createMinute( obLineEdit.value(), ui->lblTeamHome->text(), ui->lblTeamGuest->text() ) )
        {
            for( int i=0; i<qvPanelPlayersHome.size(); i++ )
            {
                poMinute->addPlayer( cTeamType::HOME, qvPanelPlayersHome.at(i)->playerStringList() );
            }

            for( int i=0; i<qvPanelPlayersGuest.size(); i++ )
            {
                poMinute->addPlayer( cTeamType::GUEST, qvPanelPlayersGuest.at(i)->playerStringList() );
            }

            _showTrayInfo( tr("Minute '%1' created.").arg( obLineEdit.value() ) );
            m_bMinuteInProgress = true;
            if( poSettings->autoSaveMinute() )
            {
                m_nTimerAutoSaveMinute = startTimer( poSettings->autoSaveMinuteMin()*60000 );
            }
        }
    }

    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbAttempt_clicked()
{
    if( nTimeOffense < poSettings->timeOffenseExt() )
    {
        nTimeOffense = poSettings->timeOffenseExt();
        if( bTeamHomePlay )         _updateTeamHomeOffenseTime();
        else if( bTeamGuestPlay )   _updateTeamGuestOffenseTime();
    }
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbMinuteClose_clicked()
{
    m_bMinuteInProgress = false;
    killTimer( m_nTimerAutoSaveMinute );
    m_nTimerAutoSaveMinute = 0;
    poMinute->closeMinute();
    poMinute->saveMinute();
    _showTrayInfo( tr( "Minute '%1' closed." ).arg( poMinute->minuteName() ) );
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbMinuteSave_clicked()
{
    poMinute->saveMinute();
    _showTrayInfo( tr( "Minute '%1' saved." ).arg( poMinute->minuteName() ) );
    _enableControls();
}

//===========================================================================================================
// Private procedures
//===========================================================================================================

//===========================================================================================================
void MainWindow::_enableControls()
{
    // Home team related
    ui->pbTeamHome->setEnabled( (nTimerMainPlayTime==0?true:false) );
    ui->pbPlayerChangeHome->setEnabled( (nTimerMainPlayTime==0 &&
                                         nCountPlayerFieldHome>0 &&
                                         qvPanelPlayersHome.size()>nCountPlayerFieldHome ? true : false) );
    ui->pbFaultHome->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );

    // Guest team related
    ui->pbTeamGuest->setEnabled( (nTimerMainPlayTime==0?true:false) );
    ui->pbPlayerChangeGuest->setEnabled( (nTimerMainPlayTime==0 &&
                                         nCountPlayerFieldGuest>0 &&
                                         qvPanelPlayersGuest.size()>nCountPlayerFieldGuest ? true : false) );
    ui->pbFaultGuest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );

    // Time / quarter related
    ui->pbEditMainTime->setEnabled( (nTimerMainPlayTime>0?false:true) );
    ui->pbHomePlay->setEnabled( poSettings->istimeoffenseused() );
    ui->pbHomePlay->setVisible( poSettings->istimeoffenseused() );
    ui->frmTimerPlayHome->setVisible( poSettings->istimeoffenseused() );
    ui->pbGuestPlay->setEnabled( poSettings->istimeoffenseused() );
    ui->pbGuestPlay->setVisible( poSettings->istimeoffenseused() );
    ui->frmTimerPlayGuest->setVisible( poSettings->istimeoffenseused() );
    ui->pnIncreaseQuarter->setEnabled( (nTimerMainPlayTime>0?false:true) );
    ui->pnDecreaseQuarter->setEnabled( (nTimerMainPlayTime>0?false:true) );

    // Game actions related
    ui->pbRequestTime->setEnabled( ( m_bMinuteInProgress && nTimerMainPlayTime==0 && m_bGameInProgress?true:false ) );
    ui->pbContinueMainTimer->setEnabled( ( m_bMinuteInProgress && nCountPlayerFieldHome == 5 && nCountPlayerFieldGuest==5?true:false ) );
    ui->pbAttempt->setEnabled( m_bMinuteInProgress && poSettings->istimeoffenseused() );

    // Minute related
    ui->pbMinuteNew->setEnabled( !m_bMinuteInProgress );
    ui->pbMinuteSave->setEnabled( m_bMinuteInProgress );
    ui->pbMinuteClose->setEnabled( m_bMinuteInProgress );
    ui->pbMinuteAddCustomText->setEnabled( m_bMinuteInProgress );

// -----------------------------------------------------------------------------------------------
// OBSOLETE but don't delete maybe later it will be used
/*    ui->pbScore1Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );
    ui->pbScore2Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );
    ui->pbScore3Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );*/

/*    ui->pbScore1Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );
    ui->pbScore2Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );
    ui->pbScore3Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );*/
// -----------------------------------------------------------------------------------------------
}

//===========================================================================================================
void MainWindow::_updateMainPlayTime()
{
    if( nTimeMainMiliSec < 1 )
    {
        _showTrayWarning( tr( "The normal play time of the quarter has expired!" ) );
        killTimer( nTimerMainPlayTime );
        killTimer( nTimerTeamPlayTime );
        nTimerMainPlayTime = 0;
        nTimerTeamPlayTime = 0;
        _enableControls();
    }
    if( nTimeMinuteMiliSec && nTimeMinuteMiliSec%60000 == 0 )
    {
        QTableWidgetItem *newItem = new QTableWidgetItem( tr( "Minute %1" ).arg( nTimeMinuteMiliSec/60000 + 1 ) );
        newItem->setTextAlignment( Qt::AlignHCenter|Qt::AlignCenter );
        ui->tbMinute->setRowCount( ++m_nMinuteRowCount );
        ui->tbMinute->setItem( m_nMinuteRowCount-1, 1, newItem );
        ui->tbMinute->scrollToBottom();
    }
    ui->ledTimeMainMinute->setText( QString( "%1" ).arg( nTimeMainMiliSec/60000, 2, 10, QChar( '0' ) ) );
    ui->ledTimeMainSecond->setText( QString( "%1" ).arg( (nTimeMainMiliSec%60000)/1000, 2, 10, QChar( '0' ) ) );
    ui->ledTimeMainMiliSecond->setText( QString( "%1" ).arg( ((nTimeMainMiliSec%60000)%1000)/10, 2, 10, QChar( '0' ) ) );
}

//===========================================================================================================
void MainWindow::_updateTeamHomeOffenseTime()
{
    ui->ledTimerPlayHome->setText( QString( "%1" ).arg( nTimeOffense, 2, 10, QChar( '0' ) ) );
    ui->ledTimerPlayGuest->setText( "00" );
    if( nTimeOffense < 1 )
    {
        _showTrayWarning( tr( "The play time has expired!" ) );
        on_pbSignalReferee_clicked();
        on_pbGuestPlay_clicked();
    }
}

//===========================================================================================================
void MainWindow::_updateTeamGuestOffenseTime()
{
    ui->ledTimerPlayHome->setText( "00" );
    ui->ledTimerPlayGuest->setText( QString( "%1" ).arg( nTimeOffense, 2, 10, QChar( '0' ) ) );
    if( nTimeOffense < 1 )
    {
        _showTrayWarning( tr( "The play time has expired!" ) );
        on_pbSignalReferee_clicked();
        on_pbHomePlay_clicked();
    }
}

//===========================================================================================================
void MainWindow::_updateDeadTime()
{
    if( nTimeDeadSecond < 1 )
    {
        _showTrayWarning( tr( "The timeout period has expired!" ) );
        _resetDeadTime();
    }
    ui->ledTimerTimeSecond->setText( QString( "%1" ).arg( nTimeDeadSecond, 2, 10, QChar( '0' ) ) );
}

//===========================================================================================================
void MainWindow::_resetDeadTime()
{
    killTimer( nTimerTimeDead );
    nTimerTimeDead = 0;
    nTimeDeadSecond = 0;
    ui->ledTimerTimeSecond->setText( QString( "%1" ).arg( nTimeDeadSecond, 2, 10, QChar( '0' ) ) );
}

//====================================================================================
void MainWindow::_showTrayInfo( QString p_qsMessage )
//------------------------------------------------------------------------------------
{
    m_stIcon->showMessage( QObject::tr("Information"), p_qsMessage, QSystemTrayIcon::Information, 5000 );
}

//====================================================================================
void MainWindow::_showTrayWarning( QString p_qsMessage )
//------------------------------------------------------------------------------------
{
    m_stIcon->showMessage( QObject::tr("Information"), p_qsMessage, QSystemTrayIcon::Warning, 5000 );
}

//====================================================================================
void MainWindow::_showTrayError( QString p_qsMessage )
//------------------------------------------------------------------------------------
{
    m_stIcon->showMessage( QObject::tr("Information"), p_qsMessage, QSystemTrayIcon::Critical, 5000 );
}

//====================================================================================
void MainWindow::_importPlayersFromFile()
{
    QString     qsDir   = QDir::currentPath();
    QString     qsFile  = "";
    QFileDialog dlgFileOpen( this );

    dlgFileOpen.setDirectory( qsDir );
    dlgFileOpen.setFileMode( QFileDialog::ExistingFile );
    dlgFileOpen.setOptions( QFileDialog::DontResolveSymlinks );
    dlgFileOpen.setViewMode( QFileDialog::Detail );

    if( dlgFileOpen.exec() )
    {
        qsDir  = dlgFileOpen.directory().absolutePath();
        qsDir.replace( '/', '\\' );
        if( qsDir.right(1).compare("\\") == 0 )
        {
            qsDir = qsDir.left(qsDir.length()-1);
        }
        qsFile = dlgFileOpen.selectedFiles().at(0).right( dlgFileOpen.selectedFiles().at(0).length()-qsDir.length()-1 );
    }

    QFile   qfPlayers( QString( "%1\\%2" ).arg( qsDir ).arg( qsFile ) );

    if( !qfPlayers.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        return;
    }

    while( !qfPlayers.atEnd() )
    {
        QByteArray qbaLine = qfPlayers.readLine();

        if( qbaLine.startsWith('@') )
        {
            qsTeamNameFromFile = QString( qbaLine );//.split("\t").at(1);
            qsTeamNameFromFile.remove( "@" );
            qsTeamNameFromFile.remove( "\t" );
            qsTeamNameFromFile.remove( "\n" );
        }
        else if( !qbaLine.startsWith('#') )
        {
            qslImportedPlayers << QString( qbaLine );
        }
    }
    qfPlayers.close();
}

//====================================================================================
void MainWindow::_addPlayerManually(bool bHome, bool addMultiplePlayers)
{
    dlgPlayerEdit   obDlgPlayerEdit( this );

    if( addMultiplePlayers )
    {
        int nRet;
        do
        {
            qslImportedPlayers = QStringList("");
            obDlgPlayerEdit.clear();
            nRet = obDlgPlayerEdit.exec();
            if( nRet == QDialog::Accepted )
            {
                qslImportedPlayers << QString( "%1\t%2" ).arg( obDlgPlayerEdit.playerNumber() ).arg( obDlgPlayerEdit.playerName() );
                _addPlayers( bHome );
            }

        } while( nRet == QDialog::Accepted );
    }
    else
    {
        qslImportedPlayers = QStringList("");
        obDlgPlayerEdit.clear();
        if( obDlgPlayerEdit.exec() == QDialog::Accepted )
        {
            qslImportedPlayers << QString( "%1\t%2" ).arg( obDlgPlayerEdit.playerNumber() ).arg( obDlgPlayerEdit.playerName() );
            _addPlayers( bHome );
        }
    }
}

//====================================================================================
void MainWindow::_addPlayers(bool addHome)
{
    if( addHome )   _addPlayersToHome();
    else            _addPlayersToGuest();
}

//====================================================================================
void MainWindow::_addPlayersToHome()
{
    for( int i=0; i<qslImportedPlayers.count(); i++ )
    {
        QString qsPlayer = qslImportedPlayers.at( i );

        if( qsPlayer.contains( "\t" ) )
        {
            QStringList  qslPlayer  = qsPlayer.split( "\t" );
            QString      qsName     = QString( qslPlayer.at(1) ).remove("\n");
            int          nNumber    = qslPlayer.at(0).toInt();

            if( _isPlayerNumberAssigned( true, nNumber ) )
            {
                QMessageBox::warning( this, tr("Warning"),
                                      tr( "This number (%1) already assigned to one of the players.\n"
                                          "Please select another number for player\n'%2'").arg( nNumber ).arg( qsName ) );
                continue;
            }

            if( qsName.length() > 0 )
            {
                cPanelPlayer *poPlayer = new cPanelPlayer( this, ++m_nPlayerId, QString::number(nNumber), qsName );

                connect( poPlayer, SIGNAL(playerClicked(cPanelPlayer*)), this, SLOT(slotPlayerPanelHomeClicked(cPanelPlayer*)) );
                connect( poPlayer, SIGNAL(playerDisqualified()),         this, SLOT(slotPlayerHomeDisqualified()) );

                bool bAdded = false;
                for( int j=0; j<qvPanelPlayersHome.size(); j++ )
                {
                    if( poPlayer->playerNumber() < qvPanelPlayersHome.at(j)->playerNumber() )
                    {
                        ui->vlPlayersHome->insertWidget( j, poPlayer );
                        qvPanelPlayersHome.insert( j, poPlayer );
                        bAdded = true;
                        break;
                    }
                }
                if( !bAdded )
                {
                    ui->vlPlayersHome->insertWidget( qvPanelPlayersHome.size(), poPlayer );
                    qvPanelPlayersHome.append( poPlayer );
                }
                if( poMinute )
                {
                    QStringList qslPlayerMinute = QStringList() << QString::number( poPlayer->playerId() )
                                                                << QString::number( poPlayer->playerNumber() )
                                                                << poPlayer->playerName()
                                                                << QString( "0" );
                    poMinute->addPlayer( cTeamType::HOME, qslPlayerMinute );
                }
            }
        }
    }
    _savePlayers( true );
}

//====================================================================================
void MainWindow::_addPlayersToGuest()
{
    for( int i=0; i<qslImportedPlayers.count(); i++ )
    {
        QString qsPlayer = qslImportedPlayers.at( i );

        if( qsPlayer.contains( "\t" ) )
        {
            QStringList  qslPlayer  = qsPlayer.split( "\t" );
            QString      qsName     = QString( qslPlayer.at(1) ).remove("\n");
            int          nNumber    = qslPlayer.at(0).toInt();

            if( _isPlayerNumberAssigned( false, nNumber ) )
            {
                QMessageBox::warning( this, tr("Warning"),
                                      tr( "This number (%1) already assigned to one of the players.\n"
                                      "Please select another number for player\n'%2'").arg( nNumber ).arg( qsName ) );
                continue;
            }

            if( qsName.length() > 0 )
            {
                cPanelPlayer *poPlayer = new cPanelPlayer( this, ++m_nPlayerId, QString::number(nNumber), qsName );

                connect( poPlayer, SIGNAL(playerClicked(cPanelPlayer*)), this, SLOT(slotPlayerPanelGuestClicked(cPanelPlayer*)) );
                connect( poPlayer, SIGNAL(playerDisqualified()),         this, SLOT(slotPlayerGuestDisqualified()) );

                bool bAdded = false;
                for( int j=0; j<qvPanelPlayersGuest.size(); j++ )
                {
                    if( poPlayer->playerNumber() < qvPanelPlayersGuest.at(j)->playerNumber() )
                    {
                        ui->vlPlayersGuest->insertWidget( j, poPlayer );
                        qvPanelPlayersGuest.insert( j, poPlayer );
                        bAdded = true;
                        break;
                    }
                }
                if( !bAdded )
                {
                    ui->vlPlayersGuest->insertWidget( qvPanelPlayersGuest.size(), poPlayer );
                    qvPanelPlayersGuest.append( poPlayer );
                }
                if( poMinute )
                {
                    QStringList qslPlayerMinute = QStringList() << QString::number( poPlayer->playerId() )
                                                                << QString::number( poPlayer->playerNumber() )
                                                                << poPlayer->playerName()
                                                                << QString( "0" );
                    poMinute->addPlayer( cTeamType::GUEST, qslPlayerMinute );
                }
            }
        }
    }
    _savePlayers( false );
}

//===========================================================================================================
void MainWindow::_processTeamPopupMenu(bool bHome)
{
    QMenu   qmMenu;
    QString qsTitle = tr( "Team GUEST" );

    if( bHome ) qsTitle = tr( "Team HOME" );

    QAction qaTitle( qsTitle, &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qfTitle.setPointSize( 11 );
    qaTitle.setFont( qfTitle );

    QFont   qfItems;
    qfItems.setPointSize( 10 );

    QAction qaImportPlayer( QIcon( ":/resources/folder.png" ), tr("Import players from file ..."), &qmMenu );
    QAction qaAddPlayer( QIcon( ":/resources/edit.png" ), tr("Add players manually ..."), &qmMenu );
    QAction qaSelectPlayers( QIcon( ":/resources/basketball_player_in.png" ), tr("Select players to field ..."), &qmMenu );
    QAction qaDeselectPlayers( QIcon( ":/resources/basketball_player_out.png" ), tr("Remove all players from field."), &qmMenu );

    qaImportPlayer.setFont( qfItems );
    qaAddPlayer.setFont( qfItems );
    qaSelectPlayers.setFont( qfItems );
    qaDeselectPlayers.setFont( qfItems );

    if( bHome ) qaSelectPlayers.setEnabled( ((nCountPlayerFieldHome<5)&&(qvPanelPlayersHome.size()>4)?true:false) );
    else        qaSelectPlayers.setEnabled( ((nCountPlayerFieldGuest<5)&&(qvPanelPlayersGuest.size()>4)?true:false) );

    if( bHome ) qaDeselectPlayers.setEnabled( ((nCountPlayerFieldHome>0)&&(qvPanelPlayersHome.size()>0)?true:false) );
    else        qaDeselectPlayers.setEnabled( ((nCountPlayerFieldGuest>0)&&(qvPanelPlayersGuest.size()>0)?true:false) );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaImportPlayer );
    qmMenu.addAction( &qaAddPlayer );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaSelectPlayers );
    qmMenu.addAction( &qaDeselectPlayers );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet == &qaImportPlayer )
    {
        qslImportedPlayers = QStringList("");
        qsTeamNameFromFile = "";
        _importPlayersFromFile();
        _addPlayers( bHome );
        if( qsTeamNameFromFile.length() > 0 )
        {
            _updateTeamName( bHome, qsTeamNameFromFile );

            QStringList qslHeader = QStringList() << ui->lblTeamHome->text() << tr("Minute") << ui->lblTeamGuest->text();

            ui->tbMinute->setHorizontalHeaderLabels( qslHeader );

            poSettings->setTeamName( bHome, qsTeamNameFromFile );
        }
    }
    else if( qaRet == &qaAddPlayer )
    {
        _addPlayerManually( bHome, true );
    }
    else if( qaRet == &qaSelectPlayers )
    {
        m_bSelectPlayersToField = true;
    }
    else if( qaRet == &qaDeselectPlayers )
    {
        if( bHome )
        {
            for( int i=0; i<qvPanelPlayersHome.size(); i++ )
            {
                qvPanelPlayersHome.at(i)->setPlayerToSubstitute();
            }
            nCountPlayerFieldHome = 0;
        }
        else
        {
            for( int i=0; i<qvPanelPlayersGuest.size(); i++ )
            {
                qvPanelPlayersGuest.at(i)->setPlayerToSubstitute();
            }
            nCountPlayerFieldGuest = 0;
        }
    }
    _enableControls();
    _savePlayers( bHome );
}

//===========================================================================================================
void MainWindow::_processPlayerPopupMenu(cPanelPlayer *poPlayerPanel, bool bHome)
{
    QMenu   qmMenu;

    QAction qaTitle( poPlayerPanel->playerWithNumber(" "), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qfTitle.setPointSize( 11 );
    qaTitle.setFont( qfTitle );

    QFont   qfItems;
    qfItems.setPointSize( 10 );

    QAction qaPlayerScore1( QIcon( ":/resources/basketball_score_1.png" ),tr("Score 1 attempt ..."), &qmMenu );
    qaPlayerScore1.setFont( qfItems );

    QAction qaPlayerScore2( QIcon( ":/resources/basketball_score_2.png" ),tr("Score 2 attempt ..."), &qmMenu );
    qaPlayerScore2.setEnabled( poPlayerPanel->isPlayerOnField() );
    qaPlayerScore2.setFont( qfItems );

    QAction qaPlayerScore3( QIcon( ":/resources/basketball_score_3.png" ),tr("Score 3 attempt ..."), &qmMenu );
    qaPlayerScore3.setEnabled( poPlayerPanel->isPlayerOnField() );
    qaPlayerScore3.setFont( qfItems );

    QAction qaPlayerFoul( QIcon( ":/resources/basketball_player_fault.png" ),tr("Player comitted foul ..."), &qmMenu );
    qaPlayerFoul.setEnabled( poPlayerPanel->isPlayerOnField() );
    qaPlayerFoul.setFont( qfItems );

    QAction qaPlayerToField( QIcon( ":/resources/basketball_player_in.png" ),tr("Move player to field ..."), &qmMenu );
    qaPlayerToField.setEnabled( _isPlayerAllowedToField( poPlayerPanel, bHome ) );
    qaPlayerToField.setFont( qfItems );

    QAction qaPlayerToSubstitute( QIcon( ":/resources/basketball_player_out.png" ),tr("Move player to substitute ..."), &qmMenu );
    qaPlayerToSubstitute.setEnabled( poPlayerPanel->isPlayerOnField() );
    qaPlayerToSubstitute.setFont( qfItems );

    QAction qaPlayerEdit( QIcon( ":/resources/edit.png" ), tr("Edit player data ..."), &qmMenu );
    qaPlayerEdit.setFont( qfItems );

    QAction qaPlayerDelete( QIcon( ":/resources/delete.png" ), tr("Delete player from team"), &qmMenu );
    qaPlayerDelete.setFont( qfItems );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerScore1 );
    qmMenu.addAction( &qaPlayerScore2 );
    qmMenu.addAction( &qaPlayerScore3 );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerFoul );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerToField );
    qmMenu.addAction( &qaPlayerToSubstitute );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerEdit );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerDelete );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet == &qaPlayerScore1 )
    {
        if( QMessageBox::question( this, "Question",
                                   tr("Is the penalty throw succeeded?"),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            _updateScore( poPlayerPanel, 1, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_1, poPlayerPanel->playerAndNumber(), bHome );
        }
        else
        {
            _updateScore( poPlayerPanel, 0, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_1_FAILED, poPlayerPanel->playerAndNumber(), bHome );
        }
    }
    else if( qaRet == &qaPlayerScore2 )
    {
        if( QMessageBox::question( this, "Question",
                                   tr("Is the throw succeeded?"),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            _updateScore( poPlayerPanel, 2, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_2, poPlayerPanel->playerAndNumber(), bHome );
        }
        else
        {
            _updateScore( poPlayerPanel, 0, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_2_FAILED, poPlayerPanel->playerAndNumber(), bHome );
        }
    }
    else if( qaRet == &qaPlayerScore3 )
    {
        if( QMessageBox::question( this, "Question",
                                   tr("Is the throw succeeded?"),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            _updateScore( poPlayerPanel, 3, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_3, poPlayerPanel->playerAndNumber(), bHome );
        }
        else
        {
            _updateScore( poPlayerPanel, 0, bHome );
            _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_3_FAILED, poPlayerPanel->playerAndNumber(), bHome );
        }
    }
    else if( qaRet == &qaPlayerFoul )
    {
        poPlayerPanel->setPlayerFault();
        QStringList qslPlayer = QStringList() << QString::number( poPlayerPanel->playerId() )
                                              << QString::number( poPlayerPanel->playerNumber() )
                                              << poPlayerPanel->playerName()
                                              << QString::number( poPlayerPanel->playerFaults() );
        poMinute->updatePlayer( (bHome ? cTeamType::HOME : cTeamType::GUEST), qslPlayer );
        _addMinuteAction( cMinActionType::MAT_PLAYER_FAULT_GAME, poPlayerPanel->playerAndNumber(), bHome );
        _savePlayers( bHome );
    }
    else if( qaRet == &qaPlayerEdit )
    {
        dlgPlayerEdit   obDlgPlayerEdit( this, poPlayerPanel->playerNumber(), poPlayerPanel->playerName() );

        if( obDlgPlayerEdit.exec() == QDialog::Accepted )
        {
            if( poPlayerPanel->playerNumber() != obDlgPlayerEdit.playerNumber() )
            {
                if( _isPlayerNumberAssigned( bHome, obDlgPlayerEdit.playerNumber() ) )
                {
                    QMessageBox::warning( this, tr("Warning"),
                                          tr( "This number (%1) already assigned to another player.\n"
                                          "Please select another number for this player'").arg( obDlgPlayerEdit.playerNumber() ) );
                    return;
                }
            }
            poPlayerPanel->setPlayerNumber( obDlgPlayerEdit.playerNumber() );
            poPlayerPanel->setPlayerName( obDlgPlayerEdit.playerName() );
            if( bHome ) _reorderPlayersHome();
            else        _reorderPlayersGuest();

            QStringList qslPlayer = QStringList() << QString::number( poPlayerPanel->playerId() )
                                                  << QString::number( poPlayerPanel->playerNumber() )
                                                  << poPlayerPanel->playerName()
                                                  << QString::number( poPlayerPanel->playerFaults() );
            if( poMinute )
            {
                poMinute->updatePlayer( ( bHome ? cTeamType::HOME : cTeamType::GUEST ),
                                        qslPlayer );
            }
        }
    }
    else if( qaRet == &qaPlayerToField )
    {
        _setPlayerToField( poPlayerPanel, bHome );
    }
    else if( qaRet == &qaPlayerToSubstitute )
    {
        _setPlayerToSubstitute( poPlayerPanel, bHome );
    }
    else if( qaRet == &qaPlayerDelete )
    {
        if( QMessageBox::question( this, tr("Question"),
                                   tr( "Are you sure you want to delete player\n'%1'\n from the team?" )
                                       .arg( poPlayerPanel->playerWithNumber(" ") ),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            _deletePlayer( poPlayerPanel, bHome );
        }
    }
    _enableControls();
    _savePlayers( bHome );
}

//===========================================================================================================
void MainWindow::_reorderPlayersHome()
{
    for( int i=0; i<qvPanelPlayersHome.size(); )
    {
        if( i+1 < qvPanelPlayersHome.size() )
        {
            if( qvPanelPlayersHome.at(i)->playerNumber() > qvPanelPlayersHome.at(i+1)->playerNumber() )
            {
                ui->vlPlayersHome->removeWidget( qvPanelPlayersHome.at(i) );
                ui->vlPlayersHome->insertWidget( i+1, qvPanelPlayersHome.at(i) );
                qvPanelPlayersHome.swap( i, i+1 );
            }
            else
            {
                i++;
            }
        }
        else
        {
            break;
        }
    }
    for( int i=qvPanelPlayersHome.size()-2; i>-1; )
    {
        if( i > -1 )
        {
            if( qvPanelPlayersHome.at(i)->playerNumber() > qvPanelPlayersHome.at(i+1)->playerNumber() )
            {
                ui->vlPlayersHome->removeWidget( qvPanelPlayersHome.at(i) );
                ui->vlPlayersHome->insertWidget( i+1, qvPanelPlayersHome.at(i) );
                qvPanelPlayersHome.swap( i, i+1 );
            }
            else
            {
                i--;
            }
        }
        else
        {
            break;
        }
    }
    _savePlayers( true );
}

//===========================================================================================================
void MainWindow::_reorderPlayersGuest()
{
    for( int i=0; i<qvPanelPlayersGuest.size(); )
    {
        if( i+1 < qvPanelPlayersGuest.size() )
        {
            if( qvPanelPlayersGuest.at(i)->playerNumber() > qvPanelPlayersGuest.at(i+1)->playerNumber() )
            {
                ui->vlPlayersGuest->removeWidget( qvPanelPlayersGuest.at(i) );
                ui->vlPlayersGuest->insertWidget( i+1, qvPanelPlayersGuest.at(i) );
                qvPanelPlayersGuest.swap( i, i+1 );
            }
            else
            {
                i++;
            }
        }
        else
        {
            break;
        }
    }
    for( int i=qvPanelPlayersGuest.size()-2; i>-1; )
    {
        if( i > -1 )
        {
            if( qvPanelPlayersGuest.at(i)->playerNumber() > qvPanelPlayersGuest.at(i+1)->playerNumber() )
            {
                ui->vlPlayersGuest->removeWidget( qvPanelPlayersGuest.at(i) );
                ui->vlPlayersGuest->insertWidget( i+1, qvPanelPlayersGuest.at(i) );
                qvPanelPlayersGuest.swap( i, i+1 );
            }
            else
            {
                i--;
            }
        }
        else
        {
            break;
        }
    }
    _savePlayers( false );
}

//===========================================================================================================
void MainWindow::_deletePlayer(cPanelPlayer *poPlayerPanel, bool bHome)
{
    QList<cPanelPlayer*>    *pQLPlayers = NULL;
    QVBoxLayout             *pQWPlayers = NULL;

    if( bHome )
    {
        pQLPlayers = &qvPanelPlayersHome;
        pQWPlayers = ui->vlPlayersHome;
    }
    else
    {
        pQLPlayers = &qvPanelPlayersGuest;
        pQWPlayers = ui->vlPlayersGuest;
    }

    if( poMinute ) poMinute->deletePlayer( ( bHome ? cTeamType::HOME : cTeamType::GUEST ),
                                           QString::number( poPlayerPanel->playerId() ) );

    for( int i=0; i<pQLPlayers->size(); i++ )
    {
        if( pQLPlayers->at(i) == poPlayerPanel )
        {
            poPlayerPanel->setVisible( false );
            pQWPlayers->removeWidget( poPlayerPanel );
            pQLPlayers->removeAt(i);
//            poPlayerPanel->removePlayer();
//            delete poPlayerPanel;
            break;
        }
    }
    _savePlayers( bHome );
}

//===========================================================================================================
void MainWindow::_setPlayerToField( cPanelPlayer *poPlayerPanel, bool bHome )
{
    poPlayerPanel->setPlayerToField();

    if( bHome )
    {
        nCountPlayerFieldHome++;
    }
    else
    {
        nCountPlayerFieldGuest++;
    }
    _enableControls();
}

//===========================================================================================================
void MainWindow::_setPlayerToSubstitute( cPanelPlayer *poPlayerPanel, bool bHome )
{
    poPlayerPanel->setPlayerToSubstitute();

    if( bHome )
    {
        nCountPlayerFieldHome--;
    }
    else
    {
        nCountPlayerFieldGuest--;
    }
    _enableControls();
}

//===========================================================================================================
void MainWindow::_processTeamNamePopupMenu(bool bHome)
{
    dlgEdit   obDlgEdit( this );

    if( bHome ) obDlgEdit.setName( ui->lblTeamHome->text() );
    else        obDlgEdit.setName( ui->lblTeamGuest->text() );

    if( obDlgEdit.exec() == QDialog::Accepted )
    {
        _updateTeamName( bHome, obDlgEdit.name() );

        QStringList qslHeader = QStringList() << ui->lblTeamHome->text() << tr("Minute") << ui->lblTeamGuest->text();

        ui->tbMinute->setHorizontalHeaderLabels( qslHeader );
    }
}

//===========================================================================================================
bool MainWindow::_isPlayerAllowedToField(cPanelPlayer *poPlayerPanel, bool bHome)
{
    if( poPlayerPanel->isPlayerOnField() )  return false;
    if( !poPlayerPanel->isEnabledToPlay() ) return false;

    if( bHome )
    {
        if( nCountPlayerFieldHome == 5 )    return false;
    }
    else
    {
        if( nCountPlayerFieldGuest == 5 )   return false;
    }

    return true;
}

//===========================================================================================================
void MainWindow::_selectPlayerFromField( bool bHome )
{
    QList<cPanelPlayer*>    *qlPlayers;
    QMenu                    qmMenu;

    if( bHome ) qlPlayers = &qvPanelPlayersHome;
    else        qlPlayers = &qvPanelPlayersGuest;

    QAction qaTitle( tr("Select player to substitute ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        if( qlPlayers->at(i)->isPlayerOnField() )
        {
            qmMenu.addAction( qlPlayers->at(i)->playerWithNumber(" - ") );
        }
    }

    QAction *qaRet = qmMenu.exec( posMenu );

    pPlayerToSubstitute = NULL;
    if( qaRet && qaRet->text().contains( " - ") )
    {
        for( int i=0; i<qlPlayers->size(); i++ )
        {
            if( qlPlayers->at(i)->playerNumber() == qaRet->text().split( " - " ).at(0).toInt() )
            {
                pPlayerToSubstitute = qlPlayers->at(i);
                break;
            }
        }
    }
}

//===========================================================================================================
void MainWindow::_selectPlayerFromSubstitute( bool bHome )
{
    QList<cPanelPlayer*>    *qlPlayers;
    QMenu                    qmMenu;

    if( bHome ) qlPlayers = &qvPanelPlayersHome;
    else        qlPlayers = &qvPanelPlayersGuest;

    QAction qaTitle( tr("Select player to field ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        if( !qlPlayers->at(i)->isPlayerOnField() && qlPlayers->at(i)->isEnabledToPlay() )
        {
            qmMenu.addAction( qlPlayers->at(i)->playerWithNumber(" - ") );
        }
    }

    QAction *qaRet = qmMenu.exec( posMenu );

    pPlayerToField = NULL;
    if( qaRet && qaRet->text().contains( " - ") )
    {
        for( int i=0; i<qlPlayers->size(); i++ )
        {
            if( qlPlayers->at(i)->playerNumber() == qaRet->text().split( " - " ).at(0).toInt() )
            {
                pPlayerToField = qlPlayers->at(i);
                break;
            }
        }
    }
}
/*
//===========================================================================================================
void MainWindow::_increaseTeamScore(int nScoreValue, bool bHome)
{
    QList<cPanelPlayer*>    *qlPlayers;
    QMenu                    qmMenu;

    if( bHome ) qlPlayers = &qvPanelPlayersHome;
    else        qlPlayers = &qvPanelPlayersGuest;

    QAction qaTitle( tr("Select player ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        if( qlPlayers->at(i)->isPlayerOnField() )
        {
            qmMenu.addAction( qlPlayers->at(i)->playerWithNumber(" - ") );
        }
    }

    posMenu.setX( QCursor::pos().x() );
    posMenu.setY( QCursor::pos().y() );

    cPanelPlayer *pPlayer = NULL;
    do
    {
        QAction *qaRet = qmMenu.exec( posMenu );

        if( qaRet && qaRet->text().contains( " - ") )
        {
            for( int i=0; i<qlPlayers->size(); i++ )
            {
                if( qlPlayers->at(i)->playerNumber() == qaRet->text().split( " - " ).at(0).toInt() )
                {
                    pPlayer = qlPlayers->at(i);
                    break;
                }
            }
        }

        if( pPlayer == NULL )
        {
            QMessageBox::warning( this, tr("Warning"),
                                  tr("Player must be selected to document the score!") );
        }
        else
        {
            _updateScore( pPlayer, nScoreValue, bHome );
        }

    } while( pPlayer == NULL );
}

//===========================================================================================================
void MainWindow::_increaseTeamScoreFault(bool bHome)
{
    QList<cPanelPlayer*>    *qlPlayers;
    QMenu                    qmMenu;

    if( bHome ) qlPlayers = &qvPanelPlayersHome;
    else        qlPlayers = &qvPanelPlayersGuest;

    QAction qaTitle( tr("Select player ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        QAction *qaPlayer = new QAction( qlPlayers->at(i)->playerWithNumber(" - "), &qmMenu );
        if( qlPlayers->at(i)->isPlayerOnField() )
        {
            QFont   qfPlayer;
            qfPlayer.setBold( true );
            qaPlayer->setFont( qfPlayer );
        }
        qmMenu.addAction( qaPlayer );
    }

    posMenu.setX( QCursor::pos().x() );
    posMenu.setY( QCursor::pos().y() );

    cPanelPlayer *pPlayer = NULL;
    do
    {
        QAction *qaRet = qmMenu.exec( posMenu );

        if( qaRet && qaRet->text().contains( " - ") )
        {
            for( int i=0; i<qlPlayers->size(); i++ )
            {
                if( qlPlayers->at(i)->playerNumber() == qaRet->text().split( " - " ).at(0).toInt() )
                {
                    pPlayer = qlPlayers->at(i);
                    break;
                }
            }
        }

        if( pPlayer == NULL )
        {
            QMessageBox::warning( this, tr("Warning"),
                                  tr("Player must be selected to document the score!") );
        }
        else
        {
            if( QMessageBox::question( this, "Question",
                                       tr("Is the penalty throw succeeded?"),
                                       QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
            {
                _updateScore( pPlayer, 1, bHome );
                _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_1, pPlayer->playerAndNumber(), bHome );
            }
            else
            {
                _updateScore( pPlayer, 0, bHome );
                _addMinuteAction( cMinActionType::MAT_PLAYER_SCORE_1_FAILED, pPlayer->playerAndNumber(), bHome );
            }
        }

    } while( pPlayer == NULL );
}
*/
//===========================================================================================================
void MainWindow::_updateScore(cPanelPlayer *poPlayerPanel, int nScoreValue, bool bHome)
{
    if( bHome )
    {
        nScoreHome += nScoreValue;
        m_nQuarterScoreHome += nScoreValue;
        ui->ledPointsHome->setText( QString::number( nScoreHome ) );
        on_pbGuestPlay_clicked();
        poSettings->setScore( bHome, nScoreHome );
    }
    else
    {
        nScoreGuest += nScoreValue;
        m_nQuarterScoreGuest += nScoreValue;
        ui->ledPointsGuest->setText( QString::number( nScoreGuest ) );
        on_pbHomePlay_clicked();
        poSettings->setScore( bHome, nScoreGuest );
    }
    if( nScoreValue> 0 && poSettings->timerStopAfterScore() ) on_pbSignalReferee_clicked();
    poPlayerPanel->increaseScore( nScoreValue );
}

//===========================================================================================================
void MainWindow::_setPlayerFault(bool bHome)
{
    QList<cPanelPlayer*>    *qlPlayers;
    QMenu                    qmMenu;

    if( bHome ) qlPlayers = &qvPanelPlayersHome;
    else        qlPlayers = &qvPanelPlayersGuest;

    QAction qaTitle( tr("Select player ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        if( qlPlayers->at(i)->isPlayerOnField() )
        {
            qmMenu.addAction( qlPlayers->at(i)->playerWithNumber(" - ") );
        }
    }

    posMenu.setX( QCursor::pos().x() );
    posMenu.setY( QCursor::pos().y() );

    cPanelPlayer *pPlayer = NULL;
    do
    {
        QAction *qaRet = qmMenu.exec( posMenu );

        if( qaRet && qaRet->text().contains( " - ") )
        {
            for( int i=0; i<qlPlayers->size(); i++ )
            {
                if( qlPlayers->at(i)->playerNumber() == qaRet->text().split( " - " ).at(0).toInt() )
                {
                    pPlayer = qlPlayers->at(i);
                    break;
                }
            }
        }

        if( pPlayer == NULL )
        {
            QMessageBox::warning( this, tr("Warning"),
                                  tr("Player must be selected to document the fault!") );
        }
        else
        {
            pPlayer->setPlayerFault();
            QStringList qslPlayer = QStringList() << QString::number( pPlayer->playerId() )
                                                  << QString::number( pPlayer->playerNumber() )
                                                  << pPlayer->playerName()
                                                  << QString::number( pPlayer->playerFaults() );
            poMinute->updatePlayer( (bHome ? cTeamType::HOME : cTeamType::GUEST), qslPlayer );
            _addMinuteAction( cMinActionType::MAT_PLAYER_FAULT_GAME, pPlayer->playerAndNumber(), bHome );
        }

    } while( pPlayer == NULL );

    _savePlayers( bHome );
}

//===========================================================================================================
void MainWindow::_savePlayers(bool bHome)
{
    QList<cPanelPlayer*>    *pQLPlayers = NULL;

    if( bHome )
    {
        pQLPlayers = &qvPanelPlayersHome;
    }
    else
    {
        pQLPlayers = &qvPanelPlayersGuest;
    }

    QStringList qslPlayers;
    QStringList qslPlayersField;

    for( int i=0; i<pQLPlayers->size(); i++ )
    {
        QString qsPlayer = QString( "%1\t%2" )
                                    .arg( pQLPlayers->at(i)->playerWithNumber() )
                                    .arg( pQLPlayers->at(i)->playerFaults() );
        qslPlayers << qsPlayer;
        if( pQLPlayers->at(i)->isPlayerOnField() )
            qslPlayersField << qsPlayer;
    }
    poSettings->setPlayers( bHome, qslPlayers );
    poSettings->setPlayersField( bHome, qslPlayersField );
}

//===========================================================================================================
void MainWindow::_addMinuteAction(cMinActionType::teAction p_teAction, QString p_qsParameter, bool bHome)
{
    if( poMinute )
    {
        QString qsAction        = QString( cMinActionType::toStr( p_teAction ) ).arg( p_qsParameter );
        int     nColumn         = ( bHome ? 0 : 2 );
        int     nScoreH         = -1;
        int     nScoreG         = -1;

        QTableWidgetItem *newItem = new QTableWidgetItem( qsAction );
        ui->tbMinute->setWordWrap( true );
        ui->tbMinute->setRowCount( ++m_nMinuteRowCount );
        ui->tbMinute->setItem( m_nMinuteRowCount-1, nColumn, newItem );

        if( p_teAction == cMinActionType::MAT_PLAYER_SCORE_1 ||
            p_teAction == cMinActionType::MAT_PLAYER_SCORE_2 ||
            p_teAction == cMinActionType::MAT_PLAYER_SCORE_3 )
        {
            QTableWidgetItem *newScore = new QTableWidgetItem( QString("%1 - %2").arg( nScoreHome ).arg( nScoreGuest ) );
            newScore->setTextAlignment( Qt::AlignCenter|Qt::AlignHCenter );
            ui->tbMinute->setItem( m_nMinuteRowCount-1, 1, newScore );
            nScoreH = nScoreHome;
            nScoreG = nScoreGuest;
        }
        ui->tbMinute->resizeRowToContents( m_nMinuteRowCount-1 );
        ui->tbMinute->scrollToBottom();
        poMinute->addAction( nTimeMinuteMiliSec,
                             ( bHome ? cTeamType::HOME : cTeamType::GUEST ),
                             p_teAction,
                             ui->ledCountQuarter->text().toInt(),
                             p_qsParameter,
                             nScoreH,
                             nScoreG );
        poMinute->updateScore( ui->ledCountQuarter->text().toInt(), m_nQuarterScoreHome, m_nQuarterScoreGuest );
    }
}

//===========================================================================================================
void MainWindow::_updateTeamName(bool bHome, QString p_qsName)
{
    QLabel *poLblName = NULL;

    if( bHome ) poLblName = ui->lblTeamHome;
    else        poLblName = ui->lblTeamGuest;

    poLblName->setText( p_qsName );

    if( poMinute )
    {
        poMinute->updateTeam( ( bHome ? cTeamType::HOME : cTeamType::GUEST ), p_qsName );
    }
}

//===========================================================================================================
bool MainWindow::_isPlayerNumberAssigned( bool bHome, int p_nNumber )
{
    QList<cPanelPlayer*>    *pQLPlayers = NULL;

    if( bHome ) {   pQLPlayers = &qvPanelPlayersHome;   }
    else        {   pQLPlayers = &qvPanelPlayersGuest;  }

    QStringList qslPlayers;
    QStringList qslPlayersField;

    for( int i=0; i<pQLPlayers->size(); i++ )
    {
        if( pQLPlayers->at(i)->playerNumber() == p_nNumber )
        {
            return true;
        }
    }

    return false;
}

void MainWindow::on_pbReset_clicked()
{

}

void MainWindow::on_pbMinuteAddCustomText_clicked()
{
    dlgLineEdit obDlgLineEdit( this );

    QMessageBox qmsgQuestion( this );

    qmsgQuestion.setWindowTitle( tr("Question") );
    qmsgQuestion.setText( tr("To which team do you want to add new entry?") );
    qmsgQuestion.setIcon( QMessageBox::Question );
    qmsgQuestion.addButton( QString("  %1  ").arg( ui->lblTeamHome->text() ), QMessageBox::YesRole );
    qmsgQuestion.addButton( QString("  %1  ").arg( ui->lblTeamGuest->text() ), QMessageBox::NoRole );

    cTeamType::teType   ctTeam  = cTeamType::HOME;
    int                 nRet    = qmsgQuestion.exec();

    if( nRet == 0 ) ctTeam  = cTeamType::HOME;
    else            ctTeam  = cTeamType::GUEST;

    obDlgLineEdit.setTitle( tr("Add custom minute entry") );
    if( obDlgLineEdit.exec() == QDialog::Accepted )
    {
        int     nColumn         = ( ctTeam == cTeamType::HOME ? 0 : 2 );

        QTableWidgetItem *newItem = new QTableWidgetItem( obDlgLineEdit.value() );
        ui->tbMinute->setWordWrap( true );
        ui->tbMinute->setRowCount( ++m_nMinuteRowCount );
        ui->tbMinute->setItem( m_nMinuteRowCount-1, nColumn, newItem );

        ui->tbMinute->resizeRowToContents( m_nMinuteRowCount-1 );
        ui->tbMinute->scrollToBottom();
        poMinute->addAction( nTimeMinuteMiliSec,
                             ctTeam,
                             cMinActionType::MAT_CUSTOM,
                             ui->ledCountQuarter->text().toInt(),
                             obDlgLineEdit.value() );
    }
}
