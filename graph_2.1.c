#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertice1;
    int vertice2;
    int edge;
    struct node* next;
} node_t;

void push(node_t** head, int vertice1, int vertice2) {
    node_t* tmp = (node_t*)calloc(sizeof(node_t), 1);
    if(tmp == NULL) return;
    tmp->vertice1 = vertice1;
    tmp->vertice2 = vertice2;
    tmp->edge = 1;
    tmp->next = (*head);
    (*head) = tmp;
}

/* ЗАПИСЬ СВЯЗЕЙ В ФАЙЛ */
void print_to_file(node_t* head, FILE* file) {
    fprintf(file, "graph graphname {\n");
    while(head != NULL) {
        if(head->edge == 1) {
            fprintf(file, "%d", head->vertice1);
            if(head->vertice2 != 0) {
                fprintf(file, " -- ");
                fprintf(file, "%d", head->vertice2);
            }
            fprintf(file, ";\n");
        }
        else {
            fprintf(file, "%d;\n", head->vertice1);
            if(head->vertice2 != 0) {
                fprintf(file, "%d;\n", head->vertice2);
            }
        }
        head = head->next;
    }
    fprintf(file, "}");
}

/* ДОБАВЛЕНИЕ СВЯЗЕЙ МЕЖДУ ВЕРШИНАМИ */
void add_edges(node_t** head) {
    while(1) {
        char c;
        int a = 0;
        int b = 0;
        int i = 0;
        int j = 0;
        int m = 1;
        int k, f;

        /* СЧИТЫВАНИЕ ИЗ КОНСОЛИ*/
        char str[7];
        while((c = getchar()) != '\n') {
            str[i] = c;
            i++;
        }

        /* ПРЕКРАЩЕНИЕ СЧИТЫВАНИЯ РЁБЕР*/
        if(str[0] == '-' && str[1] == '1') {
            break;
        }

        /* НАЙТИ ПОЗИЦИИ РАЗДЕЛИТЕЛЯ*/
        while(str[j] != '-') {
            j++;
        }

        /* ПОЛУЧЕНИЕ ПЕРВОЙ ВЕРШИНЫ*/
        k = j-1;
        while(k != -1) {
            a = a + m*(str[k] - '0');
            m = 10*m;
            k--;
        }

        /* ПОЛУЧЕНИЕ ВТОРОЙ ВЕРШИНЫ*/
        f = i-1;
        m = 1;
        while(f != j) {
            b = b + m*(str[f] - '0');
            m = 10*m;
            f--;
        }

        push(head, a, b);
    }
}

/* СОРТИРОВКА ВЕРШИН */
int vertice_sort(node_t* head) {
    int n = 0;
    int k = 0;
    int y;

    node_t* tmp = head;
    node_t* tmp1 = head;
    node_t* tmp2 = head;

    while(head != NULL) {
        n++;
        head = head->next;
    }

    int arr[n*2];

    for(int i = 0; i < n*2; i = i + 2) {
        arr[i] = tmp->vertice1;
        arr[i+1] = tmp->vertice2;
        tmp = tmp->next;
    }

    for(int i = 0; i < n*2 - 1; i++) {
        for(int j = i + 1; j < n*2; j++) {
            if(arr[i] != -1 && arr[i] == arr[j]) {
                arr[j] = -1;
            }
        }
    }

    for(int i = 0; i < n*2; i++) {
        if(arr[i] != -1 && arr[i] != 0) k++;
    }

    //printf("k = %d\n\n", k);

    y = k;
	int arr2[2][k];
    k = 0;
    for(int i = 0; i < n*2; i++) {
        if(arr[i] != -1 && arr[i] != 0) {
            arr2[1][k] = arr[i];
            arr2[2][k] = 0;
            k++;
        }
    }

    for(int j = 0; j < y; j++) {
        while(tmp1 != NULL) {
            if((arr2[1][j] == tmp1->vertice1) && (tmp1->vertice2 != 0) && (tmp1->edge == 1)) {
                arr2[2][j]++;
            }
            else if((arr2[1][j] == tmp1->vertice2) && (tmp1->vertice2 != 0) && (tmp1->edge == 1)) {
                arr2[2][j]++;
            }
            tmp1 = tmp1->next;
        }
        tmp1 = tmp2;
    }


    for(int j = 1; j < k; j++)
        for(int i = 0; i < k-1; i++)
            if(arr2[2][i] < arr2[2][i+1]) {
                int x = arr2[2][i];
                arr2[2][i] = arr2[2][i+1];
                arr2[2][i+1] = x;
                int x1 = arr2[1][i];
                arr2[1][i] = arr2[1][i+1];
                arr2[1][i+1] = x1;
            }

    for(int i = 0; i < y; i++) {
        printf("Vertice %d amount %d\n", arr2[1][i], arr2[2][i]);
    }
    return y;
}


/* УДАЛЕНИЕ ОПРЕДЕЛЕННОГО РЕБРА */
void edge_remove(node_t** thead, node_t* head) {
    //node_t *tmp = head;
    char c;
    int a = 0;
    int b = 0;
    int i = 0;
    int j = 0;
    int m = 1;
    int k, f;

    int flag = 0;
    int n = 0;

    /* СЧИТЫВАНИЕ ИЗ КОНСОЛИ*/
    char str[7];
    while((c = getchar()) != '\n') {
        str[i] = c;
        i++;
    }

    /* НАЙТИ ПОЗИЦИИ РАЗДЕЛИТЕЛЯ*/
    while(str[j] != '-') {
        j++;
    }

    /* ПОЛУЧЕНИЕ ПЕРВОЙ ВЕРШИНЫ*/
    k = j-1;
    while(k != -1) {
        a = a + m*(str[k] - '0');
        m = 10*m;
        k--;
    }

    /* ПОЛУЧЕНИЕ ВТОРОЙ ВЕРШИНЫ*/
    f = i-1;
    m = 1;
    while(f != j) {
        b = b + m*(str[f] - '0');
        m = 10*m;
        f--;
    }

    /*ПОИСК НУЖНОГО РЕБРА В ОДНОСВЯЗНОМ СПИСКЕ*/
    while(head != NULL) {
        n++;
        if(head->vertice1 == a && head->vertice2 == b) {
            flag = 1;
            head->edge = 0;

        }
        else if(head->vertice1 == b && head->vertice2 == a) {
            flag = 1;
            head->edge = 0;

        }
        head = head->next;
    }

    if(flag == 0) {
        printf("There is no such edge\n\n");
    }
}

int main(void)
{
    node_t* head = NULL;

    FILE *file;
    file = fopen("graph.dot", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    printf("GRAPH var1 - Feodor Ryzhov IU4-32b\n");
    printf("You can enter edges like 1-2\n");
    printf("If you want isolated vertice of a graph enter like 5-\n");
    printf("To stop the programm enter -1\n");

    add_edges(&head);

    print_to_file(head, file);

    fclose(file);

    system("dot -Tpng graph.dot -o graph.png");
    system("graph.png");

    printf("\nWhich edge do you want to remove?\n");

    edge_remove(&head, head);

    file = fopen("graph2.dot", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    print_to_file(head, file);

    fclose(file);

    vertice_sort(head);

    system("dot -Tpng graph2.dot -o graph2.png");
    system("graph2.png");

    return 0;
}
