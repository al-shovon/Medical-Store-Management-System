#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

//Colour and Style
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define PURPLE "\e[1;95m"
#define BOLD "\033[1m"
#define BLINK "\033[5m"
#define BW "\e[40m"

//File name
#define FILE_NAME "products.txt"

//struct
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
    char category[30];
};

struct CartItem {
    int id;
    char name[50];
    float price;
    int quantity;
    float totalCost;
};

//style
void animatedPrint(const char *text, const char *color);
void animatedPrint2(const char *text, const char *color);

//Function prototype
void Title(); //132
void Title2(); //926
void Title3(); //954
void Title4(); //992
void Title5(); //1016
void Title6();
void Main_Menu(); //147
void pauseAndWait(); //166
void adminPanel(); //235
void customerPanel(); //298
void registerUser(const char *filename); //200
int loginUser(const char *filename);  //176

//Product Function
void addProduct(); //353
void displayProducts(); //495
void deleteProduct(); //529
void updateProduct(); //571
void updateStock();  //623
void autoUpdateStock(int id, int qnt);//1048
void searchProduct(); //421
void sortAndStoreProducts(); //377
void Catagory(); //

//order function
void addToCart(struct CartItem cart[], int *cartCount); //671
void viewCart(struct CartItem cart[], int cartCount); //714
void orderCart(struct CartItem cart[], int cartCount); //746
void viewOrders(); //811
void PaymentMethod(); //819

//security function
void hideInput();//898
void showInput(); //912


//Main Function

int main(){
Title3();
printf("\n");
int choice;


while (1) {
        Title6();
        
        Main_Menu();
        printf("\n%sEnter your choice: %s", CYAN, RESET);
        scanf("%d", &choice);
        printf("\n");
        

        switch (choice) {
            case 1:
                registerUser("customers.txt");
                break;
            case 2:
                if (loginUser("customers.txt")) customerPanel();
                break;
            case 3:
                //registerUser("staff.txt");
                printf("%sPlease Contract with Main Admin\n",RED);
                break;
            case 4:
                if (loginUser("staff.txt")) adminPanel();
                break;
            case 5:
                Title5();
                //printf("%s%sThank You From SMR_PI. Goodbye!%s\n", BOLD,GREEN, RESET);
                exit(0);
            default:
                printf("%sInvalid choice! Please try again.%s\n", RED, RESET);
        }
        pauseAndWait();
        
    }







    return 0;
}


//tittle 

void Title() {
     
    printf("\033[H\033[J"); // ANSI escape: Move to top-left and clear screen
    printf("     %s%s************************************************************\n",BOLD, GREEN);
    printf("     * %sπ %s***   %s%sSMR_PI%s Medical Store Management System     %s*** %sπ %s*    \n",BLUE,GREEN, RED,BLUE,RED, GREEN, BLUE,GREEN);
    printf("     %s************************************************************\n\n", GREEN);
    printf("%s", RESET);
}





//Main_menu

void Main_Menu() {
    printf("%s",BOLD);
    animatedPrint("                        MAIN MENU", RED);
    animatedPrint("            ______________________________π", CYAN);
    printf("%s           |                               |%s\n",YELLOW,RESET);
    printf("%s           |  %s 1. Register as Customer    %s |\n",YELLOW,MAGENTA, YELLOW);
    printf("           |   %s2. Login as Customer       %s |\n",MAGENTA,YELLOW);
    printf("           |                               |\n");
    printf("           |   %s3. Register as Admin       %s |\n",CYAN,YELLOW);
    printf("           |   %s4. Login as Admin           %s|\n",CYAN,YELLOW);
    printf("           |                               |\n");
    printf("           |   %s5. Exit                    %s |\n",RED,YELLOW);
    printf("           |_______________________________|%s\n", RESET);
    //animatedPrint("            _______________________________ ", CYAN);
    
}

// Function to pause and wait for user input

