#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	int id;
	char name;
	int order;
	struct HashType* next;
	

};

// Compute the hash function
int hash(int x)
{
 return x % 10;

}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\n\t Records:\n\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t %d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n    ---End of records---\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].id != -1)
		{
			struct HashType *current = &pHashArray[i];
			printf("index %d -> ", i);
			while (current != NULL)
			{
				printf("%d %c %d -> ", current->id, current->name, current->order);
				current = current->next;
			}
			printf("\n");
		}


		

	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// hash implementation

struct HashType *pHashArray;
int hashSz = 10;
int i;
pHashArray = (struct HashType*) malloc(sizeof(struct HashType) * hashSz);
for (i = 0; i < hashSz; ++i)
{
	pHashArray[i].id = -1;
	pHashArray[i].name = ' ';
	pHashArray[i].order = -1;
	pHashArray[i].next = NULL;

}

displayRecordsInHash(pHashArray, hashSz);

return 0;
}


