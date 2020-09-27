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

tuple<int, int, int> Residue::getColorRgb(void) const
{
    if ( residueName == "ALA" ){
	return  make_tuple(204, 255, 255);

    } else if ( residueName == "ARG" ){
	return  make_tuple(230, 6, 6);

    } else if ( residueName == "ASN" ){
	return  make_tuple(255, 153, 0);

    } else if ( residueName == "ASP" ){
	return  make_tuple(255, 204, 153);

    } else if ( residueName == "CYS" ){
	return  make_tuple(0, 255, 255);

    } else if ( residueName == "GLN" ){
	return  make_tuple(255, 102, 0);

    } else if ( residueName == "GLU" ){
	return  make_tuple(255, 102, 0);

    } else if ( residueName == "GLY" ){
	return  make_tuple(0, 255, 0);

    } else if ( residueName == "HIS" ){
	return  make_tuple(255, 255, 153);

    } else if ( residueName == "ILE" ){
	return  make_tuple(0, 0, 128);

    } else if ( residueName == "LEU" ){
	return  make_tuple(51, 102, 255);

    } else if ( residueName == "LYS" ){
	return  make_tuple(198, 6, 0);

    } else if ( residueName == "MET" ){
	return  make_tuple(153, 204, 255);

    } else if ( residueName == "PHE" ){
	return  make_tuple(0, 204, 255);

    } else if ( residueName == "PRO" ){
	return  make_tuple(255, 255, 0);

    } else if ( residueName == "SER" ){
	return  make_tuple(204, 255, 153);

    } else if ( residueName == "THR" ){
	return  make_tuple(0, 255, 153);

    } else if ( residueName == "TRP" ){
	return  make_tuple(204, 153, 255);

    } else if ( residueName == "TYR" ){
	return  make_tuple(204, 255, 204);

    } else if ( residueName == "VAL" ){
	return  make_tuple(0, 0, 255);

    } else {
	// default grey color
        return  make_tuple(153, 153, 153);
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
    //cout << "Residue number: " << residueNumber << ", residue name: " << residueName << endl;
    return(true);
}

