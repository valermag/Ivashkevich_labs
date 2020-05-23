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
	printf("Введите первое многоразрядное число\n");
	scanf_s("%99s", str1, (unsigned)_countof(str1));
	printf("Введите второе многоразрядное число\n");
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
	printf("Введите короткое целое число\n");
	while (size3 > size1 || size3 > size2 || num3 < 1) {
		scanf_s("%i", &num3);
		while (temp) {	// количество разрядов short int
			temp /= 10;
			size3++;
		}
		if (size3 > size1 || size3 > size2 || num3 < 1)
			printf("Попробуйте снова\n");
	}

	while (1)
	{
		switch (menu())
		{
		case 1:
			e = Equal(&num1L, &num1R, &num2L, &num2R);
			if (e == 1)
				printf("Первое многоразрядное число больше второго\n");
			if (e == 0)
				printf("Первое многоразрядное число равно второму\n");
			if (e == -1)
				printf("Первое многоразрядное число меньше второго\n");
			break;
		case 2:
			printf("Остаток от деления первого многоразрядного числа на короткое целое число:\t%d\n", LongModShort(&num1L, &num1R, num3));
			printf("Остаток от деления второго многоразрядного числа на короткое целое число:\t%d\n", LongModShort(&num2L, &num2R, num3));
			break;
		case 3:
			printf("Целая часть от деления первого многоразрядного числа на короткое целое число:\t"); LongDivShort(&num1L, &num1R, num3); printf("\n");
			printf("Целая часть от деления второго многоразрядного числа на короткое целое число:\t"); LongDivShort(&num2L, &num2R, num3); printf("\n");
			break;
		case 4:
			printf("Первое многоразрядное число умножить на короткое целое число:\t");  LongMulShort(&num1L, &num1R, num3); printf("\n");
			printf("Второе многоразрядное число умножить на короткое целое число:\t");  LongMulShort(&num2L, &num2R, num3); printf("\n");
			break;
		case 0:
			DeleteAllDigits(&num1L, &num1R);
			DeleteAllDigits(&num2L, &num2R);
			getchar();
			return 0;
		default: printf("Попробуйте снова\n");
		}
	}
}

// создаем многоразрядное число (очередь) и ставим барьеры
void NewMNum(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	*numL = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber));	// указатель на левый барьер
	*numR = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber)); // указатель на правый барьер
	(*numL)->left = NULL;		// установка связей между элементами numL и numR
	(*numL)->right = *numR;
	(*numR)->left = *numL;
	(*numR)->right = NULL;
	return;
}

// функция добавления цифры в многоразрядное число
void AddDigit(MultiDigitalNumber* numR, int digit) {
	MultiDigitalNumber* spt = NULL;
	spt = (MultiDigitalNumber*)malloc(sizeof(MultiDigitalNumber));	// указатель на новый элемент
	spt->digit = digit;
	spt->left = numR->left;		// установка связей между добавляемым элементом и старыми элементами
	spt->right = numR;
	spt->left->right = spt;
	numR->left = spt;
	return;
}

// просмотр многоразрядного числа (очереди)
void ViewMNumber(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// указатель на первый элемент очереди (старший разряд)
	while (spt != *numR)	// цикл прохода числа
	{
		printf("%d", spt->digit);
		spt = spt->right;	// переход на следующий разряд
	}
	return;
}

// функция, возвращающая размер числа (количество элементов очереди)
int Size_(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// указатель на первый элемент очереди (старший разряд)
	int size_ = 0;
	while (spt != *numR)	// цикл прохода числа
	{
		spt = spt->right;
		size_++;
	}
	return size_;
}

