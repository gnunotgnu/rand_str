//main.cpp
//
//shared_ptr example

#include <memory>
#include <iostream>
#include <tuple>

#include <random>
#include <ctime>
#include <vector>

std::string create_random_string(const size_t &len) {
	static std::vector<std::string>history{"", "q"};
//restart:
	const std::string alphabet{"qwertyuiopasdfghjklzxcvbnm"};
	const std::string alphabet_set_2{"QWERTYUIOPASDFGHJKLZXCVBNM"};
	const std::string alphabet_set_3{"1234567890"};
	std::vector<char> letters;

	for (const auto& ch:alphabet) {
		letters.push_back(ch);
	}

	for (const auto& ch:alphabet_set_2) {
		letters.push_back(ch);
	}

	for (const auto& ch:alphabet_set_3) {
		letters.push_back(ch);
	}

	std::mt19937 gen;
	gen.seed(time(0));
	
    size_t restart_limit_counter = 100000;
restart:
	std::string random_string{""};
	for (size_t i=0; i < len; i++) {
		int j = gen();
		if (j < 0) j = -j;
		j %= letters.size();
		char ch = letters.at(j);
		random_string.push_back(ch);
	}

	//check in history
	for (auto &old:history) {
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

void writeln(std::tuple<int, std::string> t) {
	auto& [n, msg] = t;
	std::cout<< "(" << msg << " " << n << ")" << std::endl;
	if (n == 0)
		throw std::runtime_error("Ooops!");
}

void writeln(const std::string text_line) {
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

int main(int argc, char** argv) {
		if (argc == 2 && std::string(argv[1]) == "test") {
		test();
		return 0;
	}
	
	if (argc == 1) {
		std::cout << create_random_string(8) << std::endl;
		return 0;
	}

	if (argc == 2 && std::stoi(std::string(argv[1])) > 0) {
		int len = std::stoi(std::string(argv[1]));
		std::cout << create_random_string(len) << std::endl;
		return 0;
	}
	if (argc == 3 && std::stoi(std::string(argv[1])) > 0 && std::stoi(std::string(argv[2])) > 0) {
		int len = std::stoi(std::string(argv[1]));
		int count = std::stoi(std::string(argv[2]));
		for (int i =0; i < count; i++) 
			std::cout << create_random_string(len) << std::endl;
		return 0;
	}


}
