#ifndef CMINUTE_H
#define CMINUTE_H

#include <QDomDocument>
#include <QObject>
#include <QString>

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Minute action types class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

class cMinActionType
{
public:
    enum teAction
    {
        MAT_DEFAULT = 0,
        MAT_PLAYER_SCORE_1,
        MAT_PLAYER_SCORE_2,
        MAT_PLAYER_SCORE_3,
        MAT_PLAYER_SCORE_1_FAILED,
        MAT_PLAYER_SCORE_2_FAILED,
        MAT_PLAYER_SCORE_3_FAILED,
        MAT_PLAYER_FAULT_GAME,
        MAT_PLAYER_FAULT_TECHNICAL,
        MAT_PLAYER_FAULT_SUBSTITUTE,
        MAT_PLAYER_SUBSTITUTE,
        MAT_TEAM_TIMEOUT,
        MAT_TEAM_FAULT,
        MAT_GAME_OVERTIME,
        MAT_CUSTOM
    };

    static const char *toStr( teAction p_teAction )
    {
        switch( p_teAction )
        {
            case MAT_DEFAULT:                       return QObject::tr( "%1" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_1:                return QObject::tr( "%1 scored penalty" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_2:                return QObject::tr( "%1 scored short distant (2 points) throw" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_3:                return QObject::tr( "%1 scored long distant (3 points) throw" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_1_FAILED:         return QObject::tr( "%1 failed penalty" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_2_FAILED:         return QObject::tr( "%1 failed short distant (2 points) throw" ).toStdString().c_str(); break;
            case MAT_PLAYER_SCORE_3_FAILED:         return QObject::tr( "%1 failed long distant (3 points) throw" ).toStdString().c_str(); break;
            case MAT_PLAYER_FAULT_GAME:             return QObject::tr( "%1 committed foul" ).toStdString().c_str(); break;
            case MAT_PLAYER_FAULT_TECHNICAL:        return QObject::tr( "%1 punished technical foul" ).toStdString().c_str(); break;
            case MAT_PLAYER_FAULT_SUBSTITUTE:       return QObject::tr( "%1 substituted due to max. fouls" ).toStdString().c_str(); break;
            case MAT_PLAYER_SUBSTITUTE:             return QObject::tr( "Substitution: %1" ).toStdString().c_str(); break;
            case MAT_TEAM_TIMEOUT:                  return QObject::tr( "%1 requested timeout" ).toStdString().c_str(); break;
            case MAT_TEAM_FAULT:                    return QObject::tr( "Team punished foul - %1" ).toStdString().c_str(); break;
            case MAT_GAME_OVERTIME:                 return QObject::tr( "Overtime started" ).toStdString().c_str(); break;
            case MAT_CUSTOM:                        return QObject::tr( "%1" ).toStdString().c_str(); break;
            default:                                return QObject::tr( "Unknonw action" ).toStdString().c_str(); break;
        }
    }

    static const char *toCode( teAction p_teAction )
    {
        switch( p_teAction )
        {
            case MAT_DEFAULT:                       return "---"; break;
            case MAT_PLAYER_SCORE_1:                return "S1S"; break;
            case MAT_PLAYER_SCORE_2:                return "S2S"; break;
            case MAT_PLAYER_SCORE_3:                return "S3S"; break;
            case MAT_PLAYER_SCORE_1_FAILED:         return "S1F"; break;
            case MAT_PLAYER_SCORE_2_FAILED:         return "S2F"; break;
            case MAT_PLAYER_SCORE_3_FAILED:         return "S3F"; break;
            case MAT_PLAYER_FAULT_GAME:             return "FPG"; break;
            case MAT_PLAYER_FAULT_TECHNICAL:        return "FPT"; break;
            case MAT_PLAYER_FAULT_SUBSTITUTE:       return "FPS"; break;
            case MAT_PLAYER_SUBSTITUTE:             return "SUP"; break;
            case MAT_TEAM_TIMEOUT:                  return "TTO"; break;
            case MAT_TEAM_FAULT:                    return "TTF"; break;
            case MAT_GAME_OVERTIME:                 return "GOT"; break;
            case MAT_CUSTOM:                        return "CUS"; break;
            default:                                return "---"; break;
        }
    }

};

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Team types class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

class cTeamType
{
public:
    enum teType
    {
        HOME = 0,
        GUEST
    };
};

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Minute class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

class cMinute
{
public:
    cMinute();
    ~cMinute();

    QString          minuteName()                               { return qsMinuteName;          }
    bool             isMinuteClosed()                           { return m_bIsMinuteClosed;     }
    bool             createMinute(QString p_qsMinuteName,
                                  QString p_qsTeamHome,
                                  QString p_qsTeamGuest);
    void             loadMinute( QString p_qsFileName );
    void             saveMinute();
    void             closeMinute();

    void             addAction( int p_nTimeMilisec, cTeamType::teType p_teType, cMinActionType::teAction p_teAction, QString p_qsParameters = NULL );
    void             updateTeam( cTeamType::teType p_teType, QString p_qsName );
    void             addPlayer( cTeamType::teType p_teType, QStringList p_qslPlayer );
    void             updatePlayer( cTeamType::teType p_teType, QStringList p_qslPlayer );

private:

    QDomDocument    *m_obDoc;
    bool             m_bIsMinuteClosed;
    QString          qsMinuteFileName;
    QString          qsMinuteName;
    QString          qsMinuteFile;

};

#endif // CMINUTE_H
