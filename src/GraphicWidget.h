#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <PdbFile.h>

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    // constructors
    GraphicWidget(QWidget* parent);

    // rectangle size
    static constexpr auto rectWidth {18.0};
    static constexpr auto rectHeight {20.0};

protected:
    // EVENTS

    // add graphic & text
    void paintEvent(QPaintEvent* p_event);

    // mouse action
    void mousePressEvent(QMouseEvent* p_event);

private slots:
    // BUTTONS
    void clickHideGraphic(void);
    void clickShowGraphic(void);
    void clickOpenFile(void);

private:
    // HELPERS
    QString openFileDialog(void);
    void paintAllResidues(int residuesSize, QPainter& painter, const QPen& pen1) const;
    void paintSelectedResidue(int residuesSize, QPainter& painter, const QPen& pen2) const;

    // PDB File
    PdbFile pdbFile;

    // selected residue
    int selectedResidue {-1};

    // display shortcuts of residues
    bool displayShortcuts {true};
};

#endif // GRAPHICWIDGET_H
