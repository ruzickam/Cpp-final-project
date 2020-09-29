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

    // open and read PDB file
    bool readFile(const QString& dialogFileName);

    // getters
    QString getFileName(void) const;
    Residue getResidue(int index) const;
    int getResiduesSize(void) const;

private:
    // HELPER METHODS

    // open
    bool openFile(std::ifstream& ifile);

    // read
    void readLine(std::ifstream& ifile, int& numLine);

    // set
    void setResidues(void);

    // write

    // print
    void printFileName(void) const;

    // clear
    void clearVectors(void);

    // ----------------------------------------------

    // DATA

    // PDB file name
    QString fileName {"No file"};

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>    residues;
};

#endif // PDBFILE_H
