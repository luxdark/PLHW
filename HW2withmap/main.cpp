#include <fstream>
#include <iostream>

#include <conio.h>
#include <math.h>
#include <stdlib.h>

std :: ofstream fout ("map.txt");
long long resetsize = 1, steps = 0; // resetsize - current size of VectorBool needed
long long died = 0, born = 0, started = 0; // died & born on current 10 steps
double pb = 0.0; // sum { tborn / tdied }

class VectorBool {
private:
    bool *v, *y; // v - positive index, y - negative
    long long rsize; // current size = 2^K
public:
    VectorBool (int u) {
        bool* t = NULL;
        while (t == NULL) {
            t = new bool [u * sizeof (bool)];
        }
        bool* w = NULL;
        while (w == NULL) {
            w = new bool [u * sizeof (bool)];
        }
        rsize = u;
        v = t;
        y = w;

        for (int i = 0; i < rsize; i++) {
            v [i] = 0;
            y [i] = 0;
        }
        return;
    }
    long long getsize() {
        return this -> rsize;
    }
    void resize () {
        if (resetsize < this -> rsize * 2)
            resetsize = this -> rsize * 2;
        bool *a = v, *b = y; // copies
        long long size = this -> rsize;
        v = new bool [size * 2 * sizeof (bool)];
        y = new bool [size * 2 * sizeof (bool)];
        for (int i = 0; i < size; i++) { // copy old data
            this -> v [i] = a [i];
            this -> y [i] = b [i];
        }
        this -> rsize *= 2;
        for (int i = size; i < this -> rsize; i++) { // set new data
            this -> v [i] = 0;
            this -> y [i] = 0;
        }
        return;
    }
    void set (long long t, bool p) { // setting (if element doesn't exist create element
        while (abs (t) > this -> rsize - 1) {
            this -> resize ();
        }
        if (t >= 0)
            this -> v [t] = p;
        if (t <= 0)
            this -> y [abs (t)] = p;
        return;
    }
    bool get (long long t) { // getting (if element doesn't exist return false)
        if (abs(t) > rsize - 1) {
            return false;
        }
        if (t >= 0)
            return v [t];
        return y [-t];
    }
};

class MapBool { // VectorVectorBool
private:
    VectorBool **v, **y;
    long long rsize;
public:
    MapBool (int u) {
        VectorBool **t = NULL;
        while (t == NULL) {
            t = new VectorBool* [u * sizeof (VectorBool*)];
        }
        VectorBool **w = NULL;
        while (w == NULL) {
            w = new VectorBool* [u * sizeof (VectorBool*)];
        }
        rsize = u;
        v = t;
        y = w;
        for (int i = 0; i < rsize; i++) {
            v [i] = new VectorBool (resetsize);
            y [i] = new VectorBool (resetsize);
        }
        return;
    }
    long long getsize() {
        return this -> rsize;
    }
    void resize () {
        VectorBool **a = v, **b = y;
        long long size = this -> rsize;
        v = new VectorBool* [size * 2 * sizeof (VectorBool*)];
        y = new VectorBool* [size * 2 * sizeof (VectorBool*)];
        for (int i = 0; i < size; i++) {
            this -> v [i] = a [i];
            this -> y [i] = b [i];
        }
        this -> rsize *= 2;
        for (int i = size; i < this -> rsize; i++) {
            this -> v [i] = new VectorBool (resetsize);
            this -> y [i] = new VectorBool (resetsize);
        }
        return;
    }
    void set (long long t, VectorBool* p) {
        while (abs (t) > this -> rsize - 1) {
            this -> resize ();
        }
        if (t >= 0)
            this -> v [t] = p;
        if (t <= 0)
            this -> y [abs (t)] = p;
        return;
    }
    VectorBool* get (long long t) {
        if (abs(t) > rsize - 1) {
            return new VectorBool (resetsize);
        }
        if (t >= 0)
            return v [t];
        return y [-t];
    }
};

////Map////
MapBool *b;
////Map////

void normal () { // making 2^K * 2^S map
    for (int i = - b -> getsize() + 1; i < b -> getsize(); i++) {
        while (b -> get (i) -> getsize() < resetsize) {
            b -> get (i) -> resize();
        }
    }
}

