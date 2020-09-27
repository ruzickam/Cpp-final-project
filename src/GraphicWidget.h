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
    GraphicWidget(QWidget* parent);

    // open & read PDB file
    bool readPdbFile(void);

    // set residues
    bool setResidues(void);

protected:
    // add graphic & text
    void paintEvent(QPaintEvent* p_event);
    // mouse action
    void mousePressEvent(QMouseEvent* p_event);

private slots:
    // actions on button push
    void hideGraphic(void);
    void showGraphic(void);
    void openFile(void);

private:
    // PDB file name
    QString fileName {"No file"};

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>	residues;

    // selected residue
    int selectedResidue {-1};

    // rectangle size
    double rectWidth {18.0};
    double rectHeight {20.0};

    // display shortcuts of residues
    bool displayShortcuts {true};
};

#endif // GRAPHICWIDGET_H
