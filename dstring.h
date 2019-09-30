#ifndef DSTRING_H
#define DSTRING_H
#include "object.h"
namespace DS {
class String : public Object
{
protected:
    char* m_str;
    int m_length;
    void init(const char* s);
    bool isEqual(const char* s1, const char* s2, int len) const;
public:
    String();
    String(const char* s);
    String(const String& s);
    String(char c);

    int length() const;
    const char* str() const;
    ~String();

    char& operator[] (int i);
    char operator[] (int i) const;
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;
    String& insert(int i, const char* s);
    String& insert(int i, const String& s);
    String& trim();
    bool operator== (const char* s) const;
    bool operator== (const String& s) const;
    bool operator!= (const char* s) const;
    bool operator!= (const String& s) const;
    bool operator> (const char* s) const;
    bool operator> (const String& s) const;
    bool operator< (const char* s) const;
    bool operator< (const String& s) const;
    bool operator>= (const char* s) const;
    bool operator>= (const String& s) const;
    bool operator<= (const char* s) const;
    bool operator<= (const String& s) const;

    String& operator= (const char* s);
    String& operator= (const String& s);
    String& operator= (char c);
    String operator+ (const char* s) const;
    String operator+ (const String& s) const;
    String& operator+= (const char* s);
    String& operator+= (const String& s);

};
}


#endif // DSTRING_H
