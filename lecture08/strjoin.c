/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{

    int size = 0;
    int i;
    for (i=0; i<n; i++) {
        size += strlen(array[i]);
        // printf("Size: %d \n", size);
    }

    char *result = (char *) malloc(size*sizeof(char)+1);
    char *derp = malloc(6*sizeof(char));
    derp = "abcde";
    char *dest = result;

    for (i=0; i<n; i++) {
        strcpy (dest, array[i]);
        dest += strlen(array[i]);
        // printf("Result [%d]: %s \n", i, result);
    }

    printf("Derp: %s \n", derp);

    return result;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
