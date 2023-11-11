#include <iostream>
#include <exception>
#include <ctime>
#include <cstdlib>

void print(const int pond[]) {
	for (int i = 0; i < 9; ++i) {
		std::cout << "sector " << i << ": ";
		switch (pond[i]) {
			case 0:
				std::cout << "----" << std::endl;
				break;
			case 1:
				std::cout << "FISH" << std::endl;
				break;
			case 2:
				std::cout << "BOOT" << std::endl;
				break;
		}
	}
}

class Get_Boot_Exception : public std::exception {
	const char * what() const noexcept override {
		return "You caught the boot! You've lost!";
	}
};

class Get_Nothing_Exception : public std::exception {
	const char * what() const noexcept override {
		return "You didn't catch anything! Try again!";
	}
};

class Get_Fish_Exception : public std::exception {
	const char * what() const noexcept override {
		return "You caught the FISH! You Win!";
	}
};

void casting_fishing_rod(int& sector, const int pond[]) {
	if (sector < 0 || sector > 8) {
		throw std::invalid_argument("sector");
	}
	if (pond[sector] == 0) {
		throw Get_Nothing_Exception();
	}
	if (pond[sector] == 1) {
		throw Get_Fish_Exception();
	}
	if (pond[sector] == 2) {
		throw Get_Boot_Exception();
	}
}

int main() {
	int pond[9] = {0};
	std::srand(std::time(nullptr));
	pond[std::rand() % 9] = 1;

	for (int boots = 3; boots > 0; ) {
		int i = std::rand() % 9;
		if (pond[i] != 1 && pond[i] != 2) {
			pond[i] = 2;
			boots--;
		}
	}
	//print(pond);

	int sector, count = 1;
	bool input = true;
	while (input){
		std::cout << "Select a sector:";
		std::cin >> sector;
		try {
			casting_fishing_rod(sector, pond);
		}
		catch (const std::invalid_argument& ex) {
			std::cout << "Invalid argument: " << ex.what() << std::endl;
		}
		catch (const Get_Nothing_Exception& ex) {
			std::cout << "You didn't catch anything!" << std::endl;
			count++;
		}
		catch (const Get_Fish_Exception& ex) {
			input = false;
			std::cout << "You caught FISH! You WIN!" << std::endl;
			std::cout << "Tries: " << count << std::endl;
		}
		catch (const Get_Boot_Exception& ex) {
			input = false;
			std::cout << "You caught BOOT! You've lost!" << std::endl;
		}
		catch (...) {
			std::cout << "any exception!!! Try again!!!" << std::endl;
		}
	}
}