int main () {
    b = new MapBool (1);
    VectorBool* p = new VectorBool (1);

    int n, m;
    std :: cout << "Set start X and Y: ";
    std :: cin >> n >> m;
    std :: cout << "Enter map: " << std :: endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            bool k;
            std :: cin >> k;
            if (k)
                started ++;
            p -> set (j - n / 2, k); // Move center to 0
        }
        b -> set (i - m / 2, p); // Move center to 0
        p = new VectorBool (1);
    }
    std :: cout << "Set number of days: ";
    std :: cin >> steps;

    long long life = 0; // On current step
    for (int M = 0; M < steps; M++) {
        life = 0;
        long long q = b -> getsize();
        long long w = b -> get (0) -> getsize();
        MapBool *Ne = new MapBool (1); // Copy
        while (Ne -> getsize() < resetsize) {
            Ne -> resize();
        }
        for (int i = -q; i < q + 1; i++) { // Copy old data
            VectorBool *p = new VectorBool (1);
            for (int j = -w + 1; j < w; j++) {
                p -> set (j, b -> get (i) -> get (j));
            }
            Ne -> set (i, p);
        }
        long long tdied = 0, tborn = 0; // On current step
        for (int i = -q; i < q + 1; i++) {
            for (int j = -w; j < w + 1; j++) {
                int count = 0; // Count of living neightbours
                for (int I = -1; I < 2; I++) {
                    for (int J = -1; J < 2; J++) {
                        if (I != 0 || J != 0) {
                            if (Ne -> get (I + i) -> get (J + j)) {
                                count ++;
                            }
                        }
                        else {
                            if (Ne -> get (i) -> get (j)) {
                                life ++;
                            }
                        }
                    }
                }
                if (count == 3) { // Alive
                    VectorBool *p = b -> get (i);
                    p -> set (j, 1);
                    b -> set (i, p);
                    if (!Ne -> get (i) -> get (j)) {
                        tborn ++;
                        life ++;
                    }
                }
                if (count != 3 && count != 2 && abs (i) < resetsize && abs (j) < resetsize) {
                    VectorBool *p = b -> get (i);
                    p -> set (j, 0);
                    b -> set (i, p);
                    if (Ne -> get (i) -> get (j)) {
                        tdied ++;
                        life --;
                    }
                } // Kill
            }
        }
        if (tborn == tdied) {
            std :: cout << "In day " << M + 1 << " population was constant. " << std :: endl;
        }

        normal();
        born += tborn;
        died += tdied;
        //pb += (double) tborn / tdied;
        if (M % 10 == 9) {
            //pb /= 10.0;
            std :: cout << "Day " << M + 1 << ": " << std :: endl
                << born << " creatures was born. " << std :: endl
                << died << " creatures was died. " << std :: endl
                << life << " creatures living here." << std :: endl;
            //std :: cout << "born / died = " << pb << std :: endl;
            born = 0;
            died = 0;
        }
    }

    // Map to console and \map.txt
    for (int i = - b -> getsize() + 1; i < b -> getsize(); i++) {
        for (int j = - b -> get (i) -> getsize() + 1; j < b -> get (i) -> getsize(); j++) {
            char c = ' ';
            if (i == 0 || j == 0)
                c = '|';
            // std :: cout << c << b -> get (i) -> get (j) << c; // Uncomment to write to console
            fout << c << b -> get (i) -> get (j) << c;
        }
        // std :: cout << std :: endl; // Uncomment to write map to console
        fout << std :: endl;
    }

    std :: cout << "We have " << abs (life - started) << " " << ((life - started > 0) ? ("more") : ("less")) << " creatures!";

    while (kbhit()) getch();
    std :: cout << std :: endl << "Type [V] if you want to see map" << std :: endl;
    char c = getch();
    if (c == 'V' || c == 'v' || c == 'ì' || c == 'Ì') {
        int vx = 0; // View X
        int vy = 0; // View Y
        system ("cls");
        for (char f = 'B'; f != '0'; f = getch ()) {
            if (f == 'w' || f == 'W' || f == 'ö' || f == 'Ö') vx++; // Inverted
            if (f == 'a' || f == 'A' || f == 'ô' || f == 'Ô') vy++;
            if (f == 's' || f == 'S' || f == 'û' || f == 'Û') vx--;
            if (f == 'd' || f == 'D' || f == 'â' || f == 'Â') vy--;
            system ("cls");
            for (int i = vx - 3; i < vx + 3; i++) {
                for (int j = vy - 3; j < vy + 3; j++) {
                    std :: cout << '[' << (b -> get (i) -> get (j)) ? ('X') : (' ') << ']';
                }
                std :: cout << std :: endl;
            }
            std :: cout << "WASD to move map, 0 to exit";
        }
    }
    return 0;
}

