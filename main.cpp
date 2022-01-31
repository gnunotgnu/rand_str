//main.cpp
//
//

#include <memory>
#include <iostream>
//#include <tuple>

#include <random>
#include <ctime>
#include <vector>
#include <sys/unistd.h>
#include <forward_list>
#include <cstdlib>
#include <set>

/*
#include <fstream>

void rename_file(char* fn) {
    std::system("ls -l >test.txt"); // execute the UNIX command "ls -l >test.txt"
    std::cout << std::ifstream("test.txt").rdbuf();
}
*/

template<typename T>
class Node {
    T* p;
    Node *l;
    Node *r;
public:
    Node() {
        p = nullptr;
        l = nullptr;
        r = nullptr;
    }
    ~Node() {
        delete p;
    }
    void push(const T &s) {
        if (p) {
            p = new T(s);
        }
    }
    void set_left(Node* ptr) {
        l = ptr;
    }

    void set_right(Node* ptr) {
        r = ptr;
    }

};

void test() {
    auto *ar = new Node<std::string>* [1000];
    std::cout << "test\n";
    for (int i =0; i < 100; i++) {
        auto *n = new Node<std::string>();
        n->push("fff");
        ar[i] = n;

    }



}

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
    return letters;
}

std::string create_random_string(const size_t &len, std::vector<char> &letters) {
    static std::set<std::string> history;
    size_t v = getpid();
    std::mt19937 gen(v);

    int restart_limit_counter = 100000; //4294967295U;  //maximum number of attempts

    std::string random_string;
    restart:
    random_string.clear();

    for (size_t i = 0; i < len; i++) {
        size_t j = gen();
        j %= letters.size();
        random_string.push_back(letters[j]);
    }

//check in history
    if (history.find(random_string) != history.end()) {
            if (restart_limit_counter-- <= 0)
                throw std::runtime_error("Few letters - many words - collision!");
            goto restart;
    }
    history.insert(random_string);
    return random_string;
}


std::string create_random_string(const size_t &len) {
    return create_random_string(len, set_compile());
}

void check_argv(const std::string& arg_from_cmd) {
    for (const auto &ch: arg_from_cmd) {
        if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')) {
            throw std::runtime_error("expected number");
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
        std::cout << create_random_string(int(time(nullptr))%8 + 3) <<  std::endl;
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

    if (argc == 3 && std::stoi(std::string(argv[1])) > 0 && std::stoull(std::string(argv[2])) > 0) {
        int len = std::stoi(std::string(argv[1]));
        unsigned long long count = std::stoull(std::string(argv[2]));
        for (unsigned long long i = 0; i < count; i++)
            std::cout << create_random_string(len) << std::endl;
        return 0;
    }

}
