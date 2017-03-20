//===========================================================================================================
//===========================================================================================================

#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QTextStream>

//===========================================================================================================

#include "cminute.h"

//===========================================================================================================
cMinute::cMinute()
{
    m_obDoc          = new QDomDocument();
    m_bIsMinuteClosed   = false;
    qsMinuteFileName    = "";
    qsMinuteName        = "";
    qsMinuteFile        = "";
}

//===========================================================================================================
cMinute::~cMinute()
{

}

//===========================================================================================================
bool cMinute::createMinute( QString p_qsMinuteName, QString p_qsTeamHome, QString p_qsTeamGuest )
{
    qsMinuteName        = p_qsMinuteName;
    qsMinuteFileName    = QString( "%1_%2.dmin" ).arg( qsMinuteName ).arg( QDateTime::currentDateTime().toString( "yyyyMMddhhmm" ) );
    qsMinuteFile        = QString( "%1/%2" ).arg( QDir::currentPath() ).arg( qsMinuteFileName );

    QDomElement qdMinute        = m_obDoc->createElement( "Minute" );
    QDomElement qdMinuteHeader  = m_obDoc->createElement( "MinuteHeader" );
    QDomElement qdStart         = m_obDoc->createElement( "Start" );
    QDomElement qdTeamHome      = m_obDoc->createElement( "TeamHOME" );
    QDomElement qdTeamGuest     = m_obDoc->createElement( "TeamGUEST" );
    QDomElement qdMinuteActions = m_obDoc->createElement( "Actions" );
    QDomElement qdResults       = m_obDoc->createElement( "Results" );

    qdMinute.setAttribute( "Name", qsMinuteName );
    qdStart.setAttribute( "Date", QDate::currentDate().toString( "yyyy-MM-dd" ) );
    qdTeamHome.setAttribute( "Name", p_qsTeamHome );
    qdTeamGuest.setAttribute( "Name", p_qsTeamGuest );

    qdMinuteHeader.appendChild( qdStart );
    qdMinuteHeader.appendChild( qdTeamHome );
    qdMinuteHeader.appendChild( qdTeamGuest );

    for( int i=1; i<5; i++ )
    {
        QDomElement qdQuarter       = m_obDoc->createElement( "Result" );

        qdQuarter.setAttribute( "Quarter", i );
        qdQuarter.setAttribute( "ScoreHome", 0 );
        qdQuarter.setAttribute( "ScoreGuest", 0 );

        qdResults.appendChild( qdQuarter );
    }

    qdMinute.appendChild( qdMinuteHeader );
    qdMinute.appendChild( qdMinuteActions );
    qdMinute.appendChild( qdResults );
    m_obDoc->appendChild( qdMinute );

    return true;
}

//===========================================================================================================
void cMinute::loadMinute( QString /*p_qsFileName*/ )
{

}

//===========================================================================================================
void cMinute::saveMinute()
{
    QFile   file( qsMinuteFile );

    if( file.open(QFile::WriteOnly | QFile::Text) )
    {
        QTextStream stream( &file );
        stream << m_obDoc->toString();
        file.close();
    }
}

//===========================================================================================================
void cMinute::closeMinute()
{
    QDomElement qdMinute        = m_obDoc->documentElement();
    QDomElement qdResults       = qdMinute.elementsByTagName( "Results" ).at(0).toElement();
    QDomElement qdQuarter       = m_obDoc->createElement( "Result" );

    int nScoreHome  = 0;
    int nScoreGuest = 0;

    for( int i=0; i<qdResults.childNodes().count(); i++ )
    {
        QDomElement qdResult = qdResults.childNodes().at(i).toElement();

        nScoreHome  += qdResult.attribute( "ScoreHome" ).toInt();
        nScoreGuest += qdResult.attribute( "ScoreGuest" ).toInt();
    }

    qdQuarter.setAttribute( "Quarter", "Final" );
    qdQuarter.setAttribute( "ScoreHome", nScoreHome );
    qdQuarter.setAttribute( "ScoreGuest", nScoreGuest );

    qdResults.appendChild( qdQuarter );
}

//===========================================================================================================
void cMinute::addAction(int p_nTimeMilisec, cTeamType::teType p_teType, cMinActionType::teAction p_teAction, int p_nQuarter, QString p_qsParameters, int p_nScoreHome , int p_nScoreGuest )
{
    QDomElement qdMinute        = m_obDoc->documentElement();
    QDomElement qdMinuteAction  = qdMinute.elementsByTagName( "Actions" ).at(0).toElement();
    QDomElement qdAction        = m_obDoc->createElement( "Action" );
    QString     qsTimeStamp     = QString( "%1:%2:%3" ).arg( p_nTimeMilisec/60000, 2, 10, QChar( '0' ) )
                                                       .arg( (p_nTimeMilisec%60000)/1000, 2, 10, QChar( '0' ) )
                                                       .arg( ((p_nTimeMilisec%60000)%1000)/10, 2, 10, QChar( '0' ) );
    QString     qsTeamCode      = "";

    if( p_teType == cTeamType::HOME )   qsTeamCode = "H";
    else                                qsTeamCode = "G";

    qdAction.setAttribute( "Time", qsTimeStamp );
    qdAction.setAttribute( "Quarter", p_nQuarter );
    qdAction.setAttribute( "Code", QString( "%1%2" ).arg( qsTeamCode )
                                                    .arg( cMinActionType::toCode( p_teAction ) ) );
    qdAction.setAttribute( "Text", QString( cMinActionType::toStr( p_teAction ) ).arg( p_qsParameters ) );

    if( p_nScoreHome > -1 && p_nScoreGuest > -1 )
    {
        qdAction.setAttribute( "ScoreHome", QString::number( p_nScoreHome ) );
        qdAction.setAttribute( "ScoreGuest", QString::number( p_nScoreGuest ) );
    }

    qdMinuteAction.appendChild( qdAction );
}

