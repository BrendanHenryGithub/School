#include <iostream>
using namespace std;

void change(int a[]){
    int tmp;
    tmp=a[1];
    a[1]=a[0];
    a[0]=tmp;
}

void test (int &b){
    b=10000;
}

int main(){
    int arr[2]={1,100};
    change (arr);
    int testb=0;
    test(testb);
    cout << arr[0] << "  " << arr[1] << endl;
    cout << testb << endl;
    return 1;
}