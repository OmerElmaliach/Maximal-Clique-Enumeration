#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

void initiateListFromMatrix(VertexList *vertList, int *matrix, int size);

int main() {
    VertexList vertList;
    int verticesAmount, totalSize;
    int *matrix;
    printf("Please enter the number of vertices: ");
    scanf("%d", &verticesAmount);

    totalSize = verticesAmount * verticesAmount;
    matrix = (int *)malloc(totalSize * sizeof(int));
    printf("Enter the adjacency matrix: ");
    for (int i = 0; i < totalSize; i++) {
        scanf("%d", &matrix[i]);
    }

    initiateListFromMatrix(&vertList, matrix, verticesAmount);
}

void initiateListFromMatrix(VertexList *vertList, int *matrix, int size) {
    
}