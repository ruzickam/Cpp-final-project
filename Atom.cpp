#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Atom.h"

using namespace std;

Atom::Atom()
{
    recordType = RECORD_UNKNOW;
    atomNumber = 0;
    atomName = "    ";
    alternateLocation = ' ';
    residueName = "   ";
    chainId = ' ';
    residueNumber = 0;
    iCode = ' ';
    coordX = 0;
    coordY = 0;
    coordZ = 0;
    occupancy = 0;
    tempFactor = 0;
    elementName = "  ";
    formalCharge = "  ";
    isOccupancy = false;
    isTempFactor = false;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool Atom::readLine(const string &line, int numLine)
{
    string recordName;
    string s;
    istringstream sstream;

    // Line must have at least 53 chars to obtain all neccesary values
    if ( line.length() < 53 ){
        cout << "Warning: the line (" << numLine << ") is too short" << endl;
        return(false);
    }

    recordName = line.substr(0,6);
    if (recordName == "ATOM  ")
        recordType = RECORD_ATOM;
    else if (recordName == "HETATM")
        recordType = RECORD_HEATM;
    else {
        cout << "Warning: unknown record name in line (" << numLine << ")" << endl;
        return(false);    // cant continue
    }

    s = line.substr(6,5);
    sstream.str(s);
    sstream.clear();
    sstream >> atomNumber;
    if ( sstream.fail() ){
        cout << "Warning: error reading line (" << numLine << ")" << endl;
        return(false);
    }

    atomName = line.substr(12,4);

    alternateLocation = line[16];

    residueName = line.substr(17,3);

    chainId = line[21];

    s = line.substr(22,4);
    sstream.str(s);
    sstream.clear();
    sstream >> residueNumber;
    if ( sstream.fail() ){
        cout << "Warning: error reading line (" << numLine << ")" << endl;
        return(false);
    }

    iCode = line[26];

    s = line.substr(30,24);
    sstream.str(s);
    sstream.clear();
    sstream >> coordX >> coordY >> coordZ;
    if ( sstream.fail() ){
        cout << "Warning: error reading line (" << numLine << ")" << endl;
        return(false);
    }

    if (line.length() >= 60){
        s = line.substr(54,6);
        sstream.str(s);
        sstream.clear();
        sstream >> occupancy;
        if (!sstream.fail())
            isOccupancy = true;
    }

    if (line.length() >= 66){
        s = line.substr(60,6);
        sstream.str(s);
        sstream.clear();
        sstream >> tempFactor;
        if (!sstream.fail())
            isTempFactor = true;
    }

    if (line.length() >= 78){
        elementName = line.substr(76,2);
    }

    if (line.length() >= 80){
        formalCharge = line.substr(78,2);
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool Atom::writeLine(ofstream &ofile) const
{
    if ( recordType == RECORD_ATOM )
        ofile << "ATOM  ";
    else if ( recordType == RECORD_HEATM )
        ofile << "HETATM";
    else
        return(false);

    ofile << right << setw(5) << atomNumber;
    ofile << ' ';
    ofile << left << setw(4) << atomName;
    ofile << alternateLocation;
    ofile << left << setw(3) << residueName;
    ofile << ' ';
    ofile << chainId;
    ofile << right << setw(4) << residueNumber;
    ofile << iCode;
    ofile << "   ";
    ofile << right << fixed << setprecision(3);
    ofile << setw(8) << coordX;
    ofile << setw(8) << coordY;
    ofile << setw(8) << coordZ;
    if ( isOccupancy )
        ofile << right << fixed << setprecision(2) << setw(6) << occupancy;
    else
        ofile << "      ";
    if ( isTempFactor )
        ofile << right << fixed << setprecision(2) << setw(6) << tempFactor;
    else
        ofile << "      ";
    ofile << "          ";
    ofile << right << setw(2) << elementName;
    ofile << left << setw(2) << formalCharge;
    ofile << endl;

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// getters
int Atom::getResidueNumber(void) const
{
    return( residueNumber );
}

string Atom::getResidueName(void) const
{
    return( residueName );
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool Atom::print(void) const
{
    cout << "Atom number: " << atomNumber << " atom name: " << atomName << " coordinates: x=" << coordX << " y=" << coordY << " z=" << coordZ << " element name: " << elementName << endl;
    return(true);
}
