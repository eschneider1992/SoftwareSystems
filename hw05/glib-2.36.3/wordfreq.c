// Drawn from http://cboard.cprogramming.com/c-programming/40527-reading-file-word-word.html
// Drawn from http://stackoverflow.com/questions/18109458/read-from-a-text-file-and-parse-lines-into-words-in-c

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

int main (int argc, char **argv)
{
	char *input = "test.txt";
	FILE *input_file;

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
		extract_words(input_file, htable);
	}

	numWords = g_hash_table_size(htable);
	g_printf("\nThere are %d unique words in the file: \n", numWords);
	allKeys = g_new(GList, 1);
	allKeys = g_hash_table_get_keys(htable);
	g_list_foreach(allKeys, print_key_val, NULL);

	fclose(input_file);
	g_hash_table_destroy(htable);
	g_free(val);
	g_list_free(allKeys);
	g_list_free(allValues);
	return 0;
}

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

void print_key_val (gpointer data1, gpointer data2){
    key = (gchar *) data1;
	val = (guint*) g_hash_table_lookup(htable, key);
	g_printf("%d\t%s \n", *val, key);
}
