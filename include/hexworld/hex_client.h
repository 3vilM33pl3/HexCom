#pragma once

#include <string>
#include <vector>
#include "hex_com_state.h"
#include "hex_lib.h"

class HexagonClientImpl;
class HexagonClient {
public:
    HexagonClient();
    HexagonClient(std::string server_address);

    HexWorldConnectionState ConnectToServer();

    HexWorldConnectionState GetConnectionState();

    std::vector<Hexagon>* GetHexagonRing(const Hexagon* hex, const int64_t radius);
private:
    HexagonClientImpl* impl;
};