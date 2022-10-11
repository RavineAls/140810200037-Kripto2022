#include <iostream>
using namespace std;

// generates key vector
void getKeyVector(string key, int keyVector[], int textlen){
	int k = 0;
	for (int i = 0; i < textlen; i++){
		if(key[k]>= 'A' && key[k] <= 'Z'){
            keyVector[i] = (key[k]) % 65;
        }
        else if(key[k]>= 'a' && key[k] <= 'z'){
            keyVector[i] = (key[k]) % 97;
        }
        k = (k + 1) % key.length();
	}
}

//Function untuk Encrypt
string VigEnc(string message, string key){
	//get key Vector
	int keyVector[message.length()];
	getKeyVector(key, keyVector, message.length());;

    //calculate cipher text
	for(int i = 0; i<message.length(); i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            message[i] = (message[i] - 'A' + keyVector[i]) % 26 + 'A';
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            message[i] = (message[i] - 'a' + keyVector[i]) % 26 + 'a';
        }
    }

    //return cipher text
	return message;
}

string VigDec(string message, string key){
    //get key Vector
	int keyVector[message.length()];
	getKeyVector(key, keyVector, message.length());;

    //calculate dechipher text
	for(int i = 0; i<message.length(); i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            message[i] = (message[i] - 'A' - keyVector[i] + 26) % 26 + 'A';
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            message[i] = (message[i] - 'a' - keyVector[i] + 26) % 26 + 'a';
        }
    }

    //return decipher text
	return message;
}

// menu
int main(){
	int pil=0;
    cout << "\nPilih program yang ingin dijalankan";
    cout << "\n1. Encrypt";
    cout << "\n2. Decrypt";
    cout << "\nPilihan (Masukan angka saja): "; 
    cin >> pil;
    
    // Get the message to be encrypted
    cout << "\nMasukkan string text (tanpa spasi, simbol dan, angka)" << endl;
    string message /*= "BjorkaSukaNanas"*/;
    cin >> message;
    cout << "\nMasukkan string kunci" << endl;
    string key/* = "Azgar"*/;
    cin >> key;
    
    switch (pil){
    case 1:
        cout << "\nEncrypted string = ";
            cout << VigEnc (message, key);
        break;
    
    case 2:
        cout << "\nDecrypted string = ";
            cout << VigDec (message, key);
            break;
    
    default:
        break;
    }
    
	return 0;
}
