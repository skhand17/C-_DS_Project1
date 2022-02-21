//
//  encode.cpp
//  C++Project1
//
//  Created by shreyansh khandelwal on 2/8/22.
//

#include <iostream>
#include <fstream>
#include<string>
#include "defns.h"
using namespace std;
struct temp {
    char alphaSymbols;
    int alphaFrequency;
    int alphaIndex;
};
void insertionSort(tree[], int n);
void printStructure(tree[], int n);
void insertionSortOnNonAlphaCharacters(tree[], int n);
void printStructureOnNonAlphaCharacters(tree[], int n);
void recursiveMerge(tree[] , int low, int high);
void recursiveMergeOnNonAlpha(tree[], int low, int high);
symbol* constructBinaryTreeAlpha(tree[],int n);
symbol* constructBinaryTreeNonAlpha(tree[], int n);


int main(int argc, char** argv) {
    string preProcessFile = argv[1];
    string typeOfSortingMethod = argv[2];
    ifstream infile(preProcessFile);
    int asciiValue;
    int occurence;
    int countOfAlpha = 0;
    int countOfNonAlpha = 0;
    symbol symbols[NSYMBOLS];

    // Initialized the symbol array and pointers to null field.
    for(int i=0; i<NSYMBOLS; i++) {
        symbols[i].symbol = '\0';
        symbols[i].freq = 0;
        symbols[i].parent = NULL;
        symbols[i].left  = NULL;
        symbols[i].right = NULL;
        symbols[i].encoding[i] = '\0';
    }
    while(infile >> asciiValue >> occurence){

        if((asciiValue >=65 && asciiValue <=90) || (asciiValue >=97 && asciiValue <=122)){

            symbols[asciiValue].symbol = (char)asciiValue;
            symbols[asciiValue].freq = occurence;
            countOfAlpha ++;

        } else {

            symbols[asciiValue].symbol = (char)asciiValue;
            symbols[asciiValue].freq = occurence;
            countOfNonAlpha ++;

        }

    }
    infile.close();
    cout << " Num of Alpha Characters : " << countOfAlpha << endl;
    cout << " Num of Non Alpha Characters : " << countOfNonAlpha << endl;

    tree* alpha = new tree[countOfAlpha];
    tree* nonAlpha = new tree[countOfNonAlpha];

    int indexOfAlpha = 0;
    int indexOfNonAlpha = 0;
    for(int i=0; i<NSYMBOLS; i++) {
        if(symbols[i].freq > 0){
            if((i >=65 && i<=90) || (i >=97 && i<=122)) {
                alpha[indexOfAlpha].symbol = (char)i;
                alpha[indexOfAlpha].freq = symbols[i].freq;
                alpha[indexOfAlpha].index = i;
                alpha[indexOfAlpha].root = &symbols[i];
                indexOfAlpha++;
            } else{
                nonAlpha[indexOfNonAlpha].symbol = (char)i;
                nonAlpha[indexOfNonAlpha].freq = symbols[i].freq;
                nonAlpha[indexOfNonAlpha].index = i;
                nonAlpha[indexOfNonAlpha].root = &symbols[i];
                indexOfNonAlpha++;
            }
        }
    }

    int type = 0;
    if(typeOfSortingMethod == "insertion") {
        type = 1;
    } else if(typeOfSortingMethod == "merge"){
        type = 2;
    }
    switch(type) {
        case 1 :
            cout << " User selected insertion sort : " << endl;
            insertionSort(alpha, countOfAlpha);
            insertionSortOnNonAlphaCharacters(nonAlpha, countOfNonAlpha);
            printStructure(alpha, countOfAlpha);
            printStructureOnNonAlphaCharacters(nonAlpha, countOfNonAlpha);
            break;
        case 2 :
            cout << " User selected merge sort : " << endl;
            recursiveMerge(alpha , 0 , countOfAlpha-1);
            printStructure(alpha, countOfAlpha);
            recursiveMergeOnNonAlpha(nonAlpha, 0 , countOfNonAlpha-1);
            printStructureOnNonAlphaCharacters(nonAlpha, countOfNonAlpha);
            break;
        default :
            cout << " Invalid Selection : " << endl;
    }
    
    constructBinaryTreeAlpha(alpha, countOfAlpha);
    constructBinaryTreeNonAlpha(nonAlpha, countOfNonAlpha);
    
    return 0;
}
void insertionSort(tree alpha[], int n){
    int i, j;
    int alphaElementOccurence;
    char alphaElementSymbols;
    int alphaElementIndex;
    for(j=1; j<n; j++) {
        alphaElementSymbols = alpha[j].symbol;
        alphaElementOccurence = alpha[j].freq;
        alphaElementIndex = alpha[j].index;
        i = j - 1;
        while ( i > -1 && alpha[i].freq > alphaElementOccurence) {
            alpha[i+1].freq = alpha[i].freq;
            alpha[i+1].symbol = alpha[i].symbol;
            alpha[i+1].index =  alpha[i].index;
            i --;
        }
        alpha[i+1].freq = alphaElementOccurence;
        alpha[i+1].symbol = alphaElementSymbols;
        alpha[i+1].index =  alphaElementIndex;
    }
}
void insertionSortOnNonAlphaCharacters(tree nonAlpha[], int n) {
    int i, j;
    int nonAlphaElementOccurence;
    char nonAlphaElementSymbols;
    int nonAlphaElementIndex;
    for(j=1; j<n; j++) {
        nonAlphaElementSymbols = nonAlpha[j].symbol;
        nonAlphaElementOccurence = nonAlpha[j].freq;
        nonAlphaElementIndex = nonAlpha[j].index;
        i = j - 1;
        while (i > -1 && nonAlpha[i].freq > nonAlphaElementOccurence) {
            nonAlpha[i + 1].freq = nonAlpha[i].freq;
            nonAlpha[i + 1].symbol = nonAlpha[i].symbol;
            nonAlpha[i + 1].index = nonAlpha[i].index;
            i--;
        }
        nonAlpha[i + 1].freq = nonAlphaElementOccurence;
        nonAlpha[i + 1].symbol = nonAlphaElementSymbols;
        nonAlpha[i + 1].index = nonAlphaElementIndex;
    }
}
void printStructure(tree alpha[], int n) {
    int i;
    for(i=0; i<n; i++) {
        cout << " Symbol is : " << alpha[i].symbol << endl;
        cout << " Frequency of the character is : " << alpha[i].freq << endl;
        cout << " Index of the character or ascii value is : " << alpha[i].index << endl;
    }
}
void printStructureOnNonAlphaCharacters(tree nonAlpha[], int n) {
    int i;
    for(i=0; i<n; i++) {
        cout << " Symbol is : " << nonAlpha[i].symbol << endl;
        cout << " Frequency of the character is : " << nonAlpha[i].freq << endl;
        cout << " Index of the character or ascii value is : " << nonAlpha[i].index << endl;
    }
}
// Combine step of Merge Sort. Based on frequencies the elements are sorted.
// If frequencies are same then based on index they are sorted.
// Alpha characters

