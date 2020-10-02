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

    // residue data
    int numOfAtoms;
    std::string residueName;
    int residueNumber;
    double posX;
    double posY;
    int colorR;
    int colorG;
    int colorB;
    char residueChar;
};

// for std::set
bool operator< ( const Residue& a, const Residue& b );

#endif // RESIDUE_H
