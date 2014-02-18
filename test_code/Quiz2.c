#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *interleave(char *s1, char *s2);

// void main() {
//         char *test1 = "a\0";
//         if (test1[0])
//                 puts("Returned true");
//         else
//                 puts("Returned false");
// }

int main(){

    char *s1 = "clipsoool";
    char *s2 = "aloe";
    printf("%s\n", interleave(s1, s2));

    return 0;
}

char *interleave(char *s1, char *s2) {
    int i;
    int j = 0;
    int k = 0;

    int size = strlen(s1) + strlen(s2) + 1;
    char *res = malloc(size*sizeof(char));

    for (i=0; i<size-1;) {
        printf("j = %d, k = %d \n", j, k);
        if (s1[j]) {
            printf("Got to s1, i = %d \n", i);
            res[i++] = s1[j++];
        }
        if (s2[k]) {
            printf("Got to s2, i = %d \n", i);
            res[i++] = s2[k++];
        }
    }
    res[size-1] = '\0';

    return res;
}