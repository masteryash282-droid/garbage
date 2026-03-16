#include<stdio.h>

int main () {
      int n, i, j;
      char ch;
      scanf("%d", &n);

        ch = 'A';                      
        for(j = 1; j <= n; j++) {         
            printf("%c ", ch++);          
        }                                 
            ch -= 2;                                                              
        for(j = 1; j <= n-1; j++) {    
            printf("%c ", ch--);
        }
        printf("\n");
      for(i=1; i<=n; i++) {
        ch = 'A';

        for(j=1; j<=n-i; j++) {
            printf("%c ", ch++);
        }
        for(j=1; j<=2*i-1; j++) {
            printf("  ");
        }
        ch-=1;
        for(j=1; j<=n-i; j++) {
            printf("%c ", ch--);
        }
        printf("\n");
      }
}