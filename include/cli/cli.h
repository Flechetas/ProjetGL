#ifndef CLI_H
#define CLI_H

/**
 * @brief parses the flags
 * @
 */
int exec(int argc, char *argv[]);

int draw(int argc, char *argv[]);
int execTrain(int argc, char *argv[]);
int generate(int argc, char *argv[]);
int displayHelp(int argc, char *argv[]);

int endsWith(char *string, const char *suff);

#endif //CLI_H
