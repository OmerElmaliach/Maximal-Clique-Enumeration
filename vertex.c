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
    Output: 1 succeeded, 0 if is already a neighbor, -1 if was unable to allocate more memory.
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
    Output: 1 succeeded, 0 if already in the list, -1 if was unable to allocate more memory.
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