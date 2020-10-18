#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> symbolNameVector;
std::vector<std::string> stopCharsVector;
std::vector<std::string> symbolRegexVector;

int symbolNumber = 0;
int stopCharNumber = 0;
int regexNumber = 0;

/**
 * Get the real number of stop chars
 *
 * @return The number of stop chars with process done
 */
int getRealStopCharNumber() {
    int res = 0;
    for(const std::string& str : stopCharsVector) {
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == '\\') i++;
            res++;
        }
    }
    return res;
}

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
                symbolNameVector.emplace_back(stopCharName);
                stopCharsVector.emplace_back(stopChars);
                stopCharNumber++;

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

    // Get the real number of stop char
    int realStopCharNumber = getRealStopCharNumber();
    int stopCounter = 0;

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
    hExportString += "\tinline const static int stopCharNumber = " + std::to_string(realStopCharNumber) + ";\n";
    hExportString += "\tinline const static int regexNumber = " + std::to_string(regexNumber) + ";\n\n";

    for(int i = 0; i < symbolNumber; i++) {
        hExportString += "\tinline const static int " + symbolNameVector[i] + " = " + std::to_string(i) + ";\n";
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
    std::string stopCharArrayString = "const char Lexenv::stopCharArray[" + std::to_string(realStopCharNumber) + "] = {";
    std::string stopCharCodeString = "const int Lexenv::stopCharCode[" + std::to_string(realStopCharNumber) + "] = {";
    std::string regexArrayString = "const char *Lexenv::regexArray[" + std::to_string(regexNumber) + "] = {";
    std::string regexCodeString = "const int Lexenv::regexCode[" + std::to_string(regexNumber) + "] = {";
    std::string regexTArrayString = "regex_t Lexenv::regexTArray[" + std::to_string(regexNumber) + "];\n";

    // Export all values
    for(int i = 0; i < symbolNumber; i++) {
        if(i < stopCharNumber) {

            nameArrayString += "\"" + symbolNameVector[i] + "\"";
            if(i < symbolNumber - 1) {
                nameArrayString += ", ";
            }

            std::string currentStopChars = stopCharsVector[i];
            for(int j = 0; j < currentStopChars.length(); j++) {
                std::string stopChar = currentStopChars[j] == '\\' ? currentStopChars.substr(j++, 2) : currentStopChars.substr(j, 1);
                stopCharArrayString += "'" + stopChar + "'";
                stopCharCodeString += "Lexenv::" + symbolNameVector[i];

                if(stopCounter < realStopCharNumber - 1) {
                    stopCharArrayString += ", ";
                    stopCharCodeString += ", ";
                }

                stopCounter++;
            }

        } else {

            nameArrayString += "\"" + symbolNameVector[i] + "\"";
            regexArrayString += "R\"(^" + symbolRegexVector[i - stopCharNumber] + "$)\"";
            regexCodeString += "Lexenv::" + symbolNameVector[i];

            if(i < symbolNumber - 1) {
                nameArrayString += ", ";
                regexArrayString += ", ";
                regexCodeString += ", ";
            }

        }
    }

    // Close the exported arrays
    nameArrayString += "};\n\n";
    stopCharArrayString += "};\n";
    stopCharCodeString += "};\n\n";
    regexArrayString += "};\n";
    regexCodeString += "};\n";

    // Write the cpp file
    cppExport << nameArrayString << stopCharArrayString << stopCharCodeString << regexArrayString  << regexCodeString << regexTArrayString;
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