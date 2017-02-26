#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QSystemTrayIcon>

class cPanelPlayer : public QFrame
{
    Q_OBJECT

public:
    QHBoxLayout     *hlPlayer;
    QHBoxLayout     *hlPlayerNumber;
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

private:

    Ui::MainWindow          *ui;
    QSystemTrayIcon         *m_stIcon;
    QVector<cPanelPlayer*>   qvPanelPlayersHome;
    QVector<cPanelPlayer*>   qvPanelPlayersGuest;

    int                      nTimerMainPlayTime;
    int                      nTimeMainMiliSec;
    int                      nTimerTimeDead;
    int                      nTimeDeadSecond;
    bool                     bTeamHomePlay;
    bool                     bTeamGuestPlay;
    int                      nTimerTeamPlayTime;
    int                      nTimeTeamPlaySecond;

    void                    _updateMainPlayTime();
    void                    _updateTeamHomePlayTime();
    void                    _updateTeamGuestPlayTime();
    void                    _updateDeadTime();
    void                    _resetDeadTime();
    void                    _showTrayInfo( QString p_qsMessage );
    void                    _showTrayWarning( QString p_qsMessage );
    void                    _showTrayError( QString p_qsMessage );
    void                    _importPlayersFromFile();
};

#endif // MAINWINDOW_H
