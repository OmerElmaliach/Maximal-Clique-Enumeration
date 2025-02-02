#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

/*
    Checks for a given vertex if it has a specific neighbor with given id.
    Input: Vertex vert, Int id.
    Output: 1 if is a neighbor, else 0.
*/
int isNeighbor(Vertex *vert, unsigned int id) {
    if (vert) {
        for (int i = 0; i < vert->deg; i++) {
            if (vert->neighbors[i]->id == id)
                return 1;
        }
    }
    return 0;
}

/*
    For a given vertex adds another vertex as neighbor.
    Input: Vertex vert, Vertex neighbor.
    Output: 1 succeeded, 0 if is already a neighbor.
*/
int addNeighbor(Vertex *vert, Vertex *neighbor) {
    Vertex **temp;
    if (!isNeighbor(vert, neighbor->id)) {
        if (vert->deg > 0) {
            temp = (Vertex **)realloc(vert->neighbors, sizeof(Vertex *) * (vert->deg + 1));
        } else
            temp = (Vertex **)malloc(sizeof(Vertex *));
        if (temp) {
            vert->neighbors = temp;
            vert->neighbors[vert->deg] = neighbor;
            vert->deg++;
            return 1;
        }
        perror("Memory allocation failed, exit...");
        exit(EXIT_FAILURE);
    }
    return 0;
}

/*
    Checks for a given vertex list if it has a specific vertex with given id.
    Input: VertexList vertList, Int id.
    Output: 1 if in list, else 0.
*/
int isInList(VertexList *vertList, unsigned int id) {
    if (vertList && vertList->lst) {
        for (int i = 0; i < vertList->size; i++) {
            if (vertList->lst[i]->id == id)
                return 1;
        }
    }
    return 0;
}

/*
    Finds and returns the vertex with the highest degree in the list.
    Input: VertexList vertList.
    Output: Vertex with the highest degree in list.
*/
Vertex * findHighestDegVert(VertexList *vertList) {
    Vertex *maxVert = NULL;
    if (vertList && vertList->lst) {
        if (vertList->size > 0) {
            maxVert = vertList->lst[0];
            for (int i = 1; i < vertList->size; i++) {
                if (maxVert->deg < vertList->lst[i]->deg)
                    maxVert = vertList->lst[i];
            }
        }
    }
    return maxVert;
}

/*
    Frees up the memory of a vertex.
    Input: Vertex pointer.
*/
void freeMemVert(Vertex *vert) {
    free(vert->neighbors);
    free(vert);
}

/*
    For a given vertex list adds another vertex to it.
    Input: VertexList vertList, Vertex vert.
    Output: 1 succeeded, 0 if already in the list.
*/
int addVertexToList(VertexList *vertList, Vertex *vert) {
    Vertex **temp;
    if (!isInList(vertList, vert->id)) {
        if (vertList->size > 0) {
            temp = (Vertex **)realloc(vertList->lst, sizeof(Vertex *) * (vertList->size + 1));
        } else
            temp = (Vertex **)malloc(sizeof(Vertex *));
        if (temp) {
            vertList->lst = temp;
            vertList->lst[vertList->size] = vert;
            vertList->size++;
            return 1;
        }
        perror("Memory allocation failed, exit...");
        exit(EXIT_FAILURE);
    }
    return 0;
}

/*
    For a given vertex list removes a vertex from it.
    Input: VertexList vertList, int id.
    Output: 1 succeeded, 0 if not in the list.
*/
int removeVertexFromList(VertexList *vertList, Vertex *vert) {
    if (vertList && vertList->lst) {
        for (int i = 0; i < vertList->size; i++) {
            if (vertList->lst[i]->id == vert->id) {
                for (int j = i; j < vertList->size - 1; j++) {
                    vertList->lst[j] = vertList->lst[j + 1];
                }
                vertList->size--;

                if (vertList->size == 0) {  
                    freeMemList(vertList);
                    vertList->lst = NULL;
                    return 1;
                }

                Vertex **temp = (Vertex **)realloc(vertList->lst, sizeof(Vertex *) * vertList->size);
                if (temp) {
                    vertList->lst = temp;
                } else {
                    perror("Memory allocation failed, exit...");
                    exit(EXIT_FAILURE);
                }
                return 1;
            }
        }
    }
    return 0;
}

/*
    Finds the intersection vertices between two vertex lists.
    Input: Two vertex list pointers.
    Output: New vertex intersection list.
*/
VertexList findIntersection(VertexList *lst1, VertexList *lst2, VertexList *allVertices) {
    VertexList newList = { .lst = NULL, .size = 0 };
    if (lst1 && lst1->lst && lst2 && lst2->lst && allVertices) {
        int *numArray = (int *)calloc(sizeof(int), allVertices->size);
        if (numArray) {
            for (int i = 0; i < lst1->size || i < lst2->size; i++) {
                if (i < lst1->size)
                    numArray[lst1->lst[i]->id]++;
                if (i < lst2->size)
                    numArray[lst2->lst[i]->id]++;
            }
            for (int i = 0; i < allVertices->size; i++) {
                if (numArray[i] == 2)
                    addVertexToList(&newList, allVertices->lst[i]);
            }
        } else {
            perror("Memory allocation failed, exit...");
            exit(EXIT_FAILURE);
        }

        free(numArray);
    }
    return newList;
}

/*
    Creates a deep copy of a specific vertex list.
    Input: Vertex list pointer.
    Output: New vertex list.
*/
VertexList cloneList(VertexList *lst1) {
    VertexList newList = { .size = 0, .lst = NULL };
    if (lst1 && lst1->size > 0) {
        newList.size = lst1->size;
        newList.lst = (Vertex **)malloc(sizeof(Vertex *) * lst1->size);
        for (int i = 0; i < newList.size; i++) {
            newList.lst[i] = lst1->lst[i];
        }
    }
    return newList;
}

/*
    Prints a given vertex list.
    Input: Vertex list pointer.
*/
void printList(VertexList *lst) {
    if (lst) {
        printf("Size: %d\nVertices: ", lst->size);
        for (int i = 0; i < lst->size - 1; i++) {
            printf("%d, ", lst->lst[i]->id);
        }
        if (lst->size > 0)
            printf("%d\n", lst->lst[lst->size - 1]->id);
    }
}

/*
    Frees up the memory of a vertex list.
    Input: Vertex list pointer.
*/
void freeMemList(VertexList *lst) {
    if (lst && lst->lst) {
        free(lst->lst);
    }
}