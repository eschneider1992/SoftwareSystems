/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// VALUE: represents a value in a key-value pair

/* Here's one way of making a polymorphic object in C */
typedef struct {
    enum Type {INT, STRING} type;
    union {
       int i;
       char *s;
   };
} Value;


/* Makes a Value object that contains an int. */
Value *make_int_value(int i) 
{
    // Value *value = (Value *) malloc (sizeof (Value));
    Value *value = malloc (sizeof (Value));
    if (value == NULL) {
        fprintf(stderr, "Malloc failed!");
        exit(-1);
    }
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string. */
Value *make_string_value(char *s) 
{
    // Value *value = (Value *) malloc (sizeof (Value));
    Value *value = malloc (sizeof (Value));
    if (value == NULL) {
        fprintf(stderr, "Malloc failed!");
        exit(-1);
    }
    value->type = STRING;
    value->s = s;
    return value;
}


/* Prints a value object. */
void print_value (Value *value) 
{
    if (value == NULL) {
        printf ("%p", value);
        return;
    }
    switch (value->type) {
        case INT:
        printf ("%d", value->i);
        break;
        case STRING:
        printf ("%s", value->s);
        break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

hash is a pointer to a function that knows how to hash the key.
equal is a pointer to a function that knows how to compare keys.

 */

typedef struct hashable{
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
    void (*free_hash) (struct hashable *);
} Hashable;


/* Makes a Hashable object. */
Hashable *make_hashable(void *key, int (*hash) (void *), int (*equal) (void *, void *), void (*free_hash)(Hashable *))
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    if (hashable == NULL) {
        fprintf(stderr, "Malloc failed!");
        exit(-1);
    }
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    hashable->free_hash = free_hash;
    return hashable;
}


/* Prints a Hashable object. */
void print_hashable(Hashable *hashable)
{
    printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer. */
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string. */
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
       total += s[i];
       i++;
   }
   return total;
}


/* Hashes any Hashtable. */
int hash_hashable(Hashable *hashable)
{
    return hashable->hash(hashable->key);
}


/* Compares integers. */
int equal_int (void *ip, void *jp)
{
    return (*(int *)ip == *(int *)jp);
}


/* Compares strings. */
int equal_string (void *s1, void *s2)
{
    if (strcmp((char *) s1, (char*) s2) == 0)
        return 1;
    else
        return 0;
}


/* Compares Hashables. */
int equal_hashable(Hashable *h1, Hashable *h2)
{
    return h1->equal((void *) h1, (void *) h2);
}

/* Frees a Hashable int */
void free_hashable_int (Hashable *ih)
{
    free(ih->key);
    free(ih);
}

/* Frees a Hashable string */
void free_hashable_string (Hashable *sh)
{
    free(sh);
}

/* Makes a Hashable int. 

Allocates space and copies the int.
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int, free_hashable_int);
}

/* Makes a Hashable string. 

Stores a reference to the string (not a copy).
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string, free_hashable_string);
}


// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;


/* Makes a Node. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Malloc failed!\n");
        exit(-1);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = next;
    return newNode;
}


/* Prints a Node. */
void print_node(Node *node)
{
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. */
void print_list(Node *node)
{
    if (node != NULL) {
        print_node(node);
        if (node->next != NULL) {
            print_list(node->next);
        }
    }
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.
 */
Node *prepend(Hashable *key, Value *value, Node *rest)
{
    return make_node(key, value, rest);
}


/* Looks up a key and returns the corresponding value, or NULL */
Value *list_lookup(Node *list, Hashable *key)
{
    if ((list == NULL) || (key == NULL))
        return NULL;

    if (equal_hashable(list->key, key))
        return list->value;
    else if (list->next == NULL)
        return NULL;
    else
        return list_lookup(list->next, key);
}


// MAP: a map is a list of key-value pairs

typedef struct map {
    int n;
    Node **lists;
} Map;


/* Makes a Map with n lists. */
Map *make_map(int n)
{
    // FIX ME!
    Map *newMap = malloc(sizeof(Map));
    if (newMap == NULL){
        fprintf(stderr, "Malloc failed!\n");
        exit(-1);
    }
    newMap->n = n;
    newMap->lists = malloc(n*sizeof(Node));
    if (newMap->lists == NULL){
        fprintf(stderr, "Malloc failed!\n");
        exit(-1);
    }
    return newMap;
}


/* Prints a Map. */
void print_map(Map *map)
{
    int i;
    for (i=0; i<map->n; i++) {
       if (map->lists[i] != NULL) {
           printf ("In list %d out of %d\n", i, map->n);
           print_list (map->lists[i]);
       }
   }
}

int list_index(int n, int hash) {
    return abs(hash % n);
}

/* Adds a key-value pair to a map. */
void map_add(Map *map, Hashable *key, Value *value)
{
    int listIndex = list_index(map->n, key->hash(key->key));
    if (map->lists[listIndex] == NULL)
        map->lists[listIndex] = make_node(key, value, NULL);
    else
        map->lists[listIndex] = prepend(key, value, map->lists[listIndex]); // VERY UNSURE OF THIS...
}


/* Looks up a key and returns the corresponding hash/map value, or NULL. */
Value *map_lookup(Map *map, Hashable *key)
{
    int i;
    for (i = 0; i < map->n; i++) {
        Value *value = list_lookup(map->lists[i], key);
        if (value != NULL)
            return value;
    }
    return NULL;
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value(value);
    printf ("\n");
}

/* Frees a Node */
void free_node(Node* node) {
    if (node->key != NULL) node->key->free_hash(node->key);
    if (node->value != NULL) free(node->value);
    if (node->next != NULL) free(node->next);
    free(node);
}

/* Frees all the data allocated in the list */
void free_list(Node* list) {
    if (list->next == NULL)
        free_node(list);
    else {
        free_list(list->next);
        free_node(list);
    }
}

/* Frees all the data allocated in the map */
void free_map(Map *map) {
    int i;
    for (i = 0; i < map->n; i++) {
        if (map->lists[i] != NULL)
            free_list(map->lists[i]);
    }
    free(map->lists);
    free(map);
}

int main ()
{
    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Allen");
    Hashable *hashable3 = make_hashable_int (2);

    // make a list by hand
    Value *value1 = make_int_value (17);
    Node *node1 = make_node(hashable1, value1, NULL);
    print_node (node1);

    Value *value2 = make_string_value ("Downey");
    Node *list = prepend(hashable2, value2, node1);
    print_list (list);

    // run some test lookups
    Value *value = list_lookup (list, hashable1);
    print_lookup(value);

    value = list_lookup (list, hashable2);
    print_lookup(value);

    value = list_lookup (list, hashable3);
    print_lookup(value);

    // make a map
    Map *map = make_map(10);
    map_add(map, hashable1, value1);
    map_add(map, hashable2, value2);

    printf ("Map\n");
    print_map(map);

    // run some test lookups
    value = map_lookup(map, hashable1);
    print_lookup(value);

    value = map_lookup(map, hashable2);
    print_lookup(value);

    value = map_lookup(map, hashable3);
    print_lookup(value);


    // Free everything
    free(node1);
    free(list);
    free(value);
    hashable3->free_hash(hashable3);
    free_map(map);
    return 0;
}
