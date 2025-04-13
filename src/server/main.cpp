#include "pch.h"
#include "main.h"
#include "Ball.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    sf::Vector2f ballPos(50, 50);
    Ball* ball = new Ball(20, 800, 600, 0.3, ballPos, { 1,1 });

    // -------------------

    int iResult;

    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    SOCKET ClientSocket;
    struct sockaddr_in RecvAddr;
    int RecvAddrSize = sizeof(RecvAddr);
    inet_pton(AF_INET, "127.0.0.1", &RecvAddr.sin_addr.s_addr);
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(27015);

    unsigned short Port = 27015;

    char buf[8];
    float x = ball->GetPos().x;
    float y = ball->GetPos().y;

    memcpy(buf, &x, 4);
    memcpy(buf + 4, &y, 4);

    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    iResult = sendto(ClientSocket, buf, 8, 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // -------------------

    while (true) {
        ball->Update();
    }

    return 0;
}