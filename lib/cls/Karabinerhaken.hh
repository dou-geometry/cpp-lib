#ifndef __STRUCT_KARABINERHAKEN_HPP
#define __STRUCT_KARABINERHAKEN_HPP
namespace d{

    template<typename C> //Carrier type
        struct Karabinerhaken {
            Karabinerhaken* tugi=nullptr;
            C d;
            Karabinerhaken(C x, Karabinerhaken* n=nullptr): d(x), tugi(n){}
            ~Karabinerhaken() {
                delete d;
                delete tugi;
            }
            template<typename I> Karabinerhaken* after(I);
            void insertAfter(Karabinerhaken* mae) {
                tugi=(*mae).tugi;
                (*mae).tugi=this;
                return;
            }
            void insert(Karabinerhaken* mae) {
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
        };
}
#include"./Karabinerhaken.tt"
#endif
