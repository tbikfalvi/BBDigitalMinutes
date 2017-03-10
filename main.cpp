#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QDir>

QTranslator     *poTransApp;
QTranslator     *poTransQT;
QApplication    *apMainApp;

int main(int argc, char *argv[])
{
    apMainApp = new QApplication(argc, argv);

    QSettings   obPref( QString( "%1/BBDigitalMinutes.info" ).arg( QDir::currentPath() ), QSettings::IniFormat );
    QString     qsLang = obPref.value( "Lang", "hu" ).toString();

    poTransApp = new QTranslator();
    poTransQT = new QTranslator();

    poTransApp->load( QString("%1\\BBDigitalMinutes_%2.qm").arg( QDir::currentPath() ).arg(qsLang) );
    poTransQT->load( QString("%1\\qt_%2.qm").arg( QDir::currentPath() ).arg(qsLang) );

    apMainApp->installTranslator( poTransApp );
    apMainApp->installTranslator( poTransQT );

    MainWindow w;
    w.show();

    return apMainApp->exec();
}
