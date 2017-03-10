
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QTextStream>

#include "cminute.h"

cMinute::cMinute()
{
    m_obDoc          = new QDomDocument();
    m_bIsMinuteClosed   = false;
    qsMinuteFileName    = "";
    qsMinuteName        = "";
    qsMinuteFile        = "";
}

cMinute::~cMinute()
{

}

bool cMinute::createMinute( QString p_qsMinuteName, QString p_qsTeamHome, QString p_qsTeamGuest )
{
    qsMinuteName        = p_qsMinuteName;
    qsMinuteFileName    = QString( "%1_%2.dmin" ).arg( qsMinuteName ).arg( QDateTime::currentDateTime().toString( "yyyyMMddhhmm" ) );
    qsMinuteFile        = QString( "%1/%2" ).arg( QDir::currentPath() ).arg( qsMinuteFileName );

    QStringList qslHome = p_qsTeamHome.split("#");
    QStringList qslGuest= p_qsTeamGuest.split("#");

    if( qslHome.size() < 1 || qslGuest.size() < 1 )
    {
        return false;
    }

    QDomElement qdMinute        = m_obDoc->createElement( "Minute" );
    QDomElement qdMinuteHeader  = m_obDoc->createElement( "MinuteHeader" );
    QDomElement qdName          = m_obDoc->createElement( "Name" );
    QDomElement qdStart         = m_obDoc->createElement( "Start" );
    QDomElement qdTeamHome      = m_obDoc->createElement( "TeamHOME" );
    QDomElement qdTeamGuest     = m_obDoc->createElement( "TeamGUEST" );
    QDomElement qdMinuteActions = m_obDoc->createElement( "Actions" );

    qdName.setNodeValue( qsMinuteName );
    qdStart.setAttribute( "Date", QDate::currentDate().toString( "yyyy-MM-dd" ) );
    qdTeamHome.setAttribute( "Name", qslHome.at(0) );
    qdTeamGuest.setAttribute( "Name", qslGuest.at(0) );

    qdMinuteHeader.appendChild( qdName );
    qdMinuteHeader.appendChild( qdStart );
    qdMinuteHeader.appendChild( qdTeamHome );
    qdMinuteHeader.appendChild( qdTeamGuest );

    for( int i=1; i<qslHome.size(); i++ )
    {
        QStringList qslPlayer   = qslHome.at(i).split("|");
        QDomElement qdPlayer    = m_obDoc->createElement( "Player" );

        qdPlayer.setAttribute( "Number", qslPlayer.at(0) );
        qdPlayer.setAttribute( "Name", qslPlayer.at(1) );
        qdPlayer.setAttribute( "Foul", 0 );

        qdTeamHome.appendChild( qdPlayer );
    }

    for( int i=1; i<qslGuest.size(); i++ )
    {
        QStringList qslPlayer   = qslGuest.at(i).split("|");
        QDomElement qdPlayer    = m_obDoc->createElement( "Player" );

        qdPlayer.setAttribute( "Number", qslPlayer.at(0) );
        qdPlayer.setAttribute( "Name", qslPlayer.at(1) );
        qdPlayer.setAttribute( "Foul", 0 );

        qdTeamGuest.appendChild( qdPlayer );
    }

    qdMinute.appendChild( qdMinuteHeader );
    qdMinute.appendChild( qdMinuteActions );
    m_obDoc->appendChild( qdMinute );

    return true;
}

void cMinute::loadMinute( QString /*p_qsFileName*/ )
{

}

void cMinute::saveMinute()
{
    QFile   file( qsMinuteFile );

    if( file.open(QFile::WriteOnly | QFile::Text) )
    {
/*        QByteArray xmlMinute = m_obDoc->toByteArray();

        file.write(xmlMinute);*/
        QTextStream stream( &file );
        stream << m_obDoc->toString();
        file.close();
    }
}

void cMinute::closeMinute()
{
}

void cMinute::addAction( int p_nTimeMilisec, cTeamType::teType p_teType, cMinActionType::teAction p_teAction, QString p_qsParameters )
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
    qdAction.setAttribute( "Code", QString( "%1%2" ).arg( qsTeamCode )
                                                    .arg( cMinActionType::toCode( p_teAction ) ) );
    qdAction.setAttribute( "Text", QString( cMinActionType::toStr( p_teAction ) ).arg( p_qsParameters ) );

    qdMinuteAction.appendChild( qdAction );
}

void cMinute::updateTeam( cTeamType::teType p_teType, QString p_qsName )
{
    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdTeam      = qdMinute.elementsByTagName( qsTeam ).at(0).toElement();
    qdTeam.setAttribute( "Name", p_qsName );
}

void cMinute::addPlayer( cTeamType::teType p_teType, QStringList p_qslPlayer )
{
    if( p_qslPlayer.size() != 3 )   return;

    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdTeam      = qdMinute.elementsByTagName( qsTeam ).at(0).toElement();
    QDomElement qdPlayer    = m_obDoc->createElement( "Player" );

    qdPlayer.setAttribute( "Number", p_qslPlayer.at(0) );
    qdPlayer.setAttribute( "Name", p_qslPlayer.at(1) );
    qdPlayer.setAttribute( "Foul", p_qslPlayer.at(2) );

    qdTeam.appendChild( qdPlayer );
}

void cMinute::updatePlayer( cTeamType::teType p_teType, QStringList p_qslPlayer )
{
    if( p_qslPlayer.size() != 3 )   return;

    QString qsTeam;

    if( p_teType == cTeamType::HOME )   qsTeam = "TeamHOME";
    else                                qsTeam = "TeamGUEST";

    QDomElement qdMinute    = m_obDoc->documentElement();
    QDomElement qdTeam      = qdMinute.elementsByTagName( qsTeam ).at(0).toElement();

    for( int i=0; i<qdTeam.childNodes().count(); i++ )
    {
        QDomElement qdPlayer = qdTeam.childNodes().at(i).toElement();

        if( qdPlayer.attribute( "Number" ).compare( p_qslPlayer.at(0) ) == 0 )
        {
            qdPlayer.setAttribute( "Name", p_qslPlayer.at(1) );
            qdPlayer.setAttribute( "Foul", p_qslPlayer.at(2) );
            break;
        }
    }
}

