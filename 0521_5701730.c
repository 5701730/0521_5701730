#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUIT_LENGTH 30
#define INITIAL_FRUIT_COUNT 10

typedef struct FruitNode {
    char fruit[MAX_FRUIT_LENGTH];
    struct FruitNode* next;
} FruitNode;

typedef struct FruitList {
    FruitNode* head;
    FruitNode* deleted_head;
} FruitList;

FruitNode* create_node(const char* fruit) {
    FruitNode* new_node = (FruitNode*)malloc(sizeof(FruitNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    strcpy_s(new_node->fruit, MAX_FRUIT_LENGTH, fruit);
    new_node->next = NULL;
    return new_node;
}

void initialize_list(FruitList* list, const char* fruits[], int count) {
    list->head = NULL;
    list->deleted_head = NULL;
    for (int i = count - 1; i >= 0; i--) {
        FruitNode* new_node = create_node(fruits[i]);
        new_node->next = list->head;
        list->head = new_node;
    }
}

void print_list(FruitNode* head) {
    while (head != NULL) {
        printf("%s ", head->fruit);
        head = head->next;
    }
    printf("\n");
}

int find_fruit(FruitNode* head, const char* fruit) {
    while (head != NULL) {
        if (strcmp(head->fruit, fruit) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void add_fruit(FruitList* list, const char* fruit) {
    if (find_fruit(list->head, fruit)) {
        printf("이미 존재하는 과일입니다.\n");
        return;
    }
    FruitNode* new_node = create_node(fruit);
    new_node->next = list->head;
    list->head = new_node;
    printf("과일을 추가했습니다.\n");
}

void delete_fruit(FruitList* list, const char* fruit) {
    FruitNode* current = list->head;
    FruitNode* previous = NULL;
    while (current != NULL && strcmp(current->fruit, fruit) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("해당하는 과일이 없습니다.\n");
        return;
    }
    if (previous == NULL) {
        list->head = current->next;
    }
    else {
        previous->next = current->next;
    }
    current->next = list->deleted_head;
    list->deleted_head = current;
    printf("과일을 삭제했습니다.\n");
}

void print_deleted_fruits(FruitList* list) {
    printf("삭제된 과일 목록: ");
    print_list(list->deleted_head);
}

void free_list(FruitNode* head) {
    while (head != NULL) {
        FruitNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    const char* initial_fruits[INITIAL_FRUIT_COUNT] = {
        "Mango", "Orange", "Apple", "Grape", "Cherry",
        "Plum", "Guava", "Raspberry", "Banana", "Peach"
    };

    FruitList list;
    initialize_list(&list, initial_fruits, INITIAL_FRUIT_COUNT);

    int choice;
    char fruit[MAX_FRUIT_LENGTH];
    do {
        printf("\n메뉴:\n");
        printf("1. 리스트의 맨 마지막에 새로운 과일 추가\n");
        printf("2. 리스트에 있는 과일을 삭제\n");
        printf("3. 삭제된 과일 목록 출력\n");
        printf("4. 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 과일을 입력하세요: ");
            scanf_s("%s", fruit, (unsigned)_countof(fruit));
            add_fruit(&list, fruit);
            break;
        case 2:
            printf("삭제할 과일을 입력하세요: ");
            scanf_s("%s", fruit, (unsigned)_countof(fruit));
            delete_fruit(&list, fruit);
            break;
        case 3:
            print_deleted_fruits(&list);
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("다시 시도하세요.\n");
        }
    } while (choice != 4);

    free_list(list.head);
    free_list(list.deleted_head);

    return 0;
}
