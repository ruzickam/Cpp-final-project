#include <iostream>
#include <sstream>
#include "Protein.h"
#include "GraphicWidget.h"

//==============================================================================
//---AMINOACID TEMPLATES INIT---------------------------------------------------
//==============================================================================

const std::set<Residue> Protein::residueTemplates = {

    {0,"ALA",1,0.0,0.0,204, 255, 255, 'A'},
    {0,"ARG",2,0.0,0.0,230, 6, 6, 'R'},
    {0,"ASN",3,0.0,0.0,255, 153, 0, 'N'},
    {0,"ASP",4,0.0,0.0,255, 204, 153, 'D'},
    {0,"CYS",5,0.0,0.0,0, 255, 255, 'C'},
    {0,"GLN",6,0.0,0.0,255, 102, 0, 'Q'},
    {0,"GLU",7,0.0,0.0,255, 204, 0, 'E'},
    {0,"GLY",8,0.0,0.0,0, 255, 0, 'G'},
    {0,"HIS",9,0.0,0.0,255, 255, 153, 'H'},
    {0,"ILE",10,0.0,0.0,0, 0, 128, 'I'},
    {0,"LEU",11,0.0,0.0,51, 102, 255, 'L'},
    {0,"LYS",12,0.0,0.0,198, 6, 0, 'K'},
    {0,"MET",13,0.0,0.0,153, 204, 255, 'M'},
    {0,"PHE",14,0.0,0.0,0, 204, 255, 'F'},
    {0,"PRO",15,0.0,0.0,255, 255, 0, 'P'},
    {0,"SER",16,0.0,0.0,204, 255, 153, 'S'},
    {0,"THR",17,0.0,0.0,0, 255, 153, 'T'},
    {0,"TRP",18,0.0,0.0,204, 153, 255, 'W'},
    {0,"TYR",19,0.0,0.0,204, 255, 204, 'Y'},
    {0,"VAL",20,0.0,0.0,0, 0, 255, 'V'}
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
    return std::make_tuple(residues[index].posX,\
                           residues[index].posY);
}

//------------------------------------------------------------------------------

std::tuple<int, int, int> Protein::getResColor(int index) const
{
    return std::make_tuple(residues[index].colorR,\
                           residues[index].colorG,\
                           residues[index].colorB);
}

//------------------------------------------------------------------------------

char Protein::getResChar(int index) const
{
    return residues[index].residueChar;
}

//------------------------------------------------------------------------------

std::tuple<std::string, int, int> Protein::getResNameNumberAnumber(int index) const
{
    return std::make_tuple(residues[index].residueName,\
                           residues[index].residueNumber,\
                           residues[index].numOfAtoms );
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

    auto xPos {GraphicWidget::xStartPosition};                  // start position of the first residue
    auto yPos {GraphicWidget::yStartPosition};                  // start position of the first residue

    for(auto i {0}; i < atomsSize - 1; ++i) {

        auto colorR {153}, colorG {153}, colorB {153};              // residue color
        auto residueChar {'X'};                                     // res char

        auto columnPerRow {GraphicWidget::columnPerRow};            // number of columns in each row
        auto spaceBetweenRows {GraphicWidget::spaceBetweenRows};    // space between rows
        auto rectHeight {GraphicWidget::rectHeight};                // rectangle height
        auto rectWidth {GraphicWidget::rectWidth};                  // rectangle width

        // distinguish between two different residue
        if ( atoms[i].residueNumber != atoms[i+1].residueNumber ){

            std::tie(colorR, colorG, colorB, residueChar) = parseResColor_Char( atoms[i].residueName );
            residues.emplace_back( i - firstAtom + 1 , atoms[i].residueName, atoms[i].residueNumber, xPos, yPos, colorR, colorG, colorB, residueChar );

            firstAtom = i + 1;

            // check column and set xPos, yPos
            if ( columnNumber == columnPerRow ){
                yPos = yPos + rectHeight + spaceBetweenRows;
                xPos = xPos - (columnPerRow * rectWidth);
                columnNumber = 0;
            } else {
                xPos = xPos + rectWidth;
                ++columnNumber;
            }
        }
            // the last residue to be added
        if ( i + 2 == atomsSize ){

            std::tie(colorR, colorG, colorB, residueChar) = parseResColor_Char( atoms[i+1].residueName );
            residues.emplace_back( i - firstAtom + 2, atoms[i+1].residueName, atoms[i+1].residueNumber, xPos, yPos, colorR, colorG, colorB, residueChar );
        }
    }
}

//------------------------------------------------------------------------------

std::tuple<int, int, int, char> Protein::parseResColor_Char(const std::string& residueName) const
{
    const auto iter = residueTemplates.find( {0,residueName,0,0.0,0.0,0,0,0,'X'} );

    if( iter != residueTemplates.end() ){ // if aminoacid is found
        return std::make_tuple(iter->colorR, iter->colorG, iter->colorB, iter->residueChar);
    } else { // unknown residue
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
