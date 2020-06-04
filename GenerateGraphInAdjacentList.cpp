#include <iostream>
#include <stdlib.h>
#define N 7
using namespace std;
void GenerateRandomGraphs(int e) {
    int i, j, edge[e][2], count;
    i = 0;
    // generate a connection between two random numbers, for //sample a small case, limit the number of vertex to 10.
    while(i < e) {
        edge[i][0] = rand()%N+1;
        edge[i][1] = rand()%N+1;
        i++;
    }
    //Print all the connection of each vertex, irrespective of the //direction.
    cout<<"\nThe generated random graph is: ";
    for(i = 0; i < N; i++) {
        count = 0;
        cout<<"\n\t"<<i+1<<"-> { ";
        for(j = 0; j < e; j++) {
            if(edge[j][0] == i+1) {
                cout<<edge[j][1]<<" ";
                count++;
            }
            else if(edge[j][1] == i+1) {
                cout<<edge[j][0]<<" ";
                count++;
            }
            //Print “Isolated vertex” for the vertex having zero degree.
            else if(j == e-1 && count == 0)
                cout<<"Isolated Vertex!";
        }
        cout<<" }";
    }
}
int main() {
    int n, i ,e;
    cout<<"Enter the number of edges for the random graphs: ";
    cin>>e;
    GenerateRandomGraphs(e);
    printf("\n");
}
