#ifndef RESIDUE_H
#define RESIDUE_H

#include <string>
#include <tuple>

class Residue
{
public:
    // constructors
    Residue() = delete;
    Residue(int argAtomFirst, int argAtomLast, const std::string& argResidueName,\
            int argResidueNumber, double argPosX, double argPosY);

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
    int atomFirst;
    int atomLast;
    std::string residueName;
    int residueNumber;

    // residue rectangle position
    double posX;
    double posY;
};

#endif // RESIDUE_H
