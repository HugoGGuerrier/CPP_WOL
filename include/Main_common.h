#ifndef CPP_WOL_MAIN_COMMON_H
#define CPP_WOL_MAIN_COMMON_H

/**
 * This class contains all main functions that are common to the prod and dev build
 */
class Main_common {
public:
    // ----- Class methods -----

    /**
     * The function to display the console help
     *
     * @param full If you want a full or a simple help
     * @param dev If you want the dev or prod help
     */
    static void displayHelp(bool full, bool dev);

    /**
     * Parse the program arguments and initialize the configuration
     *
     * @param argc The number of args
     * @param argv The args
     * @param dev If the build is dev or prod
     */
    static void readArgs(int argc, char *argv[], bool dev);

    /**
     * Bootstrap all the application
     *
     * @throw An exception if the bootstrap cannot be done
     */
    static void bootstrap();

};

#endif // CPP_WOL_MAIN_COMMON_H
