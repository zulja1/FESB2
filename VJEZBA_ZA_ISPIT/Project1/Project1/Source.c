#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 20
//Napisati program koji omogućava rad s binarnim stablom pretraživanja.Treba
//omogućiti unošenje novog elementa u stablo, ispis elemenata(inorder, preorder, postorder i
//level order), brisanje i pronalaženje nekog elementa.

struct _ime;
typedef struct _ime* pozicija;
typedef struct _ime {
	pozicija left;
	pozicija right;
	char ime[MAX];
}Ime;

pozicija Pronalazenje(char* ime, pozicija root);
int inorder(pozicija root);
pozicija StvaranjeElementa(char* ime);
pozicija StvaranjeStabla(char* ime, pozicija root);
int Citanje_File(FILE* doc, pozicija root);
int main() {
	pozicija root = NULL;
	FILE* doc = fopen("Text.txt", "r");
	char ime[MAX];
	Citanje_File(doc, root);

	

	fclose(doc);
	return 0;
}
int Citanje_File(FILE* doc, pozicija root) {
	char ime[MAX] = { 0 };

	if (!doc) {
		printf("error");
		return -1;
	}

	while (!feof(doc)) {

		fscanf(doc, "%s", ime);
		root = StvaranjeStabla(ime, root);
	}

	inorder(root);


	printf("Provjeri je li to ime postoji u stablu: ");
	scanf("%s", ime);

	/*root=Pronalazenje(ime, root);
	if (root) {
		printf("To ime postoji u stablu\n");
	}
	else printf("Ne postoji\n");*/



	return 0;
}pozicija StvaranjeElementa(char* ime) {
	pozicija NoviElement=NULL;

	NoviElement = (pozicija)malloc(sizeof(Ime));

	NoviElement->left = NULL;
	NoviElement->right = NULL;
	strcpy(NoviElement->ime, ime);

	return NoviElement;
}
pozicija StvaranjeStabla(char* ime, pozicija root) {
	if (root == NULL) {
		return StvaranjeElementa(ime);
	}
	if (strcmp(root->ime, ime) > 0) {
		root->left = StvaranjeStabla(ime, root->left);
	}
	else if (strcmp(root->ime, ime) <= 0) {
		root->right = StvaranjeStabla(ime, root->right);
	}

	return root;
}
int inorder(pozicija root) {

	if (root) {
		inorder(root->left);
		printf("%s  ", root->ime);
		inorder(root->right);
	}

	return 0;
}
pozicija Pronalazenje(char* ime, pozicija root) {

	if (root == NULL || strcmp(root->ime, ime) == 0) {
		return root;
	}
	if (strcmp(root->ime, ime) > 0) {
		return Pronalazenje(ime, root->left);
	}
	else if (strcmp(root->ime, ime) <= 0) {
		return Pronalazenje(ime, root->right);
	}
}
