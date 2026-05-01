#ifndef SK_H
#define SK_H

#include <common.h>
#include <scanner.h>
#include <parser.h>
#include <string>

class SK {
public:
    static void run(const std::string source);
    static void error(const std::string message, const int line);
};

#endif
