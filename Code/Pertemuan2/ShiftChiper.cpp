#include<iostream>
#include<string.h>
using namespace std;

void encrypt(char msg[100], int key){
    char ch;
    for(int i = 0; msg[i] != '\0'; ++i) {
        ch = msg[i];
        //encrypt for lowercase letter
        if (ch >= 'a' && ch <= 'z'){
            if(key>5){ //error handling ASCII>127 or key>5
                ch = ch - 'z' + 'a' - 1;
                ch = ch + key;
                while(ch > 'z') {
                    ch = ch - 'z' + 'a' - 1;
                }
                while(ch < 'a'){
                    ch = ch + 'z' - 'a' + 1;
                }
                msg[i] = ch;
            }
            else{
                ch = ch + key;
                while(ch > 'z') {
                    ch = ch - 'z' + 'a' - 1;
                }
                msg[i] = ch;
            }
        }
        //encrypt for uppercase letter
        else if (ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            while(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }
            msg[i] = ch;
        }
    }
    cout << "Encrypted message: " << msg;
}

void decrypt(char msg[100], int key){
    char ch;
    for(int i = 0; msg[i] != '\0'; ++i) {
        ch = msg[i];
        //decrypt for lowercase letter
        if(ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            while(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
            }
            msg[i] = ch;
        }
        //decrypt for uppercase letter
        else if(ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            while(ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            msg[i] = ch;
        }
    }
    cout << "Decrypted message: " << msg;
}

int main(){
    cout<<"Enter the message: ";
    char msg[100];
    cin.getline(msg,100);
    int length, choice, key;
    cout << "Enter key: ";
    cin >> key;
    key = key%26;
    length = strlen(msg);
    cout<<"\nEnter your choice \n1. Encryption \n2. Decryption \nChoice:";
    cin>>choice;
    switch (choice)
    {
    case 1:
        encrypt(msg, key);
        break;
    case 2:
        decrypt(msg, key);
        break;
    default:
        break;
    }
}