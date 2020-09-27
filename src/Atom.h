#ifndef ATOM_H
#define ATOM_H

#include <string>

class Atom
{
public:
    // record types
    static constexpr int RECORD_UNKNOWN {0};
    static constexpr int RECORD_ATOM {1};
    static constexpr int RECORD_HEATM {2};

    // getters
    int getResidueNumber(void) const;
    std::string getResidueName(void) const;

    // manipulation methods
    bool readLine(const std::string& line, int numLine);
    bool writeLine(std::ofstream ofile) const;
    bool print(void) const;

private:
    // atom data
    int recordType {RECORD_UNKNOWN};
    int atomNumber {0};
    std::string atomName {"    "};
    char alternateLocation {' '};
    std::string residueName {"   "};
    char chainId {' '};
    int residueNumber {0};
    char iCode {' '};
    double coordX {0.0};
    double coordY {0.0};
    double coordZ {0.0};
    double occupancy {0.0};
    double tempFactor {0.0};
    std::string elementName {"  "};
    std::string formalCharge {"  "};
    bool isOccupancy {false};
    bool isTempFactor {false};
};

#endif // ATOM_H
