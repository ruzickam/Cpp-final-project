#include <iostream>
#include <sstream>
#include "PdbFile.h"
#include "GraphicWidget.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

PdbFile::PdbFile()
    :fileName {"No file"}
{
}

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
    ifile.open( fileName.toLatin1().constData() );
    if( ifile.fail() ){
        std::cout << "ERROR: unable to open file!" << std::endl;
        return false;
    }
    std::cout << "Opening file..." << std::endl;

    // read lines
    if ( ! readLines(ifile) )
        return false;

    // close the file
    ifile.close();

    // ---END: FILE MANIPULATION---------------------

    // set residues
    parseResidues();

    // print atoms
    for(const auto& i : atoms) {
        i.print();
    }

    // print residues
    for(const auto& i : residues) {
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

//------------------------------------------------------------------------------

int PdbFile::getResSize(void) const
{
    return static_cast<int>(residues.size());
}

//------------------------------------------------------------------------------

std::tuple<double, double> PdbFile::getResXY(int index) const
{
    return std::make_tuple(residues[index].getPosX(),\
                           residues[index].getPosY());
}

//------------------------------------------------------------------------------

std::tuple<int, int, int> PdbFile::getResRgb(int index) const
{
    std::string residueName = residues[index].getResidueName();

    if( residueName == "ALA" ){
        return std::make_tuple(204, 255, 255);

    } else if ( residueName == "ARG" ){
        return std::make_tuple(230, 6, 6);

    } else if ( residueName == "ASN" ){
        return std::make_tuple(255, 153, 0);

    } else if ( residueName == "ASP" ){
        return std::make_tuple(255, 204, 153);

    } else if ( residueName == "CYS" ){
        return std::make_tuple(0, 255, 255);

    } else if ( residueName == "GLN" ){
        return std::make_tuple(255, 102, 0);

    } else if ( residueName == "GLU" ){
        return std::make_tuple(255, 204, 0);

    } else if ( residueName == "GLY" ){
        return std::make_tuple(0, 255, 0);

    } else if ( residueName == "HIS" ){
        return std::make_tuple(255, 255, 153);

    } else if ( residueName == "ILE" ){
        return std::make_tuple(0, 0, 128);

    } else if ( residueName == "LEU" ){
        return std::make_tuple(51, 102, 255);

    } else if ( residueName == "LYS" ){
        return std::make_tuple(198, 6, 0);

    } else if ( residueName == "MET" ){
        return std::make_tuple(153, 204, 255);

    } else if ( residueName == "PHE" ){
        return std::make_tuple(0, 204, 255);

    } else if ( residueName == "PRO" ){
        return std::make_tuple(255, 255, 0);

    } else if ( residueName == "SER" ){
        return std::make_tuple(204, 255, 153);

    } else if ( residueName == "THR" ){
        return std::make_tuple(0, 255, 153);

    } else if ( residueName == "TRP" ){
        return std::make_tuple(204, 153, 255);

    }else if ( residueName == "TYR" ){
        return std::make_tuple(204, 255, 204);

    } else if ( residueName == "VAL" ){
        return std::make_tuple(0, 0, 255);

    } else {
        return std::make_tuple(153, 153, 153);
    }
}

//------------------------------------------------------------------------------

char PdbFile::getResChar(int index) const
{
    std::string residueName = residues[index].getResidueName();

    if ( residueName == "ALA" ){
        return 'A';
    }
    if ( residueName == "ARG" ){
        return 'R';
    }
    if ( residueName == "ASN" ){
        return 'N';
    }
    if ( residueName == "ASP" ){
        return 'D';
    }
    if ( residueName == "CYS" ){
        return 'C';
    }
    if ( residueName == "GLN" ){
        return 'Q';
    }
    if ( residueName == "GLU" ){
        return 'E';
    }
    if ( residueName == "GLY" ){
        return 'G';
    }
    if ( residueName == "HIS" ){
        return 'H';
    }
    if ( residueName == "ILE" ){
        return 'I';
    }
    if ( residueName == "LEU" ){
        return 'L';
    }
    if ( residueName == "LYS" ){
        return 'K';
    }
    if ( residueName == "MET" ){
        return 'M';
    }
    if ( residueName == "PHE" ){
        return 'F';
    }
    if ( residueName == "PRO" ){
        return 'P';
    }
    if ( residueName == "SER" ){
        return 'S';
    }
    if ( residueName == "THR" ){
        return 'T';
    }
    if ( residueName == "TRP" ){
        return 'W';
    }
    if ( residueName == "TYR" ){
        return 'Y';
    }
    if ( residueName == "VAL" ){
        return 'V';
    }
    return 'X';
}

//------------------------------------------------------------------------------

std::tuple<std::string, int, int> PdbFile::getResNameNumCount(int index) const
{
    return std::make_tuple(residues[index].getResidueName(),\
                           residues[index].getResidueNumber(),\
                           residues[index].getAtomLast() - residues[index].getAtomFirst() + 1 );
}

//==============================================================================
//---HELPER METHODS - OPEN------------------------------------------------------
//==============================================================================


//==============================================================================
//---HELPER METHODS - READ------------------------------------------------------
//==============================================================================

bool PdbFile::readLines(std::ifstream& ifile)
{
    // check if the file is opened
    if( ifile.fail() || ! ifile.is_open() ){
        std::cout << "ERROR: reading file failed!" << std::endl;
        return false;
    }

    // helper vars for line reading
    auto numLine {1};
    std::string line;
    std::string recordName;

    // read every line
    while ( !ifile.eof() ){

        std::getline(ifile, line);

        if ( line.length() >= 6 ){

            recordName = line.substr(0, 6);

            if ( recordName == "ATOM  " || recordName == "HETATM") {
                if ( parseAtom(line, numLine) == false )
                    std::cout << "Warning: the line (" << numLine << ") was skipped due to line corruption!" << std::endl;
            } else {
                std::cout << "Warning: Line (" << numLine << ") does not contain either ATOM or HETATM record" << std::endl;
            }
            ++numLine;
        }
    }

    return true;
}

//==============================================================================
//---HELPER METHODS - SET-------------------------------------------------------
//==============================================================================

bool PdbFile::parseAtom(const std::string& line, int numLine)
{
    // Line must have at least 53 chars to obtain all neccesary values
    if ( line.length() < 53 ){
        std::cout << "Warning: the line (" << numLine << ") is too short" << std::endl;
        return false;
    }

    // helper: string
    std::string s;

    // recordType
    auto recordType {0};
    s = line.substr(0,6);
    if (s == "ATOM  ") {
        recordType = Atom::RECORD_ATOM;
    } else {
        recordType = Atom::RECORD_HEATM;
    }

    // helper: stringstream
    std::istringstream sstream;

    // atomNumber
    auto atomNumber {0};
    s = line.substr(6,5);
    sstream.str(s);
    sstream.clear();
    sstream >> atomNumber;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown atom number in line (" << numLine << ")" << std::endl;
        return false;
    }

    // atomName
    std::string atomName;
    atomName = line.substr(12,4);

    // alternateLocation
    auto alternateLocation {'x'};
    alternateLocation = line[16];

    // residueName
    std::string residueName;
    residueName = line.substr(17,3);

    // chainID
    auto chainId {'x'};
    chainId = line[21];

    // residueNumber
    auto residueNumber {0};
    s = line.substr(22,4);
    sstream.str(s);
    sstream.clear();
    sstream >> residueNumber;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown residue number in line (" << numLine << ")" << std::endl;
        return false;
    }

    // iCode
    auto iCode {'x'};
    iCode = line[26];

    // Coordinates
    auto coordX {0.0}, coordY {0.0}, coordZ {0.0};
    s = line.substr(30,24);
    sstream.str(s);
    sstream.clear();
    sstream >> coordX >> coordY >> coordZ;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown coordinates in line (" << numLine << ")" << std::endl;
        return false;
    }

    // isOccupancy
    auto occupancy {0.0};
    auto isOccupancy {false};
    if (line.length() >= 60){
        s = line.substr(54,6);
        sstream.str(s);
        sstream.clear();
        sstream >> occupancy;
        if (!sstream.fail())
            isOccupancy = true;
    }

    // tempFactor
    auto tempFactor {0.0};
    auto isTempFactor {false};
    if (line.length() >= 66){
        s = line.substr(60,6);
        sstream.str(s);
        sstream.clear();
        sstream >> tempFactor;
        if (!sstream.fail())
            isTempFactor = true;
    }

    // elementName
    std::string elementName;
    if (line.length() >= 78){
        elementName = line.substr(76,2);
    }

    // formalCharge
    std::string formalCharge;
    if (line.length() >= 80){
        formalCharge = line.substr(78,2);
    }

    atoms.emplace_back( recordType, atomNumber, atomName, alternateLocation,\
                        residueName, chainId, residueNumber, iCode, coordX,\
                        coordY, coordZ, occupancy, tempFactor, elementName,\
                        formalCharge, isOccupancy, isTempFactor );

    return true;
}

