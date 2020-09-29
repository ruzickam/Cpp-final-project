#ifndef RESIDUE_H
#define RESIDUE_H

#include <string>
#include <tuple>

class Residue
{
public:
    // constructors

    // setters
    void setValues(int argAtomFirst, int argAtomLast, const std::string& argResidueName, int argResidueNumber, double argPosX, double argPosY);

    // getters
    int getAtomFirst(void) const;
    int getAtomLast(void) const;
    std::string getResidueName(void) const;
    int getResidueNumber(void) const;
    char getResidueChar(void) const;
    std::tuple<int, int, int> getColorRgb(void) const;
    double getPosX(void) const;
    double getPosY(void) const;
    int getAtomsCount(void) const;

    // prints
    void print(void) const;

private:
    // residue data
    int atomFirst {0};
    int atomLast {0};
    std::string residueName {"   "};
    int residueNumber {0};

    // residue rectangle position
    double posX {0.0};
    double posY {0.0};
};

#endif // RESIDUE_H
