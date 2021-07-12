#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__
#include"../../cls.hpp"
#include"../bash/stdout.hpp"
namespace d { namespace conn { namespace sage {
    namespace settings {
        struct files {
            ofstream scriptf, plotf, dataf;
            std::string script, plot, data;
            const bool rmData=false, rmScript=false, rmPlot=false;
            files():rmScript(true), rmData(true), rmPlot(true) {
                this->init(3);
            }
            files(std::string pl): rmScript(true), rmData(true) { this->init(2, pl); }
            files(std::string pl, std::string da): rmScript(true) { this->init(1, pl, da); }
            files(std::string pl, std::string da, std::string sc) {this->init(0, pl, da, sc);}
            void init(di RGFC=3, std::string p="", std::string d="", std::string s="") {
                if(RGFC>2) {
                    p=conn::bash::exec("mktemp");
                    p=p.substr(0, p.size()-1);
                }
                if(RGFC>1) {
                    d=conn::bash::exec("mktemp");
                    d=d.substr(0, d.size()-1);
                }
                if(RGFC>0) {
                    s=conn::bash::exec("mktemp");
                    s=s.substr(0, s.size()-1);
                }
                this->script=s;
                this->plot=p;
                this->data=d;
                this->scriptf.open(this->script);
                this->plotf.open(this->plot);
                this->dataf.open(this->data);
                return;
            }
            files(const files &other) =delete;
            files(files &&other) noexcept =delete;
            files& operator=(const files &other) =delete;
            files& operator=(files &&other) noexcept =delete;
            ~files() {
                if(rmScript) conn::bash::exec(("rm "+this->script).c_str());
                if(rmData) conn::bash::exec(("rm "+this->data).c_str());
                if(rmPlot) conn::bash::exec(("rm "+this->plot).c_str());
                this->scriptf.close();
                this->plotf.close();
                this->dataf.close();
            }
        };

    }
    void plot(conn::sage::settings::files&);
}}}
#endif
