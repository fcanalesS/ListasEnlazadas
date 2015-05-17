#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

typedef struct node{
    char path[150];
    char copy_path[150];
    int size;
    char extension[4];
    char ruta[100];
    node* link;
}node;

typedef node* list;

/* -- Del Problema -- */
void command_L(list);
void command_E(list &, char *);
void command_R(list, char *);
void command_L_ex(list, char *);
void command_T(list);
list command_F(list &);
/* ------------------ */

/* -- Utilitarios -- */
void searchPath(char *);
void loadlist(list &);
char* substr(char* , int, int);
/* ----------------- */


int main() {
    list l=NULL;
    int i;
    char *ex = (char *) "001.jpg";
    char *nom = (char *) "001.off";
    char *extension = (char *) "jpg";
    loadlist(l); //First to load

    do
    {}while("3");


}

void loadlist(list &l)
{
    FILE *file;
    char chara[150];
    int i, _size=0, j, size_aux=0;
    list aux;
    aux = l;
    char extension[] = "0000";
    char *path2;

    file = fopen("raiz.txt", "r");
    while (fgets(chara, 150, file) != NULL)
    {
        aux = new node;
        strcpy(aux->path, chara);
        strcpy(aux->copy_path, chara);

        for (i=0; i<strlen(chara)+1; i++)
        {
            if(chara[i] == ' ')
            {
                for (j=i+1; j<strlen(chara)+1; j++)
                {
                    _size = (chara[j] - '0');
                    if (_size >= 0)
                    {
                        //printf("%d\n", size);
                        size_aux = size_aux*10 + _size;
                        //printf("%d\n", size_aux);
                    }
                }
                //printf("%d\n", size_aux);
                aux->size = size_aux;
                //printf("SIZE: %d\n", aux->size);
                size_aux = 0;
                //printf("\n");
            }
        }

        //printf("%s\n", chara);
        for(i=0; i<strlen(chara)+1; i++)
        {
            if(chara[i] == '.')
            {
                memcpy(extension, &chara[i+1], 4);
                strcpy(aux->extension, extension);
                //printf("Esto es una extension: %s", aux->extension);
            }
        }

        for(i=0; i<strlen(chara)+1; i++)
        {
            if(chara[i] == ' ')
            {
                //printf("%s", &chara[i]);
                //printf("%s\n", substr(aux->path, 0, i));
                strcpy(aux->ruta, substr(aux->path, 0, i));
                //printf("%s\n", aux->ruta);
            }
        }
        aux->link = l;
        l = aux;
        //printf("%s", chara);
    }
}

void command_L(list l)
{
    list aux1, aux2;
    int temp;
    char p_temp[150], c_temp[150], e_temp[4], r_temp[100];

    aux1 = l;

    while(aux1 != NULL) //Ordenamiento básico de BubbleSort
    {
        aux2 = aux1->link;
        while(aux2 != NULL)
        {
            if(aux1->size > aux2->size)
            {
                temp = aux1->size;
                strcpy(p_temp, aux1->path);
                strcpy(c_temp, aux1->copy_path);
                strcpy(e_temp, aux1->extension);
                strcpy(r_temp, aux1->ruta);

                aux1->size = aux2->size;
                strcpy(aux1->path, aux2->path);
                strcpy(aux1->copy_path, aux2->copy_path);
                strcpy(aux1->extension, aux2->extension);
                strcpy(aux1->ruta, aux2->ruta);

                aux2->size = temp;
                strcpy(aux2->path, p_temp);
                strcpy(aux2->copy_path, c_temp);
                strcpy(aux2->extension, e_temp);
                strcpy(aux2->ruta, r_temp);
            }
            aux2 = aux2->link;
        }
        aux1 = aux1->link;
    }

    while(l != NULL)
    {
        printf("%s", l->copy_path);
       // printf("%d\n", l->size);
        l = l->link;
    }
}

void command_E(list &l, char *ex) // Ver como borrar el nodo en el que estoy parado
{
    list a, e;
    a = l;
    char *ret;
    int i=0;

    while( a != NULL)
    {
        ret = strstr(a->path, ex);
        if (ret)
        {
            printf("%s", ret);
            a = a->link;
            l->link = a;
            break;
        }
        a = a->link;

    }

    printf("----------------------------------------------\n");
    while (l != NULL)
    {
        printf("%s", l->copy_path);
        l = l->link;
    }
}

char* substr(char* cadena, int comienzo, int longitud)
{
    if (longitud == 0) longitud = strlen(cadena)-comienzo-1;
    char *nuevo = (char*)malloc(sizeof(char) * longitud);
    strncpy(nuevo, cadena + comienzo, longitud);
    return nuevo;
}

void command_R(list l, char *nom)
{
    list aux = l;
    char *subs;
    int i, j;
    int len1 = strlen(nom);

    while (aux != NULL)
    {
        if(strstr(aux->copy_path, nom))
        {
            for(i=0; i<strlen(aux->copy_path)+1; i++)
            {
                if(aux->copy_path[i] == ' ')
                {
                    subs = substr(aux->copy_path, 0, i + 1 - len1-1);
                }
            }
            break;
        }

        aux = aux->link;
    }

    printf("%s\n", subs);
}

void command_L_ex(list l, char *extension)
{
    int i, j;
    char *_temp[100];
    while (l != NULL)
    {
        if(strstr(l->extension, extension))
        {
            printf("%s\n", l->ruta);
        }

        l = l->link;
    }
}

void command_T(list l)
{
    float total = 0;

    while (l != NULL)
    {
        total = total + (float)l->size;
        l = l->link;
    }

    printf("Bytes:\t\t%f\n", total);
    printf("Kilobytes: \t%f\n", total/1024);
    printf("Megabytes: \t%f\n", total/1048576);
}

list command_F(list &l)
{
    free(l);
    delete l;

    return 0;
}