#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

std::vector<std::string> symbolNameVector;
std::vector<std::string> symbolRegexVector;

/**
 * Function to use to parse the lex file and fill the vectors
 *
 * @param lexFile The file to parse
 */
void parseLexFile(std::ifstream &lexFile) {
    // Prepare the line reading and counter
    std::string line;

    while(std::getline(lexFile, line)) {
        // Get the token definition
        int delimiterPosition = line.find(':');

        if(delimiterPosition != -1) {
            std::string tokenName = line.substr(0, delimiterPosition);
            std::string tokenRegex = line.substr(delimiterPosition + 1, line.length());

            // Place the token definition in the wanted vectors
            symbolNameVector.emplace_back(tokenName);
            symbolRegexVector.emplace_back(tokenRegex);
        }
    }
}

/**
 * Function to export the lexical environment in the CPP format to
 *
 * @param exportDirectory The directory where you want to export the lexenv
 * @return If the export worked
 */
int exportLexEnv(const std::string & exportDirectory) {
    // Open the two export files
    std::ofstream cppExport;
    std::ofstream hExport;
    cppExport.open(exportDirectory + "/Lexenv.cpp");
    hExport.open(exportDirectory + "/Lexenv.h");
    if(!cppExport.is_open() || !hExport.is_open()) {
        return 1;
    }

    // --- Export the H part

    // Prepare the H string
    std::unique_ptr<std::string> hExportString(new std::string);
    *hExportString += "#ifndef CPP_WOL_LEXENV_H\n#define CPP_WOL_LEXENV_H\n\nclass Lexenv {\npublic:\n\tconst static char *regexArray[];\n\tconst static char *nameArray[];\n";

    // Export static fields
    for(int i = 0; i < symbolNameVector.size(); i++) {
        *hExportString += "\tconst static int " + symbolNameVector[i] + " = " + std::to_string(i) + ";\n";
    }

    // Finalize the H file
    *hExportString += "};\n\n#endif";

    // Export the H file
    hExport << *hExportString;
    hExport.close();

    // --- Export the CPP part
    cppExport << "#include \"Lexenv.h\"\n\n";

    // Prepare the export strings
    std::unique_ptr<std::string> nameArrayString(new std::string());
    std::unique_ptr<std::string> regexArrayString(new std::string());

    // Define regex and name arrays
    *nameArrayString += "const char *Lexenv::nameArray[" + std::to_string(symbolNameVector.size()) + "] = {";
    *regexArrayString += "const char *Lexenv::regexArray[" + std::to_string(symbolRegexVector.size()) + "] = {";

    // Export all values
    for(int i = 0; i < symbolNameVector.size(); i++) {
        // Add the name and the regex
        *nameArrayString += "\"" + symbolNameVector[i] + "\"";
        *regexArrayString += "R\"(" + symbolRegexVector[i] + ")\"";

        if(i < symbolNameVector.size() - 1) {
            *nameArrayString += ", ";
            *regexArrayString += ", ";
        }
    }
    *nameArrayString += "};\n";
    *regexArrayString += "};\n";

    // Write the cpp file
    cppExport << *nameArrayString << *regexArrayString;
    cppExport.close();

    // Return the success
    return 0;
}

/**
 * The main function to create the lexical environment from the .lex file
 *
 * @param argc The number of args
 * @param argv The args
 * @return If the lexenv creation worked
 */
int main(int argc, char *argv[]) {
    // Verify the args number
    if(argc == 3) {

        // Get the lex file location and open it
        char *lexFileName = argv[1];
        std::ifstream lexFile;
        lexFile.open(lexFileName);

        // Verify that the file is open
        if(lexFile.is_open()) {
            // Call the file parsing
            parseLexFile(lexFile);

            lexFile.close();
        } else {
            std::cout << "File " << lexFileName << " is missing or unreadable" << std::endl;
            return 1;
        }

        // Export the lexical environment
        if(exportLexEnv(argv[2]) != 0) {
            std::cout << "Directory " << argv[2] << " is unwritable" << std::endl;
            return 1;
        }

        // Return the exit code
        return 0;

    } else {

        // Display the error
        std::cout << "Please provide the lex file and the output file" << std::endl;

        // Return the exit code
        return 1;

    }
}