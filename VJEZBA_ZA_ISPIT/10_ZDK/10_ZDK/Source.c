#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 30

struct _grad;
typedef struct _grad* pozicijaG;
typedef struct _grad {
	char ime[MAX];
	int ID;
	pozicijaG left;
	pozicijaG right;
	pozicijaG next;
}Grad;

struct _drzava;
typedef struct _drzava* pozicijaD;
typedef struct _drzava {
	char ime[MAX];
	int ID;
	pozicijaD next;
	pozicijaG root;
	Grad headGrad;
	pozicijaD left;
	pozicijaD right;
}Drzava;


pozicijaD PronadiRoot(pozicijaD root2, pozicijaG NoviGrad);
int inorder2(pozicijaD root2);
pozicijaD StvaranjeStablaDrzava(pozicijaD NovaDrzava, pozicijaD root2);
int inorder(pozicijaG root);
pozicijaG StvoriGrad(char* ime, int ID);
pozicijaD StvaranjeStablaGradova( pozicijaG NoviGrad, pozicijaG root);
int Povezi(pozicijaG NoviGrad, pozicijaD head);
int UnosSort(pozicijaD NovaDrzava, pozicijaD head);
int StvoriGradove(pozicijaD root2, pozicijaD head, FILE* doc2);
pozicijaD StvoriDrzavu(pozicijaD head, char* ime, int ID);
int StvaranjeListeDrzava(pozicijaD head, FILE* doc);
int ListaGradova(pozicijaG headGrad, pozicijaG NoviGrad);
int PrintanjeGradova(pozicijaG head);
int main() {
	Drzava head = { .ID = 0,.left=NULL, .right=NULL,  .ime = {0}, .next = NULL, .root = NULL , .headGrad = {.ID = 0, .ime = {0}, .next = NULL, .left = NULL, .right = NULL} };


	FILE* doc = fopen("drzave.txt", "r");

	StvaranjeListeDrzava(&head, doc);





	fclose(doc);


	return 0;
}

