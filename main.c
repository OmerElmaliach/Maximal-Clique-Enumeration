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
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < totalSize; i++) {
        scanf("%d", &matrix[i]);
    }

    initiateListFromMatrix(&vertList, matrix, verticesAmount);
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
                if (vertList->lst[i]->deg == 0) {
                    vertList->lst[i]->neighbors = (Vertex **)malloc(sizeof(Vertex *));
                    vertList->lst[i]->neighbors[0] = vertList->lst[j];
                } else {
                    vertList->lst[i]->neighbors = (Vertex **)realloc(vertList->lst[i]->neighbors, sizeof(Vertex *) * (vertList->lst[i]->deg + 1));
                    vertList->lst[i]->neighbors[vertList->lst[i]->deg] = vertList->lst[j];
                }
                vertList->lst[i]->deg++;

                if (vertList->lst[j]->deg == 0) {
                    vertList->lst[j]->neighbors = (Vertex **)malloc(sizeof(Vertex *));
                    vertList->lst[j]->neighbors[0] = vertList->lst[i];
                } else {
                    vertList->lst[j]->neighbors = (Vertex **)realloc(vertList->lst[j]->neighbors, sizeof(Vertex *) * (vertList->lst[j]->deg + 1));
                    vertList->lst[j]->neighbors[vertList->lst[j]->deg] = vertList->lst[i];
                }
                vertList->lst[j]->deg++;
            }
        }
    }
}