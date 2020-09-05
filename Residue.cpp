#include <iostream>
#include "Residue.h"

using namespace std;

Residue::Residue()
{
    atomFirst = 0;
    atomLast = 0;
    residueName = "";
    residueNumber = 0;

    posX = 0.0;
    posY = 0.0;
}

Residue::Residue(int argAtomFirst, int argAtomLast, const string &argResidueName, int argResidueNumber)
{
    atomFirst = argAtomFirst;
    atomLast = argAtomLast;
    residueName = argResidueName;
    residueNumber = argResidueNumber;

    posX = 0.0;
    posY = 0.0;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// setters (returns 0 if successful)
bool Residue::setAtomFirst(int argAtomFirst)
{
    atomFirst = argAtomFirst;
    return(true);
}

bool Residue::setAtomLast(int argAtomLast)
{
    atomLast = argAtomLast;
    return(true);
}

bool Residue::setResidueName(const string &argResidueName)
{
    residueName = argResidueName;
    return(true);
}

bool Residue::setResidueNumber(int argResidueNumber)
{
    residueNumber = argResidueNumber;
    return(true);
}

bool Residue::setPosXY(double argX, double argY)
{
    posX = argX;
    posY = argY;
    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// getters
int Residue::getAtomFirst(void) const
{
    return( atomFirst );
}

int Residue::getAtomLast(void) const
{
    return( atomLast );
}

string Residue::getResidueName(void) const
{
    return( residueName );
}

int Residue::getResidueNumber(void) const
{
    return( residueNumber );
}

char Residue::getResidueChar(void) const
{
    if ( residueName == "ALA" ){
        return( 'A' );
    }
    if ( residueName == "ARG" ){
        return( 'R' );
    }
    if ( residueName == "ASN" ){
        return( 'N' );
    }
    if ( residueName == "ASP" ){
        return( 'D' );
    }
    if ( residueName == "CYS" ){
        return( 'C' );
    }
    if ( residueName == "GLN" ){
        return( 'Q' );
    }
    if ( residueName == "GLU" ){
        return( 'E' );
    }
    if ( residueName == "GLY" ){
        return( 'G' );
    }
    if ( residueName == "HIS" ){
        return( 'H' );
    }
    if ( residueName == "ILE" ){
        return( 'I' );
    }
    if ( residueName == "LEU" ){
        return( 'L' );
    }
    if ( residueName == "LYS" ){
        return( 'K' );
    }
    if ( residueName == "MET" ){
        return( 'M' );
    }
    if ( residueName == "PHE" ){
        return( 'F' );
    }
    if ( residueName == "PRO" ){
        return( 'P' );
    }
    if ( residueName == "SER" ){
        return( 'S' );
    }
    if ( residueName == "THR" ){
        return( 'T' );
    }
    if ( residueName == "TRP" ){
        return( 'W' );
    }
    if ( residueName == "TYR" ){
        return( 'Y' );
    }
    if ( residueName == "VAL" ){
        return( 'V' );
    }
    return( 'X' );
}

void Residue::getColorRgb(int* r, int* g, int* b) const
{
    // default grey color
    *r = 153;
    *g = 153;
    *b = 153;

    if ( residueName == "ALA" ){
        *r = 204;
        *g = 255;
        *b = 255;
    }
    if ( residueName == "ARG" ){
        *r = 230;
        *g = 6;
        *b = 6;
    }
    if ( residueName == "ASN" ){
        *r = 255;
        *g = 153;
        *b = 0;
    }
    if ( residueName == "ASP" ){
        *r = 255;
        *g = 204;
        *b = 153;
    }
    if ( residueName == "CYS" ){
        *r = 0;
        *g = 255;
        *b = 255;
    }
    if ( residueName == "GLN" ){
        *r = 255;
        *g = 102;
        *b = 0;
    }
    if ( residueName == "GLU" ){
        *r = 255;
        *g = 204;
        *b = 0;
    }
    if ( residueName == "GLY" ){
        *r = 0;
        *g = 255;
        *b = 0;
    }
    if ( residueName == "HIS" ){
        *r = 255;
        *g = 255;
        *b = 153;
    }
    if ( residueName == "ILE" ){
        *r = 0;
        *g = 0;
        *b = 128;
    }
    if ( residueName == "LEU" ){
        *r = 51;
        *g = 102;
        *b = 255;
    }
    if ( residueName == "LYS" ){
        *r = 198;
        *g = 6;
        *b = 0;
    }
    if ( residueName == "MET" ){
        *r = 153;
        *g = 204;
        *b = 255;
    }
    if ( residueName == "PHE" ){
        *r = 0;
        *g = 204;
        *b = 255;
    }
    if ( residueName == "PRO" ){
        *r = 255;
        *g = 255;
        *b = 0;
    }
    if ( residueName == "SER" ){
        *r = 204;
        *g = 255;
        *b = 153;
    }
    if ( residueName == "THR" ){
        *r = 0;
        *g = 255;
        *b = 153;
    }
    if ( residueName == "TRP" ){
        *r = 204;
        *g = 153;
        *b = 255;
    }
    if ( residueName == "TYR" ){
        *r = 204;
        *g = 255;
        *b = 204;
    }
    if ( residueName == "VAL" ){
        *r = 0;
        *g = 0;
        *b = 255;
    }
}

double Residue::getPosX(void) const
{
    return( posX );
}

double Residue::getPosY(void) const
{
    return( posY );
}

int Residue::getAtomsCount(void) const
{
    return( atomLast - atomFirst );
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool Residue::print(void) const
{
    cout << "Residue number: " << residueNumber << ", residue name: " << residueName << endl;
    return(true);
}

