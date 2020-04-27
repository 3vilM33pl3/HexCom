#pragma once

#include <string>
#include <vector>
#include <hexworld/hex_com_state.h>
#include <hexworld/hex_lib.h>

class HexagonClientImpl;
class HexagonClient {
public:
    HexagonClient();
    HexagonClient(std::string server_address);

    hw_conn_state ConnectToServer();

    hw_conn_state GetConnectionState();

    std::vector<Hexagon>* GetHexagonRing(const Hexagon* hex, const int64_t radius);
private:
    HexagonClientImpl* impl;
};