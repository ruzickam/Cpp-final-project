#include <iostream>
#include <sstream>
#include "Atom.h"

//==============================================================================
//---GETTERS--------------------------------------------------------------------
//==============================================================================

int Atom::getResidueNumber(void) const
{
    return residueNumber;
}

//------------------------------------------------------------------------------

std::string Atom::getResidueName(void) const
{
    return residueName;
}

//==============================================================================
//---SETTERS--------------------------------------------------------------------
//==============================================================================

bool Atom::setValues(const std::string& line, int numLine)
{
    // helper string, stringstream
    std::string s;
    std::istringstream sstream;

    // Line must have at least 53 chars to obtain all neccesary values
    if ( line.length() < 53 ){
        std::cout << "Warning: the line (" << numLine << ") is too short" << std::endl;
        return false;
    }

    // recordType
    std::string recordName;
    recordName = line.substr(0,6);
    if (recordName == "ATOM  ")
        recordType = RECORD_ATOM;
    else if (recordName == "HETATM")
        recordType = RECORD_HEATM;
    else {
        std::cout << "Warning: unknown record name in line (" << numLine << ")" << std::endl;
        return false;    // cant continue
    }

    // atomNumber
    s = line.substr(6,5);
    sstream.str(s);
    sstream.clear();
    sstream >> atomNumber;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown atom number in line (" << numLine << ")" << std::endl;
        return false;
    }

    // atomName
    atomName = line.substr(12,4);

    // alternateLocation
    alternateLocation = line[16];

    // residueName
    residueName = line.substr(17,3);

    // chainID
    chainId = line[21];

    // residueNumber
    s = line.substr(22,4);
    sstream.str(s);
    sstream.clear();
    sstream >> residueNumber;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown residue number in line (" << numLine << ")" << std::endl;
        return false;
    }

    // iCode
    iCode = line[26];

    // Coordinates
    s = line.substr(30,24);
    sstream.str(s);
    sstream.clear();
    sstream >> coordX >> coordY >> coordZ;
    if ( sstream.fail() ){
        std::cout << "Warning: unknown coordinates in line (" << numLine << ")" << std::endl;
        return false;
    }

    // isOccupancy
    if (line.length() >= 60){
        s = line.substr(54,6);
        sstream.str(s);
        sstream.clear();
        sstream >> occupancy;
        if (!sstream.fail())
            isOccupancy = true;
    }

    // tempFactor
    if (line.length() >= 66){
        s = line.substr(60,6);
        sstream.str(s);
        sstream.clear();
        sstream >> tempFactor;
        if (!sstream.fail())
            isTempFactor = true;
    }

    // elementName
    if (line.length() >= 78){
        elementName = line.substr(76,2);
    }

    // formalCharge
    if (line.length() >= 80){
        formalCharge = line.substr(78,2);
    }

    return true;
}

//==============================================================================
//---PRINT----------------------------------------------------------------------
//==============================================================================

void Atom::print(void) const
{
    std::cout << "Atom number: " << atomNumber <<\
                 " atom name: " << atomName <<\
                 " coordinates: x=" << coordX << " y=" << coordY << " z=" << coordZ <<\
                 " element name: " << elementName <<\
                 std::endl;
}
