#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <vector>
#include "Atom.h"
#include "Residue.h"

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    // constructor
    GraphicWidget();
    
    // destructor
    virtual ~GraphicWidget();

    // open & read PDB file
    bool readPdbFile(void);

    // set residues
    bool setResidues(void);

protected:
    // add graphic & text
    virtual void paintEvent(QPaintEvent* p_event);
    // mouse action
    virtual void mousePressEvent(QMouseEvent* p_event);

private slots:
    // actions on button push
    void hideGraphic(void);
    void showGraphic(void);
    void openFile(void);

private:
    // PDB file name
    QString fileName;

    // atom & residue containers
    std::vector<Atom>		atoms;
    std::vector<Residue>	residues;

    // selected residue
    int selectedResidue;

    // rectangle size
    double rectWidth;
    double rectHeight;

    // display shortcuts of residues
    bool displayShortcuts;
};

#endif // GRAPHICWIDGET_H
