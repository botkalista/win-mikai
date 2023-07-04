#include <string>
#include <cstdio>
#include <cstring>

#include <ctime>
#include <chrono>

#include <mikai/mikai.h>
#include <mikai/mikai-reader.h>

void printHelp() {
	printf("\n\twinmikai.exe [ACTION] [ARGS]\n");
	printf("\n\tActions:\n\n");
	printf("\tcheck - Checks if the reader is connected\n");
	printf("\tadd [CREDIT] - Adds CREDIT to the key\n");
	printf("\tset [CREDIT] - Sets CREDIT to the key\n");
	printf("\tread - Reads the CREDIT of the key\n");
	printf("\thelp - Prints this help message\n");
}

void getDate(int &day, int &month, int &year) {
	std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* currentTm = std::localtime(&currentTime);
	day = currentTm->tm_mday;
    month = currentTm->tm_mon + 1;
    year = currentTm->tm_year + 1900;
}

int init(MyKey* key) {
	int readers = MyKeyGetReadersCount(key);
	if (readers == 0) {
		printf("No reader found");
		return 1;
	}
	const char* initError = MikaiInit(&key, NULL, 0);   
    if (initError != NULL) {
        printf("Error: %s", initError);
        return 1;
    }
	return 0;
}

int writeAll(MyKey* key) {
	int result = MyKeyWriteAll(key);
	if (result != 0) {
		const char* error = MikaiGetLatestError(key);
		printf("Error: %s", error);
		return result;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	MyKey* key = MikaiNew();
		
	char* action = argv[1];
	
	// No action
	if (action == NULL) { printHelp(); return 1; }
	
	// Help command
	if (std::strcmp(action, "help") == 0) { printHelp(); return 0; }
	
	// Check reader
	if (std::strcmp(action, "check") == 0) {
		int readers = MyKeyGetReadersCount(key);
		printf("Readers connected: %d", readers);
		return 0;
	} 
	
	// Read credit
	if (std::strcmp(action, "read") == 0) {
		if (init(key) == 1) return 1;
		int credit = MyKeyGetCurrentCredit(key);
		printf("Credit: %d cents", credit);
		return 0;
    }
	
		
	// Add credit
    if (std::strcmp(action, "add") == 0) {
		if (init(key) == 1) return 1;	

		int day;
		int month;
		int year;
		getDate(day,month,year);
		int credit = std::__cxx11::stoi(argv[2]);
	
		int result = MyKeyAddCents(key, credit, day, month, year);
		if (result != 0) {
			const char* error = MikaiGetLatestError(key);
			printf("Error: %s", error);
			return result;
		} else {
			if (writeAll(key) == 1) return 1;	
			printf("Credit add");
		}
    }
	
	// Set credit
	if (std::strcmp(action, "set") == 0) {
		if (init(key) == 1) return 1;
		
		int day;
		int month;
		int year;
		getDate(day,month,year);
		int credit = std::__cxx11::stoi(argv[2]);
	
		int result = MyKeySetCents(key, credit, day, month, year);
		if (result != 0) {
			const char* error = MikaiGetLatestError(key);
			printf("Error: %s", error);
			return result;
		} else {
			if (writeAll(key) == 1) return 1;	
			printf("Credit set");
		}
	}
	
	// Invalid action
	printf("\n\tAction not valid.\n");
	printHelp();
	return 1;
		
}


