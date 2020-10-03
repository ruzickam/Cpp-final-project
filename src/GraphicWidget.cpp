#include <iostream>
#include <sstream>
#include <QMouseEvent>
#include <QFileDialog>
#include "GraphicWidget.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

GraphicWidget::GraphicWidget(QWidget* parent)

     :QWidget(parent),
      selectedResidue {-1},
      areShortcutsDisplayed {true}
{
}

//==============================================================================
//---EVENTS---------------------------------------------------------------------
//==============================================================================

void GraphicWidget::paintEvent(QPaintEvent* )
{
    paintAllResidues();

    // paint highlighter for selected residue
    paintSelectedResidue();
}

//------------------------------------------------------------------------------

void GraphicWidget::mousePressEvent(QMouseEvent* p_event)
{
    // get vector size
    const int residuesSize { protein.getNumOfRes() };

    for(auto i {0}; i < residuesSize; ++i) {
        // get: posX, posY
        auto resPosX {0.0}, resPosY {0.0};
        std::tie(resPosX, resPosY) = protein.getResRectXY(i);

        // check whather we clicked inside a residue box
        if ( ( p_event->x() > resPosX &&\
               p_event->x() < ( resPosX + rectWidth ) ) &&\
             ( p_event->y() > resPosY &&\
               p_event->y() < ( resPosY + rectHeight ) ) ){

            // SHOULD UPDATE ONLY WHEN THE SELECTED RESIDUE IS CHANGED!
            if ( i != selectedResidue ){
                selectedResidue = i;
                // re-paint the residues
                update();
            }
        }
    }
}

//==============================================================================
//---BUTTONS--------------------------------------------------------------------
//==============================================================================

void GraphicWidget::hideShortcuts(void)
{
    areShortcutsDisplayed = false;

    // re-paint the residues
    update();
}

//------------------------------------------------------------------------------

void GraphicWidget::showShortcuts(void)
{
    areShortcutsDisplayed = true;

    // re-paint the residues
    update();
}

//------------------------------------------------------------------------------

void GraphicWidget::openPDBfile(void)
{
    // read a file
    if ( protein.initFromPDBfile( openFileDialog() ) == false ){
        return;
    }

    // unselect a residue
    selectedResidue = -1;

    // re-paint the residues
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

void GraphicWidget::paintAllResidues(void)
{
// 1. ---draw file name---
    QPainter painter {this}; // paint tools
    QPen pen1 {Qt::black, 4};
    QFont font1 {"Helvetica", 9, 0, false};
    painter.setPen(pen1);
    painter.setFont(font1);

    painter.drawText( 10, 10, "File:" );
    painter.drawText( 10, 30, protein.getPDBfileName() );

// 2. ---draw rectangles + symbols---
    // get vector size
    const int residuesSize { protein.getNumOfRes() };

    for(auto i {0}; i < residuesSize; ++i) {

        // get: rgb, xPos, yPos
        auto r {0}, g {0}, b {0};
        std::tie(r, g, b) = protein.getResColor(i);
        auto resPosX {0.0}, resPosY {0.0};
        std::tie(resPosX, resPosY) = protein.getResRectXY(i);

        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);

        painter.drawRect( resPosX, resPosY, rectWidth, rectHeight );

        // draw shortcuts
        if ( areShortcutsDisplayed == true ){

            const char resChar { protein.getResChar(i) };

            painter.setPen(pen1);

            painter.drawText( resPosX + (rectWidth * xTextMultiplier),\
                              resPosY + (rectHeight * yTextMultiplier),\
                              QChar( resChar ) );
        }

    }
}

//------------------------------------------------------------------------------

void GraphicWidget::paintSelectedResidue(void)
{
    // get vector size
    const int residuesSize { protein.getNumOfRes() };

    // range check
    if( ( selectedResidue < residuesSize ) && ( selectedResidue > -1 ) ){

    // 1. ---draw text for res description---
        std::ostringstream ss;
        std:: string residueName, residueDescription;
        auto residueNumber {0}, numOfAtoms {0};

        std::tie(residueName, residueNumber, numOfAtoms) = protein.getResNameNumberAnumber(selectedResidue);

        ss << "Residue: " << residueName << residueNumber;
        ss << "     Number of atoms: " << numOfAtoms;
        residueDescription = ss.str();

        QPainter painter {this};
        QPen pen1 {Qt::black, 4};
        QFont font1 {"Helvetica", 9, 0, false};

        painter.setPen(pen1);
        painter.setFont(font1);

        painter.drawText(10, height() - 10, residueDescription.c_str());

    // 2. ---draw red rect---
        QPen pen2 {Qt::red, 3};

        auto resPosX {0.0}, resPosY {0.0};
        std::tie(resPosX, resPosY) = protein.getResRectXY(selectedResidue);

        painter.setPen(pen2);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(resPosX, resPosY,\
                         rectWidth, rectHeight );
    }
}