void pauseAndWait() {
    printf("\n%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
    getchar();
}



// Registration function

void registerUser(const char *filename) {
    FILE *file = fopen(filename, "ab"); // Open file in binary append mode
    if (file == NULL) {
        printf("%sError: Unable to open file.%s\n", RED, RESET);
        return;
    }

    char name[50], password[50];
    printf("%sEnter username: %s", MAGENTA, RESET);
    scanf("%s", name);
    printf("%sEnter password: %s", MAGENTA, RESET);
    scanf("%s", password);

    // Write the username and password to the file in binary format
    fwrite(name, sizeof(char), 50, file);       // Fixed size for consistency
    fwrite(password, sizeof(char), 50, file);  // Fixed size for consistency

    printf("%sRegistration successful!%s\n", GREEN, RESET);
    fclose(file);
}


// Login function

int loginUser(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Open file in binary read mode
    if (file == NULL) {
        printf("%sError: Unable to open file.%s\n", RED, RESET);
        return 0;
    }

    char name[50], password[50];
    char storedName[50], storedPassword[50];

    printf("%sEnter username: %s", MAGENTA, RESET);
    scanf("%s", name);
    printf("%sEnter password: %s", MAGENTA, RESET);
    hideInput();
    scanf("%s", password);
    showInput();

    // Read binary data and check credentials
    while (fread(storedName, sizeof(char), 50, file) == 50 && 
           fread(storedPassword, sizeof(char), 50, file) == 50) {
        if (strcmp(name, storedName) == 0 && strcmp(password, storedPassword) == 0) {
            printf("%sLogin successful!%s\n", GREEN, RESET);
            fclose(file);
            return 1;
        }
    }

    printf("%sInvalid credentials!%s\n", RED, RESET);
    fclose(file);
    return 0;
}


// Admin panel

void adminPanel() {
    int choice;
    while (1) {
        Title();
        printf("%s",BOLD);
        animatedPrint("      ADMIN Panel  ", RED);
        animatedPrint("    |_____________|   ", BLUE);
        printf("%s\n",RESET);
        printf("%s   1. Add Product.\n",CYAN);
        printf("   2. Update Product.\n");
        printf("   3. Delete Product.\n");
        printf("   4. Search Product.\n");
        printf("   5. Display All Products.\n");
        printf("   6. Display All Order.\n");
        printf("   7. Update Only Stock of a Product.\n");
        printf("   8. Register store new Staff.\n");
        printf("   9. Logout.\n");
        
        printf("%sEnter your choice: %s", MAGENTA, RESET);
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                addProduct();
                sortAndStoreProducts();

                break;
            case 2:
                updateProduct();
                sortAndStoreProducts();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                displayProducts();
                break;
            case 6:
                viewOrders();
                break;
            case 7:
                updateStock();
                break;
            case 8:
                registerUser("staff.txt");
                break;

            case 9:
                printf("%sReturning to Main Menu...%s\n", YELLOW, RESET);
                return;
            default:
                printf("%sInvalid choice! Please try again.%s\n", RED, RESET);
        }
        pauseAndWait();
    }
}

// Customer panel

void customerPanel() {
    struct CartItem cart[100];
    int cartCount = 0;

    int choice;
    while (1) {
        Title();
        printf("%s",BOLD);
        animatedPrint("       CUSTOMER PANEL    ", RED);
        animatedPrint("     |________________|   ", BLUE);

        printf("\n%s1. Search Product\n",CYAN);
        printf("2. Display All Products\n");
        printf("3. Add to Cart\n");
        printf("4. View Cart\n");
        printf("5. Order Cart Products\n");
        printf("6. Logout\n");
        printf("%sEnter your choice: %s", MAGENTA, RESET);
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                searchProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                displayProducts();
                addToCart(cart, &cartCount);
                break;
            case 4:
                viewCart(cart, cartCount);
                break;
            case 5:
                orderCart(cart, cartCount);
                cartCount = 0; // Clear the cart after ordering
                break;
            case 6:
                printf("%sReturning to Main Menu...%s\n", YELLOW, RESET);
                return;
            default:
                printf("%sInvalid choice! Please try again.%s\n", RED, RESET);
        }
        pauseAndWait();
    }
}






//Product function

void addProduct() {
    FILE *file = fopen(FILE_NAME, "a"); // Open in text append mode
    struct Product product;

    printf("%sEnter product ID: ",BLUE);
    scanf("%d", &product.id);
    printf("Enter product name: ");
    scanf("%s", product.name);
    printf("Enter product price: ");
    scanf("%f", &product.price);
    printf("Enter product quantity: ");
    scanf("%d", &product.quantity);
    printf("Enter product category: ");
    scanf("%s", product.category); // Add category input
    printf("%s",RESET);

    fprintf(file, "%d %s %.2f %d %s\n", product.id, product.name, product.price, product.quantity, product.category);
    fclose(file);

    printf("%sProduct added successfully!\n",GREEN);
    printf("%s",RESET);
}

