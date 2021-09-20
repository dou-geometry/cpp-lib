#pragma once

namespace d {
    class Z {
        int migi, hidari;
        public:
        bool inclusive=true;
        Z(int a, int b, bool exclu=false): migi(a), hidari(b), inclusive(!exclu) {}
        inline int von() const { return migi; }
        inline int zu() const { return hidari; }
    };
    class R {
        double migi, hidari;
        public:
        bool inclusive=true;
        R(double a, double b, bool exclu=false): migi(a), hidari(b), inclusive(!exclu) {}
        inline double von() const { return migi; }
        inline double zu() const { return hidari; }
        double span() const { return hidari-migi; }
    };
}
