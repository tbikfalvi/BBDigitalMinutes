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

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Player panel class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

//===========================================================================================================
cSettings::cSettings()
{
    QSettings   qsetApplication( QString( "%1/BBDigitalMinutes.info" ).arg( QDir::currentPath() ), QSettings::IniFormat );

    pQSetTeamHome   = new QSettings( QString( "%1/TeamHome.info"  ).arg( QDir::currentPath() ), QSettings::IniFormat );
    pQSetTeamGuest  = new QSettings( QString( "%1/TeamGuest.info" ).arg( QDir::currentPath() ), QSettings::IniFormat );
    pQSetGameStatus = new QSettings( QString( "%1/Game.info"      ).arg( QDir::currentPath() ), QSettings::IniFormat );

    // Application settings related
    m_qsLang                = qsetApplication.value( "Lang",                    "en"    ).toString();
    m_bReloadSizePos        = qsetApplication.value( "ReloadSizePos",           "false" ).toBool();
    m_bReloadMinute         = qsetApplication.value( "ReloadMinute",            "false" ).toBool();
    m_bSoundEnabled         = qsetApplication.value( "SoundEnabled",            "false" ).toBool();
    m_bIsMinuteClosed       = qsetApplication.value( "MinuteClosed",            "false" ).toBool();
    m_nWindowLeft           = qsetApplication.value( "MainWindow/Left",         0       ).toInt();
    m_nWindowTop            = qsetApplication.value( "MainWindow/Top",          0       ).toInt();
    m_nWindowWidth          = qsetApplication.value( "MainWindow/Width",        1500    ).toInt();
    m_nWindowHeight         = qsetApplication.value( "MainWindow/Height",       1000    ).toInt();
    m_nCountQuarters        = qsetApplication.value( "Game/QuarterCount",       4       ).toInt();
    m_nTimeQuarter          = qsetApplication.value( "Game/QuarterTime",        10      ).toInt();
    m_bOvertimeEnabled      = qsetApplication.value( "Game/OvertimeEnabled",    true    ).toBool();
    m_nTimeOvertime         = qsetApplication.value( "Game/Overtime",           5       ).toInt();
    m_nTimeTimeout          = qsetApplication.value( "Game/Timeout",            60      ).toInt();
    m_bTimeOffenseUsed      = qsetApplication.value( "Game/OffenseTimeUsed",    false   ).toBool();
    m_nTimeOffense          = qsetApplication.value( "Game/OffenseTime",        24      ).toInt();
    m_nTimeOffenseExt       = qsetApplication.value( "Game/OffenseTimeExtend",  14      ).toInt();
}

//===========================================================================================================
cSettings::~cSettings()
{
    saveAppSettings();
}

//===========================================================================================================
void cSettings::saveAppSettings()
{
    // Application settings related
    QSettings   qsetApplication( QString( "%1/BBDigitalMinutes.info" ).arg( QDir::currentPath() ), QSettings::IniFormat );

    qsetApplication.setValue( "Lang",                   m_qsLang                );
    qsetApplication.setValue( "ReloadSizePos",          m_bReloadSizePos        );
    qsetApplication.setValue( "ReloadMinute",           m_bReloadMinute         );
    qsetApplication.setValue( "SoundEnabled",           m_bSoundEnabled         );
    qsetApplication.setValue( "MinuteClosed",           m_bIsMinuteClosed       );
    qsetApplication.setValue( "MainWindow/Left",        m_nWindowLeft           );
    qsetApplication.setValue( "MainWindow/Top",         m_nWindowTop            );
    qsetApplication.setValue( "MainWindow/Width",       m_nWindowWidth          );
    qsetApplication.setValue( "MainWindow/Height",      m_nWindowHeight         );
    qsetApplication.setValue( "Game/QuarterCount",      m_nCountQuarters        );
    qsetApplication.setValue( "Game/QuarterTime",       m_nTimeQuarter          );
    qsetApplication.setValue( "Game/OvertimeEnabled",   m_bOvertimeEnabled      );
    qsetApplication.setValue( "Game/Overtime",          m_nTimeOvertime         );
    qsetApplication.setValue( "Game/Timeout",           m_nTimeTimeout          );
    qsetApplication.setValue( "Game/OffenseTimeUsed",   m_bTimeOffenseUsed      );
    qsetApplication.setValue( "Game/OffenseTime",       m_nTimeOffense          );
    qsetApplication.setValue( "Game/OffenseTimeExtend", m_nTimeOffenseExt       );
}

