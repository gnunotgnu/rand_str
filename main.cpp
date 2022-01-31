//main.cpp
//
//

#include <memory>
#include <iostream>
#include <tuple>

#include <random>
//#include <ctime>
#include <vector>
#include <sys/unistd.h>

//void writeln(const std::string text_line);

void add_to_letters(std::vector<char> &v, const std::string &chars_set) {
    for (const auto &ch: chars_set) {
        v.push_back(ch);
    }

}

std::vector<char> &set_compile() {
    static std::vector<char> letters;
    if (!letters.empty()) return letters;

    add_to_letters(letters, "qwertyuiopasdfghjklzxcvbnm");
    add_to_letters(letters, "QWERTYUIOPASDFGHJKLZXCVBNM");
    add_to_letters(letters, "1234567890");
//add_to_letters(letters, "-_+=");
//add_to_letters(letters, ".,;:");
    return letters; //std::move(letters);
}


std::string create_random_string(const size_t &len, std::vector<char> &letters) {
    static std::vector<std::string> history{};

    size_t v = getpid();
    std::mt19937 gen(v);
    //gen.seed(time(0));

    size_t restart_limit_counter = 100000;

    restart:
    std::string random_string;
    for (size_t i = 0; i < len; i++) {
        size_t j = gen();
        if (j < 0) j = -j;
        j %= letters.size();
        char ch = letters.at(j);
        random_string.push_back(ch);
    }

//check in history
    for (auto &old: history) {
        if (old == random_string) {
//std::cout << "restart: " << old << " " << random_string << //'\n';
            if (restart_limit_counter-- <= 0)
                throw std::runtime_error("Мало букв - много слов - коллизия!");
            goto restart;
        }

    }
    history.push_back(random_string);
    return random_string;
}


std::string create_random_string(const size_t &len) {
    return create_random_string(len, set_compile());
}

void writeln(const std::tuple<int, std::string>& t) {
    auto&[n, msg] = t;
    std::cout << "(" << msg << " " << n << ")" << std::endl;
    if (n == 0)
        throw std::runtime_error("Ooops!");
}

void writeln(const std::string& text_line) {
    std::cout << text_line << std::endl;
}

void test() {

    std::shared_ptr<int> p1(new int);
    std::shared_ptr<int> p2;
    p2 = p1;
    if (p2) writeln("test()");
    std::tuple<int, std::string> t{__LINE__, __FILE__};
    writeln(t);
//writeln(std::tuple<int, std::string>(0, "x"));

}

void check_argv(const std::string& arg_from_cmd) {
    for (const auto &ch: arg_from_cmd) {
        if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')) {
            throw std::runtime_error("ожидались число(а)");
        }
    }

}

int main(int argc, char **argv) {

    if (argc == 2) {
        std::string arg_from_cmd = std::string(argv[1]);
        for (const auto &ch: arg_from_cmd) {
            if (!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')))
                goto normal_run;
        }
    }

    if (argc == 2 && std::string(argv[1]) == "test") {
        test();
        return 0;
    }


    if (argc == 2 && std::string(argv[1]).size() > 2) {
        std::vector<char> v{};
        add_to_letters(v, std::string(argv[1]));
        std::cout << create_random_string(8, v) << std::endl;
        return 0;
    }


    normal_run:
    if (argc == 1) {
        std::cout << create_random_string(8) << std::endl;
        return 0;
    }

    if (argc == 2) {
        check_argv(std::string(argv[1]));
    }
    if (argc == 3) {
        check_argv(std::string(argv[2]));
    }

    if (argc == 2 && std::stoi(std::string(argv[1])) > 0) {
        int len = std::stoi(std::string(argv[1]));
        std::cout << create_random_string(len) << std::endl;
        return 0;
    }
    if (argc == 3 && std::stoi(std::string(argv[1])) > 0 && std::stoi(std::string(argv[2])) > 0) {
        int len = std::stoi(std::string(argv[1]));
        int count = std::stoi(std::string(argv[2]));
        for (int i = 0; i < count; i++)
            std::cout << create_random_string(len) << std::endl;
        return 0;
    }


}
