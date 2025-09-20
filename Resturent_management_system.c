#include <stdio.h>
#include <string.h>

typedef struct menu_item
{
    int code;
    char name[100];
    float price;
} menu;

typedef struct user_details
{
    int id;
    char name[100];
    char pass[100];
} person;

person user[100];
int user_count = 0;
menu item[100];
int menucount = 0;

void management_system();
void editmenu();
void resetmenu();
void addmenu();
void printmenu_tofile();
void showmenu();
void take_order();
void printmenu_tofile_append();
void signup();
void login_select();
void login();

void management_system()
{
    
    int choice;
    do
    {
        system("cls");
        printf("\n-------Restaurant Management System-------\n");
        printf("1. Edit Menu\n");
        printf("2. Show Menu\n");
        printf("3. Take Order\n");
        printf("4. Exit Program\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            editmenu();
            break;
        case 2:
            showmenu();
            printf("Press any key to continue....");
            getchar();
            break;
        case 3:
            take_order();
            break;
        case 4:
            printf("Exiting the program.....");
            break;
        default:
            printf("Invalid choice.....!!\n");
            break;
        }

    } while (choice != 4);
}

void signup()
{
    system("cls");
    printf("----->Signup Panel<-----\n");
    char admin_pass[] = "admin123";
    char given_pass[50];
    FILE *data = fopen("login_data.txt", "a");
    printf("Enter your name(Without Spaces): ");
    fgets(user[user_count].name, 100, stdin);
    user[user_count].name[strcspn(user[user_count].name, "\n")] = '\0';
    printf("Enter your id: ");
    scanf("%d", &user[user_count].id);
    getchar();
    printf("Creat a password: ");
    fgets(user[user_count].pass, 100, stdin);
    user[user_count].pass[strcspn(user[user_count].pass, "\n")] = '\0';
    user_count++;
    printf("Enter the admin pass to signup: ");
    scanf("%s", given_pass);
    if (strcmp(admin_pass, given_pass) == 0)
    {
        for (int i = 0; i < user_count; i++)
        {
            fprintf(data, "%s %d %s\n", user[i].name, user[i].id, user[i].pass);
        }
        fclose(data);
        printf(">----------------------<\n");
        printf("Signup successful ;)\n");
        getchar();
        getchar();

        login_select();
    }
    else
    {
        printf(">----------------------<\n");
        printf("Wrong Admin password..!!");
        getchar();
        getchar();
        login_select();
    }
}

void login()
{
    system("cls");
    printf("----->Login panel<-----\n");
    int flag = 0;
    char pass[50];
    int user_id;
    char line[300];
    FILE *data = fopen("login_data.txt", "r");
    user_count = 0;
    while (fscanf(data, "%49s %d %49s", user[user_count].name, &user[user_count].id, user[user_count].pass) == 3)
    {
        user_count++;
    }

    // printf("total user is %d", user_count);

    printf("Enter your user id: ");
    scanf("%d", &user_id);
    getchar();
    for (int i = 0; i < user_count; i++)
    {

        if (user_id == user[i].id)
        {
            printf("Enter your password: ");
            fgets(pass, 50, stdin);
            pass[strcspn(pass, "\n")] = '\0';
            if (strcmp(pass, user[i].pass) == 0)
            {
                printf(">----------------------<\n");
                printf("Login successful ;)\n\n");
                printf("Welcome %s\n", user[i].name);
                printf("Press any key to enter the program....\n");
                getchar();
                management_system();
                flag++;
            }
            else
            {
                printf("Wrong password!!");
            }
        }
    }
    if (flag == 0)
    {
        printf("No user found by this id!!\n");
    }
    fclose(data);
}

