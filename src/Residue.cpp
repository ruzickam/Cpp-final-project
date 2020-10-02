#include <iostream>
#include "Residue.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Residue::Residue(int argNumOfAtoms, const std::string& argResidueName, int argResidueNumber, \
                 double argPosX, double argPosY, int argColorR, int argColorG, int argColorB, char argResidueChar)

     :numOfAtoms {argNumOfAtoms},
      residueName {argResidueName},
      residueNumber {argResidueNumber},
      posX {argPosX},
      posY {argPosY},
      colorR {argColorR},
      colorG {argColorG},
      colorB {argColorB},
      residueChar {argResidueChar}
{
}

//==============================================================================
//---PRINTS---------------------------------------------------------------------
//==============================================================================

void Residue::print(void) const
{
    std::cout << "Residue number: " << residueNumber << ", residue name: " << residueName << std::endl;
}

//==============================================================================
//---OPERATOR OVERLOADING-------------------------------------------------------
//==============================================================================

// compare two Residue
bool operator< ( const Residue& a, const Residue& b )
{
    return a.residueName < b.residueName;
}
