#include <iostream>
using namespace std;

// generates key matrix
void getKeyMatrix(string key, int keyMatrix[][3]){
	int k = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if(key[k]>= 'A' && key[k] <= 'Z'){
                keyMatrix[i][j] = (key[k]) % 65;
            }
            else if(key[k]>= 'a' && key[k] <= 'z'){
                keyMatrix[i][j] = (key[k]) % 97;
            }
			k++;
		}
	}
}

// generates key matrix
void getTextMatrix(string key, int keyMatrix[][3]){
	int k = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if(key[k]>= 'A' && key[k] <= 'Z'){
                keyMatrix[j][i] = (key[k]) % 65;
            }
            else if(key[k]>= 'a' && key[k] <= 'z'){
                keyMatrix[j][i] = (key[k]) % 97;
            }
			k++;
		}
	}
}

// generates Determinant
float getDeterminant(int keyMatrix[3][3]){
    return keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
           keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
           keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
}

// calculate inverse
void getInverse(int invMatrix[3][3], int det_inv, int keyMatrix[3][3]){

    invMatrix[0][0] = ((keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) * det_inv)%26;
    invMatrix[1][0] = (-(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) * det_inv)%26;
    invMatrix[2][0] = ((keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]) * det_inv)%26;
    invMatrix[0][1] = (-(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]) * det_inv)%26;
    invMatrix[1][1] = ((keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]) * det_inv)%26;
    invMatrix[2][1] = (-(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]) * det_inv)%26;
    invMatrix[0][2] = ((keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) * det_inv)%26;
    invMatrix[1][2] = (-(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]) * det_inv)%26;
    invMatrix[2][2] = ((keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) * det_inv)%26;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(invMatrix[i][j]<0){
                invMatrix[i][j]=invMatrix[i][j]+26;
            }
        }
    }
}

//encrypt process
void encrypt(int cipherMatrix[][1], int keyMatrix[][3], int messageVector[][1]){
	int x, i, j;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 1; j++){
			cipherMatrix[i][j] = 0;
		
			for (x = 0; x < 3; x++){
				cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
			}
		
			cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
		}
	}
}

//Function Encrypt
string HillEnc(string message, string key){
	//get key matrix
	int keyMatrix[3][3];
	getKeyMatrix(key, keyMatrix);
    
	int messageVector[3][1];

	//generate vector message
	for (int i = 0; i < 3; i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            messageVector[i][0] = (message[i]) % 65;
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            messageVector[i][0] = (message[i]) % 97;
        }
    }

    

	//generates encrypted vector
    int cipherMatrix[3][1];
	encrypt(cipherMatrix, keyMatrix, messageVector);

	string CipherText;
	//generate encrypted text
	for (int i = 0; i < 3; i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            CipherText += cipherMatrix[i][0] + 65;
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            CipherText += cipherMatrix[i][0] + 97;
        }
    }

    //print cipher text
	return CipherText;
}

string HillDec(string message, string key){
    int keyMatrix[3][3];
	getKeyMatrix(key, keyMatrix);
    
	int messageVector[3][1];

	//generate vector message
	for (int i = 0; i < 3; i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            messageVector[i][0] = (message[i]) % 65;
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            messageVector[i][0] = (message[i]) % 97;
        }
    }

    //generate determinant
    int det;
    det = getDeterminant(keyMatrix);

    float flag = 0;
    float det_inv = 0;
    for (int i = 0; i < 26; i++){
        flag = (det * i) % 26;
        if (flag == 1){
            det_inv = i;
        }
    }

    //generate inverse key
    int invMatrix[3][3];
    getInverse(invMatrix, det_inv, keyMatrix);

    int decipherMatrix[3][1];

    //generates decrypted vector
    encrypt(decipherMatrix, invMatrix, messageVector);
    
    string DecipherText;
	//generate decrypted text
	for (int i = 0; i < 3; i++){
        if(message[i]>= 'A' && message[i] <= 'Z'){
            DecipherText += decipherMatrix[i][0] + 65;
        }
        else if(message[i]>= 'a' && message[i] <= 'z'){
            DecipherText += decipherMatrix[i][0] + 97;
        }
    }
    
    //print decipher text
    return DecipherText;
}

void findKey(string plain, string hasil){
    //get plain matrix
	int plainMatrix[3][3];
	getTextMatrix(plain, plainMatrix);

    //get hasil matrix
	int hasilMatrix[3][3];
	getTextMatrix(hasil, hasilMatrix);

    //generate determinant
    int det;
    det=getDeterminant(plainMatrix);

    float flag = 0;
    float det_inv = 0;
    for (int i = 0; i < 26; i++){
        flag = (det * i) % 26;
        if (flag == 1){
            det_inv = i;
        }
    }
    
    //generate plain inverse
    int invPlain[3][3];
    getInverse(invPlain, det_inv, plainMatrix);

    //calculate result
    int result[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int sum = 0;
            for (int k = 0; k < 3; ++k){
                sum += hasilMatrix[i][k] * invPlain[k][j];
            }
            cout<<sum%26<<" ";
        }
        cout<<endl;
    }
}

// menu
int main(){
	int pil=0;
    cout << "\nPilih program yang ingin dijalankan";
    cout << "\n1. Encrypt";
    cout << "\n2. Decrypt";
    cout << "\n3. Find key";
    cout << "\nPilihan (Masukan angka saja): "; 
    cin >> pil;
    
    if(pil==1||pil==2){
        // Get the message to be encrypted
        cout << "\nMasukkan string text\n(tanpa spasi, jika tidak kelipatan 3 tambahkan padding di akhir string)\nContoh : SatuAA (AA diakhir adalah padding)" << endl;
        char message[100] /*= "ACT"*/;
        cin >> message;
        cout << "\nMasukkan string kunci (9 huruf)" << endl;
        string key/* = "GYBNQKURP"*/;
        cin >> key;
        
        switch (pil){
        case 1:
            cout << "\nEncrypted string = ";
            for(int i=0; message[i] != 0; i+=3){
                string plainText;
                plainText.assign(message+i,message+i+3);
                cout << HillEnc (plainText, key);
            }
            break;
        
        case 2:
            cout << "\nDecrypted string = ";
            for(int i=0; message[i] != 0; i+=3){
                string plainText;
                plainText.assign(message+i,message+i+3);
                cout << HillDec (plainText, key);
            }
            break;
        
        default:
            break;
        }
    }

    else if(pil==3){
        cout << "\nMasukkan string plain text (9 huruf tanpa spasi)" << endl;
        string plain/* = "ACTACTACT"*/;
        cin >> plain;
        cout << "\nMasukkan string hasil cipher text (9 huruf tanpa spasi)" << endl;
        string hasil/* = "POHPOHPOH"*/;
        cin >> hasil;
        cout << "\nMatrix Key = \n";
        findKey(plain, hasil);
    }

	return 0;
}
