#include "object.h"
#include<cstdlib>
namespace DS {

void* Object::operator new(unsigned long long size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p)
{
    free(p);
}

void* Object::operator new[](unsigned long long size) throw()
{
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    free(p);
}

bool Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
    return (this == &obj);
}

Object::~Object()
{

}

}


