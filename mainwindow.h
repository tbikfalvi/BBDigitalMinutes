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

class cSettings
{

public:
    cSettings();
    ~cSettings();

    // Application settings related
    QString          language()                                     { return m_qsLang;              }
    int              left()                                         { return m_nWindowLeft;         }
    int              top()                                          { return m_nWindowTop;          }
    int              width()                                        { return m_nWindowWidth;        }
    int              height()                                       { return m_nWindowHeight;       }
    int              timeQuarter()                                  { return m_nTimeQuarter;        }
    int              timeout()                                      { return m_nTimeTimeout;        }
    int              timeOffense()                                  { return m_nTimeOffense;        }
    int              timeOffenseExt()                               { return m_nTimeOffenseExt;     }

    void             setAppLang( QString lang )                     { m_qsLang          = lang;     }
    void             setWindowPosSize( int x, int y, int w, int h ) { m_nWindowLeft     = x;
                                                                      m_nWindowTop      = y;
                                                                      m_nWindowWidth    = w;
                                                                      m_nWindowHeight   = h;        }
    void             setTimeQuarter( int quarter )                  { m_nTimeQuarter    = quarter;  }
    void             setTimeout( int timeout )                      { m_nTimeTimeout    = timeout;  }
    void             setTimeOffense( int offense )                  { m_nTimeOffense    = offense;  }
    void             setTimeOffenseExt( int ext )                   { m_nTimeOffenseExt = ext;      }

    void             saveAppSettings();

    // Minute related
    bool             isMinuteClosed()                               { return m_bIsMinuteClosed;     }
    void             createMinute( QString p_qsMinuteName );
    void             loadMinute( QString p_qsFileName );
    void             saveMinute();
    void             closeMinute();

    void             saveHomeSettings();

    // Home team related
    QString          nameTeamHome()                                 { return m_qsNameTeamHome;      }

    void             setNameTeamHome( QString name )                { m_qsNameTeamHome  = name;     }

    // Guest team related

    void             saveGuestSettings();

private:

    // Application settings related
    QString          m_qsLang;
    int              m_nWindowLeft;
    int              m_nWindowTop;
    int              m_nWindowWidth;
    int              m_nWindowHeight;
    int              m_nTimeQuarter;
    int              m_nTimeTimeout;
    int              m_nTimeOffense;
    int              m_nTimeOffenseExt;

    // Minute related
    bool             m_bIsMinuteClosed;
    QString          qsMinuteFileName;

    // Home team related
    QString          m_qsNameTeamHome;

    // Guest team related
    QString          m_qsNameTeamGuest;

};

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
    void             increaseScore( int p_nScore );
    void             setPlayerFault();

    bool             isPlayerOnField()              {   return bPlayerOnField;              }
    bool             isEnabledToPlay()              {   return (nCountFaults<5?true:false); }

signals:
    void playerClicked( cPanelPlayer *poThis );
    void playerDisqualified();

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
    int              nScores;
    int              nCountSingle;
    int              nCountDouble;
    int              nCountTriple;
    int              nCountFaults;

    void             increaseSingle()               {   nCountSingle++;                     }
    void             increaseDouble()               {   nCountDouble++;                     }
    void             increaseTriple()               {   nCountTriple++;                     }
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
    void slotPlayerHomeDisqualified();
    void slotPlayerGuestDisqualified();

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
    void on_pbScore1Home_clicked();
    void on_pbScore2Home_clicked();
    void on_pbScore3Home_clicked();
    void on_pbScore1Guest_clicked();
    void on_pbScore2Guest_clicked();
    void on_pbScore3Guest_clicked();
    void on_pbFaultHome_clicked();
    void on_pbFaultGuest_clicked();
    void on_pbSettings_clicked();

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
    int                      nScoreHome;
    int                      nScoreGuest;

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
    void                    _increaseTeamScore( int nScoreValue, bool bHome = true );
    void                    _updateScore( cPanelPlayer *poPlayerPanel, int nScoreValue, bool bHome = true );
    void                    _setPlayerFault( bool bHome = true );
};

#endif // MAINWINDOW_H
