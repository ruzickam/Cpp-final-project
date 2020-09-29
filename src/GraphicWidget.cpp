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
    // setup painter, pens, font
    QPainter painter {this};
    QPen pen1 {Qt::black, 4};
    QPen pen2 {Qt::red, 3};
    QFont font1 {"Helvetica", 9, 0, false};
    painter.setFont(font1);
    painter.setPen(pen1);

    // get residues vector size
    const auto residuesSize {pdbFile.getResiduesSize()};   // vector size

    // paint all residues
    paintAllResidues(residuesSize, painter, pen1);

    // paint only selected
    paintSelectedResidue(residuesSize, painter, pen2);
}

//------------------------------------------------------------------------------

void GraphicWidget::mousePressEvent(QMouseEvent* p_event)
{
    const auto residuesSize {pdbFile.getResiduesSize()};   // vector size

    // select the residue based on click position
    for(auto i {0}; i < residuesSize; ++i) {

        if ( ( p_event->x() > pdbFile.getResidue(i).getPosX() && p_event->x() < ( pdbFile.getResidue(i).getPosX() + rectWidth ) ) &&\
             ( p_event->y() > pdbFile.getResidue(i).getPosY() && p_event->y() < ( pdbFile.getResidue(i).getPosY() + rectHeight ) ) ){

            if ( i != selectedResidue ){
                selectedResidue = i;
                // re-paint the residues
                update(); // SHOULD UPDATE ONLY WHEN THE SELECTED RESIDUE IS CHANGED!!!
            }
        }
    }
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
    selectedResidue = -1; // unselect a residue
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

//------------------------------------------------------------------------------

void GraphicWidget::paintAllResidues(int residuesSize, QPainter& painter, const QPen& pen1) const
{
    // draw file name
    painter.drawText(10, 10, "File:");
    painter.drawText(10, 30, pdbFile.getFileName());

    // paint symbols of residues
    auto r {0}, g {0}, b {0};

    for(auto i {0}; i < residuesSize; ++i) {

        // draw rectangle
        std::tie(r, g, b) = pdbFile.getResidue(i).getColorRgb();
        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);
        painter.drawRect( pdbFile.getResidue(i).getPosX(), pdbFile.getResidue(i).getPosY(), rectWidth, rectHeight );

        // draw symbol
        if ( displayShortcuts == true ){
            painter.setPen(pen1);
            painter.drawText( pdbFile.getResidue(i).getPosX() + (rectWidth * 0.28),\
                              pdbFile.getResidue(i).getPosY() + (rectHeight * 0.78),\
                              QChar( pdbFile.getResidue(i).getResidueChar() ) );
        }

    }
}

//------------------------------------------------------------------------------

void GraphicWidget::paintSelectedResidue(int residuesSize, QPainter& painter, const QPen& pen2) const
{
    if( ( selectedResidue < residuesSize ) && ( selectedResidue > -1 ) ){ // range check

        // draw text for res description
        std::string residueDescription;
        std::ostringstream ss;
        ss << "Residue: ";
        ss << pdbFile.getResidue(selectedResidue).getResidueName();
        ss << pdbFile.getResidue(selectedResidue).getResidueNumber();
        ss << "     Number of atoms: ";
        ss << pdbFile.getResidue(selectedResidue).getAtomsCount();
        residueDescription = ss.str();
        painter.drawText(10, height() - 10, residueDescription.c_str());

        // draw red rect
        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen2);
        painter.drawRect(pdbFile.getResidue(selectedResidue).getPosX(),\
                         pdbFile.getResidue(selectedResidue).getPosY(),\
                         rectWidth, rectHeight );
    }
}
