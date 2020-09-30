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
            int argResidueNumber, double argPosX, double argPosY,\
            int argColorR, int argColorG, int argColorB, char argResidueChar);

    // getters
    int getAtomFirst(void) const;
    int getAtomLast(void) const;
    std::string getResidueName(void) const;
    int getResidueNumber(void) const;
    std::tuple<double, double> getposXposY(void) const;
    std::tuple<int, int, int> getcolorRGB(void) const;
    char getResidueChar(void) const;
    std::tuple<std::string, int, int> getNameNumberCount(void) const;

    // prints
    void print(void) const;

private:
    // residue data
    int atomFirst;
    int atomLast;
    std::string residueName;
    int residueNumber;
    double posX;
    double posY;
    int colorR;
    int colorG;
    int colorB;
    char residueChar;
};

#endif // RESIDUE_H
