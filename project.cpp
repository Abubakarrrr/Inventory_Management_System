#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <windows.h>
using namespace std;

//-----------Constant Variables--------------//
// file name
fstream file;
// char arrays size
const int Size = 15;
// product name array to compare with user input
char product_name[Size];
// string name to compare allocated_to strings
string name;
// for do while loop (main)
int choice;
// add another record choice  1st case
char add_choice;
// for allocated_to string choice
char allocated_choice = 'Y';
//------ for formatting-------//
int ascii = 178;
char ch = ascii;

struct inventoryitem
{
    int item_Id;
    char name[Size];
    char category[Size];
    int item_count;
    string allocated_to[Size] = {" "};
} inventory;

//-----------function prototypes--------------------//
void show_menu();
void add_item();
void show_item();
void search_item();
void update_item();
void delete_item();
void assign_item();
void retrive_item();
void list_item();

int main()
{

    do
    {
        show_menu();
        cout << "\n"
             << ch << ch << " Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: // add inventory items
            do
            {
                system("cls");
                add_item();
                cout << "Do you want to Add another Item (Y/N) :";
                cin >> add_choice;
            } while (add_choice == 'Y' | add_choice == 'y');
            break;
        case 2: // view inventory items
            show_item();
            break;
        case 3: // search item
            search_item();
            break;
        case 4: // update item
            update_item();
            break;
        case 5: // delete item
            delete_item();
            break;
        case 6: // assign inventory item
            assign_item();
            break;
        case 7: // retrive inventory item
            retrive_item();
            break;
        case 8: // list assigned to specific inventory item
            list_item();
            break;
        case 9: // Exiting
            cout << "\n\tExiting ";
            for (int i = 0; i < 10; i++)
            {
                Sleep(200);
                cout << ".";
            }
            exit(EXIT_SUCCESS);
        default:
            cout << "\n"
                 << ch << ch << " Invalid choice ! Kindly Enter Valid Choice (1-9) : ";
            break;
        }
    } while (true);

    return 0;
}

void show_menu()
{
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Inventory Management System ";
    for (int i = 0; i < 26; i++)
        cout << ch;

    cout << "\n\n"
         << ch << ch << " 1. Add inventory items" << endl;
    cout << "\n"
         << ch << ch << " 2. View all inventory inventory items" << endl;
    cout << "\n"
         << ch << ch << " 3. Search inventory items" << endl;
    cout << "\n"
         << ch << ch << " 4. Edit inventory items" << endl;
    cout << "\n"
         << ch << ch << " 5. Delete inventory items" << endl;
    cout << "\n"
         << ch << ch << " 6. Assign inventory items" << endl;
    cout << "\n"
         << ch << ch << " 7. Retrive inventory items" << endl;
    cout << "\n"
         << ch << ch << " 8. List of faculty members who borrowed a specific item" << endl;
    cout << "\n"
         << ch << ch << " 9. Exit" << endl;
}

void add_item()
{
    // Heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Add Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";
    // User input
    cout << "\tEnter Item name:";
    cin.ignore();
    cin.getline(inventory.name, Size);
    cout << "\tEnter Item ID:";
    cin >> inventory.item_Id;
    cin.ignore();
    cout << "\tEnter Item Category:";
    cin.getline(inventory.category, Size);
    cout << "\tEnter Item count:";
    cin >> inventory.item_count;

    for (int j = 0; j < Size; j++)
    {
        inventory.allocated_to[j] = {"none"};
    }
    // Writing data to file
    file.open("inventory.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
        for (int i = 0; i < inventory.item_count; i++)
        {
            file << inventory.allocated_to[i] << "$";
        }
        file << "\n";

        cout << "\t-----------------------" << endl;
        cout << "\tItem successfully added" << endl;
        cout << "\t-----------------------" << endl;
    }
    file.close();
}