void mergeSort(tree alpha[], int low, int mid, int high) {
    int i, j, k;
    temp tempAlpha[100];
    i = low;
    j = mid + 1;
    k = low;
    while(i<=mid && j<=high) {
        if(alpha[i].freq == alpha[j].freq){
            if(alpha[i].index < alpha[j].index){
                tempAlpha[k].alphaFrequency = alpha[i].freq;
                tempAlpha[k].alphaSymbols = alpha[i].symbol;
                tempAlpha[k].alphaIndex = alpha[i].index;
                k++;
                i++;
            } else {
                tempAlpha[k].alphaFrequency = alpha[j].freq;
                tempAlpha[k].alphaSymbols = alpha[j].symbol;
                tempAlpha[k].alphaIndex = alpha[j].index;
                k++;
                j++;
            }
        } else if(alpha[i].freq < alpha[j].freq) {
            tempAlpha[k].alphaFrequency = alpha[i].freq;
            tempAlpha[k].alphaSymbols = alpha[i].symbol;
            tempAlpha[k].alphaIndex = alpha[i].index;
            k++;
            i++;
        } else {
            tempAlpha[k].alphaFrequency = alpha[j].freq;
            tempAlpha[k].alphaSymbols = alpha[j].symbol;
            tempAlpha[k].alphaIndex = alpha[j].index;
            k++;
            j++;
        }

    }

    for(; i <= mid ; i++) {
        tempAlpha[k].alphaFrequency =  alpha[i].freq;
        tempAlpha[k].alphaSymbols = alpha[i].symbol;
        tempAlpha[k].alphaIndex = alpha[i].index;
        k++;
    }
    for(; j<=high; j++){
        tempAlpha[k].alphaFrequency = alpha[j].freq;
        tempAlpha[k].alphaSymbols = alpha[j].symbol;
        tempAlpha[k].alphaIndex = alpha[j].index;
        k++;
    }
    for (int i=low; i<=high; i++) {
        alpha[i].freq = tempAlpha[i].alphaFrequency;
        alpha[i].symbol = tempAlpha[i].alphaSymbols;
        alpha[i].index = tempAlpha[i].alphaIndex;
    }
}
void recursiveMerge(tree alpha[] , int low, int high) {
    if( low < high) {
        int mid = (low + high)/2;
        recursiveMerge(alpha, low, mid);
        recursiveMerge(alpha, mid + 1, high);
        mergeSort(alpha,low, mid, high);
    }
}

// Combine step of Merge Sort. Based on frequencies the elements are sorted.
// If frequencies are same then based on index they are sorted.
// NonAlpha characters

