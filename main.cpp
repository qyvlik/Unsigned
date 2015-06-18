#include <iostream>
#include "unsigned.h"

using namespace std;

Unsigned fibonacci(Unsigned n)
{
    static Unsigned number_0("1");
    static Unsigned number_1("1");
    static Unsigned number_2("2");

    if(n == number_0) return number_0;
    if(n == number_1) return number_1;
    return fibonacci(n-number_1) + fibonacci(n-number_2);
}

int BinSearch(int Array[],int SizeOfArray,int key/*要找的值*/)
{
    int low = 0,high = SizeOfArray-1;
    int mid;
    while (low<=high)
    {
        mid = (low+high) / 2 ;
        if(key == Array[mid])
            return mid;
        if(key < Array[mid])
            high = mid-1;
        if(key>Array[mid])
            low = mid+1;
    }
    return -1;
}

int main()
{
    //    Unsigned u1(2);
    //    Unsigned u2("500000000000000000000000000000000");

    //    cout << " u1: " << u1 << endl;
    //    cout << " u2: " << u2 << endl;

    //    //cout << " u2 % u1: " << u2 % u1 << endl;
    //    cout << " u2 + u1: " << u2 + u1 << endl;
    //    cout << " u2 - u1: " << u2 - u1 << endl;
    //    //cout << " u2 / u1: " << u2 / u1 << endl;
    //    cout << " u2 * u1: " << u2 * u1 << endl;
    //    cout << " u1: " << u1 << endl;
    //    cout << " u2: " << u2 << endl;
    //    cout << " u2 * u1: " << u2 * u1 << endl;

    //    cout << " u2 <  u1: " << ((u2 <  u1) ? "true" : "false") << endl;
    //    cout << " u2 >  u1: " << ((u2 >  u1) ? "true" : "false") << endl;
    //    cout << " u2 <= u1: " << ((u2 <= u1) ? "true" : "false") << endl;
    //    cout << " u2 >= u1: " << ((u2 >= u1) ? "true" : "false") << endl;
    //    cout << " u2 == u1: " << ((u2 == u1) ? "true" : "false") << endl;

    //    cout << " u2 + 10: " << u2 + 10 << endl;
    //    cout << " u2 - 10: " << u2 - 10 << endl;
    //    cout << " u2 * 10: " << u2 * 10 << endl;

        Unsigned u3(400);
        Unsigned u4(5);
        cout << " u3 / u4: " <<
                u3 / u4
             << endl;

//        Unsigned u1("25");
//        Unsigned u2("44");

//        cout <<
//                ( u1 / u2 )
//             << endl;

    return 0;
}