//===========================================================================================================
QString cSettings::teamName(bool bHome)
{
    if( bHome ) return pQSetTeamHome->value( "TeamName",  QObject::tr("HOME team") ).toString();
    else        return pQSetTeamGuest->value( "TeamName", QObject::tr("GUEST team") ).toString();
}

//===========================================================================================================
void cSettings::setTeamName(bool bHome, QString name)
{
    if( bHome ) pQSetTeamHome->setValue( "TeamName", name );
    else        pQSetTeamGuest->setValue( "TeamName", name );
}

//===========================================================================================================
QStringList cSettings::players( bool bHome )
{
    QString qsPlayers;

    if( bHome ) qsPlayers = pQSetTeamHome->value( "Players", "" ).toString();
    else        qsPlayers = pQSetTeamGuest->value( "Players", "" ).toString();

    return qsPlayers.split( "|" );
}

//===========================================================================================================
void cSettings::setPlayers(bool bHome, QStringList players)
{
    if( bHome ) pQSetTeamHome->setValue( "Players", players.join( "|" ) );
    else        pQSetTeamGuest->setValue( "Players", players.join( "|" ) );
}

//===========================================================================================================
QStringList cSettings::playersField( bool bHome )
{
    QString qsPlayers;

    if( bHome ) qsPlayers = pQSetTeamHome->value( "PlayersOnField", "" ).toString();
    else        qsPlayers = pQSetTeamGuest->value( "PlayersOnField", "" ).toString();

    return qsPlayers.split( "|" );
}

//===========================================================================================================
void cSettings::setPlayersField(bool bHome, QStringList players)
{
    if( bHome ) pQSetTeamHome->setValue( "PlayersOnField", players.join( "|" ) );
    else        pQSetTeamGuest->setValue( "PlayersOnField", players.join( "|" ) );
}

//===========================================================================================================
int cSettings::score( bool bHome )
{
    if( bHome ) return pQSetGameStatus->value( "ScoreHome", "0" ).toInt();
    else        return pQSetGameStatus->value( "ScoreGuest", "0" ).toInt();
}

//===========================================================================================================
void cSettings::setScore( bool bHome, int score )
{
    if( bHome ) pQSetGameStatus->setValue( "ScoreHome", score );
    else        pQSetGameStatus->setValue( "ScoreGuest", score );
}

//===========================================================================================================
int cSettings::quarter()
{
    return pQSetGameStatus->value( "Quarter", "1" ).toInt();
}

//===========================================================================================================
void cSettings::setQuarter(int quarter)
{
    return pQSetGameStatus->setValue( "Quarter", quarter );
}

//===========================================================================================================
QString cSettings::minuteFileName()
{
    return pQSetGameStatus->value( "MinuteFileName", "" ).toString();
}

//===========================================================================================================
void cSettings::setMinuteFileName(QString filename)
{
    return pQSetGameStatus->setValue( "MinuteFileName", filename );
}

//===========================================================================================================

//===========================================================================================================
void cSettings::createMinute(QString p_qsMinuteName)
{
    qsMinuteFileName = QString( "%1.dmin" ).arg( p_qsMinuteName );
}

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Player panel class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

