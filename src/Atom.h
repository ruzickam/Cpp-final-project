#ifndef ATOM_H
#define ATOM_H

#include <string>

struct Atom
{
    // constructors
    Atom() = delete;
    Atom(int argRecordType, int argAtomNumber, const std::string& argAtomName, char argAlternateLocation,\
         const std::string& argResidueName, char argChainId, int argResidueNumber, char argICode, double argCoordX,\
         double argCoordY, double argCoordZ, double argOccupancy, double argTempFactor, const std::string& argElementName,\
         const std::string& argFormalCharge, bool argIsOccupancy, bool argIsTempFactor);

    // print
    void print(void) const;

    // record types
    static constexpr int unknownRecord {0};
    static constexpr int atomRecord {1};
    static constexpr int hetatmRecord {2};

    // atom data
    const int recordType;
    const int atomNumber;
    const std::string atomName;
    const char alternateLocation;
    const std::string residueName;
    const char chainId;
    const int residueNumber;
    const char iCode;
    const double coordX;
    const double coordY;
    const double coordZ;
    const double occupancy;
    const double tempFactor;
    const std::string elementName;
    const std::string formalCharge;
    const bool isOccupancy;
    const bool isTempFactor;
};

#endif // ATOM_H
