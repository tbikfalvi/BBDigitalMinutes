#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QStringList>
#include <QSettings>

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Settings class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

class cSettings
{

public:
    cSettings();
    ~cSettings();

    // Application settings related
    QString          language()                                     { return m_qsLang;                  }
    bool             isreloadsizepos()                              { return m_bReloadSizePos;          }
    bool             isreloadminute()                               { return m_bReloadMinute;           }
    bool             issoundenabled()                               { return m_bSoundEnabled;           }
    int              left()                                         { return m_nWindowLeft;             }
    int              top()                                          { return m_nWindowTop;              }
    int              width()                                        { return m_nWindowWidth;            }
    int              height()                                       { return m_nWindowHeight;           }
    int              countquarters()                                { return m_nCountQuarters;          }
    int              timeQuarter()                                  { return m_nTimeQuarter;            }
    bool             isovertimeenabled()                            { return m_bOvertimeEnabled;        }
    int              timeovertime()                                 { return m_nTimeOvertime;           }
    int              timeout()                                      { return m_nTimeTimeout;            }
    bool             istimeoffenseused()                            { return m_bTimeOffenseUsed;        }
    int              timeOffense()                                  { return m_nTimeOffense;            }
    int              timeOffenseExt()                               { return m_nTimeOffenseExt;         }

    void             setAppLang( QString lang )                     { m_qsLang              = lang;     }
    void             setReloadSizePos( bool reload )                { m_bReloadSizePos      = reload;   }
    void             setReloadMinute( bool reload )                 { m_bReloadMinute       = reload;   }
    void             setSoundEnabled( bool enabled )                { m_bSoundEnabled       = enabled;  }
    void             setWindowPosSize( int x, int y, int w, int h ) { m_nWindowLeft         = x;
                                                                      m_nWindowTop          = y;
                                                                      m_nWindowWidth        = w;
                                                                      m_nWindowHeight       = h;        }
    void             setCountQuarters( int count )                  { m_nCountQuarters      = count;    }
    void             setTimeQuarter( int quarter )                  { m_nTimeQuarter        = quarter;  }
    void             setOvertimeEnabled( bool enabled )             { m_bOvertimeEnabled    = enabled;  }
    void             setTimeOvertime( int time )                    { m_nTimeOvertime       = time;     }
    void             setTimeout( int timeout )                      { m_nTimeTimeout        = timeout;  }
    void             setTimeOffenseUsed( bool enabled )             { m_bTimeOffenseUsed    = enabled;  }
    void             setTimeOffense( int offense )                  { m_nTimeOffense        = offense;  }
    void             setTimeOffenseExt( int ext )                   { m_nTimeOffenseExt     = ext;      }

    void             saveAppSettings();

    // Team related
    QSettings       *pQSetTeamHome;
    QSettings       *pQSetTeamGuest;
    QSettings       *pQSetGameStatus;

    QString          teamName( bool bHome = true );
    QStringList      players( bool bHome = true );
    QStringList      playersField( bool bHome = true );
    int              score( bool bHome = true );
    int              quarter();
    QString          minuteFileName();

    void             setTeamName( bool bHome = true, QString name = "" );                           //
    void             setPlayers( bool bHome = true, QStringList players = QStringList("") );        //
    void             setPlayersField( bool bHome = true, QStringList players = QStringList("") );   //
    void             setScore(bool bHome = true , int score = 0 );                                  //
    void             setQuarter( int quarter = 1 );                                                 //
    void             setMinuteFileName( QString filename );

private:

    // Application settings related
    QString          m_qsLang;
    bool             m_bReloadSizePos;
    bool             m_bReloadMinute;
    bool             m_bSoundEnabled;
    int              m_nWindowLeft;
    int              m_nWindowTop;
    int              m_nWindowWidth;
    int              m_nWindowHeight;
    int              m_nCountQuarters;
    int              m_nTimeQuarter;
    bool             m_bOvertimeEnabled;
    int              m_nTimeOvertime;
    int              m_nTimeTimeout;
    int              m_bTimeOffenseUsed;
    int              m_nTimeOffense;
    int              m_nTimeOffenseExt;

    // Home team related
    QString          m_qsNameTeamHome;
    int              m_nCountPlayersHome;
    QStringList      m_qslPlayersHome;

    // Guest team related
    QString          m_qsNameTeamGuest;

};

#endif // CSETTINGS_H
