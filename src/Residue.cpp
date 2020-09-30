#include <iostream>
#include "Residue.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Residue::Residue(int argAtomFirst, int argAtomLast, const std::string& argResidueName, int argResidueNumber,\
                 double argPosX, double argPosY, int argColorR, int argColorG, int argColorB, char argResidueChar)

     :atomFirst {argAtomFirst},
      atomLast {argAtomLast},
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

std::tuple<double, double> Residue::getposXposY(void) const
{
    return std::make_tuple(posX, posY);
}

//------------------------------------------------------------------------------

std::tuple<int, int, int> Residue::getcolorRGB(void) const
{
    return std::make_tuple(colorR, colorG, colorB);
}

//------------------------------------------------------------------------------

char Residue::getResidueChar(void) const
{
    return residueChar;
}

//------------------------------------------------------------------------------

std::tuple<std::string, int, int> Residue::getNameNumberCount(void) const
{
    return std::make_tuple(residueName,\
                           residueNumber,\
                           atomLast - atomFirst + 1);
}

//==============================================================================
//---PRINTS---------------------------------------------------------------------
//==============================================================================

void Residue::print(void) const
{
    std::cout << "Residue number: " << residueNumber << ", residue name: " << residueName << std::endl;
}

