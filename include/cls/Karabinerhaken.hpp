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
            template<typename I>
                Karabinerhaken* after(I count) { 
                    if(count==0) return this;
                    auto midp=(*this).tugi;
                    while(--count) {
                        midp=midp->tugi;
                    }
                    return midp;
                }
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
        };

}
#endif
