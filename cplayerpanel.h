#ifndef CPLAYERPANEL_H
#define CPLAYERPANEL_H

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QFrame>
#include <QLabel>

//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
// Player panel class
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷

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

    int              playerFaults()                 {   return nCountFaults;                }
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

#endif // CPLAYERPANEL_H