//Sorting Category
void sortAndStoreProducts() {
    FILE *file = fopen(FILE_NAME, "r");
    struct Product products[100];
    struct Product temp;
    int count = 0;

    // Read all products into an array
    while (fscanf(file, "%d %s %f %d %s", 
                  &products[count].id, 
                  products[count].name, 
                  &products[count].price, 
                  &products[count].quantity, 
                  products[count].category) != EOF) {
        count++;
    }
    fclose(file);

    // Sort products by category
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(products[i].category, products[j].category) > 0) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    // Write sorted products back to the file
    file = fopen(FILE_NAME, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %d %s\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].quantity, 
                products[i].category);
    }
    fclose(file);
}


//Search Function

void searchProduct() {
    FILE *file = fopen(FILE_NAME, "r");
    struct Product product;
    int choice, id, found = 0;
    char category[30];

    printf("%s%sSearch by:%s\n%s1. Product ID\n2. Category%s\n%sEnter choice: %s",YELLOW,BOLD,RESET,BLUE,RESET,MAGENTA,RESET);
    scanf("%d", &choice);
    printf("\n");
    if (choice == 1) {
        printf("%sEnter product ID to search: %s",MAGENTA,RESET);
        scanf("%d", &id);

        while (fscanf(file, "%d %s %f %d %s", 
                      &product.id, 
                      product.name, 
                      &product.price, 
                      &product.quantity, 
                      product.category) != EOF) {
            if (product.id == id) {
                printf("\n%sProduct ID: %d\n", CYAN,product.id);
                printf("Name: %s\n", product.name);
                printf("Price: %.2f\n", product.price);
                printf("Quantity: %d\n", product.quantity);
                printf("Category: %s\n", product.category);
                printf("%s",RESET);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("%sProduct not found!\n",RED);
            printf("%s",RESET);
        }
    } else if (choice == 2) {
        Catagory();
        printf("\n");
        printf("%sEnter category to search: %s",MAGENTA,RESET);
        scanf("%s", category);

        
        printf("\n");
        printf("%s",BOLD);
        animatedPrint("               PRODUCT IN CATEGORY    ", RED);
        animatedPrint("    |_____________________________________|   ", BLUE);
        
        printf("\n%s",YELLOW);
        printf("%-10s %-20s %-10s %-10s %-20s\n", 
               "Product ID", "Name", "Price", "Quantity", "Category");
        printf("%s",RESET);

        while (fscanf(file, "%d %s %f %d %s", 
                      &product.id, 
                      product.name, 
                      &product.price, 
                      &product.quantity, 
                      product.category) != EOF) {
            if (strcmp(product.category, category) == 0) {
                printf("%-10d %-20s %-10.2f %-10d %-20s\n", 
                       product.id, product.name, product.price, product.quantity, product.category);
                found = 1;
            }
        }
        if (!found) {
            printf("%sNo products found in this category!%s\n",RED,RESET);
        }
    } else {
        printf("%sInvalid choice!%s\n",RED,RESET);
    }

    fclose(file);
}


//Display Product

void displayProducts() {
    FILE *file = fopen(FILE_NAME, "r");
    struct Product product;

    if (!file) {
        printf("%sNo products found!%s\n",RED,RESET);
        return;
    }


    printf("%s",BOLD);
    animatedPrint("                    PRODUCT LIST    ", RED);
    animatedPrint("|_________________________________________________|", BLUE);

    printf("\n%s",YELLOW);
    printf("%-10s %-20s %-10s %-10s %-20s\n", 
           "ID", "Name", "Price", "Quantity", "Category");
    printf("%s%s\n",RESET,CYAN);

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, 
                  product.name, 
                  &product.price, 
                  &product.quantity, 
                  product.category) != EOF) {
        printf("%-10d %-20s %-10.2f %-10d %-20s\n", 
               product.id, product.name, product.price, product.quantity, product.category);
    }

    fclose(file);
}

//Delete function

