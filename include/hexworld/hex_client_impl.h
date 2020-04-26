#pragma once

#include <string>
#include <vector>
#include <hexworld/hex_client_impl.h>
#include "hex_com_state.h"
#include "hex_lib.h"

class HexagonClientImpl {
public:
    HexagonClientImpl();

    HexagonClientImpl(std::string server_address);

    HexWorldConnectionState ConnectToServer();

    HexWorldConnectionState GetConnectionState();

    std::vector<Hexagon> * GetHexagonRing(const Hexagon *hex, const int64_t radius);
};