//===========================================================================================================
cPanelPlayer::cPanelPlayer(QWidget *p_poParent, QString p_qsPlayerNumber, QString p_qsPlayerName)
{
    nPlayerNumber   = p_qsPlayerNumber.toInt();
    qsPlayerName    = p_qsPlayerName;
    bPlayerOnField  = false;

    nScores         = 0;
    nCountSingle    = 0;
    nCountDouble    = 0;
    nCountTriple    = 0;
    nCountFaults    = 0;
    nCountFaults    = 0;

    setParent( p_poParent );

    QFont   qfPlayer;

    qfPlayer.setPointSize( 10 );
//    qfPlayer.setBold( true );

    hlPlayer = new QHBoxLayout( this );
    hlPlayer->setObjectName( QString::fromUtf8( "hlPlayer" ) );
    hlPlayer->setSpacing( 0 );
    hlPlayer->setMargin( 0 );

    //-------------------------------------------------------------------------------------------------------
    frmPlayerNumber = new QFrame( this );
    frmPlayerNumber->setObjectName( QString::fromUtf8( "frmPlayerNumber" ) );
    frmPlayerNumber->setMinimumWidth( 30 );
    frmPlayerNumber->setMinimumHeight( 30 );
    frmPlayerNumber->setMaximumWidth( 30 );
    frmPlayerNumber->setMaximumHeight( 30 );
    frmPlayerNumber->setFrameShape( QFrame::Panel );
    frmPlayerNumber->setFrameShadow( QFrame::Raised );

    lblPlayerNumber = new QLabel( frmPlayerNumber );
    lblPlayerNumber->setObjectName( QString::fromUtf8( "lblPlayerNumber" ) );
    lblPlayerNumber->setGeometry( 2, 2, 26, 26 );
    lblPlayerNumber->setFont( qfPlayer );
    lblPlayerNumber->setText( QString( "%1" ).arg( nPlayerNumber ) );//, 2, 10, QChar( '0' ) ) );

    hlPlayer->addWidget( frmPlayerNumber );

    //-------------------------------------------------------------------------------------------------------
    frmPlayerName = new QFrame( this );
    frmPlayerName->setObjectName( QString::fromUtf8( "frmPlayerName" ) );
    frmPlayerName->setMinimumHeight( 30 );
    frmPlayerName->setMaximumHeight( 30 );
    frmPlayerName->setFrameShape( QFrame::Panel );
    frmPlayerName->setFrameShadow( QFrame::Raised );

    lblPlayerName = new QLabel( frmPlayerName );
    lblPlayerName->setObjectName( QString::fromUtf8( "lblPlayerName" ) );
    lblPlayerName->setGeometry( 2, 2, 70, 26 );
    lblPlayerName->setFont( qfPlayer );
    lblPlayerName->setText( qsPlayerName );

    hlPlayerName = new QHBoxLayout( frmPlayerName );
    hlPlayerName->setObjectName( QString::fromUtf8( "hlPlayerName" ) );
    hlPlayerName->setSpacing( 1 );
    hlPlayerName->setMargin( 1 );
    hlPlayerName->addWidget( lblPlayerName );

    hlPlayer->addWidget( frmPlayerName );

    //-------------------------------------------------------------------------------------------------------
    frmFault = new QFrame( this );
    frmFault->setObjectName( QString::fromUtf8( "frmFault" ) );
    frmFault->setMinimumWidth( 112 );
    frmFault->setMinimumHeight( 30 );
    frmFault->setMaximumWidth( 112 );
    frmFault->setMaximumHeight( 30 );
    frmFault->setFrameShape( QFrame::Panel );
    frmFault->setFrameShadow( QFrame::Raised );

    lblPlayerFault1 = new QLabel( frmFault );
    lblPlayerFault1->setObjectName( QString::fromUtf8( "lblPlayerFault1" ) );
    lblPlayerFault1->setGeometry( 20, 20, 20, 20 );
    lblPlayerFault1->setScaledContents( true );
    lblPlayerFault1->setPixmap( QPixmap(":/resources/basketball_fault_inactive.png") );

    lblPlayerFault2 = new QLabel( frmFault );
    lblPlayerFault2->setObjectName( QString::fromUtf8( "lblPlayerFault2" ) );
    lblPlayerFault2->setGeometry( 20, 20, 20, 20 );
    lblPlayerFault2->setScaledContents( true );
    lblPlayerFault2->setPixmap( QPixmap(":/resources/basketball_fault_inactive.png") );

    lblPlayerFault3 = new QLabel( frmFault );
    lblPlayerFault3->setObjectName( QString::fromUtf8( "lblPlayerFault3" ) );
    lblPlayerFault3->setGeometry( 20, 20, 20, 20 );
    lblPlayerFault3->setScaledContents( true );
    lblPlayerFault3->setPixmap( QPixmap(":/resources/basketball_fault_inactive.png") );

    lblPlayerFault4 = new QLabel( frmFault );
    lblPlayerFault4->setObjectName( QString::fromUtf8( "lblPlayerFault4" ) );
    lblPlayerFault4->setGeometry( 20, 20, 20, 20 );
    lblPlayerFault4->setScaledContents( true );
    lblPlayerFault4->setPixmap( QPixmap(":/resources/basketball_fault_inactive.png") );

    lblPlayerFault5 = new QLabel( frmFault );
    lblPlayerFault5->setObjectName( QString::fromUtf8( "lblPlayerFault5" ) );
    lblPlayerFault5->setGeometry( 20, 20, 20, 20 );
    lblPlayerFault5->setScaledContents( true );
    lblPlayerFault5->setPixmap( QPixmap(":/resources/basketball_fault_inactive.png") );

    hlFault = new QHBoxLayout( frmFault );
    hlFault->setObjectName( QString::fromUtf8( "hlFault" ) );
    hlFault->setSpacing( 2 );
    hlFault->setMargin( 2 );

    hlFault->addWidget( lblPlayerFault5 );
    hlFault->addWidget( lblPlayerFault4 );
    hlFault->addWidget( lblPlayerFault3 );
    hlFault->addWidget( lblPlayerFault2 );
    hlFault->addWidget( lblPlayerFault1 );

    hlPlayer->addWidget( frmFault );

    qsFrmPlayerNumber   = frmPlayerNumber->styleSheet();
    qsLblPlayerNumber   = lblPlayerNumber->styleSheet();
    qsFrmPlayerName     = frmPlayerName->styleSheet();
    qsLblPlayerName     = lblPlayerName->styleSheet();
}

