/*
Patrick Punch
2/7/2025
CS 374
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

struct node *node_alloc(int value){
    struct node *n = malloc(sizeof(struct node));
    if (!n){
        perror("malloc");
        exit(1);
    }
    n->value = value;
    n->next = NULL;
    return n;
}

void node_free(struct node *n){
    free(n);
}

void llist_print(struct node *head){
    if (!head){
        printf("[empty]\n");
        return;
    }
    struct node *cur = head;
    while (cur){
        printf("%d", cur->value);
        if (cur->next)
            printf(" -> ");
        cur = cur->next;
    }
    printf("\n");
}

void llist_insert_head(struct node **head, struct node *n){
    n->next = *head;
    *head = n;
}

void llist_insert_tail(struct node **head, struct node *n){
    if (!*head){
        *head = n;
        return;
    }
    struct node *cur = *head;
    while (cur->next){
        cur = cur->next;
    }
    cur->next = n;
}

struct node *llist_delete_head(struct node **head){
    if (!*head){
        return NULL;
    }
    struct node *deleted = *head;
    *head = (*head)->next;
    deleted->next = NULL;
    return deleted;
}

void llist_free(struct node **head){
    struct node *cur = *head;
    while (cur){
        struct node *temp = cur;
        cur = cur->next;
        node_free(temp);
    }
    *head = NULL;
}

int main(int argc, char *argv[])
{
    struct node *head = NULL;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "ih") == 0 && i + 1 < argc){
            llist_insert_head(&head, node_alloc(atoi(argv[++i])));
        } else if (strcmp(argv[i], "it") == 0 && i + 1 < argc){
            llist_insert_tail(&head, node_alloc(atoi(argv[++i])));
        } else if (strcmp(argv[i], "dh") == 0){
            struct node *deleted = llist_delete_head(&head);
            if (deleted){
                node_free(deleted);
            }
        } else if (strcmp(argv[i], "p") == 0){
            llist_print(head);
        } else if (strcmp(argv[i], "f") == 0){
            llist_free(&head);
        }
    }
    llist_free(&head);
}

/* TESTS FOR OUTPUT

$./ llist it 1 it 2 it 3 p 
1->2->3 

$./ llist ih 1 ih 2 ih 3 p 
3->2->1 

$./ llist ih 12 ih 13 it 14 p dh p 
13->12->14 
12->14 

$./ llist ih 20 ih 40 it 5 p dh p dh p dh p 
40->20->5 
20->5 
5 
[empty]

$./ llist ih 20 p dh dh dh dh dh dh dh p 
20 
[empty] 

$./ llist ih 1 ih 2 p f p ih 3 p 
2->1 
[empty] 
3 
*/