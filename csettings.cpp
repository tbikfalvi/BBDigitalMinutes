
#include <QDir>

#include "csettings.h"

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
//    m_bIsMinuteClosed       = qsetApplication.value( "MinuteClosed",            "false" ).toBool();
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
//    qsetApplication.setValue( "MinuteClosed",           m_bIsMinuteClosed       );
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

