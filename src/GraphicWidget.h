#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    // constructors
    GraphicWidget(QWidget* parent);

protected:
    // add graphic & text
    void paintEvent(QPaintEvent* p_event);
    // mouse action
    void mousePressEvent(QMouseEvent* p_event);

private slots:
    // actions on button push
    void clickHideGraphic(void);
    void clickShowGraphic(void);
    void clickOpenFile(void);

private:
    // rectangle size
    static constexpr auto rectWidth {18.0};
    static constexpr auto rectHeight {20.0};

    // selected residue
    int selectedResidue {-1};

    // display shortcuts of residues
    bool displayShortcuts {true};
};

#endif // GRAPHICWIDGET_H
