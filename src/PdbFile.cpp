//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// HELPER METHODS

void GraphicWidget::emplaceResidue(int atomsId, int firstAtom){

    residues.emplace_back();

    residues.back().setResidueNumber(atoms[atomsId].getResidueNumber());
    residues.back().setResidueName(atoms[atomsId].getResidueName());

    residues.back().setAtomLast(atomsId);
    residues.back().setAtomFirst(firstAtom);
}
