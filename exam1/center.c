/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    int size = n+1;
    char *target = malloc(size * sizeof(char));
    int s_len = strlen(s);
    int offset_index = (n - 1 - s_len)/2;
        // printf("n: %d , s_len: %d , offset_index: %d \n", n, s_len, offset_index); // Debug

    int i;
    for (i=0; i<n; i++) {
        if ((i > offset_index) && (i<=(offset_index+s_len))) {
            target[i] = *(s+i-offset_index-1);
        } else {
            target[i] = fillchar;
        }
    }
    target[n] = '\0';

    return target;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    return 0;
}
