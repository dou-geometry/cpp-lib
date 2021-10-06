#pragma once

namespace d {
    class Z {
        int migi, hidari;
        public:
        bool inclusive=true;
        Z(int a, int b, bool exclu=false): hidari(a), migi(b), inclusive(!exclu) {}
        inline int von() const { return hidari; }
        inline int zu() const { return migi; }
    };
    class R {
        double migi, hidari;
        public:
        bool inclusive=true;
        R(double a, double b, bool exclu=false): hidari(a), migi(b), inclusive(!exclu) {}
        inline double von() const { return hidari; }
        inline double zu() const { return migi; }
        double span() const { return migi-hidari; }
        bool contains(double x) const { return hidari<=x && x<=migi; }
        bool inside(const R& another) const { return another.von()<=this->hidari && this->migi<=another.zu(); }
        bool surrounds(const R& another) const { return this->hidari<=another.von() && another.zu()<=this->migi; }
    };
}
