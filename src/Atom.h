#ifndef ATOM_H
#define ATOM_H

#include <string>

class Atom
{
public:
    // record types
    static constexpr int RECORD_UNKNOW = 0;
    static constexpr int RECORD_ATOM = 1;
    static constexpr int RECORD_HEATM = 2;

    // constructor
    Atom();

    // getters
    int getResidueNumber(void) const;
    std::string getResidueName(void) const;

    // manipulation methods
    bool readLine(const std::string& line, int numLine);
    bool writeLine(std::ofstream ofile) const;
    bool print(void) const;

private:
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