//------------------------------------------------------------------------------

void PdbFile::parseResidues(void)
{
    const auto atomsSize {static_cast<int>(atoms.size())};      // atoms vector size
    auto firstAtom {0};                                         // index of the first atom in a residue
    auto columnNumber {0};                                      // start column number
    auto xPos {GraphicWidget::xStartPosition};                  // start position of the first residue
    auto yPos {GraphicWidget::yStartPosition};                  // start position of the first residue
    auto columnPerRow {GraphicWidget::columnPerRow};            // number of columns in each row
    auto spaceBetweenRows {GraphicWidget::spaceBetweenRows};    // space between rows
    auto rectHeight {GraphicWidget::rectHeight};                // rectangle height
    auto rectWidth {GraphicWidget::rectWidth};                  // rectangle width

    for(auto i {0}; i < atomsSize - 1; ++i) {

        // distinguish between two different residue
        if ( atoms[i].getResidueNumber() != atoms[i+1].getResidueNumber() ){

            residues.emplace_back( firstAtom, i, atoms[i].getResidueName(), atoms[i].getResidueNumber(), xPos, yPos );

            firstAtom = i + 1;

            // check column and set xPos, yPos
            if ( columnNumber == columnPerRow ){
                yPos = yPos + rectHeight + spaceBetweenRows;   // 8 = space between rows
                xPos = xPos - (columnPerRow * rectWidth);
                columnNumber = 0;
            } else {
                xPos = xPos + rectWidth;
                ++columnNumber;
            }
        }

        if ( i + 2 == atomsSize ){

            residues.emplace_back( firstAtom, i+1, atoms[i+1].getResidueName(), atoms[i+1].getResidueNumber(), xPos, yPos );
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

    residues.clear();
}
