#ifndef __STRUCT_KARABINERHAKEN_HPP
#define __STRUCT_KARABINERHAKEN_HPP
#define di long unsigned int
#include<iostream>
namespace d{

    template<typename C> //Carrier type
        struct Karabinerhaken {
            Karabinerhaken* tugi=nullptr;
            C d;
            //Karabinerhaken()=delete;
            Karabinerhaken() {
                C tmp;
                d=tmp;
            }
            Karabinerhaken(C x, Karabinerhaken* n=nullptr): d(x), tugi(n){}
            ~Karabinerhaken() {
                d.~C();
                delete tugi;
            }
            Karabinerhaken& operator=(const Karabinerhaken& x)=delete;
            Karabinerhaken& operator=(const Karabinerhaken&& x)=delete;
            Karabinerhaken(const Karabinerhaken& x)=delete;
            template<typename I> Karabinerhaken* after(I);
            inline Karabinerhaken* insertAfter(Karabinerhaken* mae) {
                tugi=(*mae).tugi;
                (*mae).tugi=this;
                return this;
            }
            inline Karabinerhaken* insert(Karabinerhaken* mae) {
                return this->insertAfter(mae);
            }
            void insert(Karabinerhaken* ptr1, Karabinerhaken* ptr2) {
                if((*ptr2).tugi==ptr1) return (*this).insertAfter(ptr2);
                return (*this).insertAfter(ptr2);
            }
            inline di size() {
                di i=1;
                Karabinerhaken* cur=this;
                while(cur->tugi!=nullptr) {
                    ++i;
                    cur=cur->tugi;
                }
                return i;
            }
            static inline di size(const Karabinerhaken* x) { return x->size(); }
            inline Karabinerhaken* end() {
                Karabinerhaken* cur=this;
                for(; cur->tugi!=nullptr; cur=cur->tugi) {}
                return cur;
            }
            static inline Karabinerhaken* end(const Karabinerhaken* x) { return x->end(); }
            inline friend std::ostream& operator<<(std::ostream& os, const Karabinerhaken& x) {
                os << x.d << "\n";
                if(x->tugi!=nullptr) os << x->tugi;
                return os;
            }
            inline friend std::ostream& operator<<(std::ostream& os, const Karabinerhaken* ptr) {
                os << ptr->d << "\n";
                if(ptr->tugi!=nullptr) os << ptr->tugi;
                return os;
            }
        };
}
#include"./Karabinerhaken.tt"
#endif
