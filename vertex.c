#include <stdio.h>
#include "vertex.h"

int isNeighbor(Vertex vert, unsigned int id) {
    for (int i = 0; i < vert.deg; i++) {
        if (vert.neighbors[i].id == id)
            return 1;
    }
    return 0;
}

int addNeighbor(Vertex vert, Vertex neighbor) {
    if (!isNeighbor(vert, neighbor.id)) {
        Vertex *temp = (Vertex *)realloc(vert.neighbors, sizeof(Vertex) * (vert.deg + 1));
        if (temp) {
            vert.neighbors = temp;
            vert.neighbors[vert.deg] = neighbor;
            vert.deg++;
            return 1;
        }
        return -1;
    }
    return 0;
}

int isInList(VertexList vertList, unsigned int id) {
    for (int i = 0; i < vertList.size; i++) {
        if (vertList.lst[i].id == id)
            return 1;
    }
    return 0;
}

int addVertexToList(VertexList vertList, Vertex vert) {
    if (!isInList(vertList, vert.id)) {
        Vertex *temp = (Vertex *)realloc(vertList.lst, sizeof(Vertex) * (vertList.size + 1));
        if (temp) {
            vertList.lst = temp;
            vertList.lst[vertList.size] = vert;
            vertList.size++;
            return 1;
        }
        return -1;
    }
    return 0;
}