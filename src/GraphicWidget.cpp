#include <iostream>
#include <sstream>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include "GraphicWidget.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

GraphicWidget::GraphicWidget(QWidget* parent) : QWidget(parent) {}

//==============================================================================
//---EVENTS---------------------------------------------------------------------
//==============================================================================

// paint & mouse events

void GraphicWidget::paintEvent(QPaintEvent* p_event)
{
    QPainter painter {this};
    QPen pen1 {Qt::black, 4};
    QPen pen2 {Qt::red, 3};
    QFont font1 {"Helvetica", 9, 0, false};

    // paint file name
    painter.setPen(pen1);
    painter.setFont(font1);
    painter.drawText(10, 10, "File:");
    painter.drawText(10, 30, pdbFile.getFileName());

    // paint symbol of residues
    painter.setFont(font1);
    auto r {0};
    auto g {0};
    auto b {0};
    const auto residuesSize {pdbFile.getResiduesSize()};   // vector size

    for(auto i {0}; i < residuesSize; ++i) {

        // draw rectangle
        std::tie(r, g, b) = pdbFile.getResidue(i).getColorRgb();
        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);
        painter.drawRect( pdbFile.getResidue(i).getPosX(), pdbFile.getResidue(i).getPosY(), rectWidth, rectHeight);

        // paint symbol
        if ( displayShortcuts == true ){
            painter.setPen(pen1);
            painter.drawText( pdbFile.getResidue(i).getPosX() + (rectWidth * 0.28),\
                              pdbFile.getResidue(i).getPosY() + (rectHeight * 0.78), QChar(pdbFile.getResidue(i).getResidueChar()));
        }

    }

    // add red rect & desc for selected residue
    if( ( residuesSize > 0 ) && ( selectedResidue > -1 ) ){
        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen2);
        painter.drawRect(pdbFile.getResidue(selectedResidue).getPosX(), pdbFile.getResidue(selectedResidue).getPosY(), rectWidth, rectHeight);

        std::string residueDescription;
        std::ostringstream ss;
        ss << "Residue: ";
        ss << pdbFile.getResidue(selectedResidue).getResidueName();
        ss << pdbFile.getResidue(selectedResidue).getResidueNumber();
        ss << "     Number of atoms: ";
        ss << pdbFile.getResidue(selectedResidue).getAtomsCount();
        residueDescription = ss.str();

        painter.setPen(pen1);
        painter.drawText(10, height() - 10, residueDescription.c_str());
    }
}

//------------------------------------------------------------------------------

void GraphicWidget::mousePressEvent(QMouseEvent* p_event)
{
    const auto residuesSize {pdbFile.getResiduesSize()};   // vector size

    // select the residue based on click position
    for(auto i {0}; i < residuesSize; ++i) {

        if ( ( p_event->x() > pdbFile.getResidue(i).getPosX() && p_event->x() < ( pdbFile.getResidue(i).getPosX() + rectWidth ) ) &&\
             ( p_event->y() > pdbFile.getResidue(i).getPosY() && p_event->y() < ( pdbFile.getResidue(i).getPosY() + rectHeight ) ) ){

            selectedResidue = i;
        }
    }

    // re-paint the residues
    update();
}

//==============================================================================
//---BUTTONS--------------------------------------------------------------------
//==============================================================================

void GraphicWidget::clickHideGraphic(void)
{
    displayShortcuts = false;

    // re-paint the residues
    update();
}

//------------------------------------------------------------------------------

void GraphicWidget::clickShowGraphic(void)
{
    displayShortcuts = true;

    // re-paint the residues
    update();
}

//------------------------------------------------------------------------------

void GraphicWidget::clickOpenFile(void)
{
    // read a file
    if ( pdbFile.readFile( openFileDialog() ) == false ){
        return;
    }

    // re-paint the residues
    selectedResidue = -1;
    update();
}

//==============================================================================
//---HELPERS--------------------------------------------------------------------
//==============================================================================


QString GraphicWidget::openFileDialog(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open", "."); // "this" must be a QWidget

    return fileName;
}
