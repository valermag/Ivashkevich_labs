#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

// ��������� ��������� ������ ������
typedef struct Binary_Tree {
	int info;
	struct Binary_Tree* left;
	struct Binary_Tree* right;
};

typedef struct Binary_Tree Binary_Tree;

// ������� ���������� �������� � ������
Binary_Tree* AddElTree(Binary_Tree* root, int info)
{
	Binary_Tree* temp = (Binary_Tree*)malloc(sizeof(Binary_Tree));
	Binary_Tree* sp = NULL, * spt;
	bool b;
	temp->info = info;
	temp->left = NULL;
	temp->right = NULL;
	if (root == NULL) return temp;
	spt = root;
	while (spt != NULL)	// ����� ����� ��� ������� �������� � ��������������� ������
	{
		sp = spt;
		b = (info < spt->info);
		if (b) spt = spt->left;
		else spt = spt->right;
	}
	if (b) sp->left = temp;
	else sp->right = temp;
	return root;
}

// ������� ������ ������ �� �����
void ReadTree(Binary_Tree* spt, int level)
{
	if (spt == NULL) return;
	ReadTree(spt->left, level + 1);
	int i;
	for (i = 0; i < level; i++) printf("   ");
	printf("%d\n", spt->info);
	ReadTree(spt->right, level + 1);
}

// ������� ������ ����� ����� ������ �� �����
void ReadTreeLeft(Binary_Tree* spt, int level)
{
	if (spt == NULL) return;
	ReadTree(spt->left, level + 1);
	int i2;
	for (i2 = 0; i2 < level; i2++) printf("   ");
	printf("%d\n", spt->info);
}

// ������� ������ ������ ����� ������ �� �����
void ReadTreeRight(Binary_Tree* spt, int level)
{
	if (spt == NULL) return;
	int i3;
	for ( i3 = 0; i3 < level; i3++) printf("   ");
	printf("%d\n", spt->info);
	ReadTree(spt->right, level + 1);
}

// ������� �������� ������
Binary_Tree* DeleteTree(Binary_Tree* spt)
{
	if (spt == NULL) return NULL;
	DeleteTree(spt->left);	// �������� �����
	DeleteTree(spt->right);	// �������� ������

	free(spt);
	spt = NULL;
	return NULL;
}

// ������� �������� ������ ������
int High(Binary_Tree* spt) {
	int lheight, rheight;
	if (spt == NULL)
	{
		return 0;
	}
	else
	{
		lheight = High(spt->left);
		rheight = High(spt->right);
		if (lheight > rheight)
		{
			return ++lheight;
		}
		else
		{
			return ++rheight;
		}
	}
}

// ��������� ������
struct Ring {
	int inf;
	struct Ring* left;
	struct Ring* right;
};

typedef struct Ring Ring;

// ���������� �������� � ������
Ring* AddElRing(Ring* s, int inf) {
	Ring* sp = s;	// ��������� �� ������ ����������� ������� ������
	Ring* spt = (Ring*)malloc(sizeof(Ring));
	spt->inf = inf;
	if (sp == NULL)	// ��������������� ������
	{
		spt->left = spt;
		spt->right = spt;
	}
	else
	{
		spt->right = sp->right;
		spt->left = sp->right->left;
		sp->right->left = spt;
		sp->right = spt;
	}
	return spt;
}

// �������� ���� ��������� �� ������
Ring* DelAllRing(Ring* sl)
{
	Ring* sp = sl->right;	// ��������� �� ������ ����������� ������� ������
	Ring* spt;
	while (sp->right != sp)	// ��������������� ������
	{
		sp->left->right = sp->right;
		sp->right->left = sp->left;
		spt = sp;
		sp = sp->right;
		free(spt);	// �������� ��������
	}
	return NULL;
}

// ������� ��������� ������
void ViewRing(Ring* sl) {
	Ring* spt = sl->right;
	while (spt != sl) {
		printf("%d\n", spt->inf);
		spt = spt->right;
	}
	printf("%d\n", spt->inf);
}

// ������� �������������� ������ � ������
Binary_Tree* MakeTree(Ring* sl) {
	Binary_Tree* root = NULL;
	Ring* spt = sl->right;
	while (spt != sl) {
		root = AddElTree(root, spt->inf);
		spt = spt->right;
	}
	root = AddElTree(root, spt->inf);
	return root;
}

int main()
{
	system("chcp 1251");

	Ring* ring = NULL;
	Binary_Tree* root = NULL;
	int count, num;

	printf("������� ���������� �����, ������� �� ������ ������:\t");
	scanf_s("%d", &count);
	int i4;
	for (i4 = 0; i4 < count; i4++) {
		printf("������� �����:\t");
		scanf_s("%d", &num);
		ring = AddElRing(ring, num);
	}
	printf("�������� ������:\n");
	ViewRing(ring);

	root = MakeTree(ring);
	printf("����� ������� �����:\n");
	int l = High(root->left), r = High(root->right);
	if (l > r)
		ReadTreeLeft(root, 0);
	else if (l < r)
		ReadTreeRight(root, 0);
	else if (l == r)
		ReadTree(root, 0);
	system("pause");
	return 0;
}
