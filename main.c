#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

void initiateListFromMatrix(VertexList *vertList, int *matrix, int size);
VertexList findMaxClique(VertexList P, VertexList R, VertexList X);

int main() {
    VertexList vertList, vertListP, vertListX, maxClique;
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

    initiateListFromMatrix(&vertList, matrix, verticesAmount);
    // maxClique = findMaxClique(vertListP, vertList, vertListX);
}

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

VertexList findMaxClique(VertexList P, VertexList R, VertexList X) {
    if (!(P.size || X.size))
        return R;
    
    for (int i = 0; i < P.size; i++) {

    }

    return R;
}