void deleteProduct() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Product product;
    int id, found = 0;

    if (!file || !tempFile) {
        printf("%sError opening file!%s\n",RED,RESET);
        return;
    }

    printf("%sEnter product ID to delete: %s",MAGENTA,RESET);
    scanf("%d", &id);

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, 
                  product.name, 
                  &product.price, 
                  &product.quantity, 
                  product.category) != EOF) {
        if (product.id == id) {
            found = 1;
            printf("%sProduct with ID %d has been deleted.%s\n",GREEN, id, RESET);
        } else {
            fprintf(tempFile, "%d %s %.2f %d %s\n", 
                    product.id, product.name, product.price, product.quantity, product.category);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found) {
        printf("%sProduct not found!%s\n",RED,RESET);
    }
}

//Update Product Function

void updateProduct() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Product product;
    int id, found = 0;

    if (!file || !tempFile) {
        printf("%sError opening file!%s\n",RED,RESET);
        return;
    }

    printf("%sEnter product ID to update: %s",MAGENTA,RESET);
    scanf("%d", &id);

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, 
                  product.name, 
                  &product.price, 
                  &product.quantity, 
                  product.category) != EOF) {
        if (product.id == id) {
            found = 1;

            printf("%sEnter new name: ",CYAN);
            scanf("%s", product.name);
            printf("Enter new price: ");
            scanf("%f", &product.price);
            printf("Enter new quantity: ");
            scanf("%d", &product.quantity);
            printf("Enter new category: ");
            scanf("%s", product.category);
            printf("%s",RESET);

            printf("%sProduct with ID %d has been updated.%s\n",GREEN, id,RESET);
        }
        fprintf(tempFile, "%d %s %.2f %d %s\n", 
                product.id, product.name, product.price, product.quantity, product.category);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found) {
        printf("%sProduct not found!%s\n",RED,RESET);
    }
}

//Update Only Stock Function

void updateStock() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Product product;
    int id, found = 0;

    if (!file || !tempFile) {
        printf("%sError opening file!%s\n",RED,RESET);
        return;
    }

    printf("%sEnter product ID to update stock: %s",MAGENTA,RESET);
    scanf("%d", &id);

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, 
                  product.name, 
                  &product.price, 
                  &product.quantity, 
                  product.category) != EOF) {
        if (product.id == id) {
            found = 1;

            printf("Enter new quantity: ");
            scanf("%d", &product.quantity);

            printf("%s",RESET);

            printf("%sProduct ID %d Stock has been updated.%s\n",GREEN, id,RESET);
        }
        fprintf(tempFile, "%d %s %.2f %d %s\n", 
                product.id, product.name, product.price, product.quantity, product.category);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found) {
        printf("%sProduct not found!%s\n",RED,RESET);
    }
}


//Add to cart Function

void addToCart(struct CartItem cart[], int *cartCount) {
    int id, quantity;
    struct Product product;
    FILE *file = fopen(FILE_NAME, "r");
    int found = 0;

    printf("\n%sEnter product ID to add to cart: ",YELLOW);
    scanf("%d", &id);
    printf("Enter quantity: %s",RESET);
    scanf("%d", &quantity);

    autoUpdateStock(id,quantity);

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, product.name, &product.price, 
                  &product.quantity, product.category) != EOF) {
        if (product.id == id) {
            if (quantity > product.quantity) {
                printf("%sInsufficient stock for product ID %d!%s\n", RED,id,RESET);
            } else {
                // Add to cart
                strcpy(cart[*cartCount].name, product.name);
                cart[*cartCount].id = product.id;
                cart[*cartCount].price = product.price;
                cart[*cartCount].quantity = quantity;
                cart[*cartCount].totalCost = product.price * quantity;
                (*cartCount)++;
                printf("%sProduct added to cart!%s\n",GREEN,RESET);
                
            }
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("%sProduct not found!%s\n",RED,RESET);
    }
}




//View Cart Function.

void viewCart(struct CartItem cart[], int cartCount) {
    if (cartCount == 0) {
        printf("%sYour cart is empty!%s\n",RED,RESET);
        return;
    }

    float grandTotal = 0;
    

    printf("%s",BOLD);
    animatedPrint("       YOUR CART    ", RED);
    animatedPrint("     |___________|   \n", BLUE);
    printf("%s%s",YELLOW,BOLD);
    printf("%-10s %-20s %-10s %-10s %-10s\n", 
           "Product ID", "Name", "Price", "Quantity", "Total Cost");
    printf("%s",RESET);
    for (int i = 0; i < cartCount; i++) {
        printf("%-10d %-20s %-10.2f %-10d %-10.2f\n", 
               cart[i].id, cart[i].name, cart[i].price, 
               cart[i].quantity, cart[i].totalCost);
        grandTotal += cart[i].totalCost;
    }
    printf("\n");
    printf("%sGrand Total: %s%.2f%s\n", RED,CYAN,grandTotal,RESET);
}





