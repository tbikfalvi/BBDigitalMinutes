#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStringList>
#include <QSound>

#include "csettings.h"
#include "cplayerpanel.h"
#include "cminute.h"

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Main window class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent( QTimerEvent *p_poEvent );
    void resizeEvent(QResizeEvent *event);

private slots:
    void slotPlayerPanelHomeClicked( cPanelPlayer *poPlayerPanel );
    void slotPlayerPanelGuestClicked( cPanelPlayer *poPlayerPanel );
    void slotPlayerHomeDisqualified();
    void slotPlayerGuestDisqualified();

    void on_pbContinueMainTimer_clicked();
    void on_pbSignalReferee_clicked();
    void on_pbEditMainTime_clicked();
    void on_pbSaveMainTime_clicked();
    void on_pbCancelSaveMainTime_clicked();
    void on_pbRequestTime_clicked();
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
/*    void on_pbScore1Home_clicked();
    void on_pbScore2Home_clicked();
    void on_pbScore3Home_clicked();
    void on_pbScore1Guest_clicked();
    void on_pbScore2Guest_clicked();
    void on_pbScore3Guest_clicked();*/
    void on_pbFaultHome_clicked();
    void on_pbFaultGuest_clicked();
    void on_pbSettings_clicked();
    void on_pbMinuteNew_clicked();
    void on_pbAttempt_clicked();
    void on_pbCloseMinute_clicked();

    void on_pbMinuteSave_clicked();

    void on_pbReset_clicked();

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
    cSettings               *poSettings;
    cMinute                 *poMinute;

    QString                  qsTeamNameFromFile;
    int                      nTimerMainPlayTime;
    int                      nTimeMainMiliSec;
    int                      nTimeMinuteMiliSec;
    int                      nTimerTimeDead;
    int                      nTimeDeadSecond;
    bool                     bTeamHomePlay;
    bool                     bTeamGuestPlay;
    int                      nTimerTeamPlayTime;
    int                      nTimeOffense;
    int                      nCountPlayerFieldHome;
    int                      nCountPlayerFieldGuest;
    bool                     bSubstituteInProgress;
    int                      nScoreHome;
    int                      nScoreGuest;
    bool                     m_bMinuteInProgress;
    bool                     m_bSelectPlayersToField;
    bool                     m_bGameInProgress;
    int                      m_nMinuteRowCount;
    int                      m_nTimerAutoSaveMinute;
    int                      m_nPlayerId;
    int                      m_nQuarterScoreHome;
    int                      m_nQuarterScoreGuest;

    void                    _enableControls();
    void                    _updateMainPlayTime();
    void                    _updateTeamHomeOffenseTime();
    void                    _updateTeamGuestOffenseTime();
    void                    _updateDeadTime();
    void                    _resetDeadTime();
    void                    _showTrayInfo( QString p_qsMessage );
    void                    _showTrayWarning( QString p_qsMessage );
    void                    _showTrayError( QString p_qsMessage );
    void                    _importPlayersFromFile();
    void                    _addPlayerManually(bool bHome = true, bool addMultiplePlayers = false );
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
    void                    _processTeamNamePopupMenu( bool bHome = true );
    bool                    _isPlayerAllowedToField( cPanelPlayer *poPlayerPanel, bool bHome = true );
    void                    _selectPlayerFromField( bool bHome = true );
    void                    _selectPlayerFromSubstitute( bool bHome = true );
    void                    _increaseTeamScore( int nScoreValue, bool bHome = true );
    void                    _increaseTeamScoreFault( bool bHome = true );
    void                    _updateScore( cPanelPlayer *poPlayerPanel, int nScoreValue, bool bHome = true );
    void                    _setPlayerFault( bool bHome = true );
    void                    _savePlayers( bool bHome = true );
    void                    _addMinuteAction( cMinActionType::teAction p_teAction, QString p_qsParameter = "", bool bHome = true );
    void                    _updateTeamName( bool bHome = true, QString p_qsName = "" );
    bool                    _isPlayerNumberAssigned(  bool bHome, int p_nNumber );

};

#endif // MAINWINDOW_H
