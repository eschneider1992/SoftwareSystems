/*
* Eric Schneider
* 04/07/2014
* Drawn from http://cboard.cprogramming.com/c-programming/40527-reading-file-word-word.html
* Drawn from http://stackoverflow.com/questions/18109458/read-from-a-text-file-and-parse-lines-into-words-in-c
*/

#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF_LEN 30

void extract_words(FILE *input_file, GHashTable *htable);
void add_word_to_table(GHashTable *htable, GString *strbuf);
void print_key_val (gpointer data, gpointer user_data);

GHashTable *htable;
gchar *key;
guint *val;
guint *unit;
GList *allKeys;
GList *allValues;
guint numWords;


/*
* wordfreq.c opens a constant file, pulls the words out, writes unique words to
* a glib hashtable, and increments the frequency of non-unique words.
*/
int main (int argc, char **argv)
{
	char *input = "test.txt";
	FILE *input_file;

	// opens the file
	input_file = fopen(input, "r");

	if (input_file == 0)
	{
		fprintf(stderr, "Cannot open input file\n");
		exit(-1);
	}
	else {
		htable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
		key = g_malloc(sizeof(gchar *));
		val = g_malloc(sizeof(guint *));
		// pulls words out of file
		extract_words(input_file, htable);
	}

	// prints the words and their frequencies
	numWords = g_hash_table_size(htable);
	g_printf("\nThere are %d unique words in the file: \n", numWords);
	allKeys = g_new(GList, 1);
	allKeys = g_hash_table_get_keys(htable);
	g_list_foreach(allKeys, print_key_val, NULL);

	// tries to free all the allocated memory
	fclose(input_file);
	g_hash_table_destroy(htable);
	g_free(val);
	g_list_free(allKeys);
	g_list_free(allValues);
	return 0;
}

/*
* Takes an input file and a Glib hashtable, then calls add_word_to_table on each word
* in the file, separated by whitespace. All characters are set to lowercase here.
*
* TODO: add a filter for punctuation
*/
void extract_words(FILE *input_file, GHashTable *htable) {
	char buf[BUF_LEN];
	GString *strbuf = g_string_new(NULL);
	while( fscanf(input_file, "%s", buf) != EOF )
	{
		strbuf = g_string_assign(strbuf, buf);
		strbuf->str = g_ascii_strdown(strbuf->str, strbuf->len);
		add_word_to_table(htable, strbuf);
	}
	g_free(strbuf);
}

/*
* Takes in a Glib hashtable and a GString variable. Checks whether the string is already
* contained in the hashtable as a key. If so, the corresponding value is incremented. If
* not, a value of 1 entered alongside the string. g_strdup ensures that each key points to
* a unique string
*/
void add_word_to_table(GHashTable *htable, GString *strbuf) {
	key = g_strdup(strbuf->str);
	val = (guint*) g_hash_table_lookup(htable, key);

	if (val == NULL) {
		unit = g_malloc(sizeof(guint *));
		*unit = 1;
		g_hash_table_insert(htable, key, unit);
	}
	else {
		(*val)++;
		g_hash_table_replace(htable, key, val);
	}
}

/*
* Takes a Glib hashtable key and then prints the key and the value
* data2 is unused 
*/
void print_key_val (gpointer data1, gpointer data2){
    key = (gchar *) data1;
	val = (guint*) g_hash_table_lookup(htable, key);
	g_printf("%d\t%s \n", *val, key);
}
