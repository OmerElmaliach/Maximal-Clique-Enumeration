#ifndef VERTEX_H
#define VERTEX_H

typedef struct Vertex{
    unsigned int id;
	unsigned int deg;
	struct Vertex **neighbors;
} Vertex;

typedef struct {
	unsigned int size;
	Vertex **lst;
} VertexList;

int isNeighbor(Vertex *vert, unsigned int id);

int addNeighbor(Vertex *vert, Vertex *neighbor);

int isInList(VertexList *vertList, unsigned int id);

int addVertexToList(VertexList *vertList, Vertex *vert);

#endif