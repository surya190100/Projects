#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Item structure
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

// Function prototypes
void displayMenu();
void addItem();
void viewItems();
void updateItem();
void deleteItem();
void searchItem();

int main() {
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItems(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: searchItem(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid option. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n=== Inventory Management System ===\n");
    printf("1. Add Item\n");
    printf("2. View Items\n");
    printf("3. Update Item\n");
    printf("4. Delete Item\n");
    printf("5. Search Item\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

// Function to add a new item
void addItem() {
    FILE *file = fopen("inventory.dat", "ab");
    Item item;

    printf("\nEnter Item ID: ");
    scanf("%d", &item.id);
    printf("Enter Item Name: ");
    scanf(" %[^\n]", item.name);
    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter Price: ");
    scanf("%f", &item.price);

    fwrite(&item, sizeof(Item), 1, file);
    fclose(file);

    printf("Item added successfully!\n");
}

// Function to view all items
void viewItems() {
    FILE *file = fopen("inventory.dat", "rb");
    Item item;

    if (file == NULL) {
        printf("\nNo inventory found.\n");
        return;
    }

    printf("\nID\tName\t\tQuantity\tPrice\n");
    printf("------------------------------------------\n");
    while (fread(&item, sizeof(Item), 1, file)) {
        printf("%d\t%-15s\t%d\t\t%.2f\n", item.id, item.name, item.quantity, item.price);
    }

    fclose(file);
}

// Function to update an item
void updateItem() {
    FILE *file = fopen("inventory.dat", "rb+");
    Item item;
    int id, found = 0;

    if (file == NULL) {
        printf("\nNo inventory found.\n");
        return;
    }

    printf("\nEnter Item ID to update: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", item.name);
            printf("Enter New Quantity: ");
            scanf("%d", &item.quantity);
            printf("Enter New Price: ");
            scanf("%f", &item.price);

            fseek(file, -sizeof(Item), SEEK_CUR);
            fwrite(&item, sizeof(Item), 1, file);
            printf("Item updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Item not found.\n");

    fclose(file);
}

// Function to delete an item
void deleteItem() {
    FILE *file = fopen("inventory.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Item item;
    int id, found = 0;

    if (file == NULL) {
        printf("\nNo inventory found.\n");
        return;
    }

    printf("\nEnter Item ID to delete: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.id != id) {
            fwrite(&item, sizeof(Item), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Item deleted successfully!\n");
    else
        printf("Item not found.\n");
}

// Function to search for an item
void searchItem() {
    FILE *file = fopen("inventory.dat", "rb");
    Item item;
    int id, found = 0;

    if (file == NULL) {
        printf("\nNo inventory found.\n");
        return;
    }

    printf("\nEnter Item ID to search: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.id == id) {
            printf("\nItem Found:\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", item.id, item.name, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Item not found.\n");

    fclose(file);
}
