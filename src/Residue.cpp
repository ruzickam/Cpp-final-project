#include <iostream>
#include "Residue.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Residue::Residue(int argAtomFirst, int argAtomLast, const std::string& argResidueName, int argResidueNumber, double argPosX, double argPosY)

     :atomFirst {argAtomFirst},
      atomLast {argAtomLast},
      residueName {argResidueName},
      residueNumber {argResidueNumber},
      posX {argPosX},
      posY {argPosY}
{
}

//==============================================================================
//---GETTERS--------------------------------------------------------------------
//==============================================================================

int Residue::getAtomFirst(void) const
{
    return atomFirst;
}

//------------------------------------------------------------------------------

int Residue::getAtomLast(void) const
{
    return atomLast;
}

//------------------------------------------------------------------------------

std::string Residue::getResidueName(void) const
{
    return residueName;
}

//------------------------------------------------------------------------------

int Residue::getResidueNumber(void) const
{
    return residueNumber;
}

//------------------------------------------------------------------------------

double Residue::getPosX(void) const
{
    return posX;
}

//------------------------------------------------------------------------------

double Residue::getPosY(void) const
{
    return posY;
}

//==============================================================================
//---PRINTS---------------------------------------------------------------------
//==============================================================================

void Residue::print(void) const
{
    std::cout << "Residue number: " << residueNumber << ", residue name: " << residueName << std::endl;
}

