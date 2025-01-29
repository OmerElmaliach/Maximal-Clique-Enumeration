#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

void initiateListFromMatrix(VertexList *vertList, int *matrix, int size);
void findMaxClique(VertexList P, VertexList R, VertexList X, VertexList *maxClique);

int main() {
    VertexList vertListP, vertListR, vertListX, maxClique;
    int verticesAmount, totalSize;
    int *matrix;
    printf("Please enter the number of vertices: ");
    scanf("%d", &verticesAmount);

    totalSize = verticesAmount * verticesAmount;
    matrix = (int *)malloc(totalSize * sizeof(int));
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < totalSize; i++) {
        scanf("%d", &matrix[i]);
    }

    initiateListFromMatrix(&vertListP, matrix, verticesAmount);
    findMaxClique(vertListP, vertListR, vertListX, &maxClique);
    printList(&maxClique);
}

/*
    Converts an edge matrix in form of an array to VertexList type object.
    Input: VertexList pointer, Array pointer, array size dimensions.
*/
void initiateListFromMatrix(VertexList *vertList, int *matrix, int size) {
    vertList->lst = (Vertex **)malloc(sizeof(Vertex *) * size);
    vertList->size = size;
    for (int i = 0; i < size; i++) {
        Vertex *vert = (Vertex *)malloc(sizeof(Vertex));
        vert->id = i;
        vert->deg = 0;
        vert->neighbors = NULL;
        vertList->lst[i] = vert;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (matrix[(i * size) + j]) {
                addNeighbor(vertList->lst[i], vertList->lst[j]);
                addNeighbor(vertList->lst[j], vertList->lst[i]);
            }
        }
    }
}

void findMaxClique(VertexList P, VertexList R, VertexList X, VertexList *maxClique) {
    if (!(P.size || X.size)) {
        if (maxClique->size < R.size) {
            *maxClique = cloneList(&R);
        }
        return;
    }

    for (int i = 0; i < P.size; i++) {
        Vertex *curr = P.lst[i];
        VertexList newR = cloneList(&R), pNeighbors = { .lst = curr->neighbors, .size = curr->deg };
        addVertexToList(&newR, curr);

        findMaxClique(findIntersection(&P, &pNeighbors), newR, findIntersection(&X, &pNeighbors), maxClique);
        removeVertexFromList(&P, curr);
        addVertexToList(&X, curr);
    }
}