#include <iostream>
#include <string>
#include <vector>

#define STRMAXSIZE 10     // Zdes' mogla byt' vasha reklama
#define MAXINT 2147483647 // Constant better than (1 << 31) - 1

bool th = false; // If problems was detected, th is true

int signd (int a) {  // Sign of number
    if (th) return 0;
    if (a > 0) return 1;
    else return -1;
}

int pow (int u, int s) {  // U^S
    if (th) return 0;
    int res = 1;
    for (int i = 0; i < s; i++) {
        res *= u;
    }
    return res;
}

int to_int (std :: string t) {  // Converting std :: string to int
    if (th) return 0;
    if (t == "0") return 0;
    int res = 0, sign = 1; // signd() if not allowed for this
    if (t[0] == '-') {
        sign = -1;
        t.erase (0, 1);
    }

    if (t.size() > STRMAXSIZE) {
        std :: cout << "Long numbers"; // If user sleeped when pressed number
        th = true;
        return 0;
    }
    if (t.size() == STRMAXSIZE && t >= "2147483647") { // If user wants to test int or long long i used
        std :: cout << "Huge numbers";
        th = true;
        return 0;
    }

    for (int i = t.size() - 1; i >= 0; i--) {
        res += pow (10, t.size() - i - 1) * ((int) t[i] - '0');
    }
    if (sign == -1) {
        res *= -1;
    }
    return res;
}

std :: string to_string (int t) {  // Rewrited std :: string (of int) 'cause we doesn't use C++11
    if (th) return "0";
    std :: string res;
    int sign = signd (t);
    t *= signd (t);
    if (t == 0) return "0";
    while (t > 0) {
        res.push_back('0' + (t % 10));
        t /= 10;
    }
    for (size_t i = 0; i < res.size() / 2; i++) {
        char c = res[i];
        res[i] = res[res.size() - 1 - i];
        res[res.size() - 1 - i] = c;
    }
    if (sign == -1) {
        res.insert (0, "-");
    }
    return res;
}

int make (int a, int b, char c) {  // Function for execute simple operations
    if (th) return 0;
    if (c == '+' || c == '-') {
        if (c == '-') {
            b *= -1;
        }
        if (signd(a) != signd(b))
            return a + b;
        int sign = signd(a);
        a *= sign;
        b *= sign; // Make positive numbers
        int u = MAXINT - a;
        if (b > u) {
            std :: cout << "Huge numbers"; // If user haven't calculator
            th = true;
            return 0;
        }
        return (a + b) * sign;
    }
    if (c == '*') {
        long long h = a * b;
        if (h >= MAXINT || -h <= -MAXINT) {
            std :: cout << "Huge numbers"; // If user is a Euler
            th = true;
            return 0;
        }
        return a * b;
    }
    if (c == '/') {
        if (b != 0)
            return a / b;
        else {
            std :: cout << "Division by 0"; // If user is a monkey
            th = true;
            return 0;
        }
    }
    if (c == '%') {
        if (b != 0)
            return a % b;
        else {
            std :: cout << "Division by 0"; // If user is prescooler
            th = true;
            return 0;
        }
    }
}

std :: string simple (std :: string t) {  // Function for convert string of simple operations to int and char
    if (th) return "0";
    bool k = true; // For correct reading of 0
    std :: string a, b;
    char c;
    for (size_t i = 0; i < t.size(); i++) {
        if (t[i] != '+' && (t[i] != '-' || !k || i == 0) && t[i] != '/' && t[i] != '%' && t[i] != '*') {
            if (k) a.push_back(t[i]);
            else   b.push_back(t[i]);
        }
        else {
            if (k)
                c = t[i];
            k = false;
        }
    }
    return to_string (make (to_int (a), to_int (b), c));
}

