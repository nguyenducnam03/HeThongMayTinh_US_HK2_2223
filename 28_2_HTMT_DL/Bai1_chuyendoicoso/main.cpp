#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//chuyen tu he 10 sang he 2
//input he 10
//output he2
string c1tu10sang2(string he10){
    string he2 = "";
    int temp = atoi(he10.c_str());
    while(temp/2!=0){
        he2 = to_string(temp % 2) + he2;
        temp = temp / 2;
    }
    he2 = to_string(temp % 2) +he2;
    return he2;
}

//chuyen tu he 10 sang he 16
//input he 10
//output he16
string c2tu10sang16(string he10){
    string he16 = "";
    int temp = atoi(he10.c_str());
    while(temp/16!=0){
        he16 = to_string(temp % 16) + he16;
        temp = temp / 16;
    }
    he16 = to_string(temp % 16) +he16;
    return he16;
}

//chuyen tu he 2 sang he 10
//input he 2
//output he10
string c3tu2sang10(string he2){
    int temp = 0;
    int len = he2.length();
    for (int i = len - 1; i >= 0;i--){
        if (he2[i]=='1'){
            temp = temp + pow(2, len - i-1);
        }
    }
    return to_string(temp);
}   

//chuyen tu he 16 sang he 10
//input he 16
//output he10
string c4tu16sang10(string he16){
    int temp = 0;
    int len = he16.length();
    for (int i = len - 1; i >= 0;i--){
        if (he16[i]<'9' && he16[i]>'0'){
            temp = temp + pow(16, len - i - 1) * ((int)he16[i] - '0');
        }
        else {
            temp = temp + pow(16, len - i - 1) * ((int)he16[i] - 'A' + 10);
        }
    }
    return to_string(temp);
}

//chuyen tu he 2 sang he 16
//input he 2
//output he 15
string c5tu2sang16(string he2){
    string he10 = c3tu2sang10(he2);
    string he16 = c2tu10sang16(he10);
    return he16;
}

int main(){
    string he10 = "25";
    string he2 = "1000101";
    string he16 = "254FAB";
    cout << "he 10 sang 2: " << he10 << " = " << c1tu10sang2(he10) << endl;
    cout << "he 10 sang 16: " << he10 << " = " << c2tu10sang16(he10) << endl;
    cout << "he 2 sang 10: " << he2 << " = " << c3tu2sang10(he2) << endl;
    cout << "he 16 sang 10: " << he16 << " = " << c4tu16sang10(he16) << endl;
    cout << "he 2 sang 16: " << he2 << " = " << c5tu2sang16(he2) << endl;

    cout << endl
         << "hello world" << endl;
    return 0;
}