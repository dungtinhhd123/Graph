//
//  DFSinC.c
//  
//
//  Created by MacBook Pro on 6/3/20.
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
int color[MAX], start_visit_time[MAX], finish_visit_time[MAX];
int time = 0;

struct adj_vertex {
    int vertex_number;
    struct adj_vertex *next;
} *head[MAX], *tail[MAX];

struct stack_element {
    int vertex_number;
    struct stack_element *down;
} *top_stack = NULL;

void DFS(int vertex_number) {

//    while (top_stack != NULL) {
//        struct stack_element *pop_top = top_stack;
        printf("%i ", vertex_number);
//        top_stack = top_stack->down;
        struct adj_vertex *trace = head[vertex_number];
        while (trace != NULL) {
            if (color[trace->vertex_number] == WHITE) {
                color[trace->vertex_number] = GRAY;
//                struct stack_element *new = malloc(sizeof(struct stack_element));
//                new->down = top_stack;
//                new->vertex_number = trace->vertex_number;
//                top_stack = new;
                time++;
                start_visit_time[trace->vertex_number] = time;
                DFS(trace->vertex_number);
            }
            trace = trace->next;
        }
//    }
    time++;
    finish_visit_time[vertex_number] = time;
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
    
    printf("Traversal Order: \n");
    for (int i = 1; i <= number_of_vertices; i++) {
        if (color[i] == WHITE) {
//            top_stack = malloc(sizeof(struct stack_element));
//            top_stack->vertex_number = i;
//            top_stack->down = NULL;
            color[i] = GRAY;
            time++;
            start_visit_time[i] = time;
            DFS(i);
        }
    }
    
    printf("\n");
    for (int i = 1; i <= number_of_vertices; i++) {
        printf("Dinh: %-2i, d[%-2i]: %-2i, f[%-2i]: %-2i\n", i, i, start_visit_time[i], i, finish_visit_time[i]);
    }
    
    printf("\n");
    return 0;
}
