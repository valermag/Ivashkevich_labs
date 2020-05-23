#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


struct MultiDigitalNumber {
	int digit;
	struct MultiDigitalNumber* left;
	struct MultiDigitalNumber* right;
};

typedef struct MultiDigitalNumber MultiDigitalNumber;

void NewMNum(MultiDigitalNumber** numL, MultiDigitalNumber** numR);
void AddDigit(MultiDigitalNumber* numR, int digit);
void ViewMNumber(MultiDigitalNumber** numL, MultiDigitalNumber** numR);
int Size_(MultiDigitalNumber** numL, MultiDigitalNumber** numR);
int Equal(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, MultiDigitalNumber** num2L, MultiDigitalNumber** num2R);
int LongModShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3);
MultiDigitalNumber* LongDivShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3);
MultiDigitalNumber* DeleteDigitLeft(MultiDigitalNumber** numL);
MultiDigitalNumber* LongMulShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3);
void DeleteAllDigits(MultiDigitalNumber** numL, MultiDigitalNumber** numR);
int menu();

int main(void) {
	system("chcp 1251");

	char str1[100], str2[100];
	int num3 = 0, e;
	printf("������� ������ �������������� �����\n");
	scanf_s("%99s", str1, (unsigned)_countof(str1));
	printf("������� ������ �������������� �����\n");
	scanf_s("%99s", str2, (unsigned)_countof(str2));
	struct MultiDigitalNumber* num1L = NULL, * num1R = NULL, * num2L = NULL, * num2R = NULL;
	if (num1L == NULL) NewMNum(&num1L, &num1R);
	if (num2L == NULL)  NewMNum(&num2L, &num2R);

	for (int i = 0; i < strlen(str1); i++)
	{
		char c = str1[i];
		AddDigit(num1R, atoi(&c));
	}
	for (int i = 0; i < strlen(str2); i++)
	{
		char c = str2[i];
		AddDigit(num2R, atoi(&c));
	}
	int size1 = Size_(&num1L, &num1R), size2 = Size_(&num2L, &num2R), size3 = 0, temp = 0;
	printf("������� �������� ����� �����\n");
	while (size3 > size1 || size3 > size2 || num3 < 1) {
		scanf_s("%i", &num3);
		while (temp) {	// ���������� �������� short int
			temp /= 10;
			size3++;
		}
		if (size3 > size1 || size3 > size2 || num3 < 1)
			printf("���������� �����\n");
	}

	while (1)
	{
		switch (menu())
		{
		case 1:
			e = Equal(&num1L, &num1R, &num2L, &num2R);
			if (e == 1)
				printf("������ �������������� ����� ������ �������\n");
			if (e == 0)
				printf("������ �������������� ����� ����� �������\n");
			if (e == -1)
				printf("������ �������������� ����� ������ �������\n");
			break;
		case 2:
			printf("������� �� ������� ������� ��������������� ����� �� �������� ����� �����:\t%d\n", LongModShort(&num1L, &num1R, num3));
			printf("������� �� ������� ������� ��������������� ����� �� �������� ����� �����:\t%d\n", LongModShort(&num2L, &num2R, num3));
			break;
		case 3:
			printf("����� ����� �� ������� ������� ��������������� ����� �� �������� ����� �����:\t"); LongDivShort(&num1L, &num1R, num3); printf("\n");
			printf("����� ����� �� ������� ������� ��������������� ����� �� �������� ����� �����:\t"); LongDivShort(&num2L, &num2R, num3); printf("\n");
			break;
		case 4:
			printf("������ �������������� ����� �������� �� �������� ����� �����:\t");  LongMulShort(&num1L, &num1R, num3); printf("\n");
			printf("������ �������������� ����� �������� �� �������� ����� �����:\t");  LongMulShort(&num2L, &num2R, num3); printf("\n");
			break;
		case 0:
			DeleteAllDigits(&num1L, &num1R);
			DeleteAllDigits(&num2L, &num2R);
			getchar();
			return 0;
		default: printf("���������� �����\n");
		}
	}
}

// ������� �������������� ����� (�������) � ������ �������
void NewMNum(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	*numL = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber));	// ��������� �� ����� ������
	*numR = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber)); // ��������� �� ������ ������
	(*numL)->left = NULL;		// ��������� ������ ����� ���������� numL � numR
	(*numL)->right = *numR;
	(*numR)->left = *numL;
	(*numR)->right = NULL;
	return;
}

// ������� ���������� ����� � �������������� �����
void AddDigit(MultiDigitalNumber* numR, int digit) {
	MultiDigitalNumber* spt = NULL;
	spt = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber));	// ��������� �� ����� �������
	spt->digit = digit;
	spt->left = numR->left;		// ��������� ������ ����� ����������� ��������� � ������� ����������
	spt->right = numR;
	spt->left->right = spt;
	numR->left = spt;
	return;
}

// �������� ��������������� ����� (�������)
void ViewMNumber(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// ��������� �� ������ ������� ������� (������� ������)
	while (spt != *numR)	// ���� ������� �����
	{
		printf("%d", spt->digit);
		spt = spt->right;	// ������� �� ��������� ������
	}
	return;
}

// �������, ������������ ������ ����� (���������� ��������� �������)
int Size_(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// ��������� �� ������ ������� ������� (������� ������)
	int size_ = 0;
	while (spt != *numR)	// ���� ������� �����
	{
		spt = spt->right;
		size_++;
	}
	return size_;
}

