#ifdef DEBUG
    #ifndef PRINT_H
    #define PRINT_H

    #include <string>
    #include <cstddef>
    class Vec2;
    class Vec3;
    class IntPos;

    #define PRINTLN(a) Debug::println(a)
    #define PRINT(a) Debug::print(a)
    #define LINEINFORMATION(a) Debug::printLineInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__)

    class Debug {
    public:
        static void println();
        static void printLineInformation(const std::string &file, int line, const std::string &func);

        static void print(const std::string &text);
        static void println(const std::string &text);

        static void print(const char *text);
        static void println(const char *text);

        static void print(int num);
        static void println(int num);

        static void print(std::size_t num)   { print((int)num); };
        static void println(std::size_t num) { println((int)num); };

        static void print(float num);
        static void println(float num);

        static void print(Vec2 vec);
        static void println(Vec2 vec);

        static void print(Vec3 vec);
        static void println(Vec3 vec);

        static void print(IntPos pos);
        static void println(IntPos pos);

        static void print(bool b);
        static void println(bool b);
    
    private:
    };

    #endif
#else
    #ifndef PRINT_H
    #define PRINT_H

    #define PRINTLN(a)
    #define PRINT(a)
    #define LINEINFORMATION(a)

    #endif
#endif
