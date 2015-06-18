#include "unsigned.h"
#include <regex>
#include <iostream>

using namespace std;

// trim from start
string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}
// trim from end
string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(),
            s.end());
    return s;
}

string &trim(string &s) {
    return ltrim(rtrim(s));
}

string multiplication_char(string big, char small)
{
    small = small - 48; // get the number
    if(small == 0 || big == "0")
        return string("0");
    if(small == 1 || big == "1")
        return big;

    big.insert(0,1,'0');
    int algBit(0);
    int upBit(0);                           // 进位
    int bigIndex = big.length()-1;          // 较大数最高位

    while(bigIndex != -1){
        algBit = (big.at(bigIndex) - 48) * small + upBit;   // algBit < 100 !
        upBit = algBit / 10 ;                               // 取十位
        // algBit < 10
        algBit = algBit > 9 ? algBit % 10 : algBit;        // 取各位
        big.at(bigIndex) = algBit + 48;
        bigIndex -= 1;
    }
    return big;
}

/* //start
string multiplication(string big, string small)
{
    if(small == "0" || big == "0")
        return string("0");
    if(small == "1" || big == "1")
        return big;

    string sum("0");
    string temp("0");

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
///*/ //end


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Unsigned number_1("1");
static const Unsigned number_0("0");
static const Unsigned badNumber("0",Unsigned::Error);

Unsigned::Unsigned(const string &data /* ="0" */):
    m_data(data),
    m_state(Unsigned::Normal)
{
    this->fixData();
    //cout << "Unsigned data: " <<this->data() << endl;
}

Unsigned::Unsigned(const Unsigned &other):
    m_data(other.m_data),
    m_state(other.m_state)
{
}

Unsigned::Unsigned(const string &data, Unsigned::State state):
    m_data(data),
    m_state(state)
{
}

Unsigned::Unsigned(const unsigned long long &other):
    m_data("0"),
    m_state(Unsigned::Normal)
{
    this->setData(other);
    this->fixData();
}

Unsigned::~Unsigned()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void Unsigned::setData(const string &data)
{
    this->m_data = data;
}

void Unsigned::setData(const unsigned long long &data)
{
    char ull[21] = {0};
    sprintf(ull,"%llu",data);
    // Unsigned::setData(const string &data)
    this->setData(string(ull));
    this->fixData();

}

void Unsigned::fixData()
{
    trim(this->m_data);
    this->m_data.erase(this->m_data.begin(),
                       find_if(this->m_data.begin(),
                               this->m_data.end(),
                               not1(ptr_fun<int, int>(
                                        [&](int c)->int{
        if(c == '0') return true;
        else return false;
    }) )));

    regex r("\\D");
    if(regex_match(this->m_data,r)) {

        this->operator =(badNumber);
    }
    if(this->m_data.empty()) {
        this->m_data = "0";
    }
}

const string &Unsigned::data() const
{
    return this->m_data;
}

string &Unsigned::data()
{
    return this->m_data;
}

Unsigned::State Unsigned::state() const
{
    return this->m_state;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Unsigned Unsigned::operator +(const Unsigned &rhs) const
{
    string big = (this->operator > (rhs))? this->data() : rhs.data();
    string small = (this->operator < (rhs))? this->data() : rhs.data();

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
            // 57 + 57  -96 + upBit
            // 114 - 96 + upBit
            // 18 + upBit
            algBit = (big.at(bigIndex) + small.at(smallIndex) - 96) + upBit;
            upBit = algBit - 9;
            upBit = (upBit > 0) ? 1 : 0;                        // 进位为10
            algBit = algBit > 9 ? algBit - 10 : algBit;
            big.at(bigIndex) = static_cast<char>(algBit + 48);
            //            cout << "big[" << bigIndex << "]:" << big.at(bigIndex) << endl;
            bigIndex -= 1;
            smallIndex -= 1;
        } else if( bigIndex != -1) {
            algBit = (big.at(bigIndex) - 48) + upBit;
            upBit = algBit - 9;
            upBit = (upBit > 0) ? 1 : 0;                        // 进位为10
            algBit = algBit > 9 ? algBit - 10 : algBit;
            big.at(bigIndex) = static_cast<char>(algBit + 48);
            //            cout << "big[" << bigIndex << "]:" << big.at(bigIndex) << endl;
            bigIndex -= 1;
        } else {
            break;
        }
    }
    return Unsigned(big);
}

