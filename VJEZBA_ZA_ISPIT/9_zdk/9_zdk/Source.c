#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 20
//9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
// 
//	a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
//sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
//pokazivač na korijen stabla.
// 
//	b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
//njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
//vrijednosti u tim potomcima).Npr.stablo sa slike Slika 1 transformirat će se u stablo na
//slici Slika 2
// 
//	c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
//funkcije rand() generira slučajne brojeve u rasponu <10, 90>.Također, potrebno je
//upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
//dijela zadatka

struct _broj;
typedef struct _broj* pozicija;
typedef struct _broj {
	pozicija left;
	pozicija right;
	int broj;
}Broj;

int replace(pozicija root);
pozicija Pronalazenje(int broj, pozicija root);
int inorder(pozicija root);
pozicija StvaranjeElementa(int broj);
pozicija StvaranjeStabla(int broj, pozicija root);
int Citanje_File(FILE* doc, pozicija root);
int main() {
	pozicija root = NULL;
	FILE* doc = fopen("Text.txt", "r");
	int broj;
	Citanje_File(doc, root);



	fclose(doc);
	return 0;
}
int Citanje_File(FILE* doc, pozicija root) {
	int broj;
	int rez;
	pozicija root2 = NULL;
	if (!doc) {
		printf("error");
		return -1;
	}

	while (!feof(doc)) {

		fscanf(doc, "%d, ", &broj);
		rez = random();
		root = StvaranjeStabla(broj, root);
		root2 = StvaranjeStabla(rez, root2);
	}

	inorder(root);
	printf("\n");
	inorder(root2);

	//pronadi funkcija
	/*printf("Provjeri je li to broj postoji u stablu: ");
	scanf("%d", &broj);

	rez=Pronalazenje(broj, root);
	if (rez) {
		printf("To broj postoji u stablu\n");
	}
	else printf("Ne postoji\n");*/



	//replace funkcija
	/*replace(root);
	printf("\n");
	inorder(root);*/

	return 0;
}
pozicija StvaranjeElementa(int broj) {
	pozicija NoviElement = NULL;

	NoviElement = (pozicija)malloc(sizeof(Broj));

	NoviElement->left = NULL;
	NoviElement->right = NULL;
	NoviElement->broj = broj;

	return NoviElement;
}
pozicija StvaranjeStabla(int broj, pozicija root) {
	if (root == NULL) {
		return StvaranjeElementa(broj);
	}
	if (root->broj<broj) {
		root->left = StvaranjeStabla(broj, root->left);
	}
	else if (root->broj>=broj) {
		root->right = StvaranjeStabla(broj, root->right);
	}

	return root;
}
int inorder(pozicija root) {

	if (root) {
		inorder(root->left);
		printf("%d  ", root->broj);
		inorder(root->right);
	}

	return 0;
}
pozicija Pronalazenje(int broj, pozicija root) {

	if (root == NULL || root->broj==broj) {
		return root;
	}
	if (root->broj > broj) {
		return Pronalazenje(broj, root->left);
	}
	else if (root->broj <= broj) {
		return Pronalazenje(broj, root->right);
	}
}
int replace(pozicija root) {

	if (root == NULL) {
		return 0;
	}
	int leftbroj = replace(root->left);
	int rightbroj = replace(root->right);

	int originalbroj = root->broj;

	root->broj = leftbroj + rightbroj;

	return originalbroj+root->broj;

}
int random() {
	return (rand() % (90 - 10 + 1)) + 10;
}