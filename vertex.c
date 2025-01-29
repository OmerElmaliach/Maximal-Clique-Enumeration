#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

/*
    Checks for a given vertex if it has a specific neighbor with given id.
    Input: Vertex vert, Int id.
    Output: 1 if is a neighbor, else 0.
*/
int isNeighbor(Vertex *vert, unsigned int id) {
    for (int i = 0; i < vert->deg; i++) {
        if (vert->neighbors[i]->id == id)
            return 1;
    }
    return 0;
}

/*
    For a given vertex adds another vertex as neighbor.
    Input: Vertex vert, Vertex neighbor.
    Output: 1 succeeded, 0 if is already a neighbor, -1 if failed to allocate more memory.
*/
int addNeighbor(Vertex *vert, Vertex *neighbor) {
    if (!isNeighbor(vert, neighbor->id)) {
        Vertex **temp = (Vertex **)realloc(vert->neighbors, sizeof(Vertex *) * (vert->deg + 1));
        if (temp) {
            vert->neighbors = temp;
            vert->neighbors[vert->deg] = neighbor;
            vert->deg++;
            return 1;
        }
        return -1;
    }
    return 0;
}

/*
    Checks for a given vertex list if it has a specific vertex with given id.
    Input: VertexList vertList, Int id.
    Output: 1 if in list, else 0.
*/
int isInList(VertexList *vertList, unsigned int id) {
    for (int i = 0; i < vertList->size; i++) {
        if (vertList->lst[i]->id == id)
            return 1;
    }
    return 0;
}

/*
    For a given vertex list adds another vertex to it.
    Input: VertexList vertList, Vertex vert.
    Output: 1 succeeded, 0 if already in the list, -1 if failed to allocate more memory.
*/
int addVertexToList(VertexList *vertList, Vertex *vert) {
    if (!isInList(vertList, vert->id)) {
        Vertex **temp = (Vertex **)realloc(vertList->lst, sizeof(Vertex *) * (vertList->size + 1));
        if (temp) {
            vertList->lst = temp;
            vertList->lst[vertList->size] = vert;
            vertList->size++;
            return 1;
        }
        return -1;
    }
    return 0;
}

/*
    For a given vertex list removes a vertex from it.
    Input: VertexList vertList, int id.
    Output: 1 succeeded, 0 if not in the list, -1 if failed to allocate memory.
*/
int removeVertexFromList(VertexList *vertList, Vertex *vert) {
    for (int i = 0; i < vertList->size; i++) {
        if (vertList->lst[i]->id == vert->id) {
            if (i != vertList->size - 1) {
                for (int j = i; j < vertList->size - 1; j++) {
                    vertList->lst[j] = vertList->lst[j + 1];
                }
            }
            vertList->size--;
            Vertex **temp = (Vertex **)realloc(vertList->lst, sizeof(Vertex *) * vertList->size);
            if (temp) {
                vertList->lst = temp;
                return 1;
            } else
                return -1;
        }
    }
    return 0;
}

/*
    Finds the intersection vertices between two vertex lists.
    Input: Two vertex list pointers.
    Output: New vertex intersection list.
*/
VertexList findIntersection(VertexList *lst1, VertexList *lst2) {
    VertexList newList = { .lst = NULL, .size = 0};
    for (int i = 0; i < lst1->size; i++) {
        for (int j = 0; j < lst2->size; j++) {
            if (lst1->lst[i]->id == lst2->lst[j]->id)
                addVertexToList(&newList, lst1->lst[i]);
        }
    }
    return newList;
}

/*
    Creates a deep copy of a specific vertex list.
    Input: Vertex list pointer.
    Output: New vertex list.
*/
VertexList cloneList(VertexList *lst1) {
    VertexList newList = { .size = lst1->size, .lst = (Vertex **)malloc(sizeof(Vertex *) * lst1->size)};
    for (int i = 0; i < newList.size; i++) {
        newList.lst[i] = lst1->lst[i];
    }
    return newList;
}

/*
    Prints a given vertex list.
    Input: Vertex list pointer.
*/
void printList(VertexList *lst) {
    printf("Size: %d\nVertices: ", lst->size);
    for (int i = 0; i < lst->size - 1; i++) {
        printf("Id: %d, ", lst->lst[i]->id);
    }
    printf("Id: %d\n", lst->lst[lst->size - 1]->id);
}