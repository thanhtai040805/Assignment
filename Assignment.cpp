#include <stdio.h>
#include <string.h>

#define MAX_ROWS 50
#define MAX_NAME_LEN 20
#define MAX_CODE_LEN 5
#define MAX_DATE_LEN 20

// Function prototypes
int readData(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int *rowCount);
void printTable(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int rowCount);
void addData(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int *rowCount);

int main() {
    int STT[MAX_ROWS];
    char name[MAX_ROWS][MAX_NAME_LEN];
    char code[MAX_ROWS][MAX_CODE_LEN];
    int quantity[MAX_ROWS];
    int purchase[MAX_ROWS];
    int selling[MAX_ROWS];
    char importDate[MAX_ROWS][MAX_DATE_LEN];
    int rowCount = 0;
    int choice;
    
    if (!readData(STT, name, code, quantity, purchase, selling, importDate, &rowCount)) {
        printf("Initial data loaded successfully.\n");
    } else {
        printf("Failed to load initial data.\n");
        return 1;
    }
    
    do {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|               CHOICES                |\n");
        printf("+--------------------------------------+\n");
        printf("| 1. View Menu                         |\n");
        printf("| 2. Add Data                          |\n");
        printf("| 0. Exit                              |\n");
        printf("+--------------------------------------+\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printTable(STT, name, code, quantity, purchase, selling, importDate, rowCount);
                break;
            case 2:
                addData(STT, name, code, quantity, purchase, selling, importDate, &rowCount);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
                break;
        }
    } while (choice != 0);
    
    return 0;
}

int readData(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int *rowCount) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Could not open file data.txt\n");
        return 1;
    }
    
    while (*rowCount < MAX_ROWS && fscanf(file, "%d- %19[^-]- %4[^-]- %d- %d- %d- %19s\n", 
                                           &STT[*rowCount], 
                                           name[*rowCount], 
                                           code[*rowCount], 
                                           &quantity[*rowCount], 
                                           &purchase[*rowCount], 
                                           &selling[*rowCount], 
                                           importDate[*rowCount]) == 7) {
        (*rowCount)++;
    }
    
    fclose(file);
    return 0;
}

void printTable(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int rowCount) {
    printf("+-----+----------------------+-------+----------+------------------+------------------+----------------------+\n");
    printf("| %-3s | %-20s | %-5s | %-8s | %-16s | %-16s | %-20s |\n", "STT", "Name", "Code", "Quantity", "Purchase", "Selling", "Import Date");
    printf("+-----+----------------------+-------+----------+------------------+------------------+----------------------+\n");
    
    for (int i = 0; i < rowCount; i++) {
        printf("| %-3d | %-20s | %-5s | %-8d | %-12d VND | %-12d VND | %-20s |\n",  
               STT[i], 
               name[i], 
               code[i], 
               quantity[i], 
               purchase[i], 
               selling[i], 
               importDate[i]);
    }
    
    printf("+-----+----------------------+-------+----------+------------------+------------------+----------------------+\n");
}

void addData(int STT[], char name[][MAX_NAME_LEN], char code[][MAX_CODE_LEN], int quantity[], int purchase[], int selling[], char importDate[][MAX_DATE_LEN], int *rowCount) {
    if (*rowCount < MAX_ROWS) {
        printf("Enter new data:\n");
        printf("STT: ");
        scanf("%d", &STT[*rowCount]);
        getchar(); 
        printf("Name: ");
        fgets(name[*rowCount], MAX_NAME_LEN, stdin);
        name[*rowCount][strcspn(name[*rowCount], "\n")] = 0;
        printf("Code: ");
        scanf("%s", code[*rowCount]);
        printf("Quantity: ");
        scanf("%d", &quantity[*rowCount]);
        printf("Purchase: ");
        scanf("%d", &purchase[*rowCount]);
        printf("Selling: ");
        scanf("%d", &selling[*rowCount]);
        printf("Import Date: ");
        scanf("%s", importDate[*rowCount]);
        
        (*rowCount)++;
        
        FILE *file = fopen("data.txt", "a"); 
        if (file != NULL) {
            fprintf(file, "%d- %s- %s- %d- %d- %d- %s\n", 
                    STT[*rowCount - 1], 
                    name[*rowCount - 1], 
                    code[*rowCount - 1], 
                    quantity[*rowCount - 1], 
                    purchase[*rowCount - 1], 
                    selling[*rowCount - 1], 
                    importDate[*rowCount - 1]);
            fclose(file);
        } else {
            printf("Failed to open file data.txt for writing.\n");
        }
        
        printf("Data added successfully.\n");
    } else {
        printf("Cannot add more data. Maximum rows exceeded.\n");
    }
}