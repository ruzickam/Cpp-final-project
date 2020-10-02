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

    // record types
    static constexpr auto RECORD_UNKNOWN {0};
    static constexpr auto RECORD_ATOM {1};
    static constexpr auto RECORD_HEATM {2};

    // print
    void print(void) const;

    // atom data
    int recordType;
    int atomNumber;
    std::string atomName;
    char alternateLocation;
    std::string residueName;
    char chainId;
    int residueNumber;
    char iCode;
    double coordX;
    double coordY;
    double coordZ;
    double occupancy;
    double tempFactor;
    std::string elementName;
    std::string formalCharge;
    bool isOccupancy;
    bool isTempFactor;
};

#endif // ATOM_H
