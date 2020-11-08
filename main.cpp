/*
Name: Kien Do
ICS4U - Mr. Maloley
Last Edit: Nov 8, 2019.
Purpose: Create a colour coded selection sort program that sorts from lowest to highest.
http://www.cplusplus.com/forum/beginner/77879/
*/
/**
1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
                            7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white
**/
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

// ==============  FUNCTION PROTOTYPES  ==============
void swapp(int&, int&);
void SetColor(int);
int *generateRandomArray(int*, int);
void instructionMenu();

void displayArray(int[], int);
void displaySortedArray(int[], int, int, int);
void displayCompare(int, int, int, int, int, int);
void displaySwap(int, int, int, int, int, int);

void selectionSort(int[], int, int);

// ==============  FUNCTIONS  ==============

void swapp(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    return;
}

void SetColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

int *generateRandomArray(int *arr, int arrSize)
{
    srand(time(nullptr));
    for (int i = 0; i < arrSize; i++)
    {
        arr[i] = rand() % 300 + 1;
    }
    return arr;
}

void instructionMenu()
{
    SetColor(4);
    cout << "RED   : lowest value." << endl;
    SetColor(3);
    cout << "BLUE  : the value that is being compared to RED." << endl;
    SetColor(5);
    cout << "PURPLE: values that are being swapped." << endl;
    SetColor(2);
    cout << "GREEN : sorted values." << endl;
    SetColor(7);
    cout << "WHITE : unsorted values." << endl << endl;
    return;
}

void displayArray(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

void displaySortedArray(int arr[], int arrSize, int speed, int sorted)
{
    if (speed != 4)
    {
        instructionMenu();
    }
    for (int i = 0; i < arrSize; i++)
    {
        if (i < sorted)
        {
            SetColor(2);
        }
        cout << arr[i] << "  ";
        SetColor(7);
    }
    cout << endl;
    if (speed != 4)
    {
        Sleep(speed);
        system("CLS");
    }
    return;
}

void displayCompare(int arr[], int arrSize, int j, int lowest, int speed, int sorted)
{
    if (speed != 4)
    {
        instructionMenu();
    }
    for (int i = 0; i < arrSize; i++)
    {
        if (i < sorted)
        {
            SetColor(2);
        }
        else if (i == j)
        {
            SetColor(3);
        }
        else if (i == lowest)
        {
            SetColor(4);
        }
        cout << arr[i] << "  ";

        SetColor(7);
    }
    cout << endl;
    if (speed != 4)
    {
        Sleep(speed);
        system("CLS");
    }
    return;
}

void displaySwap(int arr[], int arrSize, int i, int lowest, int speed, int sorted)
{
    if (speed != 4)
    {
        instructionMenu();
    }
    for (int x = 0; x < arrSize; x++)
    {
        if (x < sorted)
        {
            SetColor(2);
        }
        else if (x == i)
        {
            SetColor(5);
        }
        else if (x == lowest)
        {
            SetColor(5);
        }
        cout << arr[x] << "  ";

        SetColor(7);
    }
    if (speed == 4)
    {
        cout << "  <-------   Swapping";
    }
    cout << endl;
    if (speed != 4)
    {
        Sleep(speed);
        system("CLS");
    }
    return;
}

void selectionSort(int arr[], int arrSize, int speed)
{
    int lowest = 0;
    int sorted = 0;
    if (speed == 4)
    {
        instructionMenu();
        displayArray(arr, arrSize);
    }
    for (int i = 0; i < arrSize; i++)
    {
        lowest = i;
        displayCompare(arr, arrSize, -1, lowest, speed, sorted);
        // -1 is an arbitrary number. no colour change will happen in displayCompare
        // meant to display only the lowest value + sorted
        for (int j = i+1; j < arrSize; j++)
        {
            displayCompare(arr, arrSize, j, lowest, speed, sorted);
            if (arr[j] < arr[lowest])
            {
                lowest = j;
            }
            displayCompare(arr, arrSize, -1, lowest, speed, sorted);
        }
        // call displaySwap. send arr, i, lowest
        displaySwap(arr, arrSize, i, lowest, speed, sorted);
        swapp (arr[i], arr[lowest]);
        displaySwap(arr, arrSize, i, lowest, speed, sorted);
        sorted++;
        displaySortedArray(arr, arrSize, speed, sorted);
    }
    displaySortedArray(arr, arrSize, 4, sorted);
    return;
}

int main()
{
    string repeat = "1";
    int arrSize = 0;
    int speed = 0;
    int *p;
    do
    {
        cout << "                          Selection Sort" << endl << endl;
        cout << "Enter array size    : ";
        cin >> arrSize;
        while (arrSize <= 0 || arrSize > 100) // error trap
        {
            cout << "ERROR: Please enter a positive integer from 1 to 100 inclusive." << endl;
            cout << "Enter array size    : ";
            cin >> arrSize;
        }
        int arr[arrSize] = {}; // create array after size is determined
        p = generateRandomArray(arr, arrSize);
        for (int i = 0; i < arrSize; i++)
        {
            arr[i] = *(p + i);
        }
        cout << "Random array values : ";
        displayArray(arr, arrSize);
        cout << endl << endl;
        instructionMenu();
        cout << "Select desired display speed:" << endl;
        cout << "1. Slow           2. Normal           3. Fast           4. Display all" << endl;
        cin >> speed;
        while (speed < 1 || speed > 4)
        {
            cout << "Error: Select a number that corresponds with a choice." << endl;
            cin >> speed;
        }
        if (speed == 1)
        {
            speed = 1000;
        }
        else if (speed == 2)
        {
            speed = 500;
        }
        else if (speed == 3)
        {
            speed = 50;
        }
        system("CLS");

        selectionSort(arr, arrSize, speed);
        cout << endl;
        cout << "Would you like to repeat?      1. Yes     2. No" << endl;
        cin >> repeat;
        while (repeat != "1" && repeat != "2")
        {
            cout << "ERROR: Enter 1 for yes, 2 for no." << endl;
            cin.ignore();
            getline(cin, repeat);
        }
        system("CLS");
    } while (repeat == "1");
    return 0;
}
