// Библиотеки
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

// Основные константы
#define X 88 // значение "Х" в таблице ASCCI
#define O 79 // значение "О" в таблице ASCCI
#define FREE 32 // значение " " в таблице ASCCI
#define CELL_COUNT 9 // количество ячеек игрового поля

// Объявление функций
void displayGameField(char*, int); // Функция демонстрации игрового поля
void updateGameField(char*, int); // Функция обновления экрана
int checkWin(char*, int); // Проверка на победу
void sendWinMessage(int); // Сообщение в случае победы
void sendDrawMessage(int); // Сообщенеи в случае ничьей


int main(void)
{
    int move = 1; // нечетное значение - "X", четное значение - "O"
    int choise;
    
    // Создание игрового поля
    char *field = NULL;
    // Выделение памяти
    field = (char*)malloc(CELL_COUNT*sizeof(char));
    for (int i = 0; i < CELL_COUNT; i++)
    {
        *(field+i) = FREE;
    }
    
    // Первоначальная демонстрация игрового поля
    updateGameField(field, move);

    // Главный игровой цикл
	do
    {
        int successMove = 0; // равно 0, пока ход не совершен

        do
        {
			// Ввод цифры для совершения хода
            do
            {
                scanf("%d", &choise);
				updateGameField(field, move);

            } while (choise < 0 && choise > 10);

			// Проверка выбранной ячейки
			if (*(field+choise-1) == FREE)
			{
				if (move % 2 == 0) 
				{
					*(field+choise-1) = O;
					successMove = 1;
				}

				else
				{
					*(field+choise-1) = X;
                	successMove = 1;
				}
			}

        } while (!successMove);
        
		 move++;
        updateGameField(field, move);

    } while (checkWin(field, move));

	// Проверка результата игры
	if (!checkWin(field, move-1)) 
	{
		sendWinMessage(move);

		scanf("%d", &choise);
		if (choise == 1) main();
	}
	else
	{
		sendDrawMessage(move);

		scanf("%d", &choise);
		if (choise == 1) main();
	}
	
    return 0;
}


// Функция демонстрации игрового поля
void displayGameField(char *field, int move)
{
	printf("---------------------------------------------------\n");
	printf("\tИгровое поле\t|\tУправление\n");
	printf("---------------------------------------------------\n");
    for (int i = 0; i < CELL_COUNT; i+=3)
    {
        printf("\t [%c][%c][%c]\t|\t[%d][%d][%d]\n", *(field+i), *(field+i+1), *(field+i+2), (i+1), (i+2), (i+3));
    }
	printf("---------------------------------------------------\n");
	printf("\t\t    Ходят - %c\n", (move%2==0 ? O : X));
	printf("---------------------------------------------------\n");
    
}


// Функция обновления экрана
void updateGameField(char *field, int move)
{
	system("clear");
    displayGameField(field, move);
}


// Сообщение в случае победы
void sendWinMessage(int move)
{
	printf("\t\t   Победили - %c\n", ((move-1)%2==0 ? O : X));
	printf("---------------------------------------------------\n");
	printf("\t   Играть снова (1) Да / (0) Нет\n");
}


// Сообщенеи в случае ничьей
void sendDrawMessage(int move)
{
	printf("\t\t      Ничья \n");
	printf("---------------------------------------------------\n");
	printf("\t   Играть снова (1) Да / (0) Нет\n");
}


// Проверка на победу
int checkWin(char *f, int move)
{
	// Проверка строк
	if (*(f+0)==*(f+1) && *(f+1)==*(f+2) && *(f+0)!=FREE && *(f+1)!=FREE && *(f+2)!=FREE) return 0;
	else if (*(f+3)==*(f+4) && *(f+4)==*(f+5) && *(f+3)!=FREE && *(f+4)!=FREE && *(f+5)!=FREE) return 0;
	else if (*(f+6)==*(f+7) && *(f+7)==*(f+8) && *(f+6)!=FREE && *(f+7)!=FREE && *(f+8)!=FREE) return 0;
	// Проверка столбцов
	else if (*(f+0)==*(f+3) && *(f+3)==*(f+6) && *(f+0)!=FREE && *(f+3)!=FREE && *(f+6)!=FREE) return 0;
	else if (*(f+1)==*(f+4) && *(f+4)==*(f+7) && *(f+1)!=FREE && *(f+4)!=FREE && *(f+7)!=FREE) return 0;
	else if (*(f+2)==*(f+5) && *(f+5)==*(f+8) && *(f+2)!=FREE && *(f+5)!=FREE && *(f+8)!=FREE) return 0;
	// Проверка диагоналей
	else if (*(f+0)==*(f+4) && *(f+4)==*(f+8) && *(f+0)!=FREE && *(f+4)!=FREE && *(f+8)!=FREE) return 0;
	else if (*(f+2)==*(f+4) && *(f+4)==*(f+6) && *(f+2)!=FREE && *(f+4)!=FREE && *(f+6)!=FREE) return 0;
	// Условие победы не выполнено
	else 
	{
		if (move == 10) return 0;
		else return 1;
	}
}