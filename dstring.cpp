#include "dstring.h"
#include "exception.h"
#include "cstdlib"
#include "cstring"
namespace DS {
void String::init(const char* s)
{
    m_str = strdup(s);
    if(m_str)
    {
       m_length = strlen(m_str);
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string object...");
    }
}
String::String()
{
    init("");
}
String::String(const char* s)
{
    init(s?s:"");
}
String::String(const String& s)
{
    init(s.m_str);
}
String::String(char c)
{
    char s[] = {c,'\0'};
    init(s);
}

int String::length() const
{
    return m_length;
}
const char* String::str() const
{
    return m_str;
}
char& String::operator[] (int i)
{
    if(i>=0&&i<m_length)
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");

    }
}
char String::operator[] (int i) const
{
    return const_cast<String&>(*this)[i];
}
bool String::isEqual(const char* s1, const char* s2, int len) const
{
    bool ret = true;
    for (int i=0;i<len&&ret;i++)
    {
          ret = ret && (s1[i] == s2[i]);
    }
    return  ret;
}

bool String::startWith(const char* s) const
{
    bool ret = (s!=nullptr);
    if(ret)
    {
        int len = strlen(s);
        ret = (len<m_length)&&isEqual(m_str, s, len);
    }
    return ret;
}
bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}
bool String::endOf(const char* s) const
{
    bool ret = (s!=nullptr);
    if(ret)
    {
        int len = strlen(s);
        char* str = m_str + (m_length-len);
        ret = (len<m_length)&&isEqual(str, s, len);
    }
    return ret;
}
bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}
String& String::insert(int i, const char* s)
{
    if(i>=1&&i<=m_length)
    {
        if(s!=nullptr&&s[0]!='\0')
        {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(len+m_length+1));
            if(str)
            {
                strncpy(str, m_str, i);
                strncpy(str+i, s, len);
                strncpy(str+i+len, m_str+i, m_length-i);
                str[len+m_length] = '\0';
                free(m_str);
                m_str = str;
                m_length = len + m_length;
            }
            else
            {
              THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create char* ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
    return *this;
}
String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}
bool String::String::operator== (const char* s) const
{
    return (strcmp(m_str, (s?s:""))==0);
}
bool String::operator== (const String& s) const
{
    return (strcmp(m_str, s.m_str)==0);
}
bool String::operator!= (const char* s) const
{
    return !(*this==(s?s:""));
}
bool String::operator!= (const String& s) const
{
    return !(*this==s.m_str);
}
bool String::operator> (const char* s) const
{
    return (strcmp(m_str, (s?s:""))>0);
}
bool String::operator> (const String& s) const
{
    return (strcmp(m_str, s.m_str)>0);
}
bool String::operator< (const char* s) const
{
    return (strcmp(m_str, (s?s:""))<0);
}
bool String::operator< (const String& s) const
{
    return (strcmp(m_str, s.m_str)<0);
}
bool String::operator>= (const char* s) const
{
    return (strcmp(m_str, (s?s:""))>=0);
}
bool String::operator>= (const String& s) const
{
    return (strcmp(m_str, s.m_str)>=0);
}
bool String::operator<= (const char* s) const
{
    return (strcmp(m_str, (s?s:""))<=0);
}
bool String::operator<= (const String& s) const
{
    return (strcmp(m_str, s.m_str)<=0);
}

String& String::operator= (const char* s)
{

    if(*this != s)
    {
        char* str = strdup(s?s:"");
        if(str)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create char* ...");
        }
    }
    return *this;
}
String& String::trim()
{
    int i = 0;
    int j = m_length - 1;
    while (m_str[i]!='\0') i++;
    while (m_str[j]!='\0') j--;
   if(i==0)
   {
       m_str[j+1] = '\0';
       m_length = j+1;
   }
   else
   {
       for (int k=0,m=i;m<=j;k++,m++)
       {
           m_str[k] = m_str[m];
           m_str[j-i+1] = '\0';
           m_length = j-i+1;
       }
   }
   return *this;

}
String& String::operator= (const String& s)
{
    return (*this = s);
}
String& String::operator= (char c)
{
    char s[] = {c,'\0'};
    return (*this = s);
}
String String::operator+ (const char* s) const
{
    String ret;
    int len = m_length + strlen(s?s:"");
    char* str = reinterpret_cast<char*>(malloc(len+1));
    if(str)
    {
        strcpy(str, m_str);
        strcat(str, (s?s:""));
        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create char* ...");
    }
    return ret;
}
String String::operator+ (const String& s) const
{
    return (*this + s.m_str);
}
String& String::operator+= (const char* s)
{
    return (*this = *this + s);
}
String& String::operator+= (const String& s)
{
    return (*this = *this + s);
}



String::~String()
{
    free(m_str);
}
}
