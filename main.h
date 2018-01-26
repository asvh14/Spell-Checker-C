#ifndef MAIN_H
#define MAIN_H

/**
 * Main function
 * Runs main menu
 * @param argc number of arguments on the command line
 * @param argv string array that stores command line arguements
 **/
int main(int argc, char** argv);

/**
 * used to print out data
 * @param toBePrinted data to be printed
 **/
void printNodeData(void *toBePrinted);

/**
 * used to generate a key for a word passed in
 * @param w word to generate key for
 * @return returns the key generated for the word
 **/
int createKey(char* w);

#endif
