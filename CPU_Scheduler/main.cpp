#include <iostream>
#include "CPU.h"


int main(int argc, char *argv[]){
	CPU* cpu = new CPU();
	std::vector<std::shared_ptr<Thread>> threads;

	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Thread> newThread(new Thread());
		threads.push_back(newThread);
	}

	cpu->setWorkingThread(threads.back());
	threads.pop_back();
	while(threads.size() > 0){
		while (cpu->run()) {

		}

		cpu->setWorkingThread(threads.back());
		threads.pop_back();
		std::cout << "new thread\n";
	}

	system("pause");
}