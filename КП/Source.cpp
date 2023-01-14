#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#define _USE_MATH_DEFINES

//��� �������, ��������������� ��� ������ ������, ����� ��� void
void table(int** array, int M, int N); //������� �������� ������
void total_points(int** array, int M, int N); //������� ����� ����� ������� ������
void rating(int** array, int M, int N); //������� �������
void general_table(int** array, int M, int N); //������� ����� �������
//��������� - �� ��� void
int** LoadFromFile(char* filename, int* M, int* N); //������ ������ �� �����
char Menu();
int SumLine(int** array, int M, int N, int Line); //����� ����� ����������� ������
int Sum(int** array, int M, int N); //��������� ����� �����
int RatingLine(int** array, int M, int N, int Line); //������� ����������� ������
int Rating(int** array, int M, int N); //��������� ��������
int** AddLine(int** array, int* M, int N); //�������� ����� �������
void EditLine(int** array, int M, int N, int Line);//������������� �������
int ReadNumber(int min, int max);//��������� ����� ����� � �������� ���������
void printBest(int** array, int M, int N); //������� ������ ���������
void printWorse(int** array, int M, int N); //������� ������ ���������

int main()
{
	system("chcp 1251>nul"); //��������� ������� ������� ��� ������ � �����

	int** A; //������� ������
	char filename[200]; //��� �����
	int M, N; //����������� �������
	printf("������� �������� ����� � ��� ������:");
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
			printf("\n����� ���� �� �������");
			printf("\n\n");
			break;
		}
	}
}

void table(int** array, int M, int N) //������� �������� ������
{
	printf("                  ���������� �����\n");
	printf("                      ��������� ���\n");
	printf("   ��       1 ����        2 ����        3 ����       \n");
	printf("   ���     15    15      15    15      15    15      \n");
	printf("          ����� �����  �����  �����  �����  �����\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N + 1; j++)
			printf("%5d  ", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

void total_points(int** array, int M, int N) //������� ����� ����� ������� ������
{
	puts("  \n  ���������� �����\n");
	puts("   ��     �����");
	puts("   ���    �����");
	puts("          ");
	for (int i = 0; i < M; i++)
		printf("%6d%7d\n", array[i][0], SumLine(array, M, N, i));
}

void rating(int** array, int M, int N) //������� �������
{
	puts(" \n  ���������� �����\n");
	puts("   ��      ���");
	puts("   ���     ����");
	puts("         ");
	for (int i = 0; i < M; i++)
	{
		printf("%5d %5d\n", array[i][0], RatingLine(array, M, N, i));
	}
	printf("\n");
}

void general_table(int** array, int M, int N) //������� ����� �������
{
	puts("                  ���������� �����\n");
	puts("                      ��������� ���");
	puts("   ��       1 ����        2 ����        3 ����      �����   ���");
	puts("   ���     15    15      15    15      15    15     �����   ����");
	puts("          ����� �����  �����  �����  �����  �����");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j <= N + 2; j++)
			printf("%6d ", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

int** LoadFromFile(char* filename, int* M, int* N) //������ ������ �� �����
{
	FILE* F = fopen(filename, "r");
	if (F == NULL)
	{
		*M = 0;
		*N = 0;
		perror("�� ������� ������� ����.\n������");
		exit(0); //��� �����
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
	printf("����:\n");
	printf("1.�������� ������;\n");
	printf("2.����� ����� ������� ������;\n");
	printf("3.�������;\n");
	printf("4.����� �������;\n");
	printf("5.�������� �������;\n");
	printf("6.��������� �������;\n");
	printf("7.������ ���������;\n");
	printf("8.������ ���������;\n");
	printf("9.�����.\n");
	printf("�������� ����� ����:");
	scanf(" %c", &command);
	getchar();
	return command;
}

int SumLine(int** array, int M, int N, int Line) //����� ����� ����������� ������
{
	int result = 0;
	for (int i = 1; i <= N; i++)
		result += array[Line][i];
	return result;
}

int Sum(int** array, int M, int N) //��������� ����� �����
{
	for (int i = 0; i < M; i++)
		array[i][N + 1] = SumLine(array, M, N, i);
	return 1;
}

int RatingLine(int** array, int M, int N, int Line) //������� ����������� ������
{
	int result = 0;
	for (int i = 0; i < M; i++)
		if (array[i][N + 1] <= array[Line][N + 1])
			result++;
	return result;
}

int Rating(int** array, int M, int N) //��������� ��������
{
	for (int i = 0; i < M; i++)
		array[i][N + 2] = RatingLine(array, M, N, i);
	return 1;
}

int** AddLine(int** array, int* M, int N) //�������� ����� �������
{
	array = (int**)realloc(array, sizeof(int*) * ((*M) + 1));
	array[*M] = (int*)malloc(sizeof(int) * (N + 2));
	array[*M][0] = (*M) + 1;
	(*M)++;
	return array;
}

void EditLine(int** array, int M, int N, int Line)//������������� �������
{
	for (int k = 1; k <= N; k++)
	{
		printf("Set %d = ", k); scanf("%d", &array[Line][k]);
	}
	getchar();
}

int ReadNumber(int min, int max)//��������� ����� ����� � �������� ���������
{
	char buffer[20];
	int result = min - 1;
	while (result<min || result>max)
	{
		printf("����� :");
		gets_s(buffer, sizeof(buffer));
		result = atoi(buffer);
	}
	return result;
}


void printBest(int** array, int M, int N) //������� ������ ���������
{
	printf("\n������ ���������\n");
	printf("����� �������\n");
	for (int k = 0; k < M; k++)
		if (array[k][N + 2] == 1)
			printf("%4d %4d", array[k][0], array[k][N + 2]);
	printf("\n\n");
}
void printWorse(int** array, int M, int N) //������� ������ ���������
{
	printf("\n������ ���������\n");
	printf("����� �������\n");
	for (int k = 0; k < M; k++)
		if (array[k][N + 2] == M)
			printf("%4d %4d", array[k][0], array[k][N + 2]);
	printf("\n\n");
}
