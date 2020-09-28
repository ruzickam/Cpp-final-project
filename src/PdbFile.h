#ifndef PDBFILE_H
#define PDBFILE_H

#include <vector>
#include <fstream>
#include <string>
#include <QString>
#include "Atom.h"
#include "Residue.h"

class PdbFile
{
public:
    // open & read PDB file
    bool readPdbFile(void);

    // set residues
    bool setResidues(void);

private:
    // HELPER METHODS

    bool readLine(const std::string& line, int numLine);
    bool writeLine(std::ofstream ofile) const;
    void emplaceResidue(int atomsId, int firstAtom);

    // ----------------------------------------------

    // DATA

    // PDB file name
    QString fileName {"No file"};

    // atom & residue containers
    std::vector<Atom>       atoms;
    std::vector<Residue>    residues;
};

#endif // PDBFILE_H
