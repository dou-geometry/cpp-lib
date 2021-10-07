template<d::R domain,d::R range>
inline double GM(double x) {
#ifdef SANITYCHECK
    assert(domain.contains(x));
#endif
    return range.von()*
        std::pow(range.zu()/range.von(),
        (x-domain.von())/domain.span());
}

int main() {
    return 0;
}
