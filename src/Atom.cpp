#include <iostream>
#include "Atom.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Atom::Atom(int argRecordType, int argAtomNumber, const std::string& argAtomName, char argAlternateLocation,\
           const std::string& argResidueName, char argChainId, int argResidueNumber, char argICode, double argCoordX,\
           double argCoordY, double argCoordZ, double argOccupancy, double argTempFactor, const std::string& argElementName,\
           const std::string& argFormalCharge, bool argIsOccupancy, bool argIsTempFactor)

     :recordType {argRecordType},
      atomNumber {argAtomNumber},
      atomName {argAtomName},
      alternateLocation {argAlternateLocation},
      residueName {argResidueName},
      chainId {argChainId},
      residueNumber {argResidueNumber},
      iCode {argICode},
      coordX {argCoordX},
      coordY {argCoordY},
      coordZ {argCoordZ},
      occupancy {argOccupancy},
      tempFactor {argTempFactor},
      elementName {argElementName},
      formalCharge {argFormalCharge},
      isOccupancy {argIsOccupancy},
      isTempFactor {argIsTempFactor}
{
}

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
//---PRINT----------------------------------------------------------------------
//==============================================================================

void Atom::print(void) const
{
    std::cout << "Atom number: " << atomNumber <<\
                 " atom name: " << atomName <<\
                 " coordinates: x=" << coordX <<\
                 " y=" << coordY <<\
                 " z=" << coordZ <<\
                 " element name: " << elementName <<\
                 std::endl;
}