int StvaranjeListeDrzava( pozicijaD head, FILE* doc) {
	int ID = 0;
	char ime[MAX] = { 0 };
	pozicijaD NovaDrzava = NULL;
	pozicijaD root2 = NULL;
	if (!doc) {
		printf("error");
		return -1;
	}

	while (!feof(doc)) {
		fscanf(doc, "%s %d", ime, &ID);
		//stavranje nove drzave i stalvjanje u listu sortirano
		NovaDrzava = StvoriDrzavu(head, ime, ID);
		UnosSort(NovaDrzava, head);
		//stavljanje drzava u stablo sortirano
		root2 = StvaranjeStablaDrzava(NovaDrzava, root2);

	}
	
	
	FILE* doc2 = fopen("gradovi.txt", "r");

	StvoriGradove( root2, head, doc2);

	fclose(doc2);
	return 0;
}
pozicijaD StvoriDrzavu(pozicijaD head, char* ime, int ID) {
	pozicijaD NovaDrzava = NULL;

	NovaDrzava = (pozicijaD)malloc(sizeof(Drzava));

	NovaDrzava->ID = ID;
	strcpy(NovaDrzava->ime, ime);
	NovaDrzava->next = NULL;
	NovaDrzava->root = NULL;
	NovaDrzava->left = NULL;
	NovaDrzava->right = NULL;
	NovaDrzava->headGrad.ID = 0;
	strcpy(NovaDrzava->headGrad.ime, "");
	NovaDrzava->headGrad.next = NULL;

	return NovaDrzava;
}
int StvoriGradove(pozicijaD root2, pozicijaD head, FILE* doc2) {
	char ime[MAX] = { 0 };
	int ID=0;
	pozicijaG NoviGrad=NULL;
	pozicijaD rootTemp = NULL;
	if (!doc2) {
		printf("error2");
		return -1;
	}

	while (!feof(doc2)) {
		fscanf(doc2, "%s %d", ime, &ID);
		NoviGrad = StvoriGrad(ime, ID);

		rootTemp = PronadiRoot(root2, NoviGrad);

		if (rootTemp != NULL) {
			ListaGradova(&rootTemp->headGrad, NoviGrad);
		}

		Povezi(NoviGrad, head);
	}

	pozicijaD current = head->next;
	while (current != NULL) {
		printf("%s\n", current->ime);
		inorder(current->root);

		current = current->next;
	}
	inorder2(root2);

	OslobodiMemoriju(root2);
	

	return 0;
}
int UnosSort(pozicijaD NovaDrzava, pozicijaD head) {
	pozicijaD current = head;
	while (current->next != NULL && strcmp(current->next->ime, NovaDrzava->ime) < 0) {
		current = current->next;
	}
	NovaDrzava->next = current->next;
	current->next = NovaDrzava;

	return 0;


}
pozicijaG StvoriGrad(char* ime, int ID) {

	pozicijaG NoviGrad = NULL;
	
	NoviGrad = (pozicijaG)malloc(sizeof(Grad));

	strcpy(NoviGrad->ime, ime);
	NoviGrad->ID = ID;
	NoviGrad->left = NULL;
	NoviGrad->right = NULL;
	NoviGrad->next = NULL;


	return NoviGrad;
}
int Povezi(pozicijaG NoviGrad, pozicijaD head) {
	pozicijaD current = head->next;

	while (current != NULL ) {
		if (current->ID == NoviGrad->ID) {
			break;
		}
		current = current->next;
	}
	current->root = StvaranjeStablaGradova(NoviGrad, current->root);

	

}
pozicijaD StvaranjeStablaGradova( pozicijaG NoviGrad, pozicijaG root) {
	if (root == NULL) {
		return NoviGrad;
	}
	if (strcmp(NoviGrad->ime, root->ime) < 0) {
		root->left = StvaranjeStablaGradova(NoviGrad, root->left);
	}
	else if (strcmp(NoviGrad->ime, root->ime) >= 0) {
		root->right = StvaranjeStablaGradova(NoviGrad, root->right);
	}


	return root;
}
pozicijaD StvaranjeStablaDrzava(pozicijaD NovaDrzava, pozicijaD root2) {
	if (root2 == NULL) {
		return NovaDrzava;
	}
	if (root2->ID>NovaDrzava->ID) {
		root2->left = StvaranjeStablaDrzava(NovaDrzava, root2->left);
	}
	else if (root2->ID <= NovaDrzava->ID) {
		root2->right = StvaranjeStablaDrzava(NovaDrzava, root2->right);
	}


	return root2;
}


int inorder(pozicijaG root) {
	if (root) {
		inorder(root->left);
		printf("   %s\n", root->ime);
		inorder(root->right);
	}

	return 0;
}
int inorder2(pozicijaD root2) {
	if (root2) {
		inorder2(root2->left);
		printf("\n--%s--", root2->ime);
		PrintanjeGradova(&root2->headGrad);
		inorder2(root2->right);
	}

	return 0;
}
int PrintanjeGradova(pozicijaG head) {
	pozicijaG current = head;
	while (current != NULL) {
		printf(" %s  ", current->ime);
		current = current->next;
	}
	
}

int ListaGradova(pozicijaG headGrad, pozicijaG NoviGrad) {
	pozicijaG current = headGrad;

	while (current->next != NULL) {
		current = current->next;
	}
	NoviGrad->next = current->next;
	current->next = NoviGrad;

	return 0;
}
pozicijaD PronadiRoot(pozicijaD root2, pozicijaG NoviGrad) {

	if (root2 == NULL || root2->ID == NoviGrad->ID) {
		return root2;
	}
	if (root2->ID > NoviGrad->ID) {
		return PronadiRoot(root2->left, NoviGrad);
	}
	
		return PronadiRoot(root2->right, NoviGrad);
	
}
 int OslobodiMemoriju(pozicijaD root2) {
	 if (root2 == NULL) {
		 return;
	 }
	OslobodiMemoriju(root2->left);
	OslobodiMemoriju(root2->right);



	free(root2);
}