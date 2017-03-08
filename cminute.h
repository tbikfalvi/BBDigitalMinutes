#ifndef CMINUTE_H
#define CMINUTE_H

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
        MAT_PLAYER_FAULT_GAME,
        MAT_PLAYER_FAULT_TECHNICAL,
        MAT_PLAYER_FAULT_SUBSTITUTE,
        MAT_PLAYER_SUBSTITUTE,
        MAT_TEAM_TIMEOUT,
        MAT_TEAM_FAULT,
        MAT_GAME_OVERTIME,
        MAT_CUSTOM
    };

    QString toStr( teAction p_teAction )
    {
        switch( p_teAction )
        {
            case MAT_DEFAULT:                       return QObject::tr( "%1" ); break;
            case MAT_PLAYER_SCORE_1:                return QObject::tr( "Player '%1' (%2) scored penalty" ); break;
            case MAT_PLAYER_SCORE_2:                return QObject::tr( "Player '%1' (%2) scored short distant throw (2 points)" ); break;
            case MAT_PLAYER_SCORE_3:                return QObject::tr( "Player '%1' (%2) scored long distant throw (3 points)" ); break;
            case MAT_PLAYER_FAULT_GAME:             return QObject::tr( "Player '%1' (%2) committed foul" ); break;
            case MAT_PLAYER_FAULT_TECHNICAL:        return QObject::tr( "Player '%1' (%2) punished technical foul" ); break;
            case MAT_PLAYER_FAULT_SUBSTITUTE:       return QObject::tr( "Player '%1' (%2) substituted due to max. fouls" ); break;
            case MAT_PLAYER_SUBSTITUTE:             return QObject::tr( "Player substitution: '%1' (%2) <->  '%3' (%4)" ); break;
            case MAT_TEAM_TIMEOUT:                  return QObject::tr( "Team requested timeout" ); break;
            case MAT_TEAM_FAULT:                    return QObject::tr( "Team punished fault - %1" ); break;
            case MAT_GAME_OVERTIME:                 return QObject::tr( "Overtime started" ); break;
            case MAT_CUSTOM:                        return QObject::tr( "%1" ); break;
            default:                                return QObject::tr( "Unknonw action" ); break;
        }
    }
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

    bool             isMinuteClosed()                               { return m_bIsMinuteClosed;     }
    bool             createMinute(QString p_qsMinuteName,
                                  QString p_qsTeamHome,
                                  QString p_qsTeamGuest);
    void             loadMinute( QString p_qsFileName );
    void             saveMinute();
    void             closeMinute();

    void             addAction( cMinActionType::teAction p_teAction, QString p_qsParameters = NULL );

private:

    bool             m_bIsMinuteClosed;
    QString          qsMinuteFileName;
    QString          qsMinuteName;
    QString          qsMinuteFile;

};

#endif // CMINUTE_H
