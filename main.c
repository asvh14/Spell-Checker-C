#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "HashTableAPI.h"
#include "testMain.h"

int main(int argc, char** argv)
{
	/* read in file through command line
	 * insert data from file into hashtable
	 * create a main menu
	 * add word: enter single word, add to hash table
	 * remove word: single word, remove from hash table
	 * spell check: enter filename, check if file exists
	 * if file exists, check if each word exists in the
	 * hash table, if not, print invalid word and message,
	 * then print summary of the text file after 
	 * show words: output all contents of hash table
	 */
	
	int mainMenu;
	int endFlag = 0;
	int key = 0;
	int removeKey = 0;
	int j;
	//int tempI;
	FILE* userFile;
	char** spellCheck = malloc(sizeof(char*)* 100);
	int spellKey;
	int k;
	int i;
	int h;
	int match = 0;
	int noMatch = 0;
	char* fileName = malloc(sizeof(char)* 100);
	
	char* addWord = malloc(sizeof(char)* 100);
	char* removeWord = malloc(sizeof(char)* 100);
	char* fileWord = malloc(sizeof(char)* 100);
	HTable* hashTable = createTable(101, *hashNode, *destroyNodeData, *printNodeData);
	
	FILE* file;
	
	if(argc > 1)
	{
		file = fopen(argv[1], "r");
		
		if(file != NULL)
		{
			while(!feof(file))
			{
				fscanf(file, "%s", fileWord);
				
				key = createKey(fileWord);
				
				//tempI = hashTable->hashFunction(hashTable->size, key);
				insertData(hashTable, key, (void*)fileWord);
			}
		}
		free(fileWord);
	}
	
	else
	{
		printf("Error, No File Url...\n\n");
		return 0;	
	}
	
	//store data into hash table
	
	while(endFlag == 0)
	{
		printf("Welcome to the Main Menu\n");
		printf("Please enter a valid menu option\n");
		printf("1) Add a word to Dictionary\n");
		printf("2) Remove a word from Dictionary\n");
		printf("3) Spell Check a file\n");
		printf("4) Show Dictionary words\n");
		printf("5) Quit\n");
		scanf("%d", &mainMenu);
	
		switch(mainMenu)
		{
			case 1:
				//add
				key = 0;
				printf("Please enter a single word\n");
				scanf("%s", addWord);
				
				key = createKey(addWord);

				insertData(hashTable, key, (void*)addWord);
				
				free(addWord);
				break;
			
			case 2:
				//remove
				printf("Please enter the word you wish to remove\n");
				scanf("%s", removeWord);
				
				removeKey = createKey(removeWord);
				
				for(j = 0; j < hashTable->size; j++)
				{
					if(hashTable->table[j] == NULL)
					{
						printf("[%d]NOTHING TO SEE HERE, MOVE ALONG\n", j);
					}
					
					else
					{
						printf("[%d]CONTAINS DATA - KEY(%d)\n", j, hashTable->table[j]->key);
						if(hashTable->table[j]->key == removeKey)
						{
							printf("MATCH AT INDEX(%d)\n", j);
						}
					}
				}
				
				free(removeWord);
				break;
				
			case 3:
				//spell check
				for(k = 0; k < 100; k++)
				{
					spellCheck[k] = malloc(sizeof(char)* 100);
				}
				
				k = 0;
				
				do
				{
					printf("Please enter a filename\n");
					scanf("%s", fileName);
					userFile = fopen(fileName, "r");
					
					if(userFile)
					{
						break;
					}
				
					else
					{
						printf("file does not exist\n");
					}
					
				}while(!(userFile));
				
				printf("File processed by Spell Check <fileName>\n");
				
				while(!feof(userFile))
				{
					fscanf(userFile, "%s", spellCheck[k]);
					k++;
				}
				
				spellCheck = realloc(spellCheck, sizeof(char*)* k-1);
				
				for(h = 0 ; h < k; h++)
				{
					spellKey = createKey(spellCheck[h]);
					
					for(i = 0; i < hashTable->size; i++)
					{
						if(hashTable->table[i] == NULL)
						{
							continue;
						}
						
						else
						{
							if(hashTable->table[i]->key == spellKey)
							{
								match++;
							}
							
							else
							{
								noMatch++;
							}
						}
					}
				}
				
				printf("Summary\nCorrectly spelt words: <%d>\nIncorrectly spelt words: <%d>\n", match, noMatch/((int)hashTable->size));
				fclose(userFile);
				break;
				
			case 4:
				//show all
				for(j = 0; j < hashTable->size; j++)
				{
					if(hashTable->table[j] == NULL)
					{
						printf("Empty Index(%d)\n", j);
						continue;
					}
					
					else
					{
						
						printf("Index<%d>:Key<%d>:<CONTAINS DATA>\n", j, hashTable->table[j]->key);
					}
				}
								
				break;
				
			case 5:
				//quit
				endFlag = 1;
				break;
				
			default:
				printf("Invalid menu option\n");
				break;
		}
	}
	fclose(file);
	return 0;
}

int createKey(char* w)
{
	if(&w[2] != NULL)
	{
		return (int)w[0] + (int)w[1] + (int)w[2];
	}
	
	else if(&w[1] != NULL)
	{
		return (int)w[0] + (int)w[1];
	}
	
	else
	{
		return (int)w[0];
	}
}

void destroyNodeData(void *data)
{
	if(data == NULL)
	{
		return;
	}
	
	strcpy((char*)data, "#");
	return;
}

void printNodeData(void *toBePrinted)
{
	//char* n = malloc(sizeof(char*)* 100);
	//strcpy(n, (char*)toBePrinted);
	printf("%s\n", (char*)toBePrinted);
}
