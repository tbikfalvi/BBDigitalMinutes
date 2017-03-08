#include "cplayerpanel.h"

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