//===========================================================================================================
cPanelPlayer::~cPanelPlayer()
{
}

//===========================================================================================================
int cPanelPlayer::playerNumber()
{
    return nPlayerNumber;
}

//===========================================================================================================
QString cPanelPlayer::playerName()
{
    return qsPlayerName;
}

//===========================================================================================================
QString cPanelPlayer::playerWithNumber( QString p_qsSeparator )
{
    return QString( "%1%2%3" ).arg( nPlayerNumber ).arg( p_qsSeparator ).arg( qsPlayerName );
}

//====================================================================================
void cPanelPlayer::mousePressEvent ( QMouseEvent *p_poEvent )
{
    emit playerClicked( this );
    p_poEvent->ignore();
}

//====================================================================================
void cPanelPlayer::setPlayerNumber( int p_nPlayerNumber )
{
    nPlayerNumber = p_nPlayerNumber;
    lblPlayerNumber->setText( QString( "%1" ).arg( nPlayerNumber ) );
}

//====================================================================================
void cPanelPlayer::setPlayerName( QString p_qsPlayerName )
{
    qsPlayerName = p_qsPlayerName;
    lblPlayerName->setText( qsPlayerName );
}

//====================================================================================
void cPanelPlayer::setPlayerToField()
{
    bPlayerOnField = true;
    lblPlayerNumber->setStyleSheet( "QLabel { background: rgb(0, 125, 0); font: bold; color: rgb(255, 255, 255); }" );
    lblPlayerName->setStyleSheet( "QLabel { background: rgb(0, 125, 0); font: bold; color: rgb(255, 255, 255); }" );
}

//====================================================================================
void cPanelPlayer::setPlayerToSubstitute()
{
    bPlayerOnField = false;
    frmPlayerNumber->setStyleSheet( qsFrmPlayerNumber );
    lblPlayerNumber->setStyleSheet( qsLblPlayerNumber );
    frmPlayerName->setStyleSheet( qsFrmPlayerName );
    lblPlayerName->setStyleSheet( qsLblPlayerName );
}

