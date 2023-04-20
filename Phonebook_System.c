/*
This is a C program, a simple implementation of a phonebook management system in using a struct to store records of 
people's names, father's names, phone numbers, and emails. The program provides a menu of options for the user to add, 
modify, delete, or list records. The program uses dynamic memory allocation to add new records and reallocates memory whenever a new record is added.
The addRecord function takes a pointer to the array of Person structs and an integer pointer to the number of records n. 
It then prompts the user to enter a new record and stores the record in the n-th index of the array.
The modifyRecord function takes a pointer to the array of Person structs and the number of records n. It prompts 
the user to enter the name of the record to be modified and then searches for the record in the array. If the record is found, it prompts the user to enter new information for each field of the record.
The deleteRecord function takes a pointer to the array of Person structs and an integer pointer to the number of records n. 
It prompts the user to enter the name of the record to be deleted and then searches for the record in the array. 
If the record is found, it shifts all subsequent records one position to the left and decrements the value of n.
The listRecords function takes a pointer to the array of Person structs and the number of records n. It prints a 
formatted table of all the records in the array.
The main function initializes a pointer p to NULL and n to 0. It then displays a menu of options and prompts 
the user to select an option. Depending on the user's choice, the program calls one of the four functions to 
add, modify, delete, or list records. The program runs in a loop until the user chooses to exit the program, 
at which point the memory allocated for the array is freed using free(p).

*/
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
