#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> nameArray;
std::vector<std::string> stopCharArray;
std::vector<std::string> stopCharCode;
std::vector<std::string> regexArray;
std::vector<std::string> regexCode;

int symbolNumber = 0;
int stopCharNumber = 0;
int regexNumber = 0;

/**
 * Function to use to parse the lex file and fill the vectors
 *
 * @param lexFile The file to parse
 */
void parseLexFile(std::ifstream &lexFile) {
    // Include the constant symbols
    // --- EOF
    nameArray.emplace_back("EOF_SYMBOL");
    stopCharArray.emplace_back("\\xFF");
    stopCharCode.emplace_back("Lexenv::EOF_SYMBOL");

    symbolNumber = 1;
    stopCharNumber = 1;

    // Prepare the line reading and counter
    std::string line;

    while(std::getline(lexFile, line)) {
        // Get the token definition
        int delimiterPosition = line.find(':');

        if(delimiterPosition != -1) {

            if(line[0] == '-') {

                // Add the stop char to the general symbol name array
                std::string stopCharName = line.substr(1, delimiterPosition - 1);
                nameArray.emplace_back(stopCharName);

                std::string stopChars = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);
                for(int i = 0; i < stopChars.size(); i++) {
                    std::string sChar;
                    if(stopChars[i]== '\\') {
                        sChar.push_back('\\');
                        sChar.push_back(stopChars[++i]);
                    } else {
                        sChar.push_back(stopChars[i]);
                    }

                    // Add the stop character to the vector
                    stopCharArray.emplace_back(sChar);
                    stopCharCode.emplace_back("Lexenv::" + stopCharName);

                    // Increase the stop char number
                    stopCharNumber++;
                }


            } else {

                std::string tokenName = line.substr(0, delimiterPosition);
                std::string tokenRegex = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);

                // Place the token definition in the wanted vectors
                nameArray.emplace_back(tokenName);
                regexArray.emplace_back(tokenRegex);
                regexCode.emplace_back("Lexenv::" + tokenName);
                regexNumber++;

            }

            // Increment number of found symbols
            symbolNumber++;

        } else if(line[0] == '~') {

            // Handle the symbol only lines
            std::string symbolName = line.substr(1, line.length() - 1);

            // Place the symbol in the symbol vector
            nameArray.emplace_back(symbolName);

            // Increment the symbol number
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
    hExportString += "#ifndef CPP_WOL_LEXENV_H\n#define CPP_WOL_LEXENV_H\n\n#include <regex.h>\n\nclass Lexenv {\npublic:\n"
                     "\tconst static char *nameArray[];\n\n"
                     "\tconst static char stopCharArray[];\n"
                     "\tconst static int stopCharCode[];\n\n"
                     "\tconst static char *regexArray[];\n"
                     "\tconst static int regexCode[];\n"
                     "\tstatic regex_t regexTArray[];\n\n";

    // Export static fields
    hExportString += "\tinline const static int symbolNumber = " + std::to_string(symbolNumber) + ";\n";
    hExportString += "\tinline const static int stopCharNumber = " + std::to_string(stopCharNumber) + ";\n";
    hExportString += "\tinline const static int regexNumber = " + std::to_string(regexNumber) + ";\n\n";

    for(int i = 0; i < symbolNumber; i++) {
        hExportString += "\tinline const static int " + nameArray[i] + " = " + std::to_string(i) + ";\n";
    }

    // Export the functions profile
    hExportString += "\n\tstatic int getStopCharCode(char charToTest);\n";
    hExportString += "\tstatic int getLexicalTokenCode(char *strToTest);\n";

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
    std::string stopCharArrayString = "const char Lexenv::stopCharArray[" + std::to_string(stopCharNumber) + "] = {";
    std::string stopCharCodeString = "const int Lexenv::stopCharCode[" + std::to_string(stopCharNumber) + "] = {";
    std::string regexArrayString = "const char *Lexenv::regexArray[" + std::to_string(regexNumber) + "] = {";
    std::string regexCodeString = "const int Lexenv::regexCode[" + std::to_string(regexNumber) + "] = {";
    std::string regexTArrayString = "regex_t Lexenv::regexTArray[" + std::to_string(regexNumber) + "];\n\n";

    // Export all values
    for(std::string &name : nameArray) {
        nameArrayString +=  "\"" + name + "\", ";
    }
    for(std::string &scn : stopCharArray) {
        stopCharArrayString += "'" + scn + "', ";
    }
    for(std::string &scc : stopCharCode) {
        stopCharCodeString += scc + ", ";
    }
    for(std::string &rn : regexArray) {
        regexArrayString += "R\"(^" + rn + "$)\", ";
    }
    for(std::string &rc : regexCode) {
        regexCodeString += rc + ", ";
    }

    // Close the exported arrays
    nameArrayString += "};\n\n";
    stopCharArrayString += "};\n";
    stopCharCodeString += "};\n\n";
    regexArrayString += "};\n";
    regexCodeString += "};\n\n";

    // Write the cpp file
    cppExport << nameArrayString << stopCharArrayString << stopCharCodeString << regexArrayString  << regexCodeString << regexTArrayString;

    // Export the functions
    std::string functionsExportString;

    functionsExportString += "int Lexenv::getStopCharCode(char charToTest) {\n"
                             "    for(int i = 0; i < Lexenv::stopCharNumber; i++) {\n"
                             "        if(charToTest == Lexenv::stopCharArray[i]) return Lexenv::stopCharCode[i];\n"
                             "    }\n"
                             "    return -1;\n"
                             "}\n\n";

    functionsExportString += "int Lexenv::getLexicalTokenCode(char *strToTest) {\n"
                             "    for(int i = 0; i < Lexenv::regexNumber; i++) {\n"
                             "        if(regexec(&Lexenv::regexTArray[i], strToTest, 0, nullptr, 0) == 0) return Lexenv::regexCode[i];\n"
                             "    }\n"
                             "    return -1;\n"
                             "}\n\n";

    cppExport << functionsExportString;

    // Close CPP file
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