//====================================================================================
void cPanelPlayer::removePlayer()
{
    hlFault->removeWidget( lblPlayerFault1 );
    hlFault->removeWidget( lblPlayerFault2 );
    hlFault->removeWidget( lblPlayerFault3 );
    hlFault->removeWidget( lblPlayerFault4 );
    hlFault->removeWidget( lblPlayerFault5 );

    hlPlayerName->removeWidget( lblPlayerName );

    hlPlayer->removeWidget( frmPlayerNumber );
    hlPlayer->removeWidget( frmPlayerName );
    hlPlayer->removeWidget( frmFault );

    delete lblPlayerFault1;
    delete lblPlayerFault2;
    delete lblPlayerFault3;
    delete lblPlayerFault4;
    delete lblPlayerFault5;
    delete frmFault;

    delete lblPlayerName;
    delete frmPlayerName;

    delete lblPlayerNumber;
    delete frmPlayerNumber;

    delete hlPlayer;
}

//====================================================================================
void cPanelPlayer::increaseScore( int p_nScore )
{
    nScores += p_nScore;

    switch( p_nScore )
    {
        case 1:
            increaseSingle();
            break;
        case 2:
            increaseDouble();
            break;
        case 3:
            increaseTriple();
            break;
      default:
            break;
    }
}

//====================================================================================
void cPanelPlayer::setPlayerFault()
{
    nCountFaults++;

    switch( nCountFaults )
    {
    case 1:
        lblPlayerFault1->setPixmap( QPixmap(":/resources/basketball_fault_active.png") );
        break;
    case 2:
        lblPlayerFault2->setPixmap( QPixmap(":/resources/basketball_fault_active.png") );
        break;
    case 3:
        lblPlayerFault3->setPixmap( QPixmap(":/resources/basketball_fault_active.png") );
        break;
    case 4:
        lblPlayerFault4->setPixmap( QPixmap(":/resources/basketball_fault_active.png") );
        break;
    case 5:
        lblPlayerFault5->setPixmap( QPixmap(":/resources/basketball_fault_active.png") );
        setPlayerToSubstitute();
        lblPlayerNumber->setStyleSheet( "QLabel { background: rgb(255, 0, 0); font: bold; color: rgb(255, 255, 255); }" );
        lblPlayerName->setStyleSheet( "QLabel { background: rgb(255, 0, 0); font: bold; color: rgb(255, 255, 255); }" );
        emit playerDisqualified();
        break;
    default:
        break;
    }
}

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

    poSettings = new cSettings();

    nTimerMainPlayTime      = 0;
    nTimeMainMiliSec        = poSettings->timeQuarter() * 60000;

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

    pSoundWhistle = new QSound( QString( "%1/referee_whistle.wav" ).arg( QDir::currentPath() ) );    

    _updateMainPlayTime();

    if( poSettings->isreloadsizepos() )
    {
        move( poSettings->left(), poSettings->top() );
        resize( poSettings->width(), poSettings->height() );
    }

    _enableControls();
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
        nTimeMainMiliSec -= 10;
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
void MainWindow::_enableControls()
{
    ui->pbTeamHome->setEnabled( (nTimerMainPlayTime==0?true:false) );
    ui->pbRequestTimeHome->setEnabled( (nTimerMainPlayTime==0&&m_bGameInProgress?true:false) );
    ui->pbPlayerChangeHome->setEnabled( (nTimerMainPlayTime==0 &&
                                         nCountPlayerFieldHome>0 &&
                                         qvPanelPlayersHome.size()>nCountPlayerFieldHome ? true : false) );

    ui->pbTeamGuest->setEnabled( (nTimerMainPlayTime==0?true:false) );
    ui->pbRequestTimeGuest->setEnabled( (nTimerMainPlayTime==0&&m_bGameInProgress?true:false) );
    ui->pbPlayerChangeGuest->setEnabled( (nTimerMainPlayTime==0 &&
                                         nCountPlayerFieldGuest>0 &&
                                         qvPanelPlayersGuest.size()>nCountPlayerFieldGuest ? true : false) );

    ui->pbEditMainTime->setEnabled( (nTimerMainPlayTime>0?false:true) );

    ui->pnIncreaseQuarter->setEnabled( (nTimerMainPlayTime>0?false:true) );
    ui->pnDecreaseQuarter->setEnabled( (nTimerMainPlayTime>0?false:true) );

    ui->pbScore1Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );
    ui->pbScore2Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );
    ui->pbScore3Home->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );
    ui->pbFaultHome->setEnabled( ( nCountPlayerFieldHome>0?true:false ) );

    ui->pbScore1Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );
    ui->pbScore2Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );
    ui->pbScore3Guest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );
    ui->pbFaultGuest->setEnabled( ( nCountPlayerFieldGuest>0?true:false ) );

    ui->pbContinueMainTimer->setEnabled( ( nCountPlayerFieldHome==5&&nCountPlayerFieldGuest==5?true:false ) );

    ui->pbAttempt->setEnabled( poSettings->istimeoffenseused() );
    ui->pbHomePlay->setEnabled( poSettings->istimeoffenseused() );
    ui->pbGuestPlay->setEnabled( poSettings->istimeoffenseused() );

    ui->frmTimerPlayHome->setVisible( poSettings->istimeoffenseused() );
    ui->frmTimerPlayGuest->setVisible( poSettings->istimeoffenseused() );
}

