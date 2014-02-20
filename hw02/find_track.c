/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
  "So What",
  "Freddie Freeloader",
  "Blue in Green",
  "All Blues",
  "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title of matching tracks
void find_track(char search_for[])
{
  int i;
  for (i=0; i<NUM_TRACKS; i++) {
     if (strstr(tracks[i], search_for)) {
       printf("Track %i: '%s'\n", i, tracks[i]);
   }
}
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title of matching tracks
void find_track_regex(char *pattern)
{
   regex_t regex;
   int reti;
   int i;
   char msgbuf[100];

/* Compile the regular expression for later comparison with regexec */
   reti = regcomp(&regex, pattern, 0);
   if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }

   for (i=0; i<NUM_TRACKS; i++) {
     reti = regexec(&regex, tracks[i], 0, NULL, 0);
     if( !reti )
        printf("Track %d matches the %s pattern: %s \n", i+1, pattern, tracks[i]);
}
regfree(&regex);

}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
  char *ptr = strchr(s, '\n');
  if (ptr) {
     *ptr = '\0';
 }
}

int main (int argc, char *argv[])
{
  char search_for[80];

    /* take input from the user and search */
  printf("Search for: ");
  fgets(search_for, 80, stdin);
  rstrip(search_for);

  find_track(search_for);
  find_track_regex(search_for);

  return 0;
}

/*
    Usful sites for understanding regex
    http://www.gnu.org/software/libc/manual/html_node/POSIX-Regexp-Compilation.html#POSIX-Regexp-Compilation
    http://ftp.gnu.org/old-gnu/Manuals/grep-2.4/html_chapter/grep_5.html
*/