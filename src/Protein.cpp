#include <iostream>
#include <sstream>
#include "Protein.h"
#include "GraphicWidget.h"

//==============================================================================
//---MAP FOR SWITCH-------------------------------------------------------------
//==============================================================================

const std::unordered_map<std::string,int> Protein::aminoacidMap
{
    {"ALA",1},
    {"ARG",2},
    {"ASN",3},
    {"ASP",4},
    {"CYS",5},
    {"GLN",6},
    {"GLU",7},
    {"GLY",8},
    {"HIS",9},
    {"ILE",10},
    {"LEU",11},
    {"LYS",12},
    {"MET",13},
    {"PHE",14},
    {"PRO",15},
    {"SER",16},
    {"THR",17},
    {"TRP",18},
    {"TYR",19},
    {"VAL",20}
};

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Protein::Protein()
    :pdbFileName {"No file"}
{
}

//==============================================================================
//---OPEN AND READ PDB FILE-----------------------------------------------------
//==============================================================================

bool Protein::initFromPDBfile(const QString& dialogFileName)
{
    // check the file name from dialog
    if( dialogFileName.isEmpty() ){
        std::cout << "Warning: No file was selected!" << std::endl;
        return false;
    }

    // copy file name
    pdbFileName = dialogFileName;

    // print file name
    printPDBfileName();

    // clear all previous data
    clearData();

    // ---START: FILE MANIPULATION-------------------

    // file definition
    std::ifstream ifile;

    // open file
    ifile.open( pdbFileName.toLatin1().constData() );
    if( ifile.fail() ){
        std::cout << "ERROR: Unable to open the file!" << std::endl;
        return false;
    }
    std::cout << "Opening file..." << std::endl;

    // read lines
    if ( ! readPDBlines(ifile) )
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

QString Protein::getPDBfileName(void) const
{
    return pdbFileName;
}

//------------------------------------------------------------------------------

int Protein::getNumOfRes(void) const
{
    return static_cast<int>(residues.size());
}

//------------------------------------------------------------------------------

std::tuple<double, double> Protein::getResRectXY(int index) const
{
    return residues[index].getposXposY();
}

//------------------------------------------------------------------------------

std::tuple<int, int, int> Protein::getResColor(int index) const
{
    return residues[index].getcolorRGB();
}

//------------------------------------------------------------------------------

char Protein::getResChar(int index) const
{
    return residues[index].getResidueChar();
}

//------------------------------------------------------------------------------

std::tuple<std::string, int, int> Protein::getResBasicInfo(int index) const
{
    return residues[index].getNameNumberCount();
}

//==============================================================================
//---HELPER METHODS - READ------------------------------------------------------
//==============================================================================

bool Protein::readPDBlines(std::ifstream& ifile)
{
    // check if the file is opened
    if( ifile.fail() || ! ifile.is_open() ){
        std::cout << "ERROR: reading file failed!" << std::endl;
        return false;
    }

    // helper vars
    auto numLine {1};   // we must count number of lines
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
//---HELPER METHODS - PARSE-----------------------------------------------------
//==============================================================================

bool Protein::parseAtom(const std::string& line, int numLine)
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

void Protein::parseResidues(void)
{
    const auto atomsSize {static_cast<int>(atoms.size())};      // atoms vector size
    auto firstAtom {0};                                         // index of the first atom in a residue
    auto columnNumber {0};                                      // start column number
    auto colorR {153}, colorG {153}, colorB {153};              // residue color
    auto residueChar {'X'};                                     // res char

    // consts
    auto xPos {GraphicWidget::xStartPosition};                  // start position of the first residue
    auto yPos {GraphicWidget::yStartPosition};                  // start position of the first residue
    auto columnPerRow {GraphicWidget::columnPerRow};            // number of columns in each row
    auto spaceBetweenRows {GraphicWidget::spaceBetweenRows};    // space between rows
    auto rectHeight {GraphicWidget::rectHeight};                // rectangle height
    auto rectWidth {GraphicWidget::rectWidth};                  // rectangle width

    for(auto i {0}; i < atomsSize - 1; ++i) {

        // distinguish between two different residue
        if ( atoms[i].getResidueNumber() != atoms[i+1].getResidueNumber() ){

            std::tie(colorR, colorG, colorB, residueChar) = parseResColor_Char( atoms[i].getResidueName() );
            residues.emplace_back( firstAtom, i, atoms[i].getResidueName(), atoms[i].getResidueNumber(), xPos, yPos, colorR, colorG, colorB, residueChar );

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
            // the last atom
        if ( i + 2 == atomsSize ){

            std::tie(colorR, colorG, colorB, residueChar) = parseResColor_Char( atoms[i+1].getResidueName() );
            residues.emplace_back( firstAtom, i+1, atoms[i+1].getResidueName(), atoms[i+1].getResidueNumber(), xPos, yPos, colorR, colorG, colorB, residueChar );
        }
    }
}

//------------------------------------------------------------------------------

std::tuple<int, int, int, char> Protein::parseResColor_Char(const std::string& residueName) const
{
    switch(aminoacidMap.count(residueName) ? aminoacidMap.at(residueName) : 0) {
    case 1:
        return std::make_tuple(204, 255, 255, 'A');
    case 2:
        return std::make_tuple(230, 6, 6, 'R');
    case 3:
        return std::make_tuple(255, 153, 0, 'N');
    case 4:
        return std::make_tuple(255, 204, 153, 'D');
    case 5:
        return std::make_tuple(0, 255, 255, 'C');
    case 6:
        return std::make_tuple(255, 102, 0, 'Q');
    case 7:
        return std::make_tuple(255, 204, 0, 'E');
    case 8:
        return std::make_tuple(0, 255, 0, 'G');
    case 9:
        return std::make_tuple(255, 255, 153, 'H');
    case 10:
        return std::make_tuple(0, 0, 128, 'I');
    case 11:
        return std::make_tuple(51, 102, 255, 'L');
    case 12:
        return std::make_tuple(198, 6, 0, 'K');
    case 13:
        return std::make_tuple(153, 204, 255, 'M');
    case 14:
        return std::make_tuple(0, 204, 255, 'F');
    case 15:
        return std::make_tuple(255, 255, 0, 'P');
    case 16:
        return std::make_tuple(204, 255, 153, 'S');
    case 17:
        return std::make_tuple(0, 255, 153, 'T');
    case 18:
        return std::make_tuple(204, 153, 255, 'W');
    case 19:
        return std::make_tuple(204, 255, 204, 'Y');
    case 20:
        return std::make_tuple(0, 0, 255, 'V');
    case 0: //this is for the undefined case
        return std::make_tuple(153, 153, 153, 'X');
    }
}

//==============================================================================
//---HELPER METHODS - PRINT-----------------------------------------------------
//==============================================================================

void Protein::printPDBfileName(void) const
{
    std::cout << "File name: " << pdbFileName.toLatin1().constData() << std::endl;
}

//==============================================================================
//---HELPER METHODS - CLEAR-----------------------------------------------------
//==============================================================================

void Protein::clearData(void)
{
    atoms.clear();

    residues.clear();
}
