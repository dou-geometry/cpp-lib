#include"../../cls.hh"
#include"../bash/stdout.hh"
#include<bits/stdc++.h>
#ifndef __CONN_SAGE_SETTINGS__
#define __CONN_SAGE_SETTINGS__
namespace d::conn::sage::settings {
    template<std::string plotExt="png">
    struct files {
        ofstream scriptf, dataf;
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
                p=conn::bash::exec("mktemp --suffix=."+plotExt);
                p=p.substr(0, p.size()-1);
            }
            if(RGFC>1) {
                d=conn::bash::exec("mktemp");
                d=d.substr(0, d.size()-1);
            }
            if(RGFC>0) {
                s=conn::bash::exec("mktemp --suffix=.sage");
                s=s.substr(0, s.size()-1);
            }
            this->script=s;
            this->plot=p;
            this->data=d;
            this->scriptf.open(this->script);
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
            this->dataf.close();
        }
	friend ostream& operator<<(ostream& os, files &f) {
		os << "Plot: " << f.plot << "\nData: " << f.data << "\nScript: " << f.script;
		return os;
	}
    };

};
#endif
