// Minimal link stubs for fakefsify on hosts where kernel/log.c cannot be
// linked (its syscall paths drag in task/tty symbols). fakefsify only needs
// die() and ish_printk() from it.
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int log_override = 0;
void (*die_handler)(const char *msg) = NULL;

_Noreturn void die(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fputs("fakefsify die: ", stderr);
    vfprintf(stderr, msg, args);
    va_end(args);
    fputc('\n', stderr);
    abort();
}

void ish_printk(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
}
