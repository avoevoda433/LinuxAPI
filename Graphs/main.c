// Библиотеки
#include <stdio.h>
#include <malloc.h>

// Функции
void setGraphInfo(char*, char**); // Заполнение массивов вершин и ребер
void showVerticed(char*, int); // Вывод массива вершин
void showEdges(char**, int); // Вывод массива ребер


int main(void)
{
    // Массивы вершин и ребер графа
    char *vertices = NULL;
    char **edges = NULL;

    setGraphInfo(vertices, edges);
    
    return 0;
}


// Функция для заполнения массивов верши и ребер согласно вводу пользователя
void setGraphInfo(char *verticed, char **edges)
{
    // Количество вершин и ребер на данный момент
    int v_count = 1;
    int e_count = 1;

    // Переменная определяет, будет ли добавлено ребро
    int add_edge = 0;

    char symbol;

    printf("Введите граф: ");
    while (1)
    {
        // Получаем значение символа
        symbol = getc(stdin);

        // Проверка? является ли символ вершиной?
        if ((int)symbol != 45 && 
            (int)symbol != 47 &&
            (int)symbol != 124)
            {
               // Проверка: необходимо ли добавить ребро?
                if (add_edge == 1)
                {
                    // Выделение памяти и добавление элемента в массив вершин
                    verticed = (char*)realloc(verticed, v_count*sizeof(char));
                    *(verticed+(v_count-1)) = symbol;

                    // Выделение памяти и добавление элемента в массив ребер
                    edges = (char**)realloc(edges, e_count*sizeof(char*));
                    edges[e_count-1] = (char*)malloc(2*sizeof(char));
                    *(edges[e_count-1]+0) = *(verticed+(v_count-2));
                    *(edges[e_count-1]+1) = *(verticed+(v_count-1));

                    v_count++;
                    e_count++;
                }
                else
                {
                     // Выделение памяти и добавление элемента в массив вершин
                    verticed = (char*)realloc(verticed, v_count*sizeof(char));
                    *(verticed+(v_count-1)) = symbol;
                    v_count++;
                }
            }

        // Если символ указывает на связь вершин - изменить переменную, чтобы добавить ребро
        else if ((int)symbol == 45) add_edge = 1;

        // Если символ указывает на отсутствие связи - присвоить переменной противоположное значение
        else if ((int)symbol == 47) add_edge = 0;

        // Если символ является конечным - прервать цикл
        else if ((int)symbol == 124) break;
    }

    showVerticed(verticed, v_count-1);
    showEdges(edges, e_count-1);
}


// Вывод массива вершин
void showVerticed(char *verticed, int m)
{
    printf("Вершины графа:\n");
    for (int i = 0; i < m; i++)
    {
        printf("%c%s", *(verticed+i), (i==m-1 ? "\n" : " "));
    }
}


// Вывод массива ребер
void showEdges(char **edges, int m)
{
    printf("Ребра графа:\n");
    for (int i = 0; i < m; i++)
    {
        printf("(%c,%c)%s", *(edges[i]+0), *(edges[i]+1), (i==m-1 ? "\n" : " "));
    }
}

// Добавить функцию, которая будет удалять повторяющиеся вершины из массива вершин