void login_select()
{
    system("cls");
    int login_choice;
    printf("----->Login/Signup panel<-----\n");
    printf("1. Login\n");
    printf("2. Signup\n");
    printf("------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &login_choice);
    getchar();
    switch (login_choice)
    {
    case 1:
        login();
        break;
    case 2:
        signup();
        break;
    default:
        printf("Invalid Choice!!");
    }
}

void editmenu()
{
    
    system("cls");
    char choice, choice1;
    FILE *menu = fopen("Menu.txt", "r");

    
    while (fscanf(menu, "%d %99s %f", &item[menucount].code, item[menucount].name, &item[menucount].price) == 3)
    {
        menucount++;
    }
    fclose(menu);

    printf("------>Menu Edit<------\n");
    printf("1. Make a new menu.\n");
    printf("2. Add item to menu.\n");
    printf("-----------------------\n");
    printf("Enter your choice: ");
    choice1 = getchar();
    getchar(); 
if (choice1 == '1')
    {
        menucount = 0;
    }
    int newItemsStart = menucount;

    if (choice1 == '1' || choice1 == '2') 
    {
        do
        {
            if (menucount >= 100)
            {
                printf("Cannot add more menu items!\n");
                break;
            }

            printf("Enter the item code\t\t: ");
            scanf("%d", &item[menucount].code);
            getchar(); // Consume newline

            printf("Enter the name of the item\t: ");
            fgets(item[menucount].name, 100, stdin);
            item[menucount].name[strcspn(item[menucount].name, "\n")] = '\0';

            printf("Enter price for this item\t: ");
            scanf("%f", &item[menucount].price);
            getchar(); // Consume newline

            menucount++;

            printf("Do you want to add another item? (y/n): ");
            choice = getchar();
            getchar(); // Consume newline
        } while (choice == 'y' || choice == 'Y');

        if (choice1 == '1')
        {
            printmenu_tofile();
        }
        else if (choice1 == '2')
        {
            printmenu_tofile_append(newItemsStart);
        }
    }
    else
    {
        printf("Invalid choice...\n");
    }
}

void printmenu_tofile()
{
    FILE *menu = fopen("Menu.txt", "w");

    for (int i = 0; i < menucount; i++)
    {
        fprintf(menu, "%d %s %.2f\n", item[i].code, item[i].name, item[i].price);
    }
    fclose(menu);
    printf("New menu added successfully ;)");
}

void printmenu_tofile_append(int newItemsStart)
{
    FILE *menu = fopen("Menu.txt", "a");

    for (int i = newItemsStart; i < menucount; i++)
    {
        fprintf(menu, "%d %s %.2f\n", item[i].code, item[i].name, item[i].price);
    }
    fclose(menu);
    printf("New item added successfully ;)");
}

void showmenu()
{
    FILE *menu = fopen("Menu.txt", "r");

    printf("-Code-\t -Name-\t\t\t  -Price-\n");
    printf("------------------------------------------\n");

    menucount = 0;
    while (fscanf(menu, "%d %99s %f", &item[menucount].code, item[menucount].name, &item[menucount].price) == 3)
    {
        menucount++;
    }

    for (int i = 0; i < menucount; i++)
    {
        printf("%-8d %-25s %.2f BDT\n", item[i].code, item[i].name, item[i].price);
    }
    printf("------------------------------------------\n");

    fclose(menu);
}

void take_order()
{
    system("cls");

    int order_code;
    float order_cost[100];
    int order_count;
    char choice;
    float totalcost = 0;
    int j = 0;
    int flag = 0;
    FILE *menu = fopen("Menu.txt", "r");
    FILE *bill = fopen("Bill_record.txt", "a");
    menucount = 0;
    while (fscanf(menu, "%d %99s %f", &item[menucount].code, item[menucount].name, &item[menucount].price) == 3)
    {
        menucount++;
    }
    
    do
    {
        showmenu();
        printf("Enter the item code you want to order: ");
        scanf("%d", &order_code);
        printf("Enter the quantity: ");
        scanf("%d", &order_count);

        for (int i = 0; i < menucount; i++)
        {

            if (order_code == item[i].code)
            {
                order_cost[j] = item[i].price * order_count;
                printf("For %d %s the total cost is:%.2f\n", order_count, item[i].name, order_cost[j]);
                fprintf(bill, "Sold %d %s for %.2f\n", order_count, item[i].name, order_cost[j]);
                j++;
                flag++;
                break;
            }
        }
        if (flag == 0)
        {
            printf("No Item found by this code..!!\n");
        }

        getchar();
        printf("Do you want to order another item?(y/n): ");
        choice = getchar();
        system("cls");
    } while (choice == 'y' || choice == 'Y');

    if (choice == 'n' || choice == 'N')
    {

        for (int i = 0; i <= j; i++)
        {
            totalcost += order_cost[i];
        }
        printf("Total bill: %.2f\n", totalcost);
    }
    fclose(menu);
    fclose(bill);
    printf("Press any key to continue....");
    getchar();
    getchar();
    system("cls");
}

int main()
{

    login_select();

    return 0;
}