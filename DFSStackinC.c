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
#define NEW 1
#define VISTED 2
#define DONE 3

int number_of_vertices, number_of_edges;
int start_visit_time[MAX], finish_visit_time[MAX], state[MAX];

int time = 0;

struct adj_vertex {
    int vertex_number;
    struct adj_vertex *next;
} *head[MAX], *tail[MAX];

struct stack_element {
    int vertex_number;
    struct stack_element *down;
} *top_stack = NULL;

void DFS(void) {
    while (top_stack != NULL) {
        if (state[top_stack->vertex_number] == NEW) {
            printf("%i ", top_stack->vertex_number);
            time++;
            start_visit_time[top_stack->vertex_number] = time;
            state[top_stack->vertex_number] = VISTED;
            struct adj_vertex *trace = head[top_stack->vertex_number];
            while (trace != NULL) {
                if (state[trace->vertex_number] == NEW) {
                    // Add this vertext to stack
                    struct stack_element *new_element = malloc(sizeof(struct stack_element));
                    new_element->down = top_stack;
                    new_element->vertex_number = trace->vertex_number;
                    top_stack = new_element;
                }
                trace = trace->next;
            }
            
        } else if (state[top_stack->vertex_number] == VISTED) {
            time++;
            finish_visit_time[top_stack->vertex_number] = time;
            state[top_stack->vertex_number] = DONE;
            top_stack = top_stack->down;
        } else {
            top_stack = top_stack->down;
        }
    }
}

int main() {
    scanf("%i", &number_of_vertices);
    scanf("%i", &number_of_edges);
    for (int i = 1; i <= number_of_vertices; i++) {
        head[i] = tail[i] = NULL;
        state[i] = NEW;
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
        if (state[i] == NEW) {
            top_stack = malloc(sizeof(struct stack_element));
            top_stack->vertex_number = i;
            top_stack->down = NULL;
            DFS();
        }
    }
    
    printf("\n");
    for (int i = 1; i <= number_of_vertices; i++) {
        printf("Dinh: %-2i, d[%-2i]: %-2i, f[%-2i]: %-2i\n", i, i, start_visit_time[i], i, finish_visit_time[i]);
    }
    
    printf("\n");
    return 0;
}
