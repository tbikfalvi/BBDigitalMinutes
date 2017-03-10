
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>

#include "cminute.h"

cMinute::cMinute()
{
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

    QFile   file( qsMinuteFile );

    if( file.open(QFile::WriteOnly | QFile::Text) )
    {
        QXmlStreamWriter    xmlWriter( &file );

        xmlWriter.setAutoFormatting( true );
        xmlWriter.writeStartDocument();

            xmlWriter.writeStartElement( "MinuteHeader" );

                xmlWriter.writeTextElement("Name", qsMinuteName );
                xmlWriter.writeStartElement( "Start" );
                    xmlWriter.writeAttribute("Date", QDate::currentDate().toString( "yyyy-MM-dd" ) );
                    xmlWriter.writeAttribute("Time", QTime::currentTime().toString( "hh:mm" ) );
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement( "Team HOME" );
                    xmlWriter.writeAttribute("Name", qslHome.at(0) );

                    for( int i=1; i<qslHome.size(); i++ )
                    {
                        QStringList qslPlayer = qslHome.at(i).split("|");

                        xmlWriter.writeStartElement( "Player" );
                        xmlWriter.writeAttribute("Number", qslPlayer.at(0) );
                        xmlWriter.writeAttribute("Name", qslPlayer.at(1) );
                        xmlWriter.writeEndElement();
                    }

                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement( "Team GUEST" );
                    xmlWriter.writeAttribute("Name", qslGuest.at(0) );

                    for( int i=1; i<qslGuest.size(); i++ )
                    {
                        QStringList qslPlayer = qslGuest.at(i).split("|");

                        xmlWriter.writeStartElement( "Player" );
                        xmlWriter.writeAttribute("Number", qslPlayer.at(0) );
                        xmlWriter.writeAttribute("Name", qslPlayer.at(1) );
                        xmlWriter.writeEndElement();
                    }

                xmlWriter.writeEndElement();

            xmlWriter.writeEndElement();

        xmlWriter.writeEndDocument();

        file.close();
    }
    return true;
}

void cMinute::loadMinute( QString p_qsFileName )
{

}

void cMinute::saveMinute()
{

}

void cMinute::closeMinute()
{

}

void cMinute::addAction( cMinActionType::teAction p_teAction, QString p_qsParameters )
{

}

