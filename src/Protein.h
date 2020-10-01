#ifndef PDBFILE_H
#define PDBFILE_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <QString>
#include "Atom.h"
#include "Residue.h"

class Protein
{
public:
    // constructors
    Protein();

    // open and read PDB file
    bool initFromPDBfile(const QString& dialogFileName);

    // getters
    QString getPDBfileName(void) const;
    int getNumOfRes(void) const;

    // getters for residues data
    std::tuple<double, double> getResRectXY(int index) const;
    std::tuple<int, int, int> getResColor(int index) const;
    char getResChar(int index) const;
    std::tuple<std::string, int, int> getResBasicInfo(int index) const; // residueName, residueNumber, atomsCount

private:
    // HELPER METHODS

    // read
    bool readPDBlines(std::ifstream& ifile);

    // parse
    bool parseAtom(const std::string& line, int numLine);
    void parseResidues(void);
    std::tuple<int, int, int, char> parseResColor_Char(const std::string& residueName) const;

    // print
    void printPDBfileName(void) const;

    // clear
    void clearData(void);

    // ----------------------------------------------
    // DATA

    // map for rgb, resChar
    static const std::unordered_map<std::string,int> aminoacidMap;

    // PDB file name
    QString pdbFileName;

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>    residues;
};

#endif // PDBFILE_H
