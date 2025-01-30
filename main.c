#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

void initiateListFromMatrix(VertexList *vertList, int *matrix, int size);
void findMaxClique(VertexList cliqueNeighbors, VertexList potClique, VertexList procVerts, VertexList *maxClique, VertexList *allVertices);

int main() {
    VertexList vertListP = {0}, vertListR = {0}, vertListX = {0}, maxClique = {0}, allVertices = {0};
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
    allVertices = cloneList(&vertListP);
    findMaxClique(vertListP, vertListR, vertListX, &maxClique, &allVertices);
    printList(&maxClique);

    // Free memory used.
    freeMemList(&maxClique);
    free(matrix);
    for (int i = 0; i < verticesAmount; i++) {
        freeMemVert(allVertices.lst[i]);
    }
    freeMemList(&allVertices);
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

/*
    Finds the maximum clique in a given list of vertices.
    Input:  Vertex List pointer cliqueNeighbors - Holds neighbors of vertices in R, first iteration contains all vertices.
            Vertex List pointer potClique - Potential clique.
            Vertex List pointer procVerts - Holds vertices already in some cliques.
            Vertex List pointer maxClique - Holds the maximum clique detected, empty at first iteration.
            Vertex List pointer allVertices - Holds all vertices in graph.
*/
void findMaxClique(VertexList cliqueNeighbors, VertexList potClique, VertexList procVerts, VertexList *maxClique, VertexList *allVertices) {
    if (!(cliqueNeighbors.size || procVerts.size)) {
        if (maxClique->size < potClique.size) {
            if (maxClique->lst)
                freeMemList(maxClique);
            *maxClique = cloneList(&potClique);
        }
    }

    while (cliqueNeighbors.size) {
        Vertex *curr = findHighestDegVert(&cliqueNeighbors);
        VertexList clonedPotClique = cloneList(&potClique), pNeighbors = { .lst = curr->neighbors, .size = curr->deg };
        VertexList neighborIntersection = findIntersection(&cliqueNeighbors, &pNeighbors, allVertices);
        VertexList procIntersection = findIntersection(&procVerts, &pNeighbors, allVertices);
        addVertexToList(&clonedPotClique, curr);

        findMaxClique(neighborIntersection, clonedPotClique, procIntersection, maxClique, allVertices);
        removeVertexFromList(&cliqueNeighbors, curr);
        addVertexToList(&procVerts, curr);
    }

    freeMemList(&cliqueNeighbors);
    freeMemList(&potClique);
    freeMemList(&procVerts);
}