//===========================================================================================================
void cMinute::updateTeam( cTeamType::teType p_teType, QString p_qsName )
{
    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdTeam      = qdMinute.elementsByTagName( qsTeam ).at(0).toElement();
    qdTeam.setAttribute( "Name", p_qsName );
}

//===========================================================================================================
void cMinute::addPlayer( cTeamType::teType p_teType, QStringList p_qslPlayer )
{
    if( p_qslPlayer.size() != 4 )   return;

    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdHeader    = qdMinute.elementsByTagName( "MinuteHeader" ).at(0).toElement();
    QDomElement qdTeam      = qdHeader.elementsByTagName( qsTeam ).at(0).toElement();
    QDomElement qdPlayer    = m_obDoc->createElement( "Player" );

    qdPlayer.setAttribute( "Id", p_qslPlayer.at(0) );
    qdPlayer.setAttribute( "Number", p_qslPlayer.at(1) );
    qdPlayer.setAttribute( "Name", p_qslPlayer.at(2) );
    qdPlayer.setAttribute( "Foul", p_qslPlayer.at(3) );

    qdTeam.appendChild( qdPlayer );
}

//===========================================================================================================
void cMinute::updatePlayer( cTeamType::teType p_teType, QStringList p_qslPlayer )
{
    if( p_qslPlayer.size() != 4 )   return;

    QString qsTeam;
    bool    bPlayerNotFound = true;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdHeader    = qdMinute.elementsByTagName( "MinuteHeader" ).at(0).toElement();
    QDomElement qdTeam      = qdHeader.elementsByTagName( qsTeam ).at(0).toElement();

    for( int i=0; i<qdTeam.childNodes().count(); i++ )
    {
        QDomElement qdPlayer = qdTeam.childNodes().at(i).toElement();

        if( qdPlayer.attribute( "Id" ).compare( p_qslPlayer.at(0) ) == 0 )
        {
            bPlayerNotFound = false;
            qdPlayer.setAttribute( "Number", p_qslPlayer.at(1) );
            qdPlayer.setAttribute( "Name", p_qslPlayer.at(2) );
            qdPlayer.setAttribute( "Foul", p_qslPlayer.at(3) );
            break;
        }
    }

    if( bPlayerNotFound )
    {
        addPlayer( p_teType, p_qslPlayer );
    }
}

//===========================================================================================================
void cMinute::deletePlayer(cTeamType::teType p_teType, QString p_qsPlayerId)
{
    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdHeader    = qdMinute.elementsByTagName( "MinuteHeader" ).at(0).toElement();
    QDomElement qdTeam      = qdHeader.elementsByTagName( qsTeam ).at(0).toElement();

    for( int i=0; i<qdTeam.childNodes().count(); i++ )
    {
        QDomElement qdPlayer = qdTeam.childNodes().at(i).toElement();

        if( qdPlayer.attribute( "Id" ).compare( p_qsPlayerId ) == 0 )
        {
            qdTeam.removeChild( qdPlayer );
            break;
        }
    }
}

//===========================================================================================================
void cMinute::updateScore(int p_nQuarter, int p_nScoreHome, int p_nScoreGuest)
{
    QDomElement qdMinute        = m_obDoc->documentElement();
    QDomElement qdResults       = qdMinute.elementsByTagName( "Results" ).at(0).toElement();

    for( int i=0; i<qdResults.childNodes().count(); i++ )
    {
        QDomElement qdResult = qdResults.childNodes().at(i).toElement();

        if( qdResult.attribute( "Quarter" ).toInt() == p_nQuarter )
        {
            qdResult.setAttribute( "ScoreHome", QString::number( p_nScoreHome ) );
            qdResult.setAttribute( "ScoreGuest", QString::number( p_nScoreGuest ) );
            break;
        }
    }
}

//===========================================================================================================
int cMinute::getQuarterScore( cTeamType::teType p_teType, int p_nQuarter )
{
    int     nRet = 0;
    QString qsAttribute;

    if( p_teType == cTeamType::HOME )   qsAttribute = "ScoreHome";
    else                                qsAttribute = "ScoreGuest";

    QDomElement qdMinute        = m_obDoc->documentElement();
    QDomElement qdResults       = qdMinute.elementsByTagName( "Results" ).at(0).toElement();

    for( int i=0; i<qdResults.childNodes().count(); i++ )
    {
        QDomElement qdResult = qdResults.childNodes().at(i).toElement();

        if( qdResult.attribute( "Quarter" ).toInt() == p_nQuarter )
        {
            nRet = qdResult.attribute( qsAttribute ).toInt();
            break;
        }
    }
    return nRet;
}