//Order Cart Function

void orderCart(struct CartItem cart[], int cartCount) {
    if (cartCount == 0) {
        printf("%sYour cart is empty! Add items before ordering.%s\n",RED,RESET);
        return;
    }

    char name[50], address[100], phone[15], transactionId[20];
    FILE *orderFile = fopen("orders.txt", "a");
    printf("%s",CYAN);
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your address: ");
    scanf(" %[^\n]", address); // Read multi-word input
    printf("Enter your phone number: ");
    scanf("%s", phone);
    PaymentMethod();
    printf("\n%sEnter payment transaction ID: ",YELLOW);
    scanf("%s", transactionId);
    printf("%s",RESET);
    printf("%s%s",CYAN,BOLD);
    fprintf(orderFile, "Name: %s, Address: %s, Phone: %s, Transaction ID: %s\n", 
            name, address, phone, transactionId);
    fprintf(orderFile, "Ordered Products: \n");
    
    float grandTotal = 0;
    for (int i = 0; i < cartCount; i++) {
        fprintf(orderFile, "%-10d %-20s %-10.2f %-10d %-10.2f\n", 
                cart[i].id, cart[i].name, cart[i].price, 
                cart[i].quantity, cart[i].totalCost);

        //printf("\n%d  %d\n",cart[i].id,cart[i].quantity);
        autoUpdateStock( cart[i].id, cart[i].quantity);

        grandTotal += cart[i].totalCost;
    }
    printf("%s",RED);
    fprintf(orderFile, "Grand Total: %.2f\n", grandTotal);
    printf("%s",YELLOW);
    fprintf(orderFile, "--------------------------------------------\n\n");
    printf("\n");
    fclose(orderFile);

    printf("%sOrder placed successfully!%s\n",GREEN,RESET);
}

//Catagory
void Catagory(){

printf("\n%s%sAll available category: %s\n\n",BOLD,YELLOW, RESET);
printf("%s       1. Mart\n       2.Medicine\n       Skine_Care %s\n",GREEN, RESET);


}


//View Order Function

void viewOrders() {
    FILE *orderFile = fopen("orders.txt", "r");
    char line[200];

    if (!orderFile) {
        printf("%sNo orders found!%s\n",RED,RESET);
        return;
    }

    

    printf("%s",BOLD);
    animatedPrint("                    ALL ORDERS    ", RED);
    animatedPrint("|______________________________________________________|   ", BLUE);

    printf("%s\n",CYAN);
    while (fgets(line, sizeof(line), orderFile)) {
        printf("%s",line);
        
    }
    fclose(orderFile);
    printf("%s",RESET);
    
}


//Payment Method

void PaymentMethod(){


    int method;
    printf("%s%sChoose Payment Method:%s\n %s1. Bkash\n 2. Nagad\n 3. Bank\n 4. Cash on Delivery%s\n",YELLOW,BOLD,RESET,CYAN,RESET);
    printf("%sEnter Choice: ",MAGENTA);
        scanf("%d",&method);
        printf("%s",RESET);
        printf("%s",BLUE);
        if(method == 1){
                printf("1.Bkash : 01777..19\n");
        }
        else if (method == 2)
        {
            printf("2. Nagad : 01772..09\n");
        }
        else if (method == 3)
        {
            printf("3. Bank Name : Islami Bank Bangladesh LTD.\n   Account No: 2050....1\n");
        }

        else
        {
            printf("4. Please Pay in Cash.\n   And enter 'Pay_In_Cash' as Transaction ID\n");
        }

        printf("%s",RESET);
        
        

    
}


//Style function

void animatedPrint(const char *text, const char *color) {
    printf("%s", color);
    while (*text) {
        printf("%c", *text++);
        fflush(stdout);
        usleep(10000); 
    }
    printf("%s\n", RESET); 
}

void animatedPrint2(const char *text, const char *color) {
    printf("%s", color); 
    while (*text) {
        printf("%c", *text++);
        fflush(stdout); 
        usleep(15000); 
    }
    printf("%s", RESET); 
}