//===========================================================================================================
void MainWindow::_updateMainPlayTime()
{
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
void MainWindow::_addPlayerManually(bool addHome, bool addMultiplePlayers)
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
                _addPlayers( addHome );
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
            _addPlayers( addHome );
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

            if( qsName.length() > 0 )
            {
                cPanelPlayer *poPlayer = new cPanelPlayer( this, qslPlayer.at(0), qsName );

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

            if( qsName.length() > 0 )
            {
                cPanelPlayer *poPlayer = new cPanelPlayer( this, qslPlayer.at(0), qsName );

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
    qaTitle.setFont( qfTitle );

    QAction qaImportPlayer( QIcon( ":/resources/folder.png" ), tr("Import players from file ..."), &qmMenu );
    QAction qaAddPlayer( QIcon( ":/resources/edit.png" ), tr("Add players manually ..."), &qmMenu );
    QAction qaSelectPlayers( QIcon( ":/resources/basketball_player_in.png" ), tr("Select players to field ..."), &qmMenu );
    QAction qaDeselectPlayers( QIcon( ":/resources/basketball_player_out.png" ), tr("Remove all players from field."), &qmMenu );

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
            if( bHome ) ui->lblTeamHome->setText( qsTeamNameFromFile );
            else        ui->lblTeamGuest->setText( qsTeamNameFromFile );

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
    qaTitle.setFont( qfTitle );

    QAction qaPlayerToField( QIcon( ":/resources/basketball_player_in.png" ),tr("Move player to field ..."), &qmMenu );
    qaPlayerToField.setEnabled( _isPlayerAllowedToField( poPlayerPanel, bHome ) );

    QAction qaPlayerToSubstitute( QIcon( ":/resources/basketball_player_out.png" ),tr("Move player to substitute ..."), &qmMenu );
    qaPlayerToSubstitute.setEnabled( poPlayerPanel->isPlayerOnField() );

    QAction qaPlayerEdit( QIcon( ":/resources/edit.png" ), tr("Edit player data ..."), &qmMenu );

    QAction qaPlayerDelete( QIcon( ":/resources/delete.png" ), tr("Delete player from team"), &qmMenu );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerEdit );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerToField );
    qmMenu.addAction( &qaPlayerToSubstitute );
    qmMenu.addSeparator();
    qmMenu.addAction( &qaPlayerDelete );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet == &qaPlayerEdit )
    {
        dlgPlayerEdit   obDlgPlayerEdit( this, poPlayerPanel->playerNumber(), poPlayerPanel->playerName() );

        if( obDlgPlayerEdit.exec() == QDialog::Accepted )
        {
            poPlayerPanel->setPlayerNumber( obDlgPlayerEdit.playerNumber() );
            poPlayerPanel->setPlayerName( obDlgPlayerEdit.playerName() );
            if( bHome ) _reorderPlayersHome();
            else        _reorderPlayersGuest();
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
void MainWindow::_processTeamNamePopupMenu(QLabel *poLblName)
{
    dlgEdit   obDlgEdit( this );

    obDlgEdit.setName( poLblName->text() );
    if( obDlgEdit.exec() == QDialog::Accepted )
    {
        poLblName->setText( obDlgEdit.name() );
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
                                       tr("Is the penalty succeeded?"),
                                       QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
            {
                _updateScore( pPlayer, 1, bHome );
            }
            else
            {
                _updateScore( pPlayer, 0, bHome );
            }
        }

    } while( pPlayer == NULL );
}

//===========================================================================================================
void MainWindow::_updateScore(cPanelPlayer *poPlayerPanel, int nScoreValue, bool bHome)
{
    if( bHome )
    {
        nScoreHome += nScoreValue;
        ui->ledPointsHome->setText( QString::number( nScoreHome ) );
        on_pbGuestPlay_clicked();
        poSettings->setScore( bHome, nScoreHome );
    }
    else
    {
        nScoreGuest += nScoreValue;
        ui->ledPointsGuest->setText( QString::number( nScoreGuest ) );
        on_pbHomePlay_clicked();
        poSettings->setScore( bHome, nScoreGuest );
    }
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
void MainWindow::on_pbRequestTimeHome_clicked()
{
    nTimeDeadSecond = 61;
    nTimerTimeDead = startTimer( 1000 );
    _showTrayInfo( tr( "Home team requested timeout!" ) );
    _enableControls();
}

//===========================================================================================================
void MainWindow::on_pbRequestTimeGuest_clicked()
{
    nTimeDeadSecond = 61;
    nTimerTimeDead = startTimer( 1000 );
    _showTrayInfo( tr( "Guest team requested timeout!" ) );
    _enableControls();
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

void MainWindow::on_pbEditTeamHome_clicked()
{
    _processTeamNamePopupMenu( ui->lblTeamHome );
    poSettings->setTeamName( true, ui->lblTeamHome->text() );
}

void MainWindow::on_pbEditTeamGuest_clicked()
{
    _processTeamNamePopupMenu( ui->lblTeamGuest );
    poSettings->setTeamName( true, ui->lblTeamGuest->text() );
}

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
            }
        }
    }
    _enableControls();
    _savePlayers( true );
}

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
            }
        }
    }
    _enableControls();
    _savePlayers( false );
}

void MainWindow::on_pbScore1Home_clicked()  {   _increaseTeamScoreFault( true );    }
void MainWindow::on_pbScore2Home_clicked()  {   _increaseTeamScore( 2, true );      }
void MainWindow::on_pbScore3Home_clicked()  {   _increaseTeamScore( 3, true );      }
void MainWindow::on_pbScore1Guest_clicked() {   _increaseTeamScoreFault( false  );  }
void MainWindow::on_pbScore2Guest_clicked() {   _increaseTeamScore( 2, false );     }
void MainWindow::on_pbScore3Guest_clicked() {   _increaseTeamScore( 3, false );     }

void MainWindow::on_pbFaultHome_clicked()
{
    _setPlayerFault( true );
}

void MainWindow::on_pbFaultGuest_clicked()
{
    _setPlayerFault( false );
}

void MainWindow::on_pbSettings_clicked()
{
    dlgSettings obDlgSettings( this, poSettings );

    if( obDlgSettings.exec() == QDialog::Accepted )
    {
        ui->retranslateUi( this );
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

void MainWindow::on_pbMinuteNew_clicked()
{
    m_bMinuteInProgress = true;

    _enableControls();
}

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
