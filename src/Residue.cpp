#include <iostream>
#include "Residue.h"

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

bool Residue::setResidueName(const std::string& argResidueName)
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

std::string Residue::getResidueName(void) const
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

std::tuple<int, int, int> Residue::getColorRgb(void) const
{
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
    std::cout << "Residue number: " << residueNumber << ", residue name: " << residueName << std::endl;
    return(true);
}

