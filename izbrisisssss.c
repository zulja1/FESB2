#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
struct _cvor;
typedef struct _cvor* pozicija;
typedef struct _cvor {
	char rijec[MAX];
	int duljina;
	pozicija left;
	pozicija right;
}Cvor;

int file(pozicija root, FILE* doc);
int inorder(pozicija root);
pozicija Stvori(char* rijec, int duljina);
pozicija StvoriStablo(int duljina, char* rijec, pozicija root);
int main() {
	pozicija root = NULL;

	FILE* doc = fopen("Text.txt", "r");

	
	file(root, doc);
	inorder(root);

	fclose(doc);

	return 0;
}int file(pozicija root, FILE* doc) {

	if (!doc) {
		printf("erorr");
		return -1;
	}

	char rijec[MAX] = { 0 };
	int duljina = 0;


	while (!feof(doc)) {
		fscanf(doc, "%s ", rijec);
		duljina = strlen(rijec);
		root = StvoriStablo(duljina, rijec, root);
	}
	return 0;
}
pozicija StvoriStablo(int duljina, char* rijec, pozicija root) {

	if (root == NULL) {
		return Stvori(rijec, duljina);
	}
	if (strcmp(root->rijec, rijec) < 0) {
		root->left = StvoriStablo(duljina, rijec, root->left);
	}
	else if (strcmp(root->rijec, rijec) >= 0) {
		root->right = StvoriStablo(duljina, rijec, root->right);
	}
	return root;
}
pozicija Stvori(char* rijec, int duljina) {
	pozicija NovaRijec=NULL;

	NovaRijec = (pozicija)malloc(sizeof(Cvor));

	NovaRijec->duljina = duljina;
	NovaRijec->left = NULL;
	NovaRijec->right = NULL;
	strcpy(NovaRijec->rijec, rijec);


	return NovaRijec;

}
int inorder(pozicija root) {

	if (root) {
		inorder(root->left);
		printf("%s %d\n", root->rijec, root->duljina);
		inorder(root->right);
	}


	return 0;
}
