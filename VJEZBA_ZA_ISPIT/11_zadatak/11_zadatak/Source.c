#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define HASH_TABLE_SIZE 11

struct _town;
typedef struct _town* TownPosition;
typedef struct _town
{
	char name[MAX_LENGTH];
	int population;
	TownPosition next;
	TownPosition left;
	TownPosition right;
} Town;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country
{
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
	TownPosition townRootTree;
	Town townListHead;
} Country;

struct _hash_table {
	CountryPosition buckets[HASH_TABLE_SIZE];
};
typedef struct _hash_table HashTable;

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, HashTable* hashTable);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
CountryPosition createNewCountry(char* countryName);
TownPosition createNewTown(char* townName, int townPopulation);
TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown);
CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName);
int printTownTree(TownPosition townRootTree);



//hash
HashTable* createHashTable() {
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (!hashTable) {
		printf("Can't allocate memory for hash table!\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hashTable->buckets[i] = NULL;
	}

	return hashTable;
}
unsigned int calculateHash(char* countryName) {
	unsigned int hashValue = 0;
	int i = 0;
	while (i < 5 && countryName[i] != '\0') {
		hashValue += (unsigned int)countryName[i];
		i++;
	}
	return hashValue % HASH_TABLE_SIZE;
}
void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry) {
	unsigned int index = calculateHash(newCountry->name);

	if (hashTable->buckets[index] == NULL) {
		hashTable->buckets[index] = newCountry;
		newCountry->next = NULL;
	}
	else {
		// Handle collision by adding the new country to the linked list at this index
		newCountry->next = hashTable->buckets[index];
		hashTable->buckets[index] = newCountry;
	}
}
CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName) {
	unsigned int index = calculateHash(countryName);
	CountryPosition currentCountry = hashTable->buckets[index];

	while (currentCountry != NULL && strcmp(currentCountry->name, countryName) != 0) {
		currentCountry = currentCountry->next;
	}

	return currentCountry;
}

int printAllCountriesFromHash(HashTable* hashTable) {
	for (int index = 0; index < HASH_TABLE_SIZE; index++) {
		CountryPosition currentCountry = NULL;
		currentCountry = hashTable->buckets[index];

		while (currentCountry != NULL) {
			printf("\n%s", currentCountry->name);
			printTownTree(currentCountry->townRootTree);
			currentCountry = currentCountry->next;
		}
	}
}

int main() {
	Country countryHeadList = {
		.name = { 0 },
		.next = NULL,
		.left = NULL,
		.right = NULL,
		.townRootTree = NULL,
		.townListHead = {
			.name = { 0 },
			.population = 0,
			.next = NULL,
			.left = NULL,
			.right = NULL,
		}
	};

	CountryPosition countryRootTree = NULL;


	CountryPosition countries[] = { NULL, NULL };

	HashTable* hashTable = createHashTable();

	countryRootTree = readAndFillCountries(&countryHeadList, countryRootTree, hashTable);
	
	printf("HASH");
	printAllCountriesFromHash(hashTable);



	char searchCountryName[MAX_LENGTH] = { 0 };
	printf("\nEnter country name to search in the hash table: ");
	scanf(" %s", searchCountryName);

	CountryPosition foundCountry = searchCountryInHashTable(hashTable, searchCountryName);

	if (foundCountry != NULL) {
		printf("\nCountry found in the hash table: %s", foundCountry->name);
	}
	else {
		printf("\nCountry not found in the hash table.");
	}



	return EXIT_SUCCESS;
}

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, HashTable* hashTable) {
	FILE* filePointer = NULL;
	char countryName[MAX_LINE] = { 0 };
	char countryFile[MAX_LINE] = { 0 };
	char nullString[MAX_LINE] = { 0 };
	CountryPosition newCountryHash = NULL;
	CountryPosition countries[] = { NULL, NULL, NULL };

	filePointer = fopen("drzave.txt", "r");
	if (!filePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	while (!feof(filePointer)) {
		fscanf(filePointer, " %s %s", countryName, countryFile);
		createNewCountryFromBuffer(countryName, countryFile, countries);

		newCountryHash = countries[2];
		
		insertCountryIntoHashTable(hashTable, newCountryHash);
		strcpy(countryName, nullString);
		strcpy(countryFile, nullString);
	}

	fclose(filePointer);

	return countryRootTree;
}

int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries) {
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryFilePointer = NULL;

	CountryPosition newCountryHash = NULL;

	TownPosition newTownHash = NULL;
	char townName[MAX_LENGTH] = { 0 };
	int townPopulation = 0;

	strcpy(countryLocation, countryFile);

	countryFilePointer = fopen(countryLocation, "r");
	if (!countryFilePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	newCountryHash = createNewCountry(countryName);

	while (!feof(countryFilePointer)) {
		fscanf(countryFilePointer, " %s %d", townName, &townPopulation);

		newTownHash = createNewTown(townName, townPopulation);
	
		newCountryHash->townRootTree = insertNewTownTree(newCountryHash->townRootTree, newTownHash);
	}
	
	countries[2] = newCountryHash;

	fclose(countryFilePointer);

	return EXIT_SUCCESS;
}

CountryPosition createNewCountry(char* countryName) {
	CountryPosition country = NULL;
	country = (CountryPosition)malloc(sizeof(Country));
	if (!country) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}


	strcpy(country->name, countryName);
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;
	country->townRootTree = NULL;
	//strcpy(country->townHeadList.name, NULL);
	country->townListHead.population = 0;
	country->townListHead.next = NULL;
	country->townListHead.left = NULL;
	country->townListHead.right = NULL;

	return country;
}

TownPosition createNewTown(char* townName, int townPopulation) {
	TownPosition town = NULL;
	town = (TownPosition)malloc(sizeof(Town));
	if (!town) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	strcpy(town->name, townName);
	town->population = townPopulation;
	town->next = NULL;
	town->left = NULL;
	town->right = NULL;

	return town;
}

TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown) {
	if (townRootTree == NULL)
		return newTown;

	if (newTown->population > townRootTree->population)//dodaj provjeru po imenima naknadno...
		townRootTree->left = insertNewTownTree(townRootTree->left, newTown);
	else if (newTown->population <= townRootTree->population)
		townRootTree->right = insertNewTownTree(townRootTree->right, newTown);

	return townRootTree;
}

int printTownTree(TownPosition townRootTree) {
	if (townRootTree) {
		printTownTree(townRootTree->left);
		printf("\n\t%s %d", townRootTree->name, townRootTree->population);
		printTownTree(townRootTree->right);
	}
	return EXIT_SUCCESS;
}

CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName) {
	if (countryRootTree == NULL || strcmp(countryRootTree->name, countryName) == 0)
		return countryRootTree;

	if (strcmp(countryRootTree->name, countryName) > 0)
		return searchCountryTree(countryRootTree->left, countryName);

	return searchCountryTree(countryRootTree->right, countryName);
}