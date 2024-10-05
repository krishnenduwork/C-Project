#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 100
// Structure to store details of an item
struct Item {
    char name[50];
    int quantity;
    float price;
    float total;
};
// Function to print a bill header
void printBillHeader(char customerName[50]) {
    printf("*****************************\n");
    printf("        CUSTOMER BILL        \n");
    printf("*****************************\n");
    printf("Customer: %s\n", customerName);
    printf("-----------------------------\n");
    printf("Item        Quantity    Price    Total\n");
    printf("-----------------------------\n");
}
// Function to print the bill footer (total amount)
void printBillFooter(float totalBill) {
    printf("-----------------------------\n");
    printf("Total Amount: %.2f\n", totalBill);
    printf("*****************************\n");
    printf("Thank you for shopping with us!\n");
    printf("*****************************\n");
}
int main() {
    struct Item items[MAX_ITEMS];
    int itemCount = 0;
    char customerName[50];
    float totalBill = 0.0;
    // Get the customer's name
    printf("Enter customer name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0'; // Remove the newline character
    // Ask user how many items are being purchased
    printf("Enter the number of items: ");
    scanf("%d", &itemCount);
    // Input item details
    for (int i = 0; i < itemCount; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Enter item name: ");
        scanf("%s", items[i].name);
        printf("Enter quantity: ");
        scanf("%d", &items[i].quantity);
        printf("Enter price: ");
        scanf("%f", &items[i].price);
        // Calculate total price for the current item
        items[i].total = items[i].quantity * items[i].price;
        // Add to total bill
        totalBill += items[i].total;
    }
    // Print the bill
    printBillHeader(customerName);
    for (int i = 0; i < itemCount; i++) {
        printf("%-10s   %d       %.2f    %.2f\n", items[i].name, items[i].quantity, items[i].price, items[i].total);
    }
    printBillFooter(totalBill);
    return 0;
}
