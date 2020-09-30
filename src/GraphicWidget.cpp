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
    // paint all residues
    paintAllResidues();

    // paint highlighter for selected residue
    paintSelectedResidue();
}

//------------------------------------------------------------------------------

void GraphicWidget::mousePressEvent(QMouseEvent* p_event)
{
    // get vector size
    const auto residuesSize {pdbFile.getResSize()};

    // select the residue based on click position
    for(auto i {0}; i < residuesSize; ++i) {

        auto resPosX {0.0}, resPosY {0.0};
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

void GraphicWidget::paintAllResidues(void)
{
// 1. ---draw file name---
    // paint tools
    QPainter painter {this}; // paint tools
    QPen pen1 {Qt::black, 4};
    QFont font1 {"Helvetica", 9, 0, false};
    painter.setPen(pen1);
    painter.setFont(font1);

    // draw text
    painter.drawText( 10, 10, "File:" );
    painter.drawText( 10, 30, pdbFile.getFileName() );

// 2. ---draw rectangles + symbols---
    // get vector size
    const auto residuesSize {pdbFile.getResSize()};

    for(auto i {0}; i < residuesSize; ++i) {

        // get data
        auto r {0}, g {0}, b {0};
        std::tie(r, g, b) = pdbFile.getResRgb(i);
        auto resPosX {0.0}, resPosY {0.0};
        std::tie(resPosX, resPosY) = pdbFile.getResXY(i);

        // draw rectangle
        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);
        painter.drawRect( resPosX, resPosY, rectWidth, rectHeight );

        // draw symbol
        if ( displayShortcuts == true ){
            auto resChar {pdbFile.getResChar(i)};
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
    const auto residuesSize {pdbFile.getResSize()};

    if( ( selectedResidue < residuesSize ) && ( selectedResidue > -1 ) ){ // range check

    // 1. ---draw text for res description---
        // output string
        std:: string residueName;
        auto residueNumber {0};
        auto atomsCount {0};
        std::tie(residueName, residueNumber, atomsCount) = pdbFile.getResNameNumCount(selectedResidue);
        std::string residueDescription;
        std::ostringstream ss;
        ss << "Residue: " << residueName << residueNumber;
        ss << "     Number of atoms: " << atomsCount;
        residueDescription = ss.str();

        // paint tools
        QPainter painter {this};
        QPen pen1 {Qt::black, 4};
        QFont font1 {"Helvetica", 9, 0, false};
        painter.setPen(pen1);
        painter.setFont(font1);

        // draw text
        painter.drawText(10, height() - 10, residueDescription.c_str());

    // 2. ---draw red rect---
        // paint tools
        QPen pen2 {Qt::red, 3};
        painter.setPen(pen2);
        painter.setBrush(Qt::NoBrush);

        // get position
        auto resPosX {0.0}, resPosY {0.0};
        std::tie(resPosX, resPosY) = pdbFile.getResXY(selectedResidue);

        // draw rect
        painter.drawRect(resPosX, resPosY,\
                         rectWidth, rectHeight );
    }
}
