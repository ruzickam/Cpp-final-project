#ifndef ATOM_H
#define ATOM_H

#include <string>

class Atom
{
public:
    // constructors

    // getters
    int getResidueNumber(void) const;
    std::string getResidueName(void) const;

    // manipulation methods
    bool print(void) const;

private:
    // record types
    static constexpr auto RECORD_UNKNOWN {0};
    static constexpr auto RECORD_ATOM {1};
    static constexpr auto RECORD_HEATM {2};

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
