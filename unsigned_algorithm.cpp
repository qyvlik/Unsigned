#include "unsigned_algorithm.h"
#include <iostream>

//std::string multiplication_char(std::string big, char small)
//{
//    small = small - 48; // get the number
//    if(small == 0 || big == "0")
//        return std::string("0");
//    if(small == 1 || big == "1")
//        return big;
//    std::cout << "multiplication_char" << std::endl;

//    big.insert(0,1,'0');
//    int algBit(0);
//    int upBit(0);                           // 进位
//    int bigIndex = big.length()-1;          // 较大数最高位

//    while(bigIndex != -1){
//        algBit = (big.at(bigIndex) - 48) * small + upBit;   // algBit < 100 !
//        upBit = algBit / 10 ;                               // 取十位
//        algBit = algBit > 10 ? algBit % 10 : algBit;        // 取各位
//        big.at(bigIndex) = algBit + 48;
//        bigIndex -= 1;
//    }
//    return big;
//}


std::string addition(std::string big, std::string small)
{
    big.insert(0,1,'0');

    int upBit(0);                           // 进位
    int algBit(0);                          // 正在计算的位
    int smallIndex = small.length()-1;      // 较小数最高位
    int bigIndex = big.length()-1;          // 较大数最高位

    // char int
    //   -1  47
    //    0  48
    //    1  49
    //    2  50
    //    3  51
    //    4  52
    //    5  53
    //    6  54
    //    7  55
    //    8  56
    //    9  57

    while( 1 ){
        if(smallIndex != -1){
            algBit = (big.at(bigIndex) + small.at(smallIndex) - 96) + upBit;
            upBit = algBit - 9;
            upBit = (upBit > 0) ? 1 : 0;                        // 进位为10
            big.at(bigIndex) = static_cast<char>(algBit + 48);
            //            std::cout << "big[" << bigIndex << "]:" << big.at(bigIndex) << std::endl;
            bigIndex -= 1;
            smallIndex -= 1;
        } else if( bigIndex != -1) {
            algBit = (big.at(bigIndex) - 48) + upBit;
            upBit = algBit - 9;
            upBit = (upBit > 0) ? 1 : 0;                        // 进位为10
            big.at(bigIndex) = static_cast<char>(algBit + 48);
            //            std::cout << "big[" << bigIndex << "]:" << big.at(bigIndex) << std::endl;
            bigIndex -= 1;
        } else {
            break;
        }

    }
    return big;
}


std::string subtraction(std::string big, std::string small)
{
    if(big == small)  return std::string("0");

    int algBit(0);                          // 正在计算的位
    int smallIndex = small.length()-1;      // 较小数最高位
    int bigIndex = big.length()-1;          // 较大数最高位

    while( 1 ){
        if( smallIndex != -1) {

            // 校准借位
            if(big.at(bigIndex) < 48) {
                if(bigIndex - 1 != -1) {
                    big.at(bigIndex) += 10;
                    big.at(bigIndex - 1 ) -= 1;
                }
            }
            algBit = big.at(bigIndex) - small.at(smallIndex) ;

            if(bigIndex - 1 != -1)
                big.at(bigIndex - 1) -= (algBit < 0 ? 1 : 0);

            algBit = algBit < 0 ? algBit + 10 : algBit;

            big.at(bigIndex) = static_cast<char>(algBit + 48);
            bigIndex -= 1;
            smallIndex -= 1;
        } else if(bigIndex != -1) {
            // 校准借位
            if(big.at(bigIndex) < 48) {
                if(bigIndex - 1 != -1) {
                    big.at(bigIndex) += 10;
                    big.at(bigIndex - 1 ) -= 1;
                }
            }
            bigIndex -= 1;
        } else {
            break;
        }
    }
    return big;
}


std::string multiplication(std::string big, std::string small)
{
    if(small == "0" || big == "0")
        return std::string("0");
    if(small == "1" || big == "1")
        return big;

    std::string sum("0");
    std::string temp("0");

    int smallIndex(small.length()-1);      // 较小数最高位
    int zero_count(0);

    while(smallIndex != -1){

        temp = multiplication_char(big, small.at(smallIndex));
        temp.append(zero_count,'0');
        // sum and temp who is bigger !
        // if sum smaller than temp
        // addition will throw a out_of_range
        sum = addition(sum,temp);
        zero_count += 1;
        smallIndex -= 1;
    }
    return sum;
}

