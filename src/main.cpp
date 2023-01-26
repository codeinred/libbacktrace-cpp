#include <backtrace.h>
#include <cstdlib>

void error_callback(void* data, const char* msg, int errnum) { std::exit(1); }
auto state = backtrace_create_state(nullptr, 1, error_callback, nullptr);

void a() {
    puts("backtrace from a()");
    backtrace_print(state, 0, stdout);
}
void b() {
    puts("backtrace from b()");
    backtrace_print(state, 0, stdout);
}
void c() {
    puts("backtrace from c()");
    backtrace_print(state, 0, stdout);
}
void foo() {

    a();

    b();

    c();
}

int main() { foo(); }
