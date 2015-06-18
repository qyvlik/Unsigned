#ifndef UNSIGNED_H
#define UNSIGNED_H

#include <string>
#include <iostream>

// 123
// [1,2,3]
// 0,1,2
// length 是 最低位
// 0 为最高位

class Unsigned
{

public:
    enum State {
        Undefine = 0,
        Error = -1,
        Normal = 1
    };

    Unsigned(const std::string& data, Unsigned::State state);

    Unsigned(const std::string& data="0");
    Unsigned& operator =  (const std::string& data);

    Unsigned(const Unsigned& other);
    Unsigned& operator = (const Unsigned& other);

    Unsigned(const unsigned long long& other);
    Unsigned& operator = (const unsigned long long& other);

    ~Unsigned();

    friend std::ostream& operator << (std::ostream& os, const Unsigned& rhs){
        if(rhs.state() != Unsigned::Error)
            os << rhs.data() ;
        else
            os << "bad number" << std::endl;
        return os;
    }

    State state() const;

    typedef const unsigned long long uint64;

    Unsigned operator +(const Unsigned& rhs) const;
    Unsigned operator -(const Unsigned& rhs) const;
    Unsigned operator *(const Unsigned& rhs) const;
    Unsigned operator /(const Unsigned &divisor) const;
    Unsigned operator %(const Unsigned &rhs) const;

    Unsigned operator +(const uint64& rhs) const;
    Unsigned operator -(const uint64& rhs) const;
    Unsigned operator *(const uint64& rhs) const;
    Unsigned operator /(const uint64 &rhs) const;
    Unsigned operator %(const uint64 &rhs) const;


    bool operator <  (const Unsigned& rhs) const;
    bool operator >  (const Unsigned& rhs) const;

    bool operator <  (const uint64& rhs) const;
    bool operator >  (const uint64& rhs) const;


    bool operator != (const Unsigned& rhs) const;
    bool operator <= (const Unsigned& rhs) const;
    bool operator >= (const Unsigned& rhs) const;
    bool operator == (const Unsigned& rhs) const;

    bool operator != (const uint64& rhs) const;
    bool operator <= (const uint64& rhs) const;
    bool operator >= (const uint64& rhs) const;
    bool operator == (const uint64& rhs) const;


    Unsigned& operator += (const Unsigned& rhs);
    Unsigned& operator -= (const Unsigned& rhs);
    Unsigned& operator *= (const Unsigned& rhs);
    Unsigned& operator /= (const Unsigned& rhs);

    Unsigned& operator += (const uint64& rhs);
    Unsigned& operator -= (const uint64& rhs);
    Unsigned& operator *= (const uint64& rhs);
    Unsigned& operator /= (const uint64& rhs);


    static std::string toUnsignedString(std::string& unsignedString);
    //static std::string toUnsignedString(const unsigned long long rhs);

protected:
    void setData(const std::string& data);
    void setData(const unsigned long long& data);
    void fixData();

    const std::string& data() const;
    std::string& data();

    void setState(Unsigned::State state);

    size_t length() const;

private:
    std::string m_data;
    State m_state;
};

#endif // UNSIGNED_H
