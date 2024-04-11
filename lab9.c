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
	struct RecordType *data;
	struct HashType *next;
};

// Compute the hash function
int hash(int x)
{
	// return x%31;
	// int val = ((47*(((int)(x/73))+22))%31);
	// printf("%d\n", val);
	//47* /37: 4 2s, 1 3s


	return ((47 * ( ((int)(x/37)) + 22) ) % 31);

	return ((7*(x + 22)) % 31);
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
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType **pHashArray, int hashSz)
{
	printf("Records in Hash Table:\n");
	int i;

	// printf("%d \t", pHashArray[15].data->id);

	struct HashType *temp;
	for (i=0;i<hashSz;++i)
	{
		if (pHashArray[i] != NULL)
		{
			printf("index %d: ", i);
			temp = pHashArray[i];
			do 
			{
				printf("%5d, %c, %2d; ", temp->data->id, temp->data->name, temp->data->order);
				temp = temp->next;
			} while (temp != NULL);
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
	// Your hash implementation

	//create hash table filled with null values
	struct HashType **HashArray = malloc(31*sizeof(struct HashType*));
	for (int i = 0; i < 31; i++)
	{
		HashArray[i]= NULL;
	}

	//put inputs into the hash table
	for (int i = 0; i < 31; i++)
	{
		//find the index on the hash table
		int input = hash(pRecords[i].id);
		//create a new node
		struct HashType *temp = malloc(sizeof(struct HashType));
		//data = current item being iterated
		temp->data = &pRecords[i];
		//next value is taken from the hash table to insert it at the front
		temp->next = HashArray[input];
		//hash table now points the the new front item
		HashArray[input] = temp;
	}

	displayRecordsInHash(HashArray, 31);
	


}