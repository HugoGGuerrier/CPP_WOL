#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int STOP_CHAR_TABLE_SIZE = 256;

std::vector<std::string> nameArray;
std::string stopCharTable[STOP_CHAR_TABLE_SIZE];
std::vector<std::string> literalArray;
std::vector<std::string> literalCode;
std::vector<std::string> regexArray;
std::vector<std::string> regexCode;

int symbolNumber = 0;
int stopCharNumber = 0;
int literalNumber = 0;
int regexNumber = 0;

/**
 * Get the escaped char value
 *
 * @param charToEscape The char to escape
 * @return The escaped char
 */
char getEscapedChar(char charToEscape) {
    switch (charToEscape) {
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t';
        case 'v': return '\v';
        case '\\': return '\\';
        case '\'': return '\'';
        case '"': return '\"';
        case '?': return '\?';
        default: return -1;
    }
}

/**
 * Function to use to parse the lex file and fill the vectors
 *
 * @param lexFile The file to parse
 */
void parseLexFile(std::ifstream &lexFile) {
    // Initialize the stop char table
    for(auto &str : stopCharTable) {
        str = "-1";
    }

    // Include the constant symbols
    // --- EOF
    nameArray.emplace_back("EOF_SYMBOL");
    stopCharTable[255] = "Lexenv::EOF_SYMBOL";

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
                    unsigned char sChar;
                    if(stopChars[i]== '\\') {
                        sChar = getEscapedChar(stopChars[++i]);
                    } else {
                        sChar = stopChars[i];
                    }

                    // Add the stop character to the table
                    stopCharTable[sChar] = "Lexenv::" + stopCharName;

                    // Increase the stop char number
                    stopCharNumber++;
                }


            } else if(line[0] == '+') {

                std::string literalName = line.substr(1, delimiterPosition - 1);
                std::string literalValue = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);

                // Place the literal in the wanted vectors
                nameArray.emplace_back(literalName);
                literalArray.emplace_back(literalValue);
                literalCode.emplace_back("Lexenv::" + literalName);
                literalNumber++;

            } else {

                std::string regexName = line.substr(0, delimiterPosition);
                std::string regexExpr = line.substr(delimiterPosition + 1, line.length() - delimiterPosition);

                // Place the token definition in the wanted vectors
                nameArray.emplace_back(regexName);
                regexArray.emplace_back(regexExpr);
                regexCode.emplace_back("Lexenv::" + regexName);
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
                     "\tconst static int stopCharTable[];\n\n"
                     "\tconst static char *literalArray[];\n"
                     "\tconst static int literalCode[];\n\n"
                     "\tconst static char *regexArray[];\n"
                     "\tconst static int regexCode[];\n"
                     "\tstatic regex_t regexTArray[];\n\n";

    // Export static fields
    hExportString += "\tinline const static int symbolNumber = " + std::to_string(symbolNumber) + ";\n";
    hExportString += "\tinline const static int stopCharNumber = " + std::to_string(stopCharNumber) + ";\n";
    hExportString += "\tinline const static int literalNumber = " + std::to_string(literalNumber) + ";\n";
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
    cppExport << "#include <cstring>\n\n#include \"Lexenv.h\"\n\n";

    // Prepare the export strings
    std::string nameArrayString = "const char *Lexenv::nameArray[" + std::to_string(symbolNumber) + "] = {";
    std::string stopCharTableString = "const int Lexenv::stopCharTable[" + std::to_string(STOP_CHAR_TABLE_SIZE) + "] = {";
    std::string literalArrayString = "const char *Lexenv::literalArray[" + std::to_string(literalNumber) + "] = {";
    std::string literalCodeString = "const int Lexenv::literalCode[" + std::to_string(literalNumber) + "] = {";
    std::string regexArrayString = "const char *Lexenv::regexArray[" + std::to_string(regexNumber) + "] = {";
    std::string regexCodeString = "const int Lexenv::regexCode[" + std::to_string(regexNumber) + "] = {";
    std::string regexTArrayString = "regex_t Lexenv::regexTArray[" + std::to_string(regexNumber) + "];\n\n";

    // Export all values
    for(std::string &name : nameArray) {
        nameArrayString +=  "\"" + name + "\", ";
    }
    for(std::string &scc : stopCharTable) {
        stopCharTableString += scc + ", ";
    }
    for(std::string &ln : literalArray) {
        literalArrayString += "\"" + ln + "\", ";
    }
    for(std::string &lc : literalCode) {
        literalCodeString += lc + ", ";
    }
    for(std::string &rn : regexArray) {
        regexArrayString += "R\"(^" + rn + "$)\", ";
    }
    for(std::string &rc : regexCode) {
        regexCodeString += rc + ", ";
    }

    // Close the exported arrays
    nameArrayString += "};\n\n";
    stopCharTableString += "};\n\n";
    literalArrayString += "};\n";
    literalCodeString += "};\n\n";
    regexArrayString += "};\n";
    regexCodeString += "};\n\n";

    // Write the cpp file
    cppExport <<
    nameArrayString <<
    stopCharTableString <<
    literalArrayString << literalCodeString <<
    regexArrayString  << regexCodeString << regexTArrayString;

    // Export the functions
    std::string functionsExportString;

    functionsExportString += "int Lexenv::getStopCharCode(char charToTest) {\n"
                             "    return Lexenv::stopCharTable[(unsigned char)charToTest];\n"
                             "}\n\n";

    functionsExportString += "int Lexenv::getLexicalTokenCode(char *strToTest) {\n"
                             "    for(int i = 0; i < Lexenv::literalNumber; i++) {\n"
                             "        if(strcmp(strToTest, Lexenv::literalArray[i]) == 0) return Lexenv::literalCode[i];\n"
                             "    }\n"
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