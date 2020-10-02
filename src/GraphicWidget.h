#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QPainter>
#include <Protein.h>

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    // constructors
    GraphicWidget() = delete;
    GraphicWidget(QWidget* parent);

    // window size
    static constexpr auto minWindowWidth {400};
    static constexpr auto minWindowHeight {700};

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

    // graphic & text painting
    void paintEvent(QPaintEvent* ) override;

    // click to select a residue
    void mousePressEvent(QMouseEvent* p_event) override;

private slots:
    // BUTTONS
    void hideShortcuts(void);
    void showShortcuts(void);
    void openPDBfile(void);

private:
    // HELPERS
    QString openFileDialog(void);
    void paintAllResidues(void);
    void paintSelectedResidue(void);

    // DATA------------------------------------------

    Protein protein;

    int selectedResidue;

    bool areShortcutsDisplayed;
};

#endif // GRAPHICWIDGET_H
