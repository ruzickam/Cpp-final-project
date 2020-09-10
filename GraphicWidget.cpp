#include <iostream>
#include <fstream>
#include <sstream>
#include <QPainter>
#include <QFileDialog>
#include <QMouseEvent>
#include "GraphicWidget.h"

using namespace std;

GraphicWidget::GraphicWidget()
{
    fileName = "No file";
    selectedResidue = -1;
    rectWidth = 18;
    rectHeight = 20;
    displayShortcuts = true;
}

GraphicWidget::~GraphicWidget()
{
    // clear p_residues
    int selection = p_residues.size();
    for(int i=0; i < selection; i++){
        delete p_residues[i];
        p_residues[i] = NULL;
    }
    
    // clear p_atoms
    selection = p_atoms.size();
    for(int i=0; i < selection; i++){
        delete p_atoms[i];
        p_atoms[i] = NULL;
    }
        
    // not necessary to .clear()
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool GraphicWidget::readPdbFile(void)
{
    cout << endl << "Reading PDB file..." << endl;

    ifstream ifile;

    ifile.open( fileName.toLatin1().constData() );
    if( ifile.fail() ){
        cout << "ERROR: unable to open input file!" << endl;
        return(false);
    }

    string line;
    string recordName;
    int numLine = 1;

    while ( !ifile.eof() ){
        getline(ifile,line);
        if ( line.length() >= 6 ){
            recordName = line.substr(0,6);
            if ( recordName == "ATOM  " ||
                 recordName == "HETATM") {
                Atom* p_atom = new Atom;
                p_atom->readLine(line,numLine);
                p_atoms.push_back(p_atom);
                p_atom = NULL;
            } else {
                cout << "Warning: Line (" << numLine << ") does not contain either ATOM or HETATM record" << endl;
            }
            numLine++;
        }
    }

    ifile.close();

    // print atoms
    int selection = p_atoms.size();

    for(int i=0; i < selection; i++) {
        p_atoms[i]->print();
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool GraphicWidget::setResidues(void)
{
    int firstAtom = 0;                  // index of the first atom in a residue
    int selection = p_atoms.size();     // how many atoms are selected

    for(int i=0; i < selection; i++) {
        if ( (i+1) == selection ){ // last atom in molecule
            if ( p_atoms[i]->getResidueNumber() != p_atoms[i-1]->getResidueNumber() ){  // distinguish between two different residue

                Residue* p_residue = new Residue;

                p_residue->setResidueNumber(p_atoms[i]->getResidueNumber());
                p_residue->setResidueName(p_atoms[i]->getResidueName());

                p_residue->setAtomLast(i);
                p_residue->setAtomFirst(i);

                p_residues.push_back(p_residue);
                p_residue = NULL;
            }
        } else { // all other atoms
            if ( p_atoms[i]->getResidueNumber() != p_atoms[i+1]->getResidueNumber() ){  // distinguish between two different residue

                Residue* p_residue = new Residue;

                p_residue->setResidueNumber(p_atoms[i]->getResidueNumber());
                p_residue->setResidueName(p_atoms[i]->getResidueName());

                p_residue->setAtomLast(i);
                p_residue->setAtomFirst(firstAtom);
                firstAtom = i+1;

                p_residues.push_back(p_residue);
                p_residue = NULL;
            }
        }
    }

    // print residues
    selection = p_residues.size();

    for(int i=0; i < selection; i++) {
        p_residues[i]->print();
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// paint & mouse events

void GraphicWidget::paintEvent(QPaintEvent* p_event)
{
    QPainter painter(this);
    QPen pen1(Qt::black, 4);
    QPen pen2(Qt::red, 3);
    QFont font1("Helvetica",9,0,false);

    // file name
    painter.setPen(pen1);
    painter.setFont(font1);
    painter.drawText(10,10,"Soubor:");
    painter.drawText(10,30,fileName);

    // print symbol of residues
    painter.setFont(font1);
    int selection = p_residues.size();
    int column = 0;
    int xPos = 10;  // start position of the first residue
    int yPos = 56;  // start position of the first residue
    int r = 0;
    int g = 0;
    int b = 0;
    for(int i=0; i < selection; i++) {
        // draw rectangle
        p_residues[i]->getColorRgb(&r,&g,&b);
        painter.setBrush(QColor(r,g,b));
        painter.setPen(Qt::NoPen);
        painter.drawRect(xPos,yPos,rectWidth,rectHeight);
        p_residues[i]->setPosXY(xPos,yPos);
        // print symbol
        if ( displayShortcuts == true ){
            painter.setPen(pen1);
            painter.drawText(xPos+(rectWidth*0.28),yPos+(rectHeight*0.78),QChar(p_residues[i]->getResidueChar()));
        }
        // check column
        if ( column == 19 ){
            yPos = yPos + rectHeight + 8;   // 8 = space between rows
            xPos = xPos - (19*rectWidth);
            column = 0;
        } else {
            // set x position
            xPos = xPos + rectWidth;
            column++;
        }
    }

    // add red rect & desc for selected residue
    if( ( selection > 0 ) && ( selectedResidue > -1 ) ){
        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen2);
        painter.drawRect(p_residues[selectedResidue]->getPosX(),p_residues[selectedResidue]->getPosY(),rectWidth,rectHeight);

        string residueDescription;
        ostringstream ss;
        ss << "Residuum: ";
        ss << p_residues[selectedResidue]->getResidueName();
        ss << p_residues[selectedResidue]->getResidueNumber();
        ss << "     Pocet atomu: ";
        ss << p_residues[selectedResidue]->getAtomsCount();
        residueDescription = ss.str();

        painter.setPen(pen1);
        painter.drawText(10,height()-10,residueDescription.c_str());
    }


}

void GraphicWidget::mousePressEvent(QMouseEvent *p_event)
{
    int selection = p_residues.size();

    for(int i=0; i < selection; i++) {
        if ( ( p_event->x() > p_residues[i]->getPosX() && p_event->x() < ( p_residues[i]->getPosX() + rectWidth ) ) && ( p_event->y() > p_residues[i]->getPosY() && p_event->y() < ( p_residues[i]->getPosY() + rectHeight ) ) ){
            selectedResidue = i;
        }
    }

    update();
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// buttons

void GraphicWidget::hideGraphic(void)
{
    displayShortcuts = false;
    update();
}

void GraphicWidget::showGraphic(void)
{
    displayShortcuts = true;
    update();
}

void GraphicWidget::openFile(void)
{
    // open PDB file
    fileName = QFileDialog::getOpenFileName(this,"Open",".");
    if( fileName.isEmpty() ) return;
    string strFileName;
    strFileName = fileName.toLatin1().constData();
    cout << "File name: " << strFileName << endl;

    // clear all previous data
    int selection = p_residues.size();
    for(int i=0; i < selection; i++){
        delete p_residues[i];
        p_residues[i] = NULL;
    }
    selection = p_atoms.size();
    for(int i=0; i < selection; i++){
        delete p_atoms[i];
        p_atoms[i] = NULL;
    }
    p_residues.clear();
    p_atoms.clear();
    selectedResidue = -1;

    // read PDB file
    readPdbFile();

    // set residues
    setResidues();

    update();
}