// функция сравнения двух многоразрядных чисел
int Equal(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, MultiDigitalNumber** num2L, MultiDigitalNumber** num2R) {
	MultiDigitalNumber* spt1 = (*num1L)->right;	// указатель старший разряд первого числа
	MultiDigitalNumber* spt2 = (*num2L)->right;	// указатель старший разряд второго числа
	int size1 = Size_(num1L, num1R), size2 = Size_(num2L, num2R);	// высчитываем количество разрядов первого и второго числа и далее сравниваем >, < или =
	if (size1 > size2)
		return 1;
	else if (size1 < size2)
		return -1;
	else if (size1 == size2)	// если =, то необходимо сравнить значение разрядов, начиная с первого, пока он не будет >, < или пока разряды не закончатся
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

// остаток от деления на short int
int LongModShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	int del = 0;
	MultiDigitalNumber* spt = (*num1L)->right;	// указатель на старший разряд

	while (spt != *num1R)	// цикл прохода числа с делением на short int
	{
		del = del * 10 + spt->digit;
		spt = spt->right;
		del %= num3;
	}
	return del;
}

// целая часть от деления на short int
MultiDigitalNumber* LongDivShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	MultiDigitalNumber* divL = NULL, * divR = NULL;
	if (divL == NULL) NewMNum(&divL, &divR);	// создание нового числа для хранения делимого
	int del = 0;
	MultiDigitalNumber* spt = (*num1L)->right;	// указатель на  старший разряд

	while (spt != *num1R)		// цикл прохода числа с делением на short int
	{
		del = del * 10 + spt->digit;
		spt = spt->right;
		AddDigit(divR, del / num3);
		del %= num3;
	}
	while (divL->right->digit == 0)	//удаляем ненужные нулевые старшие разряды
	{
		divL = DeleteDigitLeft(&divL);
	}
	ViewMNumber(&divL, &divR);
	return divL;
}

// функция для удаления старших разрядов
MultiDigitalNumber* DeleteDigitLeft(MultiDigitalNumber** numL) {
	MultiDigitalNumber* spt = (*numL)->right;	// указатель на  старший разряд
	MultiDigitalNumber* tmp = spt;
	spt->left->right = spt->right;	// переопределение связей
	spt->right->left = spt->left;
	free(tmp);		// удаление элемента
	spt = (*numL)->right;
	return spt->left;
}

// функция умножения на short int
MultiDigitalNumber* LongMulShort(MultiDigitalNumber** num1L, MultiDigitalNumber** num1R, int num3) {
	int size = 0, temp = num3, count = 0;
	while (temp) {	// количество разрядов short int
		temp /= 10;
		size++;
	}
	size += Size_(num1L, num1R);	// +количество разрядов многоразрядного числа
	MultiDigitalNumber* numL = NULL, * numR = NULL;
	if (numL == NULL) NewMNum(&numL, &numR);	// создание нового числа, для хранения результата умножения
	for (int i = 0; i < size; i++)		// разряды нового числа в количестве size заролняем нулями
		AddDigit(numR, 0);
	int digit = 0, pos = 0;
	MultiDigitalNumber* spt = (*num1R)->left, * spt1 = numR->left;	//указатели на младший разряд
	int mod = num3 % 10;	// первая цифра, на которую умножаем
	num3 = num3 / 10;

	while (mod != 0) {		// выполняем умножение
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
	while (numL->right->digit == 0)	//удаляем ненужные нулевые старшие разряды
	{
		numL = DeleteDigitLeft(&numL);
	}
	ViewMNumber(&numL, &numR);
	return numL;
}

//функция удаления всего числа
void DeleteAllDigits(MultiDigitalNumber** numL, MultiDigitalNumber** numR) {
	MultiDigitalNumber* spt = (*numL)->right;	// указатель на старший разряд
	while (spt != *numR)		// цикл прохода числа с соответствующим удалением разрядов
	{
		MultiDigitalNumber* tmp = spt;
		spt->left->right = spt->right;	// переопределение связей
		spt->right->left = spt->left;
		free(tmp);
		spt = (*numL)->right;
	}
	free(*numL); *numL = NULL;	// удаление барьеров и их установка в NULL
	free(*numR); *numR = NULL;
	printf("Многоразрядное число удалено\n");
	return;
}

int menu() {
	int i = 0;
	printf("Выберите:\n");
	printf("1. Сравнение двух многоразрядных:\n");
	printf("2. Остаток от деления на короткое число:\n");
	printf("3. Целая часть от деления на короткое число:\n");
	printf("4. Умножение на короткое число:\n");
	printf("0. Выход:\n");
	scanf_s("%i", &i);
	return i;
}
