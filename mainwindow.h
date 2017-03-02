#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QStringList>
#include <QMouseEvent>
#include <QSound>

class cPanelPlayer : public QFrame
{
    Q_OBJECT

public:
    QHBoxLayout     *hlPlayer;
    QFrame          *frmPlayerNumber;
    QLabel          *lblPlayerNumber;
    QHBoxLayout     *hlPlayerName;
    QFrame          *frmPlayerName;
    QLabel          *lblPlayerName;
    QHBoxLayout     *hlFault;
    QFrame          *frmFault;
    QLabel          *lblPlayerFault1;
    QLabel          *lblPlayerFault2;
    QLabel          *lblPlayerFault3;
    QLabel          *lblPlayerFault4;
    QLabel          *lblPlayerFault5;

    cPanelPlayer( QWidget *p_poParent = 0, QString p_qsPlayerNumber = "", QString p_qsPlayerName = "" );
    ~cPanelPlayer();

    int              playerNumber();
    QString          playerName();
    QString          playerWithNumber( QString p_qsSeparator = "\t" );
    void             setPlayerNumber( int p_nPlayerNumber );
    void             setPlayerName( QString p_qsPlayerName );
    void             setPlayerToField();
    void             setPlayerToSubstitute();
    void             removePlayer();

    bool             isPlayerOnField()                          {   return bPlayerOnField;              }

signals:
    void playerClicked( cPanelPlayer *poThis );

protected:
    void mousePressEvent ( QMouseEvent *p_poEvent );

private:
    QString          qsFrmPlayerNumber;
    QString          qsLblPlayerNumber;
    QString          qsFrmPlayerName;
    QString          qsLblPlayerName;

    int              nPlayerNumber;
    QString          qsPlayerName;
    bool             bPlayerOnField;

};

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent( QTimerEvent *p_poEvent );

private slots:
    void slotPlayerPanelHomeClicked( cPanelPlayer *poPlayerPanel );
    void slotPlayerPanelGuestClicked( cPanelPlayer *poPlayerPanel );

    void on_pbContinueMainTimer_clicked();
    void on_pbSignalReferee_clicked();
    void on_pbEditMainTime_clicked();
    void on_pbSaveMainTime_clicked();
    void on_pbCancelSaveMainTime_clicked();
    void on_pbRequestTimeHome_clicked();
    void on_pbRequestTimeGuest_clicked();
    void on_pbHomePlay_clicked();
    void on_pbGuestPlay_clicked();
    void on_pnIncreaseQuarter_clicked();
    void on_pnDecreaseQuarter_clicked();
    void on_pbTeamHome_clicked();
    void on_pbTeamGuest_clicked();
    void on_pbEditTeamHome_clicked();
    void on_pbEditTeamGuest_clicked();
    void on_pbPlayerChangeHome_clicked();
    void on_pbPlayerChangeGuest_clicked();

private:

    Ui::MainWindow          *ui;
    QSystemTrayIcon         *m_stIcon;
    QList<cPanelPlayer*>     qvPanelPlayersHome;
    QList<cPanelPlayer*>     qvPanelPlayersGuest;
    QStringList              qslImportedPlayers;
    QSound                  *pSoundWhistle;
    cPanelPlayer            *pPlayerToSubstitute;
    cPanelPlayer            *pPlayerToField;
    QPoint                   posMenu;

    QString                  qsTeamNameFromFile;
    int                      nTimerMainPlayTime;
    int                      nTimeMainMiliSec;
    int                      nTimerTimeDead;
    int                      nTimeDeadSecond;
    bool                     bTeamHomePlay;
    bool                     bTeamGuestPlay;
    int                      nTimerTeamPlayTime;
    int                      nTimeTeamPlaySecond;
    int                      nCountPlayerFieldHome;
    int                      nCountPlayerFieldGuest;
    bool                     bSubstituteInProgress;

    void                    _updateMainPlayTime();
    void                    _updateTeamHomePlayTime();
    void                    _updateTeamGuestPlayTime();
    void                    _updateDeadTime();
    void                    _resetDeadTime();
    void                    _showTrayInfo( QString p_qsMessage );
    void                    _showTrayWarning( QString p_qsMessage );
    void                    _showTrayError( QString p_qsMessage );
    void                    _importPlayersFromFile();
    void                    _addPlayerManually( bool addHome = true, bool addMultiplePlayers = false );
    void                    _addPlayers( bool addHome = true );
    void                    _addPlayersToHome();
    void                    _addPlayersToGuest();
    void                    _processTeamPopupMenu(bool bHome = true );
    void                    _processPlayerPopupMenu( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _reorderPlayersHome();
    void                    _reorderPlayersGuest();
    void                    _deletePlayer( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _setPlayerToField( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _setPlayerToSubstitute( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _processTeamNamePopupMenu( QLabel *poLblName );
    bool                    _isPlayerAllowedToField( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _selectPlayerFromField( bool bHome = true );
    void                    _selectPlayerFromSubstitute( bool bHome = true );
};

#endif // MAINWINDOW_H
