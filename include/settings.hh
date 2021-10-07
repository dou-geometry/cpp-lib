#include<stdout.hh>
#include<fstream>
#include<iostream>
#include<iomanip>
#ifndef __CONN_SAGE_SETTINGS__
#define __CONN_SAGE_SETTINGS__
namespace d::conn::sage::settings {
    // file Extensions
    static const char png[]="png";
    static const char gif[]="gif";
    static const char apng[]="apng";
    static const char jpeg[]="jpeg";
    static const char indent[]="\t";
    static const char dindent[]="\t\t";

    template<const char *plotExt=png, const char *prependText=indent>
    struct files {
        std::ofstream scriptf, dataf;
        std::string script, plot, data;
        const bool rmData=false, rmScript=false;
        files():rmScript(true), rmData(true) {
            this->init(3);
        }
        files(bool rD, bool rS=true): rmData(rD), rmScript(rS) {
            this->init(3);
        }
        files(std::string pl): rmScript(true), rmData(true) { this->init(2, pl); }
        files(std::string pl, std::string da): rmScript(true) { this->init(1, pl, da); }
        files(std::string pl, std::string da, std::string sc) {this->init(0, pl, da, sc);}
        void init(di RGFC=3, std::string p="", std::string d="", std::string s="") {
            if(RGFC>2) {
                p=conn::bash::exec("mktemp --suffix=."+(std::string)plotExt);
                p=p.substr(0, p.size()-1);
            }
            if(RGFC>1) {
                d=conn::bash::exec("mktemp --suffix=.data");
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
            //conn::bash::exec(("rm "+this->plot).c_str());
            this->scriptf.close();
            this->dataf.close();
            if(rmScript) conn::bash::exec(("rm "+this->script).c_str());
            conn::bash::exec(("[ -e "+this->script+".py ] && rm -- "+this->script+".py").c_str());
            if(rmData) conn::bash::exec(("rm "+this->data).c_str());
        }
        files& newplot() {
            std::string p=conn::bash::exec("mktemp --suffix=."+(std::string)plotExt);
            p=p.substr(0, p.size()-1);
            this->plot=p;
            return *this;
        }
        files& newdata() {
            this->dataf.close();
            if(rmData) conn::bash::exec(("rm "+this->data).c_str());
            std::string d=conn::bash::exec("mktemp --suffix=.data");
            d=d.substr(0, d.size()-1);
            this->data=d;
            this->dataf.open(this->data);
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const files &f) {
            os << prependText << "Plot: " << f.plot << "\n"<<prependText<<"Data: " << f.data << (f.rmData?" (deleted)":"") << "\n"<<prependText<<"Script: " << f.script << (f.rmScript?" (deleted)":"");
            return os;
        }
    };

};
#endif
