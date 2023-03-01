// This project was made in like 10 minutes with my shitty C++ project generator

#include <basic.hpp>

#define VERSION "1.1.0"

struct Server {
	std::string name;
	std::string ip;
};

int main() {
	// Lexer? Parser? AST Tree? Whats that?
	std::string buffer = "";
	std::string byond = "";
	std::vector<Server> servers;

	std::ifstream file("config.txt");
	if(!file.is_open()) {
		std::cout << "Failed to open config file\n";
	}

	while(file) {
		file >> buffer;

		if(buffer == "#") {
			getline(file, buffer);
			file >> std::ws;
			buffer = "";
		}

		if(buffer == "byond") {
			getline(file, buffer);
			file >> std::ws;
			byond = buffer;
		}

		if(buffer == "server") {
			Server fuck;

			file >> std::ws;

			getline(file, buffer, '|');
			file >> std::ws;
			if(buffer[buffer.length()] == ' ') {buffer.pop_back();}
			fuck.name = buffer;
			file >> std::ws;

			getline(file, buffer);
			fuck.ip = buffer;
			file >> std::ws;

			servers.push_back(fuck);
		}
	}
	file.close();

	// Oh lord.
	std::cout << "\t\t\t\t\tLAUNCHER 13\n\nVersion " << VERSION << "\n\n\nSelect a server to play:\n";
	for(unsigned long i = 0; i < servers.size(); i++) {
		std::cout << i + 1 << ". " << servers[i].name << "\n";
	}
selection:
	unsigned long selection;
	std::cout << "> ";
	std::cin >> selection;

	if(selection - 1 > servers.size()) {
		goto selection;
	}
	selection--;
	std::string cmd = byond + "\\" "dreamseeker.exe " + servers[selection].ip;
	std::cout << "Loading " << servers[selection].name << "...\nNote: Program might take a moment to respond when you close the game\n";
	system(cmd.c_str());
	goto selection;
	return 0;
}