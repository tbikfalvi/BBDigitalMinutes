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

//===========================================================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgplayeredit.h"
#include "dlgedit.h"


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

    nTimerMainPlayTime      = 0;
    nTimeMainMiliSec        = 600000;

    nTimerTimeDead          = 0;
    nTimeDeadSecond         = 61;

    bTeamHomePlay           = false;
    bTeamGuestPlay          = false;
    nTimerTeamPlayTime      = 0;
    nTimeTeamPlaySecond     = 24;

    nCountPlayerFieldHome   = 0;
    nCountPlayerFieldGuest  = 0;

    bSubstituteInProgress   = false;

    pSoundWhistle = new QSound( QString( "%1/referee_whistle.wav" ).arg( QDir::currentPath() ) );

    _updateMainPlayTime();
}

//===========================================================================================================
MainWindow::~MainWindow()
{
    m_stIcon->hide();

    delete ui;
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
        nTimeTeamPlaySecond --;
        if( bTeamHomePlay )         _updateTeamHomePlayTime();
        else if( bTeamGuestPlay )   _updateTeamGuestPlayTime();
    }
}

//===========================================================================================================
void MainWindow::slotPlayerPanelHomeClicked( cPanelPlayer *poPlayerPanel )
{
    _processPlayerPopupMenu( poPlayerPanel, true );
}

//===========================================================================================================
void MainWindow::slotPlayerPanelGuestClicked( cPanelPlayer *poPlayerPanel )
{
    _processPlayerPopupMenu( poPlayerPanel, false );
}

//===========================================================================================================
void MainWindow::_updateMainPlayTime()
{
    ui->ledTimeMainMinute->setText( QString( "%1" ).arg( nTimeMainMiliSec/60000, 2, 10, QChar( '0' ) ) );
    ui->ledTimeMainSecond->setText( QString( "%1" ).arg( (nTimeMainMiliSec%60000)/1000, 2, 10, QChar( '0' ) ) );
    ui->ledTimeMainMiliSecond->setText( QString( "%1" ).arg( ((nTimeMainMiliSec%60000)%1000)/10, 2, 10, QChar( '0' ) ) );
}

//===========================================================================================================
void MainWindow::_updateTeamHomePlayTime()
{
    ui->ledTimerPlayHome->setText( QString( "%1" ).arg( nTimeTeamPlaySecond, 2, 10, QChar( '0' ) ) );
    ui->ledTimerPlayGuest->setText( "00" );
    if( nTimeTeamPlaySecond < 1 )
    {
        _showTrayWarning( tr( "The play time has expired!" ) );
        on_pbSignalReferee_clicked();
        on_pbGuestPlay_clicked();
    }
}

//===========================================================================================================
void MainWindow::_updateTeamGuestPlayTime()
{
    ui->ledTimerPlayHome->setText( "00" );
    ui->ledTimerPlayGuest->setText( QString( "%1" ).arg( nTimeTeamPlaySecond, 2, 10, QChar( '0' ) ) );
    if( nTimeTeamPlaySecond < 1 )
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

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();
    qmMenu.addAction( QIcon( ":/resources/folder.png" ), tr("Import players from file ...") );
    qmMenu.addAction( QIcon( ":/resources/edit.png" ), tr("Add players manually ...") );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet )
    {
        if( qaRet->text().compare( tr("Import players from file ...") ) == 0 )
        {
            qslImportedPlayers = QStringList("");
            qsTeamNameFromFile = "";
            _importPlayersFromFile();
            _addPlayers( bHome );
            if( qsTeamNameFromFile.length() > 0 )
            {
                if( bHome ) ui->lblTeamHome->setText( qsTeamNameFromFile );
                else        ui->lblTeamGuest->setText( qsTeamNameFromFile );
            }
        }
        else if( qaRet->text().compare( tr("Add players manually ...") ) == 0 )
        {
            _addPlayerManually( bHome, true );
        }
    }
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

    QAction qaTitle( tr("Select player to substitute ..."), &qmMenu );
    QFont   qfTitle;
    qfTitle.setBold( true );
    qaTitle.setFont( qfTitle );

    qmMenu.addAction( &qaTitle );
    qmMenu.addSeparator();

    for( int i=0; i<qlPlayers->size(); i++ )
    {
        if( !qlPlayers->at(i)->isPlayerOnField() )
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
// GUI control management procedures
//===========================================================================================================

//===========================================================================================================
void MainWindow::on_pbContinueMainTimer_clicked()
{
    nTimerMainPlayTime = startTimer( 10 );
    nTimerTeamPlayTime = startTimer( 1000 );
    _resetDeadTime();
    _showTrayInfo( tr( "Play continued, timer is live!" ) );
}

//===========================================================================================================
void MainWindow::on_pbSignalReferee_clicked()
{
    killTimer( nTimerMainPlayTime );
    killTimer( nTimerTeamPlayTime );
    nTimerMainPlayTime = 0;
    nTimerTeamPlayTime = 0;
    pSoundWhistle->play();
    _showTrayInfo( tr( "Play halted, timer stopped!" ) );
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
}

//===========================================================================================================
void MainWindow::on_pbRequestTimeHome_clicked()
{
    nTimeDeadSecond = 61;
    nTimerTimeDead = startTimer( 1000 );
    _showTrayInfo( tr( "Home team requested timeout!" ) );
}

//===========================================================================================================
void MainWindow::on_pbRequestTimeGuest_clicked()
{
    nTimeDeadSecond = 61;
    nTimerTimeDead = startTimer( 1000 );
    _showTrayInfo( tr( "Guest team requested timeout!" ) );
}

//===========================================================================================================
void MainWindow::on_pbHomePlay_clicked()
{
    if( !bTeamHomePlay )
    {
        ui->pbHomePlay->setIcon( QIcon(":/resources/basketball.png") );
        ui->pbGuestPlay->setIcon( QIcon(":/resources/basketball_inactive.png") );
        bTeamHomePlay = true;
        bTeamGuestPlay = false;
        nTimeTeamPlaySecond = 24;
        if( nTimerMainPlayTime > 0 && nTimerTeamPlayTime == 0 ) nTimerTeamPlayTime = startTimer( 1000 );
        _updateTeamHomePlayTime();
    }
}

//===========================================================================================================
void MainWindow::on_pbGuestPlay_clicked()
{
    if( !bTeamGuestPlay )
    {
        ui->pbHomePlay->setIcon( QIcon(":/resources/basketball_inactive.png") );
        ui->pbGuestPlay->setIcon( QIcon(":/resources/basketball.png") );
        bTeamHomePlay = false;
        bTeamGuestPlay = true;
        nTimeTeamPlaySecond = 24;
        if( nTimerMainPlayTime > 0 && nTimerTeamPlayTime == 0 ) nTimerTeamPlayTime = startTimer( 1000 );
        _updateTeamGuestPlayTime();
    }
}

//===========================================================================================================
void MainWindow::on_pnIncreaseQuarter_clicked()
{
    if( ui->ledCountQuarter->text().toInt() < 4 )
    {
        if( QMessageBox::question( this, tr("Question"),
                                   tr( "Are you sure to jump to the next quarter?\n"
                                       "The minutes will be updated with the closure of the quarter."),
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            ui->ledCountQuarter->setText( QString::number( ui->ledCountQuarter->text().toInt()+1 ) );
        }
    }
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
}

void MainWindow::on_pbEditTeamGuest_clicked()
{
    _processTeamNamePopupMenu( ui->lblTeamGuest );
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
}
