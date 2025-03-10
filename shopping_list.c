#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_CATEGORY 30

// Structure to store shopping list items
typedef struct {
    char name[50];
    int quantity;
    char category[MAX_CATEGORY];
} Item;

Item shoppingList[MAX_ITEMS];
int itemCount = 0;

// Function Prototypes
void addItem();
void removeItem();
void displayList();
void saveToFile();
void loadFromFile();
void sortAlphabetically();
void sortByQuantity();
void searchItem();

int main() {
    int choice;
    loadFromFile(); // Load existing data on startup

    while (1) {
        printf("\n🛒 Shopping List Manager\n");
        printf("1. Add an item\n");
        printf("2. Remove an item\n");
        printf("3. View list\n");
        printf("4. Sort list alphabetically\n");
        printf("5. Sort list by quantity\n");
        printf("6. Search for an item\n");
        printf("7. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                displayList();
                break;
            case 4:
                sortAlphabetically();
                printf("List sorted alphabetically!\n");
                break;
            case 5:
                sortByQuantity();
                printf("List sorted by quantity!\n");
                break;
            case 6:
                searchItem();
                break;
            case 7:
                saveToFile();
                printf("Shopping list saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
}

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Shopping list is full!\n");
        return;
    }
    printf("Enter item name: ");
    fgets(shoppingList[itemCount].name, 50, stdin);
    strtok(shoppingList[itemCount].name, "\n"); // Remove newline
    
    printf("Enter quantity: ");
    scanf("%d", &shoppingList[itemCount].quantity);
    getchar(); // Clear buffer
    
    printf("Enter category: ");
    fgets(shoppingList[itemCount].category, MAX_CATEGORY, stdin);
    strtok(shoppingList[itemCount].category, "\n"); // Remove newline
    
    itemCount++;
    printf("Item added successfully!\n");
}

void removeItem() {
    char name[50];
    printf("Enter the item name to remove: ");
    fgets(name, 50, stdin);
    strtok(name, "\n"); // Remove newline

    for (int i = 0; i < itemCount; i++) {
        if (strcmp(shoppingList[i].name, name) == 0) {
            for (int j = i; j < itemCount - 1; j++) {
                shoppingList[j] = shoppingList[j + 1];
            }
            itemCount--;
            printf("Item removed successfully!\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void displayList() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    printf("\nYour Shopping List:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - %d [%s]\n", i + 1, shoppingList[i].name, shoppingList[i].quantity, shoppingList[i].category);
    }
}

void sortAlphabetically() {
    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {
            if (strcmp(shoppingList[j].name, shoppingList[j + 1].name) > 0) {
                Item temp = shoppingList[j];
                shoppingList[j] = shoppingList[j + 1];
                shoppingList[j + 1] = temp;
            }
        }
    }
}

void sortByQuantity() {
    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {
            if (shoppingList[j].quantity > shoppingList[j + 1].quantity) {
                Item temp = shoppingList[j];
                shoppingList[j] = shoppingList[j + 1];
                shoppingList[j + 1] = temp;
            }
        }
    }
}

void searchItem() {
    char name[50];
    printf("Enter the item name to search: ");
    fgets(name, 50, stdin);
    strtok(name, "\n"); // Remove newline

    for (int i = 0; i < itemCount; i++) {
        if (strcmp(shoppingList[i].name, name) == 0) {
            printf("\nItem Found!\n");
            printf("%s - %d [%s]\n", shoppingList[i].name, shoppingList[i].quantity, shoppingList[i].category);
            return;
        }
    }
    printf("Item not found.\n");
}
void saveToFile() {
    FILE *file = fopen("shopping_list.txt", "w");
    if (file == NULL) {
        printf("Error saving file.\n");
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s %d %s\n", shoppingList[i].name, shoppingList[i].quantity, shoppingList[i].category);
    }
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen("shopping_list.txt", "r");
    if (file == NULL) {
        return; // No file yet
    }
    while (fscanf(file, "%49s %d %29s", shoppingList[itemCount].name, &shoppingList[itemCount].quantity, shoppingList[itemCount].category) != EOF) {
        itemCount++;
    }
    fclose(file);
}
