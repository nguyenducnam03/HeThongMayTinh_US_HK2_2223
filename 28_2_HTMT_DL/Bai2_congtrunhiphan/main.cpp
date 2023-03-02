#include <iostream>
#include <string>

using namespace std;

//Tinh tong hai day bit nhi phan o dang bu 2
//input hai day bit d1 d2 8bit
//output la tong hai ma nhi phan
string c1tonghaidaybit(string he21, string he22){
    int len = he21.length();
    string re = "";
    int mod = 0;
    for (int i = len - 1; i >= 0;i--){
        int temp = (int)(he21[i]) + (int)he22[i] - 2*'0' + mod;
        if (temp>=2){
            mod = 1;
            re = to_string(temp-2) + re;
        }
        else{
            mod = 0;
            re = to_string(temp) + re;
        }
    }
    if (he21[0] == he22[0] && re[0]!=he21[0]){
        return "Overflow";
    }
    return re;
}

//ham tim so bu 2 cua bien x co 8 bit
//input string x 8 bit 
//so bu 2 cua x 8 bit
string subc2_sobu2(string x){
    int len = x.length();
    for (int i = 0; i < len;i++){
        if (x[i]=='0'){
            x[i] = '1';
        }
        else {
            x[i] = '0';
        }
    }
    x = c1tonghaidaybit(x, "00000001");
    return x;
}

//tinh hieu hai day bit nhi phan bu 2
//input hai ma nhi phan he21 22
//output ma nhi phan kq = he21 - he22
string c2hieuhaidaybit(string he21, string he22){
    string bu2he22 = subc2_sobu2(he22);
    return c1tonghaidaybit(he21, bu2he22);
}

//ham return ve shift right cua ma nhi phan
//input string x
//output SHR(x)
string subc3_shift_right(string x){
    int len = x.length();
    for (int i = len-1; i > 0;i--){
        x[i] = x[i - 1];
    }
    x[0] = '0';
    return x;
}

//Tinh tong hai day bit nhi phan duong
//input hai day bit d1 d2 8bit
//output la tong hai ma nhi phan
string subc3_tonghaidaybitduong(string he21, string he22){
    int len = he21.length();
    string re = "";
    int mod = 0;
    for (int i = len - 1; i >= 0;i--){
        int temp = (int)(he21[i]) + (int)he22[i] - 2*'0' + mod;
        if (temp>=2){
            mod = 1;
            re = to_string(temp-2) + re;
        }
        else{
            mod = 0;
            re = to_string(temp) + re;
        }
    }
    if (mod==1){
        re = '1' + re;
    }
    return re;
}

//ham chuyen tu so am sang so duong he bu 2 (so duong nay khong dau)
//input sobu2 x am
//output so duong khong dau
string subc3_soamsangduong(string x){
    int len = x.length();
    for (int i = 0; i < len;i++){
    if (x[i]=='0'){
        x[i] = '1';
    }
    else {
        x[i] = '0';
    }
    }
    x = subc3_tonghaidaybitduong(x, "00000001");
    return x;
}

//ham tra ve tich cua hai ma nhi phan bu 2 co dau
//vi la phep nhan nen ket qua se la 2*8+1 = 17 bit
//input hai ma nhi phan bu 2
//output ket qua hai ma nhi phan bu 2 nhan voi nhau
string c3tichhainhiphan(string he21,string he22){
    int sign = 0;
    if (he21[0] != he22[0]){
        sign = 1;
    }
    if (he21[0] == '1'){
        he21 = subc3_soamsangduong(he21);
    }
    if (he22[0] == '1'){
        he22 = subc3_soamsangduong(he22);
    }
    int len = he21.length();
    int n = len;
    string CAQ = "000000000" + he22;
    string temp = "";
    while (n>0){
        if (CAQ[2*len] == '1'){
        temp = subc3_tonghaidaybitduong(he21, CAQ.substr(1, 8));
        if (temp.length()==len+1){
            CAQ.replace(0, len + 1, temp);
        }
        else{
            CAQ.replace(1, len, temp);
        }
        }
        CAQ = subc3_shift_right(CAQ);
        n--;
    }
    if (sign == 1){
        for (int i = 0; i <= 2 * len;i++){
            if (CAQ[i] == '0'){
            CAQ[i] = '1';
            }
            else {
            CAQ[i] = '0';
            }
        }
        CAQ = subc3_tonghaidaybitduong(CAQ, "00000000000000001");
    }
    return CAQ;
}

//ham return ve shift left cua ma nhi phan
//input string x
//output SHL(x)
string subc4_shift_left(string x){
    int len = x.length();
    for (int i = 0; i <len-1;i++){
        x[i] = x[i + 1];
    }
    x[len-1] = '0';
    return x;
}

//chia hai ma nhi phan, dua ra ket qua la so nguyen
//input hai ma nhi phan
//output he21/he22
string c4chiahainhiphan(string he21, string he22){
    int sign1, sign2 = 0;
    if (he21[0] == '1'){
        sign1 = 1;
        he21 = subc3_soamsangduong(he21);
    }
    if (he22[0] == '1'){
        sign2 = 1;
        he22 = subc3_soamsangduong(he22);
    }
    int len = he21.length();
    int n = len;
    string AQ = "00000000" + he21;
    string temp = "";
    while (n>0){
        AQ = subc4_shift_left(AQ);
        temp = c2hieuhaidaybit(AQ.substr(0, 8), he22);
        if (temp[0]=='0'){
            AQ.replace(0, 8, temp);
            AQ[2 * len - 1] = '1';
        }
        n--;
    }
    if (sign1 == sign2 && sign1 == 1){
        string temp2 = AQ.substr(0, 8);
        temp2 = subc2_sobu2(temp2);
        AQ.replace(0, 8, temp2);
    }
    else if (sign1!=sign2 && sign1 == 0){
        string temp2 = AQ.substr(8, 8);
        temp2 = subc2_sobu2(temp2);
        AQ.replace(8, 8, temp2);
    }
    else if (sign1!=sign2 && sign1 == 1){
        string temp2 = AQ.substr(0, 8);
        temp2 = subc2_sobu2(temp2);
        AQ.replace(0, 8, temp2);

        temp2 = AQ.substr(8, 8);
        temp2 = subc2_sobu2(temp2);
        AQ.replace(8, 8, temp2);
    }
    return AQ;
}

int main(){
    string he21 = "10101111";//-81
    string he22 = "11010111";//-86
    string he23 = "00110111";//55
    string he24 = "01010100"; //so bu 2 cua he21
    string he25 = "00000111";
    string he26 = "00000011";
    // cout << "he 1: " << he21 << endl;
    // cout << "he 2: " << he22 << endl;

    // cout << "cong hai ma nhi phan: " << c1tonghaidaybit(he21, he22) << endl;
    // cout << "so bu 2 : " << subc2_sobu2(he21) << endl;
    // cout << "tru hai ma nhi phan: " << c2hieuhaidaybit(he21, he22) << endl;
    // cout << "shift right: " << subc3_shift_right(he21) << endl;
    // cout << "so am sang so duong: " << subc3_soamsangduong("10000001") << endl;
    // cout << "tich hai ma nhi phan: " << c3tichhainhiphan(he21, he23) << endl;
    cout << "chia hai ma nhi phan: " << c4chiahainhiphan(he21, he23);

    cout << endl
         << "hello world" << endl;
    return 0;
}

