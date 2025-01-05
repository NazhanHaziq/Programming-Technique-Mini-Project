#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void displayMainMenu(); /*void with no parameters*/
void displayNecessities();
void displayFruits();
void displayVegetables();
void displayMeats();
float calculateNecessities(); /*non void with no parameters*/
float calculateFruits();
float calculateVegetables();
float calculateMeats();
float calculatePrice(float);   /*non void with parameters*/
void displayTotalPrice(float); /*void with parameters*/

void main()
{
    float totalPrice = 0;
    int menuInput = 1; /*default menu input*/
    char name[40], phoneNo[20];

    time_t rawTime; /*returns the current system time*/
    struct tm *timeinfo;

    time(&rawTime);
    timeinfo = localtime(&rawTime); /*converts current time to a struct*/

    printf("\n-----------------------");
    printf("\nWELCOME TO RETAIL GROCERY ORDER SYSTEM");
    printf("\n-----------------------");
    printf("\nInsert customer's name : ");
    fgets(name, 40, stdin);
    printf("Insert customer's phone number : ");
    fgets(phoneNo, 20, stdin);

    FILE *fptr; /*declare a file*/

    fptr = fopen("Receipt.txt", "a+");                                                                                                       /*opens the file Receipt.txt for appending (a+), create new file if it doesn't exist*/
    fprintf(fptr, "\n%s \n%s \n%s\n", "----------------------------------", "RETAIL GROCERY RECEIPT", "----------------------------------"); /*fprintf prints information into receipt.txt/file*/
    fprintf(fptr, "%s %s", "Name : ", name);
    fprintf(fptr, "%s %s", "Phone Number : ", phoneNo);
    fprintf(fptr, "%s %d%s%d%s%d\n", "Transaction Time : ", timeinfo->tm_hour, ":", timeinfo->tm_min, ":", timeinfo->tm_sec);
    fprintf(fptr, "%s %d%s%d%s%d", "Transaction Date : ", timeinfo->tm_mday, "-", timeinfo->tm_mon, "-", (timeinfo->tm_year + 1900));
    fprintf(fptr, "\n%s", "----------------------------------");
    fprintf(fptr, "\n%s\t\t%s\t%s", "Item", "Quantity", "Price (RM)");

    while (menuInput != 0 && menuInput < 5) /*menuInput = 0 or 5 to stop the operation*/
    {
        displayMainMenu();
        printf("\nPlease insert commands : ");
        scanf("%d", &menuInput);

        if (menuInput == 1)
        {
            displayNecessities(); /*display menu - item names & price rates for necessities*/
            totalPrice = totalPrice + calculatePrice(calculateNecessities());
        }
        else if (menuInput == 2)
        {
            displayFruits(); /*display menu - item names & price rates for fruits*/
            totalPrice = totalPrice + calculatePrice(calculateFruits());
        }
        else if (menuInput == 3)
        {
            displayVegetables(); /*display menu - item names & price rates for vegetables*/
            totalPrice = totalPrice + calculatePrice(calculateVegetables());
        }
        else if (menuInput == 4)
        {
            displayMeats(); /*display menu - item names & price rates for meats*/
            totalPrice = totalPrice + calculatePrice(calculateMeats());
        }
    }

    displayTotalPrice(totalPrice); /*display total price of transaction*/
    fclose(fptr);                  /*closes Receipt.txt*/
}

void displayMainMenu()
{
    printf("-----------------------");
    printf("\n1. NECESSITIES\n2. FRUITS\n3. VEGETABLES\n4. MEAT\n5. Finalize");
    printf("\n-----------------------");
}

void displayNecessities()
{
    printf("\n-----------------------");
    printf("\nNECESSITIES");
    printf("\n-----------------------");
    printf("\n1. MILK \t\tRM 5.00 (per 1000ml)");
    printf("\n2. BREAD \t\tRM 4.00 (per 600g)");
    printf("\n3. RICE \t\tRM 9.00 (per 1000g)");
    printf("\n4. EGG \t\t\tRM 0.30 (per unit)");
}

void displayFruits()
{
    printf("\n-----------------------");
    printf("\nFRUITS");
    printf("\n-----------------------");
    printf("\n1. APPLES \t\tRM 1.20 (per unit)");
    printf("\n2. BANANA \t\tRM 4.90 (per 1000g)");
    printf("\n3. ORANGE \t\tRM 1.50 (per unit)");
}

void displayVegetables()
{
    printf("\n-----------------------");
    printf("\nVEGETABLES");
    printf("\n-----------------------");
    printf("\n1. TOMATO \t\tRM 3.90 (per 500g)");
    printf("\n2. ONION \t\tRM 3.25 (per 500g)");
    printf("\n3. LETTUCE \t\tRM 10.00 (per 1000g)");
}

void displayMeats()
{
    printf("\n-----------------------");
    printf("\nMEATS");
    printf("\n-----------------------");
    printf("\n1. CHICKEN \t\tRM 16.53 (per 1000g)");
    printf("\n2. BEEF \t\tRM 30.53 (per 1000g)");
    printf("\n3. LAMB \t\tRM 16.00 (per 200g)");
}

