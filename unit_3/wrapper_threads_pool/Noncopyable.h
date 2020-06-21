#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__
#include<iostream>
using namespace std;
namespace meihao
{
        class Noncopyable
        {
                public:
                        Noncopyable(){};
                        ~Noncopyable(){};
                private:
                        Noncopyable(const Noncopyable&);
                        Noncopyable& operator=(const Noncopyable&);
        };
};
#endif 