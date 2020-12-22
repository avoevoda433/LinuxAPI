// Библиотеки
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Функции
void addNewGraph(void); // Добавление нового графа
void setGraphInfo(void); // Заполнение массивов вершин и ребер
void showGraphInfo(void); // Вывод информации о графе

// Структура графоф
struct Graph
{
    // Массивы вершин и ребер графа
    char name[1];
    char *vertices, **edges;
    int v_count, e_count;

};

// Объявляем тип данных "граф"
typedef struct Graph graph;

// Создаем массив структур
graph *graphs = NULL;
int graphCount = 1;


int main(void)
{
    int choise;
    do
    {
        printf("\n\n%s\n%s\n%s\n", "(1) Добавить граф", 
                                 "(2) Информация о графе", 
                                 "(0) Выход");

        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                addNewGraph();
                break;

            case 2:
                showGraphInfo();
                break;

            case 0:
                break;
        
            default:
                main();
        }

    } while (choise != 0);
    
    
    return 0;
}


void addNewGraph()
{
    graphs = (graph*)realloc(graphs, graphCount*sizeof(graph));
    graphCount++;
    setGraphInfo();
}


// Функция для заполнения массивов верши и ребер согласно вводу пользователя
void setGraphInfo()
{
    // Количество вершин и ребер на данный момент
    int v_count = 1;
    int e_count = 1;

    // Переменная определяет, будет ли добавлено ребро
    int add_edge = 0;

    char symbol;

    printf("\nВведите имя графа: ");
    scanf("%s", (graphs+(graphCount-2))->name);

    printf("Введите граф: ");
    while (1)
    {
        // Получаем значение символа
        symbol = getc(stdin);

        // Проверка: является ли символ вершиной?
        if ((int)symbol != 45 && 
            (int)symbol != 47 &&
            (int)symbol != 124)
            {
               // Проверка: необходимо ли добавить ребро?
                if (add_edge == 1)
                {
                    // Выделение памяти и добавление элемента в массив вершин
                    (graphs+(graphCount-2))->vertices = (char*)realloc((graphs+(graphCount-2))->vertices, v_count*sizeof(char));
                    (graphs+(graphCount-2))->vertices[v_count-1] = symbol;

                    // Выделение памяти и добавление элемента в массив ребер
                    (graphs+(graphCount-2))->edges = (char**)realloc((graphs+(graphCount-2))->edges, e_count*sizeof(char*));
                    (graphs+(graphCount-2))->edges[e_count-1] = (char*)malloc(2*sizeof(char));
                    (graphs+(graphCount-2))->edges[e_count-1][0] = (graphs+(graphCount-2))->vertices[v_count-2];
                    (graphs+(graphCount-2))->edges[e_count-1][1] = (graphs+(graphCount-2))->vertices[v_count-1];
                   
                    v_count++;
                    e_count++;
                }
                else
                {
                     // Выделение памяти и добавление элемента в массив вершин
                    (graphs+(graphCount-2))->vertices = (char*)realloc((graphs+(graphCount-2))->vertices, v_count*sizeof(char));
                    (graphs+(graphCount-2))->vertices[v_count-1] = symbol;
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

    // Записываем количество вершин и ребер
    (graphs+(graphCount-2))->v_count = v_count-1;
    (graphs+(graphCount-2))->e_count = e_count-1;
}


void showGraphInfo(void)
{
    char findGraphName[1];
    
    printf("\nВведите имя графа: ");
    scanf("%s", findGraphName);

    // Поиск совпадений
    for (int i = 0; i < graphCount-1; i++)
    {
        if (strspn(findGraphName, (graphs+i)->name) == 1)
        {
            printf("\nИмя графа: %s\n", findGraphName);

            // Вывод массива вершин
            printf("Вершины графа: ");
            for (int j = 1; j < (graphs+i)->v_count; j++)
            {
                printf("%c%s", (graphs+i)->vertices[j], (j==(graphs+i)->v_count-1 ? "\n" : ", "));
            }

            // Вывод массива ребер
            printf("Ребра графа: ");
            for (int k = 0; k < (graphs+i)->e_count; k++)
            {
                printf("(%c,%c)%s", (graphs+(graphCount-2))->edges[i][0], (graphs+(graphCount-2))->edges[i][1], (i==(graphs+i)->e_count-1 ? "\n" : " "));
            }
        }
    }
}
    
