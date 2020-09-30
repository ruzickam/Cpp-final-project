#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QPainter>
#include <PdbFile.h>

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    // constructors
    GraphicWidget() = delete;
    GraphicWidget(QWidget* parent);

    // graphic constants
    static constexpr auto rectWidth {18.0};
    static constexpr auto rectHeight {20.0};

    static constexpr auto xStartPosition {10.0};
    static constexpr auto yStartPosition {56.0};

    static constexpr auto columnPerRow {19};
    static constexpr auto spaceBetweenRows {8};

    static constexpr auto xTextMultiplier {0.28};
    static constexpr auto yTextMultiplier {0.78};

protected:
    // EVENTS

    // add graphic & text
    void paintEvent(QPaintEvent* ) override;

    // mouse action
    void mousePressEvent(QMouseEvent* p_event) override;

private slots:
    // BUTTONS
    void clickHideGraphic(void);
    void clickShowGraphic(void);
    void clickOpenFile(void);

private:
    // HELPERS
    QString openFileDialog(void);
    void paintAllResidues(int residuesSize, QPainter& painter, const QPen& pen1);
    void paintSelectedResidue(int residuesSize, QPainter& painter, const QPen& pen1, const QPen& pen2);

    // ----------------------------------------------
    // DATA

    // PDB File
    PdbFile pdbFile;

    // selected residue
    int selectedResidue;

    // display shortcuts of residues
    bool displayShortcuts;
};

#endif // GRAPHICWIDGET_H
