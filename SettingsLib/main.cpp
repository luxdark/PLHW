#include <iostream>

#include "settings.h"

using namespace std;

int main () {
    settings a("C:\\workspace\\sett.stg");
    a.reset();
    a.set("bunniesThisSummer", "4");
    cout << a.get("bunniesThisSummer");
}









