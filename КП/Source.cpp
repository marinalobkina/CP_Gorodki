#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#define _USE_MATH_DEFINES

//Все функции, предназначенные для вывода таблиц, имеют тип void
void table(int** array, int M, int N); //Выводит исходные данные
void total_points(int** array, int M, int N); //Выводит сумму очков каждого города
void rating(int** array, int M, int N); //Выводит рейтинг
void general_table(int** array, int M, int N); //Выводит общую таблицу
//остальные - не тип void
int** LoadFromFile(char* filename, int* M, int* N); //Читает данные из файла
char Menu();
int SumLine(int** array, int M, int N, int Line); //Сумма очков добавленной строки
int Sum(int** array, int M, int N); //Заполнить суммы очков
int RatingLine(int** array, int M, int N, int Line); //Рейтинг добавленной строки
int Rating(int** array, int M, int N); //Заполнить рейтинги
int** AddLine(int** array, int* M, int N); //Добавить новую строчку
void EditLine(int** array, int M, int N, int Line);//Редактировать строчку
int ReadNumber(int min, int max);//Прочитать целое число в заданном интервале
void printBest(int** array, int M, int N); //Вывести лучший результат
void printWorse(int** array, int M, int N); //Вывести худший результат

int main()
{
	system("chcp 1251>nul"); //Настройка кодовой таблицы для вывода и ввода

	int** A; //Рабочий массив
	char filename[200]; //имя файла
	int M, N; //Размерность массива
	printf("Введите название файла и его формат:");
	scanf("%s", &filename);
	A = LoadFromFile(filename, &M, &N);
	Sum(A, M, N);
	Rating(A, M, N);
	while (true)
	{
		switch (Menu())
		{
		case '1':
			table(A, M, N);
			break;
		case '2':
			total_points(A, M, N);
			break;
		case '3':
			rating(A, M, N);
			break;
		case '4':
			general_table(A, M, N);
			break;
		case '5':
			A = AddLine(A, &M, N);
			EditLine(A, M, N, M - 1);
			Sum(A, M, N);
			Rating(A, M, N);
			break;
		case '6':
		{
			int line = ReadNumber(1, M - 1);
			EditLine(A, M, N, line - 1);
			Sum(A, M, N);
			Rating(A, M, N);
		}
		case '7':
			printBest(A, M, N);
			break;
		case '8':
			printWorse(A, M, N);
			break;
		case '9':
			return 0;
		default:
			printf("\nПункт меню не опознан");
			printf("\n\n");
			break;
		}
	}
}

void table(int** array, int M, int N) //Выводит исходные данные
{
	printf("                  Городошный спорт\n");
	printf("                      Затрачено бит\n");
	printf("   Го       1 день        2 день        3 день       \n");
	printf("   род     15    15      15    15      15    15      \n");
	printf("          фигур фигур  фигур  фигур  фигур  фигур\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N + 1; j++)
			printf("%5d  ", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

void total_points(int** array, int M, int N) //Выводит сумму очков каждого города
{
	puts("  \n  Городошный спорт\n");
	puts("   Го     Сумма");
	puts("   род    очков");
	puts("          ");
	for (int i = 0; i < M; i++)
		printf("%6d%7d\n", array[i][0], SumLine(array, M, N, i));
}

void rating(int** array, int M, int N) //Выводит рейтинг
{
	puts(" \n  Городошный спорт\n");
	puts("   Го      Рей");
	puts("   род     тинг");
	puts("         ");
	for (int i = 0; i < M; i++)
	{
		printf("%5d %5d\n", array[i][0], RatingLine(array, M, N, i));
	}
	printf("\n");
}

void general_table(int** array, int M, int N) //Выводит общую таблицу
{
	puts("                  Городошный спорт\n");
	puts("                      Затрачено бит");
	puts("   Го       1 день        2 день        3 день      Сумма   Рей");
	puts("   род     15    15      15    15      15    15     очков   тинг");
	puts("          фигур фигур  фигур  фигур  фигур  фигур");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j <= N + 2; j++)
			printf("%6d ", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

int** LoadFromFile(char* filename, int* M, int* N) //Читает данные из файла
{
	FILE* F = fopen(filename, "r");
	if (F == NULL)
	{
		*M = 0;
		*N = 0;
		perror("Не удалось открыть файл.\nОшибка");
		exit(0); //Нет файла
	}
	fscanf(F, "%d", M);
	fscanf(F, "%d", N);
	int** result = (int**)malloc((*M) * sizeof(int*));
	for (int r = 0; r < *M; r++)
	{
		result[r] = (int*)malloc((*N) * sizeof(int));
		for (int c = 0; c < (*N) + 2; c++)
			fscanf(F, "%d", &result[r][c]);
	}
	fclose(F);
	return result;
}

char Menu()
{
	char command;
	printf("Меню:\n");
	printf("1.Исходные данные;\n");
	printf("2.Сумма очков каждого города;\n");
	printf("3.Рейтинг;\n");
	printf("4.Общая таблица;\n");
	printf("5.Добавить строчку;\n");
	printf("6.Исправить строчку;\n");
	printf("7.Лучший результат;\n");
	printf("8.Худший результат;\n");
	printf("9.Выход.\n");
	printf("Выберите пункт меню:");
	scanf(" %c", &command);
	getchar();
	return command;
}

int SumLine(int** array, int M, int N, int Line) //Сумма очков добавленной строки
{
	int result = 0;
	for (int i = 1; i <= N; i++)
		result += array[Line][i];
	return result;
}

int Sum(int** array, int M, int N) //Заполнить суммы очков
{
	for (int i = 0; i < M; i++)
		array[i][N + 1] = SumLine(array, M, N, i);
	return 1;
}

int RatingLine(int** array, int M, int N, int Line) //Рейтинг добавленной строки
{
	int result = 0;
	for (int i = 0; i < M; i++)
		if (array[i][N + 1] <= array[Line][N + 1])
			result++;
	return result;
}

int Rating(int** array, int M, int N) //Заполнить рейтинги
{
	for (int i = 0; i < M; i++)
		array[i][N + 2] = RatingLine(array, M, N, i);
	return 1;
}

int** AddLine(int** array, int* M, int N) //Добавить новую строчку
{
	array = (int**)realloc(array, sizeof(int*) * ((*M) + 1));
	array[*M] = (int*)malloc(sizeof(int) * (N + 2));
	array[*M][0] = (*M) + 1;
	(*M)++;
	return array;
}

void EditLine(int** array, int M, int N, int Line)//Редактировать строчку
{
	for (int k = 1; k <= N; k++)
	{
		printf("Set %d = ", k); scanf("%d", &array[Line][k]);
	}
	getchar();
}

int ReadNumber(int min, int max)//Прочитать целое число в заданном интервале
{
	char buffer[20];
	int result = min - 1;
	while (result<min || result>max)
	{
		printf("целое :");
		gets_s(buffer, sizeof(buffer));
		result = atoi(buffer);
	}
	return result;
}


void printBest(int** array, int M, int N) //Вывести лучший результат
{
	printf("\nЛучший результат\n");
	printf("Город рейтинг\n");
	for (int k = 0; k < M; k++)
		if (array[k][N + 2] == 1)
			printf("%4d %4d", array[k][0], array[k][N + 2]);
	printf("\n\n");
}
void printWorse(int** array, int M, int N) //Вывести худший результат
{
	printf("\nХудший результат\n");
	printf("Город рейтинг\n");
	for (int k = 0; k < M; k++)
		if (array[k][N + 2] == M)
			printf("%4d %4d", array[k][0], array[k][N + 2]);
	printf("\n\n");
}