void show_item()
{
    int show_count = 0;
    // Heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " View Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";
    // Retriving data from file and display records
    file.open("inventory.txt", ios::in);
    if (file.is_open())
    {
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {
            cout << "\t\t Displaying Record" << endl;
            cout << "\t--------------------" << endl;
            cout << "\tProduct name : ";
            cout << inventory.name << endl;
            cout << "\tProduct ID:";
            cout << inventory.item_Id << endl;
            cout << "\tProduct Category:";
            cout << inventory.category << endl;
            cout << "\tItem count:";
            cout << inventory.item_count << endl;
            cout << "\tAssigned to:" << endl;
            for (int j = 0; j < inventory.item_count; j++)
            {
                cout << "\t(" << j + 1 << ") . " << inventory.allocated_to[j] << endl;
            }
            cout << "\t--------------------" << endl;
            show_count++;
            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        if (show_count == 0)
        {
            cout << "\t No Record added till now !!!" << endl;
            cout << "\t Add Record and Try Again !!!" << endl;
        }
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
    file.close();
}

void search_item()
{
    int search_count = 0;
    // Heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Search Inventory item ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";
    // Retriving data from file and searching the record by name
    file.open("inventory.txt", ios::in);

    if (file.is_open())
    {
        cin.ignore();
        cout << "\tEnter Inventory Item name you want to search : ";
        cin.getline(product_name, Size);
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {
            if ((stricmp(product_name, inventory.name)) == 0)
            {
                system("cls");
                cout << "\tItem found" << endl;
                cout << "\t--------------------" << endl;
                cout << "\tItem name : ";
                cout << inventory.name << endl;
                cout << "\tItem ID:";
                cout << inventory.item_Id << endl;
                cout << "\tItem Category:";
                cout << inventory.category << endl;
                cout << "\tItem count:";
                cout << inventory.item_count << endl;
                cout << "\tAssigned to:" << endl;
                for (int k = 0; k < inventory.item_count; k++)
                {
                    cout << "\t(" << k + 1 << ") . " << inventory.allocated_to[k] << endl;
                }
                cout << "\t--------------------" << endl;
                search_count++;
            }
            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        if (search_count == 0)
        {
            cout << "\tItem not found....." << endl;
        }
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
    file.close();
}

void update_item()
{
    int update_count = 0, allocated_count = 0;
    fstream file1;
    // Heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Edit inventory items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";

    file.open("inventory.txt", ios::in);
    file1.open("inventory1.txt", ios::out);
    if (file.is_open())
    {
        cin.ignore();
        cout << "\tEnter Item name you want to edit ? :";
        cin.getline(product_name, Size);
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {
            if ((stricmp(product_name, inventory.name)) == 0)
            {

                cout << "\t--------------------" << endl;
                cout << "\t\t Already entered Record" << endl;
                cout << "\t--------------------" << endl;
                cout << "\tProduct name : ";
                cout << inventory.name << endl;
                cout << "\tProduct ID:";
                cout << inventory.item_Id << endl;
                cout << "\tProduct Category:";
                cout << inventory.category << endl;
                cout << "\tItem count:";
                cout << inventory.item_count << endl;
                cout << "\tAssigned to:" << endl;
                for (int j = 0; j < inventory.item_count; j++)
                {
                    cout << "\t(" << j + 1 << ") . " << inventory.allocated_to[j] << endl;
                }

                cout << "\t-----------------------" << endl;
                cout << "\t--Edit Item--" << endl;
                cout << "\t-----------------------" << endl;
                cout << "\tItem name : ";
                cout << inventory.name << endl;
                cout << "\tEnter Item ID:";
                cin >> inventory.item_Id;
                cin.ignore();
                cout << "\tEnter Category:";
                cin.getline(inventory.category, Size);
                cout << "\tEnter Item count:";
                cin >> inventory.item_count;

                int i = 0;
                while (i < inventory.item_count && (allocated_choice == 'Y' || allocated_choice == 'y'))
                {
                    cin.ignore();
                    cout << "\tAllocate to :";
                    getline(cin, inventory.allocated_to[i]);
                    allocated_count++;
                    cout << "\tDo you want to allocate it to another person also? (Y/N) :";
                    cin >> allocated_choice;
                    if (allocated_count >= inventory.item_count && (allocated_choice == 'Y' || allocated_choice == 'y'))
                    {
                        cout << "\tSorry ! All items are booked " << endl;
                        cout << "\tCan't assign to more members...." << endl;
                        cout << "\t-----------------------" << endl;
                        break;
                    }
                    i++;
                }
                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
                update_count++;
                cout << "\tItem successfully edited" << endl;
                cout << "\t-----------------------" << endl;
            }
            else
            {
                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
            }
            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        if (update_count == 0)
        {
            cout << "\tItem not found....." << endl;
        }
        file.close();
        file1.close();
        remove("inventory.txt");
        rename("inventory1.txt", "inventory.txt");
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
    file.close();
}

void delete_item()
{
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Delete Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";

    int delete_count = 0;
    fstream file1;

    file.open("inventory.txt", ios::in);
    if (file.is_open())
    {
        cout << "\tEnter Item name you want to delete ? :";
        cin.ignore();
        cin.getline(product_name, Size);
        cout << "\tAre you sure you want to delete?(Y/N)";
        cin >> add_choice;
        if (add_choice == 'Y' || add_choice == 'y')
        {
            file1.open("inventory1.txt", ios::out);
            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
            while ((!file.eof()))
            {
                if ((stricmp(product_name, inventory.name)) == 0)
                {
                    cout << "\t-----------------------" << endl;
                    cout << "\tRecord is deleted Succesfully !!!" << endl;
                    cout << "\t-----------------------" << endl;
                    delete_count++;
                }
                else
                {
                    file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                    for (int i = 0; i < inventory.item_count; i++)
                    {
                        file1 << inventory.allocated_to[i] << "$";
                    }
                }
                file1 << "\n";
                file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
                for (int j = 0; j < inventory.item_count; j++)
                {
                    getline(file, inventory.allocated_to[j], '$');
                }
            }
            if (delete_count == 0)
            {
                cout << "\t-----------------------" << endl;
                cout << "\tRecord not found....." << endl;
                cout << "\t-----------------------" << endl;
            }
            file.close();
            file1.close();
            remove("inventory.txt");
            rename("inventory1.txt", "inventory.txt");
        }
        else
        {
            cout << "\t-----------------------" << endl;
            cout << "Not deleting the record..." << endl;
            cout << "\t-----------------------" << endl;
        }
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
}

void assign_item()
{
    // int assign_count = 0;
    fstream file1;
    // heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Assign Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";

    file.open("inventory.txt", ios::in);
    file1.open("inventory1.txt", ios::out);
    if (file.is_open())
    {
        cin.ignore();
        cout << "\tEnter the name of item you have to assign to: ";
        cin.getline(product_name, Size);
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {
            if ((stricmp(product_name, inventory.name)) == 0)
            {
                cout << "\tAssigned record: " << endl;
                for (int k = 0; k < inventory.item_count; k++)
                {
                    cout << "\t(" << k + 1 << ") . " << inventory.allocated_to[k] << endl;
                }
                int allocated_count = 0;
                int i = 0;
                cout << "Press enter to continue:";
                while (i < inventory.item_count && (allocated_choice == 'Y' || allocated_choice == 'y'))
                {
                    cin.ignore();
                    cout << "\tAllocate to :";
                    getline(cin, inventory.allocated_to[i]);
                    cout << "\t---------------------------" << endl;
                    cout << "\tItem successfully assigned to :" << inventory.allocated_to[i] << endl;
                    cout << "\t---------------------------" << endl;

                    // assign_count++;
                    cout << "\tAllocate it to another person also? (Y/N):";
                    cin >> allocated_choice;
                    allocated_count++;
                    if (allocated_count >= inventory.item_count && (allocated_choice == 'Y' || allocated_choice == 'y'))
                    {
                        cout << "\t---------------------------" << endl;
                        cout << "\tSorry ! All items are booked " << endl;
                        cout << "\tCannot assign to more....." << endl;
                        cout << "\t---------------------------" << endl;
                        break;
                    }
                    i++;
                }
                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
            }
            else
            {
                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
            }

            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        // if (assign_count == 0)
        // {
        //     cout << "\t---------------------------" << endl;
        //     cout << "\tRecord not found !!!" << endl;
        //     cout << "\t---------------------------" << endl;
        // }
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
    file.close();
    file1.close();
    remove("inventory.txt");
    rename("inventory1.txt", "inventory.txt");
}

void retrive_item()
{
    int retrive_member_count = 0, retrive_name_count = 0;
    fstream file1;
    // heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " Retrive Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";

    file.open("inventory.txt", ios::in);
    file1.open("inventory1.txt", ios::out);
    if (file.is_open())
    {
        cout << "\tEnter the name of item you want to retrive from: ";
        cin.ignore();
        cin.getline(product_name, Size);
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {

            if ((stricmp(product_name, inventory.name)) == 0)
            {
                for (int i = 0; i < inventory.item_count; i++)
                {
                    cout << "\tAlready assigned to: ";
                    cout << inventory.allocated_to[i] << endl;
                    retrive_name_count++;
                }

                cout << "\tEnter the name of member you want to retrive from: ";
                getline(cin, name);
                for (int i = 0; i < inventory.item_count; i++)
                {
                    if (name == inventory.allocated_to[i])
                    {
                        cout << "\t---------------------------" << endl;
                        cout << "\tItem successfully Retrived from " << inventory.allocated_to[i] << endl;
                        cout << "\t---------------------------" << endl;
                        inventory.allocated_to[i] = "none";
                        retrive_member_count++;
                    }
                }

                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
            }

            else
            {
                file1 << inventory.name << " " << inventory.item_Id << " " << inventory.category << " " << inventory.item_count;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    file1 << inventory.allocated_to[i] << "$";
                }
                file1 << "\n";
            }

            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        if (retrive_member_count == 0)
        {
            cout << "\t---------------------------" << endl;
            cout << "\tNo member found of this name !!!" << endl;
            cout << "\t---------------------------" << endl;
        }
        if (retrive_name_count == 0)
        {
            cout << "\t---------------------------" << endl;
            cout << "\tNo record found of this name!!!" << endl;
            cout << "\t---------------------------" << endl;
        }
        file.close();
        file1.close();
        remove("inventory.txt");
        rename("inventory1.txt", "inventory.txt");
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
}

void list_item()
{
    int list_count = 0;
    // Heading
    system("cls");
    cout << "\n";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << " List Inventory Items ";
    for (int i = 0; i < 26; i++)
        cout << ch;
    cout << "\n\n";

    cout << "\tList of faculty members who borrowed a specific item" << endl;
    cout << "\t-----------------------" << endl;
    file.open("inventory.txt", ios::in);
    if (file.is_open())
    {
        cout << "\tEnter the name of item to see assigned members list: ";
        cin.ignore();
        cin.getline(product_name, Size);
        file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
        for (int j = 0; j < inventory.item_count; j++)
        {
            getline(file, inventory.allocated_to[j], '$');
        }
        while ((!file.eof()))
        {

            if ((stricmp(product_name, inventory.name)) == 0)
            {
                cout << "\tAssigned to:" << endl;
                for (int i = 0; i < inventory.item_count; i++)
                {
                    cout << "\t(" << i + 1 << ") . " << inventory.allocated_to[i] << endl;
                }
                list_count++;
                break;
            }
            file >> inventory.name >> inventory.item_Id >> inventory.category >> inventory.item_count;
            for (int j = 0; j < inventory.item_count; j++)
            {
                getline(file, inventory.allocated_to[j], '$');
            }
        }
        if (list_count == 0)
        {
            cout << "\t---------------------------" << endl;
            cout << "\tRecord not found !!!" << endl;
            cout << "\t---------------------------" << endl;
        }
        file.close();
    }
    else
    {
        cout << "\tError ! Cannot open the file";
    }
}