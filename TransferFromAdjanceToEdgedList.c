//
//  TransferFromAdjanceToEdgedList.c
//  
//
//  Created by MacBook Pro on 6/2/20.
//

#include <stdio.h>

#define IN 1
#define OUT 0
#define false 0
#define true 1
#define MAX 50

int main() {
    int n;
    int mark[MAX][MAX], number = OUT;
    
    scanf("%i", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mark[i][j] = false;
        }
    }
    
    int j = 0;
    char c;
    for (int i = 1; i <= n; i++) {
        while ((c = getchar()) != '>');
        while ((c = getchar()) != '\n') {
            if (c < 48 || c > 57) {
                if (number == IN) {
                    number = OUT;
                    if (!mark[i][j]) {
                        mark[j][i] = mark[i][j] = true;
                    }
                    j = 0;
                }
            } else {
                j = j * 10 + (c - 48);
                number = IN;
            }
        }
        j = 0;
        number = OUT;
    }
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mark[i][j] && i != j) {
                count++;
                printf("%i %i\n", i, j);
                mark[i][j] = mark[j][i] = false;
            }
        }
    }
    
    printf("count: %i\n", count);
    return 0;
}