//Security Function

void hideInput() {
    struct termios oldt, newt;

    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    
    newt.c_lflag &= ~ECHO;

    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void showInput() {
    struct termios oldt, newt;

    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    
    newt.c_lflag |= ECHO;

    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Title2() {
     
    printf("\033[H\033[J"); 
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);
    printf("     %s",BOLD);
    animatedPrint2("*",GREEN);
    printf(" ");
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("***   ",GREEN);
    animatedPrint2("SMR_PI ",BLUE);
    animatedPrint2("Medical Store Management System     ",RED);
    printf("%s",BOLD);
    animatedPrint2("*** ",GREEN);
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("*",GREEN);
    printf("\n");
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);  
    printf("%s", RESET);
}



void Title3() {
     
    printf("\033[H\033[J"); 
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("  ******   **       ** ********       ********      ******   ",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint(" **        ***     *** **      **     **      **      **     ",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint(" **        **  ***  ** **      **     **      **      **     ",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);
    printf("     %s",BOLD);
    animatedPrint2("*",GREEN);
    printf(" ");
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("***   ",GREEN);
    animatedPrint2("SMR_PI ",BLUE);
    animatedPrint2("Medical Store Management System     ",RED);
    printf("%s",BOLD);
    animatedPrint2("*** ",GREEN);
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("*",GREEN);
    printf("\n");
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("       **  **       ** **  **         **              **     ",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("       **  **       ** **   **        **              **     ",GREEN);
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("  ******   **       ** **    **       **            ******   ",GREEN);  
    printf("%s", RESET);
}


void Title5() {
    printf("\033[H\033[J");
    printf("\n\n\n\n\n\n"); 
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);
    printf("     %s",BOLD);
    animatedPrint2("*",GREEN);
    printf(" ");
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("***   ",GREEN);
    animatedPrint2("    ",BLUE);
    animatedPrint2("        COME BACK AGAIN.               ",RED);
    printf("%s",BOLD);
    animatedPrint2("*** ",GREEN);
    printf("%s",BOLD);
    animatedPrint2("π ",BLUE);
    printf("%s",BOLD);
    animatedPrint2("*",GREEN);
    printf("\n");
    printf("     %s%s",BOLD, GREEN);
    animatedPrint("************************************************************",GREEN);  
    printf("\n\n\n%s", RESET);
}


//Update Auto Stock Function

void autoUpdateStock(int id, int qnt) {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Product product;

    if (!file || !tempFile) {
        
        return;
    }

    while (fscanf(file, "%d %s %f %d %s", 
                  &product.id, product.name, &product.price, 
                  &product.quantity, product.category) != EOF) {
        if (product.id == id) {
            product.quantity -= qnt;
        }
        fprintf(tempFile, "%d %s %.2f %d %s\n", 
                product.id, product.name, product.price, product.quantity, product.category);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    
}

void Title6() {
     
    printf("\033[H\033[J"); // ANSI escape: Move to top-left and clear screen
    printf("%s%s",BOLD, CYAN);
    printf("       ******   **       ** ********       %s%s********      ******   %s%s\n",BOLD,PURPLE,CYAN,BOLD);
 
    printf("      **        ***     *** **      **     %s%s**      **      **     %s%s\n",BOLD,PURPLE,CYAN,BOLD);
 
    printf("      **        **  ***  ** **      **     %s%s**      **      **     %s%s\n",BOLD,PURPLE,CYAN,BOLD);
    printf("     %s%s************************************************************\n",BOLD, GREEN);
    printf("     * %sπ %s***   %s%s%sSMR_PI%s Medical Store Management System%s    %s %s*** %sπ %s*    \n",BLUE,GREEN, RED,BLUE,BW,RED,RESET,BOLD, GREEN, BLUE,GREEN);
    printf("     %s************************************************************\n", GREEN);
    printf("%s", RESET);

    printf("     %s%s",BOLD, CYAN);
   
    printf("       **  **       ** **  **         %s%s**              **     %s%s\n",BOLD,PURPLE,CYAN,BOLD);

    printf("            **  **       ** **   **       %s %s**              **     %s%s\n",BOLD,PURPLE,CYAN,BOLD);
    printf("       ******   **       ** **    **      %s %s**            ******   %s%s\n",BOLD,PURPLE,CYAN,BOLD);  
    printf("%s\n\n", RESET);  

}
