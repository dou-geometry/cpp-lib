#pragma once

namespace d {
    struct rad {
        double val;
        operator d::deg() const {
            return val/M_PI*180.;
        }
    };
    struct trig {
        double val;
    };
    struct jigen {
        di val;
    };
}
