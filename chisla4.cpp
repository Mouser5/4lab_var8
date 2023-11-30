#include <stdio.h>
#include "conio.h"
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

#include "windows.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Tree {
    double key;
    Tree* left;
    Tree* right;
};

Tree* FillTree(Tree* tree, double key) {
        if (tree == NULL) {
            tree = (Tree*)malloc(sizeof(Tree));
            tree->left = NULL;
            tree->right = NULL;
            tree->key = key;
        }
        else
        {
            if (tree->key > key)
                tree ->left=FillTree(tree->left, key);
            if (tree->key < key)
                tree->right=FillTree(tree->right, key);
        }
        return (tree);
}

Tree* Delete(Tree* tree) {
    if (tree->left != NULL)
        tree->left =Delete(tree->left);
    if ((tree != NULL)&&(tree->right!=NULL))
        tree->right =Delete(tree->right);
    tree = nullptr;
    return (tree);
}

Tree* FindKey(Tree *tree, double key) {
    if (tree == NULL)
        return(tree);
    if (tree->key == key)
        tree =Delete(tree);
    else
        if (tree->key > key)
            tree->left=FindKey(tree->left, key);
        else
           tree->right= FindKey(tree->right, key);
    return (tree);
}

int x = 0,temp=0;
int PrintTree(Tree * tree, int y)
{
    if (tree != NULL)
    {
        PrintTree(tree->left, y + 1);
        if (y>temp)
            temp = y;
        gotoxy(x, y); 
        printf("%.0f", tree->key);
        
        x++;
        PrintTree(tree->right, y + 1);
    }
    return (temp);
}

void Program(){
    Tree* tree = NULL;
    int tempkey=0;
    double key;
    ifstream inFile("input.txt", ios::in);
    while (!inFile.eof()) {
        inFile >> key; 
        tree=FillTree(tree, key);
    }
    cout << "This is your tree:" << endl;
    int temp= PrintTree(tree,1);
    x = 0;
    gotoxy(0, temp + 1);
    cout << "What key you want to delete?" << endl;
    cin >> tempkey;
    cout << "New tree:" << endl;
    tree =FindKey(tree, tempkey);
    temp=PrintTree(tree, 4+ temp);
    gotoxy(0, temp);
}

int main()
{
    Program();
}
