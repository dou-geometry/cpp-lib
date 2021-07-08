#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__
namespace d { namespace conn { namespace sage { namespace settings {

struct files {
    ofstream scriptf, plotf, dataf;
    std::string script, plot, data;
    const bool rmData, rmScript, rmPlot;
    files():files(3) rmScript(true), rmData(true), rmPlot(true) {}
    files(std::string pl):files(2, pl), rmScript(true), rmData(true) {}
    files(std::string pl, std::string da):files(1, pl, da), rmScript(true) {}
    files(std::string pl, std::string da, std::string sc):files(0, pl, da, sc) {}
    files(di RGFC=3, std::string p="", std::string d="", std::string s="") {
        if(RGFC>2) p=d::conn::bash::exec("mktemp");
        if(RGFC>1) d=d::conn::bash::exec("mktemp");
        if(RGFC>0) s=d::conn::bash::exec("mktemp");
        this->script=s;
        this->plot=p;
        this->data=d;
        this->scriptf.open(this->script);
        this->plotf.open(this->plot);
        this->dataf.open(this->data);
    }
    ~files() {
        if(rmScript) d::conn::bash::exec("rm "+this->script);
        if(rmData) d::conn::bash::exec("rm "+this->data);
        if(rmPlot) d::conn::bash::exec("rm "+this->plot);
        this->scriptf.close();
        this->plotf.close();
        this->dataf.close();
    }
}

}}}
#endif
