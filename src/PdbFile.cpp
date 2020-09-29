#include <iostream>
#include "PdbFile.h"
#include "GraphicWidget.h"

//==============================================================================
//---OPEN AND READ PDB FILE-----------------------------------------------------
//==============================================================================

bool PdbFile::readFile(const QString& dialogFileName)
{
    // check the file name from dialog
    if( dialogFileName.isEmpty() ){
        std::cout << "ERROR: Empty or no file was selected!" << std::endl;
        return false;
    }

    // copy file name
    fileName = dialogFileName;

    // print file name
    printFileName();

    // clear all previous data
    clearVectors();

    // ---START: FILE MANIPULATION-------------------

    // file definition
    std::ifstream ifile;

    // open file
    if ( openFile(ifile) == false )
        return false;

    // read lines
    auto numLine {1};
    while ( !ifile.eof() ){
        readLine(ifile, numLine);
    }

    // close the file
    ifile.close();

    // ---END: FILE MANIPULATION-------------------

    // set residues
    setResidues();

    // print atoms
    for(auto const& i : atoms) {
        i.print();
    }

    // print residues
    for(auto const& i : residues) {
        i.print();
    }

    return true;
}

//==============================================================================
//---GETTERS--------------------------------------------------------------------
//==============================================================================

QString PdbFile::getFileName(void) const
{
    return fileName;
}

Residue PdbFile::getResidue(int index) const
{
    return residues[index];
}

int PdbFile::getResiduesSize(void) const
{
    return static_cast<int>(residues.size());
}

//==============================================================================
//---HELPER METHODS - OPEN------------------------------------------------------
//==============================================================================

bool PdbFile::openFile(std::ifstream& ifile)
{
    ifile.open( fileName.toLatin1().constData() ); // because of this cannot use const &

    // fail
    if( ifile.fail() ){
        std::cout << "ERROR: unable to open file!" << std::endl;
        return false;
    }

    // success
    std::cout << "Opening file..." << std::endl;
    return true;
}

//==============================================================================
//---HELPER METHODS - READ------------------------------------------------------
//==============================================================================

void PdbFile::readLine(std::ifstream& ifile, int& numLine)
{
    std::string line;
    std::string recordName;

    std::getline(ifile, line);

    if ( line.length() >= 6 ){

        recordName = line.substr(0, 6);

        if ( recordName == "ATOM  " || recordName == "HETATM") {
            atoms.emplace_back();
            if ( atoms.back().setValues(line, numLine) == false )
                std::cout << "Warning: the line (" << numLine << ") was skipped due to line corruption!" << std::endl;
        } else {
            std::cout << "Warning: Line (" << numLine << ") does not contain either ATOM or HETATM record" << std::endl;
        }
        ++numLine;
    }
}

//==============================================================================
//---HELPER METHODS - SET-------------------------------------------------------
//==============================================================================

void PdbFile::setResidues(void)
{
    auto firstAtom {0};         // index of the first atom in a residue
    auto xPos {10.0};             // start position of the first residue
    auto yPos {56.0};             // start position of the first residue
    auto column {0};            // start column number
    const auto atomsSize {static_cast<int>(atoms.size())};       // atoms vector size

    for(auto i {0}; i < atomsSize - 1; ++i) {

        // distinguish between two different residue
        if ( atoms[i].getResidueNumber() != atoms[i+1].getResidueNumber() ){

            residues.emplace_back();
            residues.back().setValues( firstAtom, i, atoms[i].getResidueName(), atoms[i].getResidueNumber(), xPos, yPos );

            firstAtom = i + 1;

            // check column and set xPos, yPos
            if ( column == 19 ){
                yPos = yPos + GraphicWidget::rectHeight + 8;   // 8 = space between rows
                xPos = xPos - (19 * GraphicWidget::rectWidth);
                column = 0;
            } else {
                // set x position
                xPos = xPos + GraphicWidget::rectWidth;
                ++column;
            }
        }

        // last atom
        if ( i + 2 == atomsSize ){

            residues.emplace_back();
            residues.back().setValues( firstAtom, i+1, atoms[i+1].getResidueName(), atoms[i+1].getResidueNumber(), xPos, yPos );
        }
    }
}

//==============================================================================
//---HELPER METHODS - WRITE-----------------------------------------------------
//==============================================================================


//==============================================================================
//---HELPER METHODS - PRINT-----------------------------------------------------
//==============================================================================

void PdbFile::printFileName(void) const
{
    std::cout << "File name: " << fileName.toLatin1().constData() << std::endl;
}

//==============================================================================
//---HELPER METHODS - CLEAR-----------------------------------------------------
//==============================================================================

void PdbFile::clearVectors(void)
{
    atoms.clear();
    atoms.shrink_to_fit();

    residues.clear();
    residues.shrink_to_fit();
}
