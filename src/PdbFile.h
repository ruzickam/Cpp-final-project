#ifndef PDBFILE_H
#define PDBFILE_H

#include <vector>
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

    std::tuple<double, double> getResXY(int index) const;
    std::tuple<int, int, int> getResRgb(int index) const;
    char getResChar(int index) const;
    std::tuple<std::string, int, int> getResNameNumCount(int index) const;

private:
    // HELPER METHODS

    // open

    // read
    bool readLines(std::ifstream& ifile);

    // parse
    bool parseAtom(const std::string& line, int numLine);
    void parseResidues(void);

    // write

    // print
    void printFileName(void) const;

    // clear
    void clearVectors(void);

    // ----------------------------------------------
    // DATA

    // PDB file name
    QString fileName;

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>    residues;
};

#endif // PDBFILE_H
