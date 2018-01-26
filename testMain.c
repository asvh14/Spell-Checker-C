#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "HashTableAPI.h"

/*
 * Because of the issue with my program stated in the README, i was
 * unable to perform some of the tests as no actual data could be viewed
 * outside of the API file
 */ 

int main(int argc, char ** argv)
{
	//Test 1: Create HashTable
	printf("T1\n");
	HTable* dummyHT = createTable(101, *hashNode, *destroyNodeData, *printNodeData);
	
	//Test 2: Insert Data
	printf("T2\n");
	insertData(dummyHT, 60, "CIS");
	
	//Test 3: Open File and read in data
	//test with both valid and non valid filename
	printf("T3\n");
	int key = 0;
	char* fileWord = malloc(sizeof(char)* 100);
	
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
				
				insertData(dummyHT, key, (void*)fileWord);
			}
		}
		free(fileWord);
	}
	
	else
	{
		printf("Error, No File Url...\n\n");
		return 0;	
	}
	
	//Test 4: add to dictionary
	printf("T4\n");
	char* addWord = malloc(sizeof(char)* 100);
	key = 0;
	printf("Please enter a single word\n");
	scanf("%s", addWord);
	
	key = createKey(addWord);

	insertData(dummyHT, key, (void*)addWord);
	
	//Test 5: remove
	/*NOTE** Doesnt actually remove because of previously stated issues
	 * but does pinpoint which element to remove
	 */
	char* removeWord = malloc(sizeof(char)* 100);
	int removeKey = 0;
	int j;
	printf("T5\n");
	printf("Please enter the word you wish to remove\n");
	scanf("%s", removeWord);
	
	removeKey = createKey(removeWord);
	
	for(j = 0; j < dummyHT->size; j++)
	{
		if(dummyHT->table[j] == NULL)
		{
			printf("[%d]NOTHING TO SEE HERE, MOVE ALONG\n", j);
		}
		
		else
		{
			printf("[%d]CONTAINS DATA - KEY(%d)\n", j, dummyHT->table[j]->key);
			if(dummyHT->table[j]->key == removeKey)
			{
				printf("MATCH AT INDEX(%d)\n", j);
			}
		}
	}
	
	free(removeWord);

	return 0;
}
