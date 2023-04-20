#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    char father_name[50];
    char phone_number[15];
    char email[50];
};

void addRecord(struct Person *p, int *n) {
    printf("\n\t\t\tEnter name: ");
    scanf("%s", p[*n].name);
    printf("\n\t\t\tEnter last name: ");
    scanf("%s", p[*n].father_name);
    printf("\n\t\t\tEnter phone number: ");
    scanf("%s", p[*n].phone_number);
    printf("\n\t\t\tEnter email: ");
    scanf("%s", p[*n].email);
    (*n)++;
}

void modifyRecord(struct Person *p, int n) {
    char name[50];
    printf("\n\t\t\tEnter name to modify: ");
    scanf("%s", name);
    for(int i=0; i<n; i++) {
        if(strcmp(p[i].name, name) == 0) {
            printf("\n\t\t\tEnter new name: ");
            scanf("%s", p[i].name);
            printf("\n\t\t\tEnter new father's name: ");
            scanf("%s", p[i].father_name);
            printf("\n\t\t\tEnter new phone number: ");
            scanf("%s", p[i].phone_number);
            printf("\n\t\t\tEnter new email: ");
            scanf("%s", p[i].email);
            return;
        }
    }
    printf("Record not found!\n");
}

void deleteRecord(struct Person *p, int *n) {
    char name[50];
    printf("\n\t\t\tEnter name to delete: ");
    scanf("%s", name);
    for(int i=0; i<*n; i++) {
        if(strcmp(p[i].name, name) == 0) {
            for(int j=i; j<*n-1; j++) {
                p[j] = p[j+1];
            }
            (*n)--;
            printf("\n\t\t\tRecord deleted!\n");
            return;
        }
    }
    printf("\n\t\t\tRecord not found!\n");
}

void listRecords(struct Person *p, int n) {
    printf("\n\t\t\tName\t\tFather's Name\t\tPhone Number\t\tEmail\n");
    for(int i=0; i<n; i++) {
        printf("\n\t\t\t%s\t\t%s\t\t%s\t\t%s\n", p[i].name, p[i].father_name, p[i].phone_number, p[i].email);
    }
}

int main() {
    struct Person *p = NULL;
    int n = 0;
    int choice;
system("color 2");
 printf("\t\t\t\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic");
    do {
        printf("\n\t\t\tPhonebook Management System\n");
        printf("\n\t\t\t1. Add new record\n");
        printf("\n\t\t\t2. Modify record\n");
        printf("\n\t\t\t3. Delete record\n");
        printf("\n\t\t\t4. List all records\n");
        printf("\n\t\t\t5. Exit\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                p = (struct Person*)realloc(p, (n+1)*sizeof(struct Person));
                addRecord(p, &n);
                break;
            case 2:
                modifyRecord(p, n);
                break;
            case 3:
                deleteRecord(p, &n);
                break;
            case 4:
                listRecords(p, n);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 5);

    free(p);
//The code was developed by Oliver Nikolajevic
    return 0;
}
