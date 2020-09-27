#ifndef RESIDUE_H
#define RESIDUE_H

#include <string>
#include <tuple>

class Residue
{
public:  
    // constructors
    Residue();
    Residue(int argAtomFirst, int argAtomLast, const std::string& argResidueName, int argResidueNumber);

    // setters
    bool setAtomFirst(int argAtomFirst);
    bool setAtomLast(int argAtomLast);
    bool setResidueName(const std::string& argResidueName);
    bool setResidueNumber(int argResidueNumber);
    bool setPosXY(double argX, double argY);

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

    // manipulation methods
    bool print(void) const;

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
