/* TOPA Mihai - Sebastian 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct car
{
    char simbol;
    struct car *next;
    struct car *prev;
} car;

typedef struct trainStruct
{
    struct car *mechanic;
    struct car *sentinel;
    int len;
} trainStruct;
// structuri pentru tren

typedef struct node
{
    char *comanda;
    struct node *next;
    struct node *prev;
} node;

typedef struct queue
{
    struct node *head;
    struct node *tail;
    int len;
} queue;
// structuri pentru coada

// functii pentru initializari
trainStruct *init(trainStruct *train)
{
    train = (trainStruct *)malloc(sizeof(trainStruct));
    car *newNode = (car *)malloc(sizeof(car));
    newNode->simbol = '#';
    train->sentinel = (car *)malloc(sizeof(car));
    train->sentinel->next = newNode;
    train->sentinel->prev = newNode;
    newNode->next = train->sentinel->next;
    newNode->prev = train->sentinel->prev;
    train->mechanic = newNode;
    train->len = 1;
    return train;
}

queue *initQueue(queue *q)
{
    q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

void addQueue(queue *q, char *comanda)
{
    node *newNode = (node *)malloc(sizeof(node));
    char *newNodeComanda = (char *)malloc(strlen(comanda) + 1);
    strcpy(newNodeComanda, comanda);
    newNode->comanda = newNodeComanda;
    newNode->next = NULL;

    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->len++;
}

void popQueue(queue *q)
{
    if (q->head == q->tail)
    {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        node *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    q->len--;
}

void switchQueue(queue *q)
{
    if (q->head == NULL || q->head->next == NULL)
    {
        // nu ai ce sa schimbi
        return;
    }

    node *prev = NULL;
    node *current = q->head;
    node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    q->tail = q->head;
    q->head = prev;
}

void search(trainStruct *train, char *sir, FILE *g)
{
    int ok = 0;
    car *current = train->mechanic;
    int lgSir = strlen(sir);
    int i, k = 0, contor = 0;
    char *aux = (char *)malloc((lgSir + 1) * sizeof(char));
    aux[lgSir] = '\0';
    while (contor != train->len)
    {
        if (sir[k] == current->simbol)
        {
            aux[k] = current->simbol;
            k++;
            if (strcmp(aux, sir) == 0)
            {
                train->mechanic = current;
                for (i = 0; i < lgSir - 1; i++)
                {
                    if (train->mechanic == train->sentinel->next)
                    {
                        train->mechanic = train->sentinel->prev;
                    }
                    else
                    {
                        train->mechanic = train->mechanic->prev;
                    }
                }
                ok = 1;
                break;
            }
        }
        else
        {
            k = 0;
            if (sir[k] == current->simbol)
            {
                aux[k] = current->simbol;
                k++;
                if (strcmp(aux, sir) == 0)
                {
                    train->mechanic = current;
                    for (i = 0; i < lgSir - 1; i++)
                    {
                        if (train->mechanic == train->sentinel->next)
                        {
                            train->mechanic = train->sentinel->prev;
                        }
                        else
                        {
                            train->mechanic = train->mechanic->prev;
                        }
                    }
                    ok = 1;
                    break;
                }
            }
            strcpy(aux, "");
        }
        contor++;
        current = current->next;
    }
    if (ok == 0)
        fprintf(g, "ERROR\n");
    free(aux);
}

void searchLeft(trainStruct *train, char *sir, FILE *g)
{
    int ok = 0;
    car *current = train->mechanic;
    int lgSir = strlen(sir);
    int k = 0;
    do
    {
        if (sir[k] == current->simbol)
        {
            k++;
            if (k == lgSir)
            {
                train->mechanic = current;
                // asta chiar e pozitia de la inceput pentru ca se cauta invers
                // si nu mai trebuie facut acel for
                ok = 1;
                break;
            }
        }
        else
        {
            k = 0;
        }

        if (current != train->sentinel->next)
        {
            current = current->prev;
        }
        else
        {
            current = train->sentinel->prev;
        }

    } while (current != train->sentinel->prev);
    if (ok == 0)
        fprintf(g, "ERROR\n");
}

void searchRight(trainStruct *train, char *sir, FILE *g)
{
    int ok = 0;
    car *current = train->mechanic;
    int lgSir = strlen(sir);
    int k = 0;

    do
    {
        if (sir[k] == current->simbol)
        {
            k++;
            if (k == lgSir)
            {
                train->mechanic = current;
                // asta chiar e pozitia de la inceput pentru ca se cauta invers
                // si nu mai trebuie facut acel for
                ok = 1;
                break;
            }
        }
        else
        {
            k = 0;
        }

        if (current->next == train->sentinel->next)
        {
            break;
        }
        else
            current = current->next;
    } while (current != train->sentinel->next);

    if (ok == 0)
        fprintf(g, "ERROR\n");
}

// aceasta functie afiseaza continutul intregului trenulet
void show(trainStruct *train, FILE *f)
{
    int contor = 0;
    car *current = train->sentinel->next;
    while (contor != train->len)
    {
        if (current == train->mechanic)
        {
            fprintf(f, "|%c|", current->simbol);
        }
        else
        {
            fprintf(f, "%c", current->simbol);
        }
        current = current->next;
        contor++;
    }
}

void showCurrent(trainStruct *train, FILE *f)
{
    fprintf(f, "%c", train->mechanic->simbol);
}

void move(trainStruct *train, char *comanda)
{
    if (strcmp(comanda, "MOVE_LEFT") == 0 && train->mechanic == train->sentinel->next)
    {
        train->mechanic = train->sentinel->prev;
    }
    if (strcmp(comanda, "MOVE_LEFT") == 0 && train->mechanic != train->sentinel->next)
    {
        train->mechanic = train->mechanic->prev;
    }
    if (strcmp(comanda, "MOVE_RIGHT") == 0 && train->mechanic == train->sentinel->prev)
    {
        car *newCar = (car *)malloc(sizeof(car));
        newCar->simbol = '#';
        newCar->prev = train->sentinel->prev;
        train->sentinel->prev->next = newCar;
        train->sentinel->prev = newCar;
        train->sentinel->prev->next = train->sentinel->next;
        train->mechanic = newCar;
        train->len++;
    }
    if (strcmp(comanda, "MOVE_RIGHT") == 0 && train->mechanic != train->sentinel->prev)
    {
        train->mechanic = train->mechanic->next;
    }
}

void write(trainStruct *train, char simbol)
{
    train->mechanic->simbol = simbol;
}

void clearCell(trainStruct *train)
{
    if (train->mechanic == train->sentinel->next)
    {
        train->sentinel->next = train->mechanic->next;
        train->mechanic->next->prev = train->sentinel;
        free(train->mechanic);
        train->mechanic = train->sentinel->next;
        train->len--;
    }
    else if (train->mechanic == train->sentinel->prev)
    {
        train->sentinel->prev = train->mechanic->prev;
        train->mechanic->prev->next = train->sentinel;
        free(train->mechanic);
        train->mechanic = train->sentinel->prev;
        train->len--;
    }
    else
    {
        car *aux = train->mechanic->prev;
        train->mechanic->prev->next = train->mechanic->next;
        train->mechanic->next->prev = train->mechanic->prev;
        free(train->mechanic);
        train->mechanic = aux;
        train->len--;
    }
}

void clearAll(trainStruct *train)
{
    while (train->mechanic != train->sentinel->prev)
    {
        train->mechanic = train->mechanic->next;
    }
    while (train->mechanic != train->sentinel->next)
    {
        clearCell(train);
    }
    train->mechanic->simbol = '#';
    train->len = 1;
}

// aici este de verificat
void insertRight(trainStruct *train, char simbol)
{
    car *newCar = (car *)malloc(sizeof(car));
    newCar->simbol = simbol;
    // la tail
    if (train->mechanic == train->sentinel->prev)
    {
        newCar->next = train->sentinel->next;
        newCar->prev = train->sentinel->prev;
        train->sentinel->prev->next = newCar;
        train->sentinel->prev = newCar;
    }
    // in tren
    else
    {
        newCar->prev = train->mechanic;
        newCar->next = train->mechanic->next;
        train->mechanic->next->prev = newCar;
        train->mechanic->next = newCar;
    }

    train->mechanic = newCar;
    train->len++;
}

// aici este de verificat
void insertLeft(trainStruct *train, char simbol, FILE *g)
{
    car *newCar = (car *)malloc(sizeof(car));

    if (train->mechanic == train->sentinel->next)
    {
        fprintf(g, "ERROR\n");
        free(newCar);
    }
    else
    {
        newCar->next = train->mechanic;
        newCar->prev = train->mechanic->prev;

        train->mechanic->prev->next = newCar;
        train->mechanic->prev = newCar;

        train->mechanic = train->mechanic->prev;
        train->len++;
        newCar->simbol = simbol;
    }
}

void splitString(char *str, char *sub1, char *sub2)
{
    char *spacePos = strchr(str, ' ');

    if (spacePos != NULL)
    {
        int pos = spacePos - str;
        strncpy(sub1, str, pos);
        sub1[pos] = '\0';
        strcpy(sub2, spacePos + 1);
    }
    else
    {
        strcpy(sub1, str);
        sub2[0] = '\0';
    }
}

void execute(trainStruct *train, queue *q, FILE *g)
{
    char *comanda = (char *)malloc(sizeof(char) * (strlen(q->head->comanda) + 1));
    char *sub1 = (char *)malloc(sizeof(char) * (1 + strlen(q->head->comanda)));
    char *sub2 = (char *)malloc(sizeof(char) * (1 + strlen(q->head->comanda)));
    strcpy(comanda, q->head->comanda);
    splitString(comanda, sub1, sub2);
    if (strcmp(sub1, "WRITE") == 0)
    {
        write(train, sub2[0]);
    }
    if (strcmp(sub1, "MOVE_RIGHT") == 0)
    {
        move(train, "MOVE_RIGHT");
    }
    if (strcmp(sub1, "MOVE_LEFT") == 0)
    {
        move(train, "MOVE_LEFT");
    }
    if (strcmp(sub1, "SEARCH_RIGHT") == 0)
    {
        searchRight(train, sub2, g);
    }
    if (strcmp(sub1, "SEARCH_LEFT") == 0)
    {
        searchLeft(train, sub2, g);
    }
    if (strcmp(sub1, "SEARCH") == 0)
    {
        search(train, sub2, g);
    }
    if (strcmp(sub1, "CLEAR_ALL") == 0)
    {
        clearAll(train);
    }
    if (strcmp(sub1, "CLEAR_CELL") == 0)
    {
        clearCell(train);
    }
    if (strcmp(sub1, "INSERT_LEFT") == 0)
    {
        insertLeft(train, sub2[0], g);
    }
    if (strcmp(sub1, "INSERT_RIGHT") == 0)
    {
        insertRight(train, sub2[0]);
    }
    free(comanda);
    free(sub1);
    free(sub2);
    popQueue(q);
}

int main()
{
    trainStruct *train = NULL;
    queue *q = NULL;
    train = init(train);
    q = initQueue(q);
    int n, i;
    char comanda[3000], sub1[3000], sub2[3000];
    FILE *f = fopen("tema1.in", "r");
    FILE *g = fopen("tema1.out", "w");
    fscanf(f, "%d", &n);
    int c;
    while ((c = fgetc(f)) != '\n')
        ;
    for (i = 0; i < n; i++)
    {
        fgets(comanda, sizeof(comanda), f);

        int len = strlen(comanda);
        if (comanda[len - 1] == '\n')
        {
            comanda[len - 1] = '\0';
        }

        splitString(comanda, sub1, sub2);

        if (strcmp(sub1, "SHOW") == 0)
        {
            show(train, g);
            fprintf(g, "\n");
        }
        else if (strcmp(sub1, "SHOW_CURRENT") == 0)
        {
            showCurrent(train, g);
            fprintf(g, "\n");
        }
        else if (strcmp(sub1, "SWITCH") == 0)
        {
            switchQueue(q);
        }
        else if (strcmp(comanda, "EXECUTE") == 0)
        {
            execute(train, q, g);
        }
        else
        {
            addQueue(q, comanda);
        }
    }
    fclose(f);
    fclose(g);
    clearAll(train);
    free(train->sentinel->next);
    free(train->sentinel);
    free(train);
    for (i = 0; i < q->len; i++)
        popQueue(q);
    free(q);
    return 0;
}