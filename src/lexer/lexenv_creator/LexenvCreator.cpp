#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

std::vector<std::string> stopCharNameVector;
std::vector<std::string> stopCharsVector;

std::vector<std::string> symbolNameVector;
std::vector<std::string> symbolRegexVector;

int symbolNumber = 0;
int regexNumber = 0;

// TODO : Export all stop chars in an array

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
            if(line[0] == '-') {

                std::string stopCharName = line.substr(1, delimiterPosition - 1);
                std::string stopChars = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);

                // Place the stop char in the vector
                stopCharNameVector.emplace_back(stopCharName);
                stopCharsVector.emplace_back(stopChars);

            } else {

                std::string tokenName = line.substr(0, delimiterPosition);
                std::string tokenRegex = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);

                // Place the token definition in the wanted vectors
                symbolNameVector.emplace_back(tokenName);
                symbolRegexVector.emplace_back(tokenRegex);
                regexNumber++;

            }

            // Increment number of found symbols
            symbolNumber++;
        }
    }
}

/**
 * Function to export the lexical environment in the CPP format to
 *
 * @param exportDirectory The directory where you want to export the lexenv
 * @return If the export worked
 */
int exportLexEnv(const std::string &exportDirectory) {
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
    std::string hExportString;
    hExportString += "#ifndef CPP_WOL_LEXENV_H\n#define CPP_WOL_LEXENV_H\n\nclass Lexenv {\npublic:\n\tconst static char *regexArray[];\n\tconst static int regexCode[];\n\tconst static char *nameArray[];\n";

    // Export static fields
    hExportString += "\n\tinline const static int symbolNumber = " + std::to_string(symbolNumber) + ";\n";
    hExportString += "\tinline const static int regexNumber = " + std::to_string(regexNumber) + ";\n\n";

    for(int i = 0; i < symbolNumber; i++) {
        if(i < stopCharNameVector.size()) {
            hExportString += "\tinline const static int " + stopCharNameVector[i] + " = " + std::to_string(i) + ";\n";
        } else {
            hExportString += "\tinline const static int " + symbolNameVector[i - stopCharNameVector.size()] + " = " + std::to_string(i) + ";\n";
        }
    }

    // Finalize the H file
    hExportString += "};\n\n#endif";

    // Export the H file
    hExport << hExportString;
    hExport.close();

    // --- Export the CPP part

    // Include the h file
    cppExport << "#include \"Lexenv.h\"\n\n";

    // Prepare the export strings
    std::string nameArrayString = "const char *Lexenv::nameArray[" + std::to_string(symbolNumber) + "] = {";
    std::string regexArrayString = "const char *Lexenv::regexArray[" + std::to_string(regexNumber) + "] = {";
    std::string regexCodeArrayString = "const int Lexenv::regexCode[" + std::to_string(regexNumber) + "] = {";

    // Export all values
    for(int i = 0; i < symbolNumber; i++) {
        if(i < stopCharNameVector.size()) {

            nameArrayString += "\"" + stopCharNameVector[i] + "\"";

            if(i < symbolNumber - 1) {
                nameArrayString += ", ";
            }

        } else {
            unsigned int j = i - stopCharNameVector.size();

            nameArrayString += "\"" + symbolNameVector[j] + "\"";
            regexArrayString += "R\"(" + symbolRegexVector[j] + ")\"";
            regexCodeArrayString += "Lexenv::" + symbolNameVector[i - stopCharNameVector.size()];

            if(i < symbolNumber - 1) {
                nameArrayString += ", ";
                regexArrayString += ", ";
                regexCodeArrayString += ", ";
            }

        }
    }

    // Close the exported arrays
    nameArrayString += "};\n\n";
    regexArrayString += "};\n";
    regexCodeArrayString += "};\n";

    // Write the cpp file
    cppExport << nameArrayString << regexArrayString << regexCodeArrayString;
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