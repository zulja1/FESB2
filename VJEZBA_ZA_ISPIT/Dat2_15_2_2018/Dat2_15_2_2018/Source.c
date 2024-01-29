#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 20
struct _rijec;
typedef struct _rijec* pozicijaR;
typedef struct _rijec {
	char rijec[MAX];
	pozicijaR next;
}Rijec;

struct _cvor;
typedef struct _cvor* pozicijaC;
typedef struct _cvor {
	char rijec[MAX];
	pozicijaC left;
	pozicijaC right;
	Rijec head;
	
}Cvor;
//--------------------------------------------

int file(FILE* doc, pozicijaC root);
int inorder(pozicijaC root);
pozicijaC StvoriStablo(pozicijaC root, pozicijaC NovaRijec);
pozicijaC StvoriRijec(char* rijec);
pozicijaC Provjera(pozicijaC root, pozicijaC NovaRijec);
int Lista(pozicijaR head, pozicijaR NovaRijec);
int PrintanjeListe(pozicijaR head);
pozicijaR StvoriRijec2(char* rijec);
//--------------------------------------------
int main() {
	pozicijaC root = NULL;

	FILE* doc = fopen("Text.txt", "r");

	if (!doc) {
		printf("error");
		return -1;
	}

	file(doc, root);


	fclose(doc);

	return 0;
}

pozicijaC StvoriRijec(char* rijec) {
	pozicijaC NovaRijec = NULL;

	NovaRijec = (pozicijaC)malloc(sizeof(Cvor));

	strcpy(NovaRijec->rijec, rijec);
	NovaRijec->left = NULL;
	NovaRijec->right = NULL;
	NovaRijec->head.next = NULL;
	strcpy(NovaRijec->head.rijec, "");


	return NovaRijec;
}
pozicijaR StvoriRijec2(char* rijec) {
	pozicijaR NovaRijec = NULL;

	NovaRijec = (pozicijaR)malloc(sizeof(Rijec));

	strcpy(NovaRijec->rijec, rijec);
	NovaRijec->next = NULL;


	return NovaRijec;
}
pozicijaC StvoriStablo(pozicijaC root, pozicijaC NovaRijec) {
	if (root == NULL) {
		return NovaRijec;
	}
	if (strcmp(root->rijec, NovaRijec->rijec) < 0) {
		root->left = StvoriStablo(root->left, NovaRijec);
	}else if (strcmp(root->rijec, NovaRijec->rijec) >= 0) {
		root->right = StvoriStablo(root->right, NovaRijec);
	}

	return root;
}
int inorder(pozicijaC root) {

	if (root) {
		inorder(root->left);
		printf("\n%s  ", root->rijec);
		PrintanjeListe(&root->head);
		inorder(root->right);
	}
	return 0;
}
int file(FILE* doc, pozicijaC root) {
	char rijec[MAX] = { 0 };
	pozicijaC root2 = NULL;
	pozicijaC NovaRijec = NULL;
	pozicijaR NovaRijec2 = NULL;
	while (!feof(doc) ){
		root2 = NULL;
		fscanf(doc, "%s ", rijec);
		NovaRijec = StvoriRijec(rijec);
		root2 = Provjera(root, NovaRijec);
		if (root2 != NULL) {
			NovaRijec2 = StvoriRijec2(rijec);
			Lista(&root2->head, NovaRijec2);
		}
		else {
			root = StvoriStablo(root, NovaRijec);
		}

	}

	

	inorder(root);

	return 0;
}
pozicijaC Provjera(pozicijaC root, pozicijaC NovaRijec) {
	if (root == NULL || strcmp(root->rijec, NovaRijec->rijec) == 0) {
		return root;
	}
	if (strcmp(root->rijec, NovaRijec->rijec) < 0) {
		return Provjera(root->left, NovaRijec);
	}

	return Provjera(root->right, NovaRijec);
}
int Lista(pozicijaR head, pozicijaR NovaRijec) {
	pozicijaR current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	NovaRijec->next = current->next;
	current->next = NovaRijec;
	return 0;
}
int PrintanjeListe(pozicijaR head) {
	pozicijaR current = head->next;

	while (current != NULL) {
		printf("-%s-", current->rijec);
		current = current->next;
	}
	printf("\n");
}