// ������� ��������� ���� �������������� �����
int Equal(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, MultiDigitalNumber** num2L, MultiDigitalNumber** num2R) {
	MultiDigitalNumber* spt1 = (*num1L)->right;	// ��������� ������� ������ ������� �����
	MultiDigitalNumber* spt2 = (*num2L)->right;	// ��������� ������� ������ ������� �����
	int size1 = Size_(num1L, num1R), size2 = Size_(num2L, num2R);	// ����������� ���������� �������� ������� � ������� ����� � ����� ���������� >, < ��� =
	if (size1 > size2)
		return 1;
	else if (size1 < size2)
		return -1;
	else if (size1 == size2)	// ���� =, �� ���������� �������� �������� ��������, ������� � �������, ���� �� �� ����� >, < ��� ���� ������� �� ����������
	{
		while (spt1 != *num1R) {

			if (spt1->digit > spt2->digit)
				return 1;
			if (spt1->digit < spt2->digit)
				return -1;
			spt1 = spt1->right;
			spt2 = spt2->right;
		}
	}
	return 0;
}

// ������� �� ������� �� short int
int LongModShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	int del = 0;
	MultiDigitalNumber* spt = (*num1L)->right;	// ��������� �� ������� ������

	while (spt != *num1R)	// ���� ������� ����� � �������� �� short int
	{
		del = del * 10 + spt->digit;
		spt = spt->right;
		del %= num3;
	}
	return del;
}

// ����� ����� �� ������� �� short int
MultiDigitalNumber* LongDivShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	MultiDigitalNumber* divL = NULL, * divR = NULL;
	if (divL == NULL) NewMNum(&divL, &divR);	// �������� ������ ����� ��� �������� ��������
	int del = 0;
	MultiDigitalNumber* spt = (*num1L)->right;	// ��������� ��  ������� ������

	while (spt != *num1R)		// ���� ������� ����� � �������� �� short int
	{
		del = del * 10 + spt->digit;
		spt = spt->right;
		AddDigit(divR, del / num3);
		del %= num3;
	}
	while (divL->right->digit == 0)	//������� �������� ������� ������� �������
	{
		divL = DeleteDigitLeft(&divL);
	}
	ViewMNumber(&divL, &divR);
	return divL;
}

// ������� ��� �������� ������� ��������
MultiDigitalNumber* DeleteDigitLeft(MultiDigitalNumber** numL) {
	MultiDigitalNumber* spt = (*numL)->right;	// ��������� ��  ������� ������
	MultiDigitalNumber* tmp = spt;
	spt->left->right = spt->right;	// ��������������� ������
	spt->right->left = spt->left;
	free(tmp);		// �������� ��������
	spt = (*numL)->right;
	return spt->left;
}

// ������� ��������� �� short int
MultiDigitalNumber* LongMulShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	int size = 0, temp = num3, count = 0;
	while (temp) {	// ���������� �������� short int
		temp /= 10;
		size++;
	}
	size += Size_(num1L, num1R);	// +���������� �������� ��������������� �����
	MultiDigitalNumber* numL = NULL, * numR = NULL;
	if (numL == NULL) NewMNum(&numL, &numR);	// �������� ������ �����, ��� �������� ���������� ���������
	for (int i = 0; i < size; i++)		// ������� ������ ����� � ���������� size ��������� ������
		AddDigit(numR, 0);
	int digit = 0, pos = 0;
	MultiDigitalNumber* spt = (*num1R)->left, * spt1 = numR->left;	//��������� �� ������� ������
	int mod = num3 % 10;	// ������ �����, �� ������� ��������
	num3 = num3 / 10;

	while (mod != 0) {		// ��������� ���������
		while (spt != *num1L)
		{
			spt1->digit += (spt->digit * mod + pos);
			pos = 0;
			if (spt1->digit >= 10) {
				pos = spt1->digit / 10;
				spt1->digit = spt1->digit % 10;
			}
			//pos = (spt->digit * mod + pos) / 10;
			spt = spt->left;
			spt1 = spt1->left;
		}
		count++;
		if (pos) {
			spt1->digit += pos;
			pos = 0;
		}
		mod = num3 % 10;
		num3 = num3 / 10;
		spt = (*num1R)->left;
		spt1 = numR->left;
		for (int i = 0; i < count; i++)
			spt1 = spt1->left;
	}
	while (numL->right->digit == 0)	//������� �������� ������� ������� �������
	{
		numL = DeleteDigitLeft(&numL);
	}
	ViewMNumber(&numL, &numR);
	return numL;
}

//������� �������� ����� �����
void DeleteAllDigits(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// ��������� �� ������� ������
	while (spt != *numR)		// ���� ������� ����� � ��������������� ��������� ��������
	{
		MultiDigitalNumber* tmp = spt;
		spt->left->right = spt->right;	// ��������������� ������
		spt->right->left = spt->left;
		free(tmp);
		spt = (*numL)->right;
	}
	free(*numL); *numL = NULL;	// �������� �������� � �� ��������� � NULL
	free(*numR); *numR = NULL;
	printf("�������������� ����� �������\n");
	return;
}

int menu() {
	int i = 0;
	printf("��������:\n");
	printf("1. ��������� ���� ��������������:\n");
	printf("2. ������� �� ������� �� �������� �����:\n");
	printf("3. ����� ����� �� ������� �� �������� �����:\n");
	printf("4. ��������� �� �������� �����:\n");
	printf("0. �����:\n");
	scanf_s("%i", &i);
	return i;
}
