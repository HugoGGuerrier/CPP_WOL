#ifndef CPP_WOL_VIRTUALMACHINE_H
#define CPP_WOL_VIRTUALMACHINE_H

#include <iostream>
#include <fstream>

/**
 * This class represent the WOL interpreter that contains all parsed files, variables, heap and stack
 */
class VirtualMachine {
private:

    // ----- Attributes -----

    // ----- Internal methods -----

public:

    // ----- Constructors -----

    /**
     * Init the interpreter with a WOL file
     *
     * @param initialFile
     */
    VirtualMachine(std::ifstream initialFile);

    /**
     * Create an empty interpreter
     */
    VirtualMachine();

    // ----- Getters -----

    // ----- Setters -----

    // ----- Class methods -----

};


#endif // CPP_WOL_VIRTUALMACHINE_H
