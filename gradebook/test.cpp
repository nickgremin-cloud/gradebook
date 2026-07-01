#define TABULATE_DISABLE_COLORS
#include "tabulate/table.hpp"
#include <iostream>
#include <locale>

using namespace tabulate;
using namespace std;

// Фикс локали ДО запуска main
static const bool fix_locale = []() {
    try { locale::global(locale("C")); } catch (...) {}
    return true;
}();

int main() {
    cout.imbue(locale("C"));

    Table table;
    table.add_row({"ID", "Name", "Surname", "Avg"});
    table.add_row({"101", "Ivan", "Petrov", "85.0"});
    
    cout << table << endl;
    return 0;
}