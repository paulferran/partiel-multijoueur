#include "pch.h"
#include "main.h"
#include "Ball.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    sf::Vector2f ballPos(50, 50);
    Ball ball(20, 800, 600, 0.5, ballPos, { 1,1 });

    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        std::cerr << "Erreur d'initialisation Winsock" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur socket serveur: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr, clientAddr;
    int clientLen = sizeof(clientAddr);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(27015);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur bind: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    char recvBuf[512];
    std::cout << "Serveur prêt sur le port 27015." << std::endl;

    while (true) {
        int result = recvfrom(serverSocket, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&clientAddr, &clientLen);
        if (result > 0) {
            // Mise à jour de la balle
            ball.Update();
            float x = ball.GetPos().x;
            float y = ball.GetPos().y;

            char posBuf[8];
            memcpy(posBuf, &x, 4);
            memcpy(posBuf + 4, &y, 4);

            sendto(serverSocket, posBuf, 8, 0, (sockaddr*)&clientAddr, clientLen);
        }

        Sleep(33); // rythme ~30 FPS
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}