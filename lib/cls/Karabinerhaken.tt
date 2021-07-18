namespace d::Karabinerhaken {
    template<typename I> Karabinerhaken* after(I count) { 
        if(count==0) return this;
        auto midp=(*this).tugi;
        while(--count) {
            midp=midp->tugi;
        }
        return midp;
    }
}