// return abs
Unsigned Unsigned::operator - (const Unsigned &rhs) const
{
    if(*this == rhs)  return Unsigned("0");

    string big = (this->operator > (rhs))? this->data() : rhs.data();
    string small = (this->operator < (rhs))? this->data() : rhs.data();

    int algBit(0);                          // 正在计算的位
    int smallIndex = small.length()-1;      // 较小数最高位
    int bigIndex = big.length()-1;          // 较大数最高位

    while( 1 ){
        if( smallIndex != -1) {

            // 校准借位
            if(big.at(bigIndex) - 48 < 0) {
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
            if(big.at(bigIndex) - 48 < 0) {
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
    return Unsigned(big);
}

Unsigned Unsigned::operator *(const Unsigned &rhs) const
{
    string big = (this->operator > (rhs))? this->data() : rhs.data();
    string small = (this->operator < (rhs))? this->data() : rhs.data();
    string number_0("0");
    string number_1("1");

    if(big == number_0 || small == number_0)
        return Unsigned(number_0);
    if(big == number_1 || small == number_1)
        return Unsigned(big);

    Unsigned sum("0");

    int smallIndex(small.length()-1);      // 较小数最高位
    int zero_count(0);

    while(smallIndex != -1){

        Unsigned temp (multiplication_char(big, small.at(smallIndex)));
        temp.data().append(zero_count,'0');
        // sum and temp who is bigger !
        // if sum smaller than temp
        // addition will throw a out_of_range
        sum += temp;
        zero_count += 1;
        smallIndex -= 1;
    }

    return sum;
}

// this / other
/////////////////////
/////// bad /////////
/////////////////////
Unsigned Unsigned::operator / (const Unsigned &divisor) const
{
    if(*this < divisor )
        return number_0;

    if(divisor  == number_1)
        return (*this);

    if(divisor == number_0)
        return badNumber;

    // this->length() > rhs.length();

    string answer;
    // rhs divisor 除数
    const string& dividendData = this->data();  // 被除数
    const size_t dividendRange = this->length() -1;
    const size_t divisorLength = divisor.length();         // divisor // 除数的长度

    Unsigned tempDiviend(string(dividendData.substr(0, divisorLength)));
    size_t algIndex(divisorLength-1);                                 // 计算的末尾


    if(tempDiviend < divisor ){
        tempDiviend.data().append(dividendData.substr(algIndex+1, 1));
        algIndex += 1;
    }

    // 1,2,3,4, 6,7,8,9;
    char low = 0;
    char high = 9;
    char find = 0;// find 就是商的某一位

    Unsigned tempBit;
    while( algIndex <= dividendRange){
        // 二分
        // bit Search
        while (1) {
            find = (low + high) / 2;
            tempBit = divisor * find;

            if(tempBit < tempDiviend){
                low = find+1;
            } else if(tempBit > tempDiviend)  {
                if(divisor * (find - 1) <= tempDiviend){
                    find -= 1;
                    break;
                } else {
                    low = find - 1;
                }
            } else {
                break;
            }
        }

        tempDiviend -= divisor * find ;
        answer.append(1, static_cast<char>(find+48));

        low = 0;
        high = 9;
        find =(low + high) / 2;

        if(tempDiviend == number_0){
            if(algIndex + divisorLength <=  dividendRange){
                tempDiviend.data().append(dividendData.substr(algIndex+1, divisorLength));
                tempDiviend.fixData();
                if(tempDiviend < divisor)
                    answer.append(divisorLength-1, static_cast<char>(48));
                algIndex += divisorLength;
            } else {
                tempDiviend.data().append(dividendData.substr(algIndex+1, dividendRange - algIndex ));
                if(tempDiviend < divisor)
                    answer.append( dividendRange - algIndex -1, static_cast<char>(48));
                algIndex = dividendRange ;
                break;
            }
        } else {
            int l = divisorLength - tempDiviend.length();
            if( algIndex + l <= dividendRange){
                tempDiviend.data().append(dividendData.substr(algIndex+1, l));
                algIndex += l;
            }
            if(tempDiviend < divisor ){
                if( algIndex + 1 <= dividendRange ){
                    tempDiviend.data().append(dividendData.substr(algIndex, 1));
                    algIndex += 1;
                } else {
                    // 如果 tempDiviend 小于 rhs 除数
                    // 但是 此时 algIndex 已经在 dividendRange
                    // 就不用添加零了
                    if(algIndex < dividendRange)
                        answer.append(tempDiviend.length(),static_cast<char>(48) );
                    // tempDiviend 是余数了
                    break;
                }
            }
        }
        // tempDivisor 从除数中拿出位来补，直到没数可不，就是余数，find直接为零置入answer
        // 有数可以补且位数大于等于 rhs ，再次运算
    }

    return Unsigned(answer);
}

Unsigned Unsigned::operator %(const Unsigned &rhs) const
{
    if(*this < rhs )
        return *this;
    if(rhs  == number_1)
        return number_0;

    if(rhs == number_0)
        return badNumber;

    const string& dividend = this->data();  // 被除数
    const size_t range = this->length() -1;
    const size_t length = rhs.length();

    Unsigned tempDivisor(string(dividend.substr(0, length)));
    size_t algIndex(length-1);                                 // 计算的末尾
    // string& answerData = answer.data();

    int find=5; // find 就是商的某一位
    // 1,2,3,4, 6,7,8,9;

    Unsigned tempBit;
    while( algIndex <= range){
        // 二分
        while (1) {
            tempBit = rhs * find;

            if(tempBit < tempDivisor){
                find += find / 2;
            } else if(tempBit > tempDivisor)  {
                if(rhs.operator *(find - 1) <= tempDivisor){
                    find -= 1;
                    break;
                } else {
                    find -= find / 2;
                }
            } else {
                break;
            }
        }

        tempDivisor -= rhs * find ;
        find = 5;
        // tempDivisor 从除数中拿出位来补，直到没数可不，就是余数，find直接为零置入answer
        // 有数可以补且位数大于等于 rhs ，再次运算

        if( algIndex + length >  range){
            tempDivisor.data().append(dividend.substr(algIndex, range - algIndex));
            break;
        } else {
            tempDivisor.data().append(dividend.substr(algIndex, algIndex + length));
            algIndex += length;
        }
    }

    return tempDivisor;
}

Unsigned Unsigned::operator +(const Unsigned::uint64 &rhs) const
{
    return this->operator +(Unsigned(rhs));
}

Unsigned Unsigned::operator -(const Unsigned::uint64 &rhs) const
{
    return this->operator -(Unsigned(rhs));
}

Unsigned Unsigned::operator *(const Unsigned::uint64 &rhs) const
{
    return this->operator *(Unsigned(rhs));
}

Unsigned Unsigned::operator /(const Unsigned::uint64 &rhs) const
{
    return this->operator /(Unsigned(rhs));
}

Unsigned Unsigned::operator %(const Unsigned::uint64 &rhs) const
{
    return this->operator %(Unsigned(rhs));
}

void Unsigned::setState(Unsigned::State state)
{
    this->m_state = state;
}

size_t Unsigned::length() const
{
    return this->data().size();
}



/*
    Unsigned u3("60");
    Unsigned u4("12");

    cout << "(u3 < u4):" << (u3 < u4) << endl;
    // true
*/

bool Unsigned::operator < (const Unsigned &rhs) const
{
    size_t l1 = this->length();
    size_t l2 = rhs.length();

    if( l1 == l2 ) {
        const string& me = this->data();
        const string& other = rhs.data();
        for(size_t i = 0; i < l1 ; i++ ){
            if(me.at(i) < other.at(i)) {
                return true;
            }
        }
        return false;
    } else {
        return (l1 < l2);
    }
}

bool Unsigned::operator >(const Unsigned &rhs) const
{
    return !this->operator <(rhs);
}

bool Unsigned::operator <(const Unsigned::uint64 &rhs) const
{
    return this->operator <(Unsigned(rhs));
}

bool Unsigned::operator >(const Unsigned::uint64 &rhs) const
{
    return this->operator >(Unsigned(rhs));
}

bool Unsigned::operator !=(const Unsigned &rhs) const
{
    return (rhs.data() != this->data());
}

bool Unsigned::operator <=(const Unsigned &rhs) const
{
    return (this->operator <(rhs) || this->operator ==(rhs));
}

bool Unsigned::operator >=(const Unsigned &rhs) const
{
    return (this->operator >(rhs) || this->operator ==(rhs));
}


bool Unsigned::operator ==(const Unsigned &rhs) const
{
    return (rhs.data() == this->data());
}

bool Unsigned::operator !=(const Unsigned::uint64 &rhs) const
{
    return this->operator !=(Unsigned(rhs));
}

bool Unsigned::operator <=(const Unsigned::uint64 &rhs) const
{
    return this->operator <=(Unsigned(rhs));
}

bool Unsigned::operator >=(const Unsigned::uint64 &rhs) const
{
    return this->operator >=(Unsigned(rhs));
}

bool Unsigned::operator ==(const Unsigned::uint64 &rhs) const
{
    return this->operator ==(Unsigned(rhs));
}

Unsigned &Unsigned::operator +=(const Unsigned &rhs)
{
    /////////////////////
    /////// bad /////////
    /////////////////////

    this->setData(this->operator +(rhs).data());
    return *this;
}

Unsigned &Unsigned::operator -=(const Unsigned &rhs)
{
    /////////////////////
    /////// bad /////////
    /////////////////////

    this->setData((this->operator -(rhs)).data());
    return *this;
}

Unsigned &Unsigned::operator *=(const Unsigned &rhs)
{
    /////////////////////
    /////// bad /////////
    /////////////////////

    this->setData(this->operator *(rhs).data());
    return *this;
}

Unsigned &Unsigned::operator /=(const Unsigned &rhs)
{
    /////////////////////
    /////// bad /////////
    /////////////////////

    this->setData(this->operator /(rhs).data());
    return *this;
}

Unsigned &Unsigned::operator +=(const Unsigned::uint64 &rhs)
{
    return this->operator +=(Unsigned(rhs));
}

Unsigned &Unsigned::operator -=(const Unsigned::uint64 &rhs)
{
    return this->operator -=(Unsigned(rhs));
}

Unsigned &Unsigned::operator *=(const Unsigned::uint64 &rhs)
{
    return this->operator *=(Unsigned(rhs));
}

Unsigned &Unsigned::operator /=(const Unsigned::uint64 &rhs)
{
    return this->operator /=(Unsigned(rhs));
}

Unsigned &Unsigned::operator =(const Unsigned &other)
{
    this->setData(other.data());
    this->setState(other.state());
    return *this;
}

Unsigned &Unsigned::operator =(const string &data)
{
    this->setData(data);
    this->fixData();
    return *this;
}

Unsigned &Unsigned::operator =(const unsigned long long &other)
{
    this->setData(other);
    this->fixData();
    return *this;
}

string Unsigned::toUnsignedString(string &unsignedString)
{
    trim(unsignedString);
    unsignedString.erase(unsignedString.begin(),
                         find_if(unsignedString.begin(),
                                 unsignedString.end(),
                                 not1(ptr_fun<int, int>(
                                          [&](int c)->int{
        if(c == '0') return true;
        else return false;
    }) )));

    regex r("\\D");
    if(regex_match(unsignedString,r)) {
        unsignedString = "0";
    }
    return unsignedString;
}