std :: string comp (std :: string t) { // Making priority for non-brackets expression, and calculate it
    if (t[0] != '-' && (t[0] < '0' || t[0] > '9')) {
        std :: cout << "Expression can't start with '+', '/', '*', '%' or haven't numbers"; // If user hates me
        th = true;
        return "0";
    }
    if (t[t.size() - 1] < '0' || t[t.size() - 1] > '9') {
        std :: cout << "Expression can't end with '+', '-', '/', '*' or '%'"; // If user wants more
        th = true;
        return "0";
    }
    for (size_t i = 0; i < t.size() - 1; i++) {
        if (t[i] == '+' || t[i] == '-' || t[i] == '*' || t[i] == '/' || t[i] == '%') {
            if (t[i + 1] == '+' || t[i + 1] == '*' || t[i + 1] == '/' || t[i + 1] == '%') {
                std :: cout << "Not valid operations: " << t[i] << t[i + 1]; // If user knows c++
                th = true;
                return "0";
            }
        }
    }
    std :: vector <std :: string> nums;
    std :: vector <char> opers;
    std :: string u; // Buffer
    int y = 0;
    bool d = true; // For correct reading of 0
    if (t[0] == '-') {
        u.push_back('-');
        y = 1;
    }
    for (size_t i = y; i < t.size(); i++) {
        if ((t[i] >= '0' && t[i] <= '9') || (t[i] == '-' && !d)) {
            u.push_back(t[i]);
            d = true;
        }
        else {
            nums.push_back (u);
            u = "";
            opers.push_back (t[i]);
            d = false;
        }
    }
    if (u != "") {
        nums.push_back (u);
    }
    opers.push_back('+'); // Nothing to see here
    nums.push_back ("0"); // And here
    while (nums.size() > 1) {
        for (size_t i = 0; i < opers.size(); i++) {
            if (opers[i] == '*' || opers[i] == '/' || opers[i] == '%') {
                std :: string w = nums[i] + opers[i] + nums[i + 1];
                nums[i + 1] = simple (w);
                for (size_t j = i; j < opers.size() - 1; j++) {
                    nums[j] = nums[j + 1];
                    opers[j] = opers[j + 1];
                }
                opers.pop_back();
                nums.pop_back();
                i--;
            }
        }

        while (opers.size() > 0) {
            int i = 0;
            std :: string w = nums[i] + opers[i] + nums[i + 1];
            nums[i + 1] = simple (w);
            for (size_t j = i; j < opers.size() - 1; j++) {
                nums[j] = nums[j + 1];
                opers[j] = opers[j + 1];
            }
            opers.pop_back();
            nums.pop_back();
        }
    }
    return nums[0]; // It's only one stayed alive
}

std :: string div (std :: string t) { // Divide to non-brackets expressions, than execute
    while (t.find ("(") < t.size() && t.find ("(") >= 0) { // While brackets is alive
        int l = 0;
        std :: string u;
        for (size_t i = 0; i < t.size(); i++) {
            if (t[i] == '(') {
                l = i;
                u = "";
                continue;
            }
            if (t[i] == ')') {
                t.replace (l, i - l + 1, comp (u)); // Execute expression and kill brackets
                //std :: cout << t << std :: endl;   // If you want to see step-by-step
                break;
            }
            u.push_back (t[i]);
        }
    }
    t = comp (t);
    return t;
}

int main () {
    int op = 0;
    std :: string s, ex = "+-*/:%0123456789()";  // ex - correct symbols
    while (true) {
        char c;
        std :: cin.get(c); // cin can't read '\n', but cin.get() can
        std :: cout << std :: flush; // for cin.get() working
        if (c == '\n')
            break;
        if (ex.find (c) >= 0 && ex.find (c) < ex.size()) // If symbol is correct
            s.push_back(c);
        else {
            if (c == ' ') {}
            else {
                std :: cout << "Wrong symbol : " << c; // If meteorite crashed to user's keyboard
                return 0;
            }
        }
        if (c == '(') {
            op++;
        }
        if (c == ')') {
            op--;
        }
        if (op < 0) {
            std :: cout << "Wrong brackets"; // If user likes right brackets
            return 0;
        }
    }
    if (op != 0) {
        std :: cout << "Wrong brackets"; // If user hates right brackets
        return 0;
    }
    std :: string res = div (s); // Execute s
    if (th) return 0;
    std :: cout << res;
}
