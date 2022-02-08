//
//  preprocess.cpp
//  C++Project1
//
//  Created by shreyansh khandelwal on 2/8/22.
//

#include <iostream>
#include <string>
#include "defns.h"
using namespace std;
int main() {
    string inputText;
    int i;
    int occurence[NSYMBOLS] = {0};
    /*
    for (inputText; getline(cin,inputText);) {
         char ch[inputText.size() + 1];
         inputText.copy(ch, inputText.size() + 1);
         for (i = 0; i < inputText.size(); i++) {
             if (ch[i] != '\0') {
                 occurence[ch[i]]++;
             }
         }
     }
     */
    
    while(getline(cin, inputText) && !inputText.empty()){
        char ch[inputText.size() + 1];
        inputText.copy(ch, inputText.size() + 1);
        for (i = 0; i < inputText.size(); i++) {
            if (ch[i] != '\0') {
                occurence[ch[i]]++;
            }
        }
    }
    symbol symbol[NSYMBOLS];
    for ( i = 0 ; i < NSYMBOLS ; i ++ ) {
        if(occurence[i] > 0){
            symbol[i].symbol = char(i);
            symbol[i].freq  = occurence[i];
        } else {
            symbol[i].symbol = '\0';
            symbol[i].freq = 0;
        }
    }
    for( i=0 ; i<NSYMBOLS; i++){
        if(symbol[i].freq > 0){
            cout << i << '\t' << symbol[i].freq << endl;
        }
    }
    int numOfAlphaCharacters = 0;
    int numOfNonAlphaCharacters = 0;
    for( i = 0 ; i<NSYMBOLS; i++) {
        if(symbol[i].freq > 0) {
            if((i >=65 && i<=90) || (i>=97 && i<=122)) {
                numOfAlphaCharacters ++;
            } else {
                numOfNonAlphaCharacters ++;
            }
        }
    }
    return 0;

}

