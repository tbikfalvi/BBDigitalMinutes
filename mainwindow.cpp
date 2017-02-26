//===========================================================================================================
//
//===========================================================================================================

#include <QMessageBox>
#include <QTimer>
#include <QMenu>
#include <QFileDialog>

//===========================================================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Player panel class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

//===========================================================================================================
cPanelPlayer::cPanelPlayer(QWidget *p_poParent, QString p_qsPlayerNumber, QString p_qsPlayerName)
{
    setParent( p_poParent );

    QFont   qfPlayer;

    qfPlayer.setPointSize( 10 );
    qfPlayer.setBold( true );

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
    lblPlayerNumber->setText( QString( "%1" ).arg( p_qsPlayerNumber.toInt(), 2, 10, QChar( '0' ) ) );

/*    hlPlayerNumber = new QHBoxLayout( frmPlayerNumber );
    hlPlayerNumber->setObjectName( QString::fromUtf8( "hlPlayerNumber" ) );
    hlPlayerNumber->setSpacing( 1 );
    hlPlayerNumber->setMargin( 1 );*/
//    hlPlayerNumber->addWidget( lblPlayerNumber );

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
    lblPlayerName->setText( p_qsPlayerName );

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
}



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

        if( !qbaLine.startsWith('#') )
        {
            qslImportedPlayers << QString( qbaLine );
        }
    }
    qfPlayers.close();
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

                ui->vlPlayersHome->insertWidget( qvPanelPlayersHome.size(), poPlayer );
                qvPanelPlayersHome.append( poPlayer );
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

                ui->vlPlayersGuest->insertWidget( qvPanelPlayersGuest.size(), poPlayer );
                qvPanelPlayersGuest.append( poPlayer );
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
    QMenu   qmMenu;

    qmMenu.addAction( QIcon( ":/resources/folder.png" ), tr("Import players from file ...") );
    qmMenu.addAction( QIcon( ":/resources/edit.png" ), tr("Add players manually ...") );
    qmMenu.addAction( QIcon( ":/resources/database.png" ), tr("Load players from database ...") );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet )
    {
        if( qaRet->text().compare( tr("Import players from file ...") ) == 0 )
        {
            qslImportedPlayers = QStringList("");
            _importPlayersFromFile();
            _addPlayersToHome();
        }
        else if( qaRet->text().compare( tr("Add players manually ...") ) == 0 )
        {
        }
        else if( qaRet->text().compare( tr("Load players from database ...") ) == 0 )
        {
        }
    }
}

void MainWindow::on_pbTeamGuest_clicked()
{
    QMenu   qmMenu;

    qmMenu.addAction( QIcon( ":/resources/folder.png" ), tr("Import players from file ...") );
    qmMenu.addAction( QIcon( ":/resources/edit.png" ), tr("Add players manually ...") );
    qmMenu.addAction( QIcon( ":/resources/database.png" ), tr("Load players from database ...") );

    QAction *qaRet = qmMenu.exec( QCursor::pos() );

    if( qaRet )
    {
        if( qaRet->text().compare( tr("Import players from file ...") ) == 0 )
        {
            qslImportedPlayers = QStringList("");
            _importPlayersFromFile();
            _addPlayersToGuest();
        }
        else if( qaRet->text().compare( tr("Add players manually ...") ) == 0 )
        {
        }
        else if( qaRet->text().compare( tr("Load players from database ...") ) == 0 )
        {
        }
    }
}
