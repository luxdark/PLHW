#include "settings.h"

void settings :: reset() {
    std :: ofstream fout (file);
    fout << "preset " << 0 << " preset " << "file" << std :: endl;
    fout << "postset " << "endfile" << " postset " << "file" << std :: endl;
    std :: map <std :: string, param> u;
    params = u;
}

#include <chrono>

void settings :: reload() {
    std :: ifstream fin (file);
    int count = 0;
    using std :: string;
    params.clear();
    string s[4];
    fin >> s[0] >> s[1] >> s[2] >> s[3];
    if (s[0] == s[2] && s[2] == "preset") {
        count = std :: stoi (s[1]);
    }
    for (int i = 0; i < count; i++) {
        settings :: param k;
        fin >> s[0] >> s[1] >> s[2] >> s[3];
        k = s[2];
        params[s[1]] = k;
    }
    fin >> s[0] >> s[1] >> s[2] >> s[3];
    if (s[0] == "postset" && s[2] == s[0] && s[1] == "endfile") {
        return;
    }
    fin.close();
    std :: ofstream fout (file);
    fout << "preset 0 preset file\npostset endfile postset file";
}

void settings :: set(std::string const & name, std::string const & value) {
    if (value.size() > 0)
        params[name] = value;
    int count = params.size();
    std :: ofstream fout (file);
    fout << "preset " << count << " preset " << "file" << std :: endl;
    for (std :: map <std :: string, param> :: iterator u = params.begin(); u != params.end(); u++) {
        fout << "param " << u->first << " " << (std :: string) u->second << " param" << std :: endl;
    }
    fout << "postset " << "endfile" << " postset " << "file" << std :: endl;
}

std :: string const & settings :: get(std::string const & name, std::string const & def, std :: string res) const {
    std :: map <std :: string, param> buff = params;
    res = def;
    if (!buff[name].is_empty()) {
        res = (std :: string) buff [name];
    }
    return res;
}

settings :: settings(std::string const & filename) {
    file = filename;
    std :: ifstream fin (filename);
    int count = 0;
    using std :: string;
    string s[4];
    fin >> s[0] >> s[1] >> s[2] >> s[3];
    if (s[0] == s[2] && s[2] == "preset") {
        count = std :: stoi (s[1]);
    }
    for (int i = 0; i < count; i++) {
        settings :: param k;
        fin >> s[0] >> s[1] >> s[2] >> s[3];
        k = s[2];
        params[s[1]] = k;
    }
    fin >> s[0] >> s[1] >> s[2] >> s[3];
    if (s[0] == "postset" && s[2] == s[0] && s[1] == "endfile") {
        return;
    }
    fin.close();
    std :: ofstream fout (filename);
    fout << "preset 0 preset file\npostset endfile postset file";
}

settings :: param :: operator std :: string () const {
    if (rval == "empty") return "";
    return val + ((tval.size () != 0) ? ("." + tval) : (""));
}

settings :: param :: operator int() const {
    return std :: stoi (val);
}

settings :: param :: operator double() const {
    if (tval.size() > 0)
        return std :: stod (val + '.' + tval);
    return std :: stod (val);
}

settings :: param :: operator bool() const {
    if (((tval == "0" || tval == "") && val == "0") || val.size() == 0 || val == "false") {
        return false;
    }
    return true;
}

settings :: param & settings :: param :: operator=(std::string const & s) {
    rval = "";
    for (char c : s) {
        if ((c < '0' || c > '9') && c != '-' && c != '.' && c != '+') {
            rval = "str";
            break;
        }
    }
    std :: string v, t;
    unsigned int i;
    for (i = 0; i < s.size() && s[i] != '.'; i++) {
        v.push_back (s[i]);
    }
    for (i++; i < s.size(); i++) {
        t.push_back (s[i]);
    }
    val = v;
    tval = t;
    if (s == "true") {
        val = "1";
    }
    if (s == "false") {
        val = "0";
    }
    return *this;
}

settings :: param & settings :: param :: operator=(int i) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    val = std :: to_string (i);
    tval = "";
    return *this;
}

settings :: param & settings :: param :: operator=(bool b) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    val = ((b) ? "1" : "0");
    tval = "";
    return *this;
}

settings :: param & settings :: param :: operator=(double d) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    val = std :: to_string (d);
    unsigned int i, j;
    for (i = 0; i < val.size(); i++) {
        if (val[i] == '.') {
            break;
        }
    }
    j = i;
    tval = "";
    for (i++; i < val.size(); i++) {
        tval.push_back (val[i]);
    }
    val.resize(j);
    return *this;
}

settings :: param & settings :: param :: operator+=(std :: string const & s) {
    rval = "str";
    val = val + ((tval.size() > 0) ? ('.' + tval) : ("")) + s;
    return *this;
}

settings :: param & settings :: param :: operator+=(int i) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    val = std :: to_string (std :: stoi (val) + i);
    return *this;
}

settings :: param & settings :: param :: operator-=(int i) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    val = std :: to_string (std :: stoi (val) - i);
    return *this;
}

settings :: param & settings :: param :: operator*=(int i) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u * i;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator/=(int i) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u / i;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator+=(double d) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u + d;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator-=(double d) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u - d;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator*=(double d) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u * d;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator/=(double d) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    settings :: param k = *this;
    double u = k;
    k = u / d;
    val = k.val;
    tval = k.tval;
    return *this;
}

settings :: param & settings :: param :: operator|=(bool b) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    bool q = *this;
    tval = "";
    val = (q | b ? "1" : "0");
    return *this;
}

settings :: param & settings :: param :: operator&=(bool b) {
    if (rval == "str") {
        return *this;
    }
    rval = "";
    bool q = *this;
    tval = "";
    val = (q & b ? "1" : "0");
    return *this;
}

bool settings :: param :: is_empty() const {
    return ((rval != "empty") ? false : true);
}
