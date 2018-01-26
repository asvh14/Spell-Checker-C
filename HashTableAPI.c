/**
 * @file HashTableAPI.h
 * @author Michael Ellis
 * @date February 2017
 * @brief File containing the function definitions of a hash table
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTableAPI.h"
#include "main.h"
#include "testMain.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted))
{
	HTable* tempTable = malloc(sizeof(HTable));
	
	if(tempTable != NULL)
	{
		tempTable->size = size;
		tempTable->table = malloc(sizeof(Node*)* tempTable->size;
		
		tempTable->hashFunction = hashFunction;
		tempTable->destroyData = destroyData;
		tempTable->printNode = printNode;
	}
	
	return tempTable;
}

Node *createNode(int key, void *data)
{
	Node* n = malloc(sizeof(Node));
	
	n->key = key;
	n->data = data;
	n->next = NULL;
	
	return n;
}

void destroyTable(HTable *hashTable);  

void insertData(HTable *hashTable, int key, void *data)
{
	int index = hashTable->hashFunction(hashTable->size, key);
	
	if(hashTable->table[index] == NULL || strcmp((char*)hashTable->table[index]->data, "#") == 0)
	{
		hashTable->table[index] = createNode(key, data);
		
		printf("*%s* successfully added with key: <%d> at index: (%d)\n", ((char*)hashTable->table[index]->data), hashTable->table[index]->key, index);
	}
	
	else if(data == NULL)
	{
		return;
	}
	
	else
	{
		insertData(hashTable, key+1, data);
	}
}

//lazy delete, store an symbol to indicate nothing is there
void removeData(HTable *hashTable, int key)
{
	void* toRemove = lookupData(hashTable, key);
	
	if(toRemove == NULL)
	{
		return;
	}
	
	hashTable->destroyData(toRemove);
}

void *lookupData(HTable *hashTable, int key)
{
	int searchIndex = 0;// = hashTable->hashFunction(hashTable->size, key);
	void* tempData;
	
	tempData = hashTable->table[searchIndex]->data;
	printf("data = %s\n", (char*)tempData);
	
	return tempData;
}

int hashNode(size_t tableSize, int key)
{
	return key%tableSize;
}

int hashFunction2(size_t tableSize, int key)
{
	return key+1%tableSize;
}
