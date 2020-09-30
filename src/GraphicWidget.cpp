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
      displayShortcuts {true}
{
}

//==============================================================================
//---EVENTS---------------------------------------------------------------------
//==============================================================================

// paint & mouse events

void GraphicWidget::paintEvent(QPaintEvent* )
{
    // paint tools
    QPainter painter {this};
    QPen pen1 {Qt::black, 4};
    QPen pen2 {Qt::red, 3};
    QFont font1 {"Helvetica", 9, 0, false};

    // initial setup
    painter.setFont(font1);

    // vector size
    const auto residuesSize {pdbFile.getResSize()};

    // -----------------------------------------------------

    // paint all residues
    paintAllResidues(residuesSize, painter, pen1);

    // paint only selected
    paintSelectedResidue(residuesSize, painter, pen1, pen2);
}

//------------------------------------------------------------------------------

void GraphicWidget::mousePressEvent(QMouseEvent* p_event)
{
    const auto residuesSize {pdbFile.getResSize()};   // vector size
    auto resPosX {0.0};
    auto resPosY {0.0};

    // select the residue based on click position
    for(auto i {0}; i < residuesSize; ++i) {

        std::tie(resPosX, resPosY) = pdbFile.getResXY(i);

        if ( ( p_event->x() > resPosX &&\
               p_event->x() < ( resPosX + rectWidth ) ) &&\
             ( p_event->y() > resPosY &&\
               p_event->y() < ( resPosY + rectHeight ) ) ){

            if ( i != selectedResidue ){
                selectedResidue = i;
                // re-paint the residues
                update(); // SHOULD UPDATE ONLY WHEN THE SELECTED RESIDUE IS CHANGED!
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

void GraphicWidget::paintAllResidues(int residuesSize, QPainter& painter, const QPen& pen1)
{
    // 1. ---draw file name---
    painter.setPen(pen1);
    painter.drawText( 10, 10, "File:" );
    painter.drawText( 10, 30, pdbFile.getFileName() );

    // 2. ---draw rectangles + symbols---
    auto r {0}, g {0}, b {0};
    auto resPosX {0.0};
    auto resPosY {0.0};
    auto resChar {'x'};

    for(auto i {0}; i < residuesSize; ++i) {

        // get data
        std::tie(r, g, b) = pdbFile.getResRgb(i);
        std::tie(resPosX, resPosY) = pdbFile.getResXY(i);
        resChar = pdbFile.getResChar(i);

        // draw rectangle
        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);
        painter.drawRect( resPosX, resPosY, rectWidth, rectHeight );

        // draw symbol
        if ( displayShortcuts == true ){
            painter.setPen(pen1);
            painter.drawText( resPosX + (rectWidth * xTextMultiplier),\
                              resPosY + (rectHeight * yTextMultiplier),\
                              QChar( resChar ) );
        }

    }
}

//------------------------------------------------------------------------------

void GraphicWidget::paintSelectedResidue(int residuesSize, QPainter& painter, const QPen& pen1, const QPen& pen2)
{
    if( ( selectedResidue < residuesSize ) && ( selectedResidue > -1 ) ){ // range check

        // get data
        auto resPosX {0.0};
        auto resPosY {0.0};
        std:: string residueName {""};
        auto residueNumber {0};
        auto atomsCount {0};

        std::tie(resPosX, resPosY) = pdbFile.getResXY(selectedResidue);
        std::tie(residueName, residueNumber, atomsCount) = pdbFile.getResNameNumCount(selectedResidue);

        // 1. ---draw text for res description---
        painter.setPen(pen1);      
        std::string residueDescription;
        std::ostringstream ss;

        ss << "Residue: " << residueName << residueNumber;
        ss << "     Number of atoms: " << atomsCount;
        residueDescription = ss.str();

        painter.drawText(10, height() - 10, residueDescription.c_str());

        // 2. ---draw red rect---
        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen2);

        painter.drawRect(resPosX, resPosY,\
                         rectWidth, rectHeight );
    }
}
