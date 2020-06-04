//
//  BFSinC.c
//  
//
//  Created by MacBook Pro on 5/31/20.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define YES 1
#define NO 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

int number_of_vertices, number_of_edges;
int color[MAX];

struct adj_vertex {
    int vertex_number;
    struct adj_vertex *next;
} *head[MAX], *tail[MAX];

struct queue {
    int vertex_number;
    struct queue *previous;
} *tail_queue = NULL, *head_queue = NULL;

void dequeue(struct queue *tail, int vertex_number) {
    tail->previous = NULL;
    tail->vertex_number = vertex_number;
}

struct queue *enqueue(struct queue *head) {
    struct queue *temp_vertext = head;
    head = head->previous;
    return temp_vertext;
}

void BFS(int vertex) {
    while (head_queue != NULL) {
        struct adj_vertex *trace = head[head_queue->vertex_number];
        printf("%i ", head_queue->vertex_number);
        while (trace != NULL) {
            if (color[trace->vertex_number] == WHITE) {
                color[trace->vertex_number] = GRAY;
                tail_queue->previous = malloc(sizeof(struct queue));
                tail_queue = tail_queue->previous;
                tail_queue->vertex_number = trace->vertex_number;
                tail_queue->previous = NULL;
            }
            trace = trace->next;
        }
        color[head_queue->vertex_number] = BLACK;
        head_queue = head_queue->previous;
    }
}

int main() {
    scanf("%i", &number_of_vertices);
    scanf("%i", &number_of_edges);
    for (int i = 1; i <= number_of_vertices; i++) {
        head[i] = tail[i] = NULL;
        color[i] = WHITE;
    }
    
    int vertex_1, vertex_2;
    for (int i = 1; i <= number_of_edges; i++) {
        scanf("%i%i", &vertex_1, &vertex_2);
        
        // Add vertex_2 into the adjacent list of vertex_1
        if (head[vertex_1] == NULL) {
            head[vertex_1] = tail[vertex_1] = malloc(sizeof(struct adj_vertex));
            tail[vertex_1]->vertex_number = vertex_2;
            tail[vertex_1]->next = NULL;
        } else {
            tail[vertex_1] = tail[vertex_1]->next = malloc(sizeof(struct adj_vertex));
            tail[vertex_1]->vertex_number = vertex_2;
            tail[vertex_1]->next = NULL;
        }
        
        // Add vertex_1 into the adjacent list of vertex_2
        if (head[vertex_2] == NULL) {
            head[vertex_2] = tail[vertex_2] = malloc(sizeof(struct adj_vertex));
            tail[vertex_2]->vertex_number = vertex_1;
            tail[vertex_2]->next = NULL;
        } else {
            tail[vertex_2] = tail[vertex_2]->next = malloc(sizeof(struct adj_vertex));
            tail[vertex_2]->vertex_number = vertex_1;
            tail[vertex_2]->next = NULL;
        }
    }
    
    struct adj_vertex *trace;
    for (int i = 1; i <= number_of_vertices; i++) {
        printf("%2i: ", i);
        trace = head[i];
        while (trace != NULL) {
            printf("%i ", trace->vertex_number);
            trace = trace->next;
        }
        printf("\n");
    }

    int count = 0;
    for (int i = 1; i <= number_of_vertices; i++) {
        if (color[i] == WHITE) {
            color[i] = GRAY;
            head_queue = tail_queue = malloc(sizeof(struct queue));
            tail_queue->previous = NULL;
            tail_queue->vertex_number = i;
            count++;
            if (count % 10 == 1) {
                printf("The %ist BFS tree: ", count);
            } else if (count % 10 == 2) {
                printf("The %ind BFS tree: ", count);
            } else if (count % 10 == 3) {
                printf("The %ird BFS tree: ", count);
            } else {
                printf("The %ith BFS tree: ", count);
            }
            BFS(i);
            printf("\n");
        }
    }
    printf("Connected Component: %i\n", count);
    
    return 0;
}
