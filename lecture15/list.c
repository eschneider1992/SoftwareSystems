/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    *head = make_node(val, *head);
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *current = *head;
    Node *last = NULL;

    if ((*head)->val == val) {
        *head = (*head)->next;
        free(current);
        return 1;
    }
    while (current != NULL) {
        if (current->val == val) {
            last->next = current->next;
            free(current);
            return 1;
        }
        last = current;
        current = current->next;
    }
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    Node *top = NULL;
    Node *middle = *head;
    Node *bottom = (*head)->next;

    while (middle != NULL) {
        middle->next = top;
        top = middle;
        middle = bottom;
        if (bottom != NULL)
            bottom = bottom->next;
    }
    *head = top;
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    printf("I removed so many: %d\n", remove_by_value(&test_list, 3));
    printf("I removed so many: %d\n", remove_by_value(&test_list, 7));
    print_list(test_list);

    reverse(&test_list);
    print_list(test_list);
}