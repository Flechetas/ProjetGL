#ifndef CLI_H
#define CLI_H

/**
 * @brief parses the flags
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 on success, error code otherwise
 */
int exec(int argc, char *argv[]);

/**
 * @brief parses the draw command
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 on success, error code otherwise
 */
int draw(int argc, char *argv[]);

/**
 * @brief parses the train command
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 on success, error code otherwise
 */
int execTrain(int argc, char *argv[]);

/**
 * @brief parses the generate command
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 on success, error code otherwise
 */
int generate(int argc, char *argv[]);

/**
 * @brief displays help
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 on success, error code otherwise
 */
int displayHelp(int argc, char *argv[]);

/**
    * @brief parses the benchmark command
    * @param argc number of arguments
    * @param argv arguments
    * @return 0 on success, error code otherwise
 */
int benchmark_execTrain(int argc, char *argv[]);

/*
 * @brief check if string has suffix suff
 * @param string source string
 * @param suff suffix to search in source string
 * @return 0 on success, error code otherwise
 */
int endsWith(char *string, const char *suff);

#endif //CLI_H
