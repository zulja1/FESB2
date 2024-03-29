#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct _cvor;
typedef struct _cvor* pozicija;
typedef struct _cvor {
	pozicija left;
	pozicija right;
	int broj;

}cvor;

int find(int broj, pozicija root);
int inorder(FILE* doc, pozicija root);
int postorder(FILE* doc, pozicija root);
int preorder(pozicija root);
int levelOrder(pozicija root);
pozicija SNoviBroj(int broj);
pozicija Stablo(int broj, pozicija root);
int replace(pozicija root);
pozicija Izbrisi(pozicija root, int value);

int main() {
	FILE* doc = fopen("stablo.txt", "w+");
	cvor head = { .left = NULL, .right = NULL, .broj = 0 };
	pozicija root=NULL;
	int i;
	int broj;
	for (i = 0; i < 10; i++) {
		broj = random();
		root = Stablo(broj, root);
	}
	 

	inorder(doc, root);


	/*if(find(5, root)) {
		printf("ima broj");
	}
	else printf("nema broja");*/ 


	fclose(doc);
	
	return 0;
}

pozicija SNoviBroj(int broj) {
	pozicija NoviBroj;

	NoviBroj = (pozicija)malloc(sizeof(cvor));

	NoviBroj->broj = broj;
	NoviBroj->left = NULL;
	NoviBroj->right = NULL; 

	return NoviBroj;
}
pozicija Stablo(int broj, pozicija root) {
	if (root == NULL) {
		return SNoviBroj(broj);
	}
	if (root->broj > broj) {
		root->right = Stablo(broj, root->right);
	}
	else if (root->broj <= broj) {
		root->left = Stablo(broj, root->left);
	}

	return root;
}
int inorder(FILE* doc, pozicija root) {

	int broj;
	if (!doc) {
		printf("eeorrrr");
		return -1;
	}
	if (root) {
		inorder(doc, root->left);
		printf("%d  ", root->broj);
		fprintf(doc, " %d", root->broj);
		inorder(doc, root->right);
	}


	
	return 0;
}
int postorder(FILE* doc, pozicija root) {

	int broj;
	if (!doc) {
		printf("eeorrrr");
		return -1;
	}
	if (root) {
		postorder(doc, root->left);
		postorder(doc, root->right);
		printf("%d  ", root->broj);
		fprintf(doc, " %d", root->broj);
	}



	return 0;
}
int preorder(pozicija root) {
	if (root) {
		printf("%d ", root->broj);
		preorder(root->left);
		preorder(root->right);
	}
	return 0;
}
int find(int broj, pozicija root) {

	if (root==NULL||root->broj == broj) {
		return root;
	}
	if (broj < root->broj) {
		root->left = find(broj, root->left);
	}
	else if (broj > root->broj) {
		root->right = find(broj, root->right);
	}

	
}
int replace(pozicija root) {
	if (root == NULL) {
		return 0;
	}

	int leftBroj = replace(root->left);
	int rightBroj = replace(root->right);

	int original = root->broj;

	root->broj = leftBroj + rightBroj;

	return original+root->broj;


}
int random() {
	return (rand() % (90 - 10 + 1)) + 10;
}
int levelOrder(pozicija root) {
	if (root == NULL)
		return;

	pozicija queue[100] = { 0 };
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		pozicija current = queue[front++];

		printf("%d ", current->broj);

		if (current->left != NULL)
			queue[rear++] = current->left;

		if (current->right != NULL)
			queue[rear++] = current->right;
	}
	return 0;
}
pozicija Izbrisi(pozicija root, int value) {
	if (root == NULL)
		return root;

	
	if (value < root->broj)
		root->left = Izbrisi(root->left, value);
	else if (value > root->broj)
		root->right = Izbrisi(root->right, value);
	else {
		
		if (root->left == NULL) {
			pozicija temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			pozicija temp = root->left;
			free(root);
			return temp;
		}

	
		pozicija temp = root->right;
		while (temp->left != NULL)
			temp = temp->left;

	
		root->broj = temp->broj;

		
		root->right = Izbrisi(root->right, temp->broj);
	}

	return root;
}
