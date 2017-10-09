#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"

#include <iostream>
#define DATA_SIZE 100

void runServer() {
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;

	tcpSocket.setBlocking(false);

	if (tcpListener.listen(53000) != sf::Socket::Done) {
		std::cout << "Couldn't bind listener to port...\n";
	}

	if (tcpListener.accept(tcpSocket) != sf::Socket::Done) {
		std::cout << "Couldn't accept the connection...\n";
	}

	sf::IpAddress clientIp = tcpSocket.getRemoteAddress();
	std::cout << "CONNECTED: "<< clientIp << std::endl;

	size_t bytesReceived;
	while (1) {
		char data[DATA_SIZE];
		if (tcpSocket.receive(data, DATA_SIZE, bytesReceived) != sf::Socket::Done) {
		}
		else {
			
			std::cout << "RECEIVED DATA!\n";
			std::cout << "BYTES RECEIVED: " << bytesReceived << std::endl;
			data[bytesReceived] = '\0';
			std::cout << "DATA RECEIVED: " << data << std::endl;
		}
	}
}
void runClient() {
	sf::TcpSocket tcpSocket;
	sf::Socket::Status status = tcpSocket.connect("192.168.0.107", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Not connected...\n";
		std::cout << "Press any key...\n";
		std::cin.ignore(1);
		exit(0);
	}
	else {
		std::cout << "Connected!\n";
		std::string username;
		std::cout << "Your username: ";
		std::cin >> username;
		
		char data[DATA_SIZE];
//		std::cout << "Message size: " << DATA_SIZE << std::endl;
		std::cin.ignore(1);

		while (1) {

			std::cout << username << ": ";
			std::cin.getline(data, 256,'\n');
			
			if (strlen(data) > DATA_SIZE - 1) { std::cout << "Too long! Must be only " << DATA_SIZE << " characters long!\n"; }
			else {
				if (tcpSocket.send(data, strlen(data)) != sf::Socket::Done) {

				}
				else {

				}
			}
		}
	}
}


int main()
{
	
	std::cout << "0 - server, 1 - client\n";
	bool serverOrClient;
	std::cin >> serverOrClient;

	if (serverOrClient) { //client
		runClient();
	}
	else //server
	{
		runServer();
	}
	std::cin.ignore(2);
	return 0;
}