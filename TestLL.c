#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} LL;

void add(LL** head, int _data) {
    LL* newNode = (LL*)malloc(sizeof(LL));
    newNode->data = _data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        LL* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void printList(LL* head) {
    LL* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int isLittleEndian() {
    int one = 1;
    char *byte = (char *)&one;
    return (*byte == 1);
}

void convertToBinary(int n) {
    // binary format
    int r = n;

    while (r) {
        printf("%d", r % 2);
        r = r >> 1;
    }
}
int main() {
    LL* head = NULL;
    for (int inx = 0; inx < 5; inx++) {
        add(&head, inx);
        printList(head);
    }

    // Clean up memory
    LL* current = head;
    LL* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    return 0;
}