void mergeSortOnNonAlpha(tree nonAlpha[], int low, int mid, int high) {
    int i, j, k;
    temp tempNonAlpha[100];
    i = low;
    j = mid + 1;
    k = low;
    while(i<=mid && j<=high) {
        if(nonAlpha[i].freq == nonAlpha[j].freq) {
            if (nonAlpha[i].index < nonAlpha[j].index) {
                tempNonAlpha[k].alphaFrequency = nonAlpha[i].freq;
                tempNonAlpha[k].alphaSymbols = nonAlpha[i].symbol;
                tempNonAlpha[k].alphaIndex = nonAlpha[i].index;
                k++;
                i++;
            } else {
                tempNonAlpha[k].alphaFrequency = nonAlpha[j].freq;
                tempNonAlpha[k].alphaSymbols = nonAlpha[j].symbol;
                tempNonAlpha[k].alphaIndex = nonAlpha[j].index;
                k++;
                j++;
            }
        } else if(nonAlpha[i].freq < nonAlpha[j].freq) {
            tempNonAlpha[k].alphaFrequency = nonAlpha[i].freq;
            tempNonAlpha[k].alphaSymbols = nonAlpha[i].symbol;
            tempNonAlpha[k].alphaIndex = nonAlpha[i].index;
            k++;
            i++;
        } else {
            tempNonAlpha[k].alphaFrequency = nonAlpha[j].freq;
            tempNonAlpha[k].alphaSymbols = nonAlpha[j].symbol;
            tempNonAlpha[k].alphaIndex = nonAlpha[j].index;
            k++;
            j++;
        }
    }
    for(; i <= mid ; i++) {
        tempNonAlpha[k].alphaFrequency =  nonAlpha[i].freq;
        tempNonAlpha[k].alphaSymbols = nonAlpha[i].symbol;
        tempNonAlpha[k].alphaIndex = nonAlpha[i].index;
        k++;
    }
    for(; j<=high; j++){
        tempNonAlpha[k].alphaFrequency = nonAlpha[j].freq;
        tempNonAlpha[k].alphaSymbols = nonAlpha[j].symbol;
        tempNonAlpha[k].alphaIndex = nonAlpha[j].index;
        k++;
    }
    for (int i=low; i<=high; i++) {
        nonAlpha[i].freq = tempNonAlpha[i].alphaFrequency;
        nonAlpha[i].symbol = tempNonAlpha[i].alphaSymbols;
        nonAlpha[i].index = tempNonAlpha[i].alphaIndex;
    }
}
void recursiveMergeOnNonAlpha(tree nonAlpha[] , int low, int high) {
    if( low < high) {
        int mid = (low + high)/2;
        recursiveMergeOnNonAlpha(nonAlpha, low, mid);
        recursiveMergeOnNonAlpha(nonAlpha, mid + 1, high);
        mergeSortOnNonAlpha(nonAlpha,low, mid, high);
    }
}

symbol* constructBinaryTreeAlpha(tree alphaArray[], int n) {
    for (int j = 0; j < n - 1; j++) {

        tree left_tree = alphaArray[0];
        tree right_tree = alphaArray[1];

        symbol* p = new symbol; // p is of type symbol*
        p->parent = NULL;
        p->symbol = '$';

        left_tree.root->parent = p;
        right_tree.root->parent = p;

        p->left = left_tree.root;
        p->right = right_tree.root;
        p->freq = left_tree.freq + right_tree.freq;

        alphaArray++;

        // Storing the parent symbol information in the alphaArray
        alphaArray[0].root = p;
        alphaArray[0].freq = p->freq;
        alphaArray[0].symbol = p->symbol;
        
        // Sorting the elements and putting them in the correct order
        for (int i = 1; alphaArray[i].freq <= alphaArray[i - 1].freq && i < n - 1; i++) {
            tree temp = alphaArray[i];
            alphaArray[i] = alphaArray[i - 1];
            alphaArray[i - 1] = temp;
        }
    }
    return alphaArray[0].root;
}

symbol* constructBinaryTreeNonAlpha(tree nonAlphaArray[], int n) {
    for (int j = 0; j < n - 1; j++) {

        tree left_tree = nonAlphaArray[0];
        tree right_tree = nonAlphaArray[1];

        symbol* p = new symbol; // p is of type symbol*
        p->parent = NULL;
        p->symbol = '$';

        left_tree.root->parent = p;
        right_tree.root->parent = p;

        p->left = left_tree.root;
        p->right = right_tree.root;
        p->freq = left_tree.freq + right_tree.freq;

        nonAlphaArray++;

        // Storing the parent symbol information in the alphaArray
        nonAlphaArray[0].root = p;
        nonAlphaArray[0].freq = p->freq;

        // put all elements into correct positions
        for (int i = 1; nonAlphaArray[i].freq <= nonAlphaArray[i - 1].freq && i < n - 1; i++) {
            tree temp = nonAlphaArray[i];
            nonAlphaArray[i] = nonAlphaArray[i - 1];
            nonAlphaArray[i - 1] = temp;
        }
    }
    return nonAlphaArray[0].root;
}


