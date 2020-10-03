#ifndef RESIDUE_H
#define RESIDUE_H

#include <string>

struct Residue
{
    // constructors
    Residue() = delete;
    Residue(int argNumOfAtoms, const std::string& argResidueName,\
            int argResidueNumber, double argPosX, double argPosY,\
            int argColorR, int argColorG, int argColorB, char argResidueChar);

    // prints
    void print(void) const;

    // unknown residue data
    static constexpr int unknownColorR {153};
    static constexpr int unknownColorG {153};
    static constexpr int unknownColorB {153};
    static constexpr char unknownResidueChar {'X'};

    // residue data
    const int numOfAtoms;
    const std::string residueName;
    const int residueNumber;
    const double posX;
    const double posY;
    const int colorR;
    const int colorG;
    const int colorB;
    const char residueChar;
};

// for std::set
bool operator< ( const Residue& a, const Residue& b );

#endif // RESIDUE_H