float calculateNecessities()
{
    int loop = 1;
    float necessitiesPrice = 0;
    float price;
    float necessitiesCost[2][4] = {
        {5.00, 4.00, 9.00, 0.30}, /*first row is the price and second row is the rate (per X grams/etc) - 2D array*/
        {1000, 600, 1000, 1}};
    int decision, quantity;
    char menu[4][10] = {"Milk", "Bread", "Rice", "Egg"}; /*for purpose of printing the name on Receipt.txt*/

    FILE *fptr;
    fptr = fopen("Receipt.txt", "a");

    while (loop == 1)
    {
        printf("\nPlease insert the item desired (1-4) : ");
        scanf(" %d", &decision);
        printf("Please insert quantity (in GRAMS/ML/unit) : ");
        scanf(" %d", &quantity);

        price = (quantity * necessitiesCost[0][decision - 1] / necessitiesCost[1][decision - 1]);
        necessitiesPrice = necessitiesPrice + price;

        fprintf(fptr, "\n%s\t\t", menu[decision - 1]); /*prints items, quantity & price into Receipt.txt*/
        fprintf(fptr, "%d\t\t", quantity);
        fprintf(fptr, "%.2f", price);

        printf("Do you want to add more?(1 = YES | 0 = EXIT) : ");
        scanf("%d", &loop);
    }
    return necessitiesPrice;
}

float calculateFruits()
{
    int loop = 1;
    float fruitsPrice = 0;
    float price;
    float fruitsCost[2][3] = {
        {1.20, 4.90, 1.50}, /*first row is the price and second row is the rate (per X grams/etc) - 2D array*/
        {1, 1000, 1}};
    int decision, quantity;
    char menu[3][10] = {"Apples", "Banana", "Orange"}; /*for purpose of printing the name on Receipt.txt*/

    FILE *fptr;
    fptr = fopen("Receipt.txt", "a");

    while (loop == 1)
    {
        printf("\nPlease insert the item desired (1-3) : ");
        scanf(" %d", &decision);
        printf("Please insert quantity (in GRAMS/ML/unit) : ");
        scanf(" %d", &quantity);

        price = (quantity * fruitsCost[0][decision - 1] / fruitsCost[1][decision - 1]);
        fruitsPrice = fruitsPrice + price;

        fprintf(fptr, "\n%s\t\t", menu[decision - 1]);
        fprintf(fptr, "%d\t\t", quantity);
        fprintf(fptr, "%.2f", price);

        printf("Do you want to add more?(1 = YES | 0 = EXIT) : ");
        scanf("%d", &loop);
    }
    return fruitsPrice;
}

float calculateVegetables()
{
    int loop = 1;
    float vegetablesPrice = 0;
    float vegetablesCost[2][3] = {
        {3.90, 3.25, 10.00}, /*first row is the price and second row is the rate (per X grams/etc) - 2D array*/
        {500, 500, 1000}};
    int decision, quantity;
    char menu[3][10] = {"Tomato", "Onion", "Lettuce"}; /*for purpose of printing the name on Receipt.txt*/
    float price;

    FILE *fptr;
    fptr = fopen("Receipt.txt", "a");

    while (loop == 1)
    {
        printf("\nPlease insert the item desired (1-3) : ");
        scanf(" %d", &decision);
        printf("Please insert quantity (in GRAMS/ML/unit) : ");
        scanf(" %d", &quantity);

        price = (quantity * vegetablesCost[0][decision - 1] / vegetablesCost[1][decision - 1]);
        vegetablesPrice = vegetablesPrice + price;

        fprintf(fptr, "\n%s\t\t", menu[decision - 1]); /*prints items, quantity & price into Receipt.txt*/
        fprintf(fptr, "%d\t\t", quantity);
        fprintf(fptr, "%.2f", price);

        printf("Do you want to add more?(1 = YES | 0 = EXIT) : ");
        scanf("%d", &loop);
    }
    return vegetablesPrice;
}

float calculateMeats()
{
    int loop = 1;
    float meatsPrice = 0;
    float meatsCost[2][3] = {
        {16.53, 30.53, 16.00}, /*first row is the price and second row is the rate (per X grams/etc) - 2D array*/
        {1000, 1000, 200}};
    int decision, quantity;
    char menu[3][10] = {"Chicken", "Beef", "Lamb"}; /*for purpose of printing the name on Receipt.txt*/
    float price;

    FILE *fptr;
    fptr = fopen("Receipt.txt", "a");

    while (loop == 1)
    {
        printf("\nPlease insert the item desired (1-2) : ");
        scanf(" %d", &decision);
        printf("Please insert quantity (in GRAMS/ML/unit) : ");
        scanf(" %d", &quantity);

        price = (quantity * meatsCost[0][decision - 1] / meatsCost[1][decision - 1]);
        meatsPrice = meatsPrice + price;

        fprintf(fptr, "\n%s\t\t", menu[decision - 1]); /*prints items, quantity & price into Receipt.txt*/
        fprintf(fptr, "%d\t\t", quantity);
        fprintf(fptr, "%.2f", price);

        printf("Do you want to add more?(1 = YES | 0 = EXIT) : ");
        scanf("%d", &loop);
    }
    return meatsPrice;
}

float calculatePrice(float currentPrice)
{
    float price = 0;

    price = price + currentPrice;

    return price;
}

void displayTotalPrice(float totalPrice)
{
    FILE *fptr;
    fptr = fopen("Receipt.txt", "a");

    printf("\nTotal Price = RM %.2f\nReceipt has been recorded, please refer to Receipt.txt file.", totalPrice);
    fprintf(fptr, "\n%s", "----------------------------------");
    fprintf(fptr, "\n%s %.2f", "Total Price = RM ", totalPrice);
}
