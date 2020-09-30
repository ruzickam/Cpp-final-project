#ifndef PDBFILE_H
#define PDBFILE_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <QString>
#include "Atom.h"
#include "Residue.h"

class PdbFile
{
public:
    // constructors
    PdbFile();

    // open and read PDB file
    bool readFile(const QString& dialogFileName);

    // getters
    QString getFileName(void) const;
    int getResSize(void) const;

    // getters for residues data
    std::tuple<double, double> getResXY(int index) const;
    std::tuple<int, int, int> getResRgb(int index) const;
    char getResChar(int index) const;
    std::tuple<std::string, int, int> getResNameNumCount(int index) const;

private:
    // HELPER METHODS

    // read
    bool readLines(std::ifstream& ifile);

    // parse
    bool parseAtom(const std::string& line, int numLine);
    void parseResidues(void);
    std::tuple<int, int, int, char> parseRGB_Char(const std::string& residueName) const;

    // print
    void printFileName(void) const;

    // clear
    void clearVectors(void);

    // ----------------------------------------------
    // DATA

    // map for rgb, resChar
    static const std::unordered_map<std::string,int> aminoacid_map;

    // PDB file name
    QString fileName;

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>    residues;
};

#endif // PDBFILE_H
