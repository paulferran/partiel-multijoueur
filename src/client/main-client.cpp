#include "pch.h"
#include "main.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    // Initialisation de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client SFML window");
    sf::CircleShape ball(30);
    ball.setFillColor(sf::Color::Magenta);
    ball.setPosition(0, 0); // position initiale arbitraire

    // Initialisation de Winsock
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        std::cerr << "Erreur d'initialisation Winsock" << std::endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(27015);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);

    char recvBuf[8];
    char ping[] = "ping";
    sockaddr_in fromAddr;
    int fromLen = sizeof(fromAddr);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Envoie un "ping" au serveur
        sendto(sock, ping, sizeof(ping), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));

        // Réception de la position x, y
        int result = recvfrom(sock, recvBuf, 8, 0, (sockaddr*)&fromAddr, &fromLen);
        std::cout << "ca tourne" << std::endl;
        if (result == 8) {
            float x, y;
            memcpy(&x, recvBuf, 4);
            memcpy(&y, recvBuf + 4, 4);
            ball.setPosition(x, y);
        }

        window.clear();
        window.draw(ball);
        window.display();

        Sleep(33); // environ 30 FPS
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}