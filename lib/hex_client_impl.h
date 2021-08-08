#pragma once

#include <string>
#include <vector>
#include <grpc++/grpc++.h>
#include <hexworld/hex_com_state.h>
#include <hexworld/hex_client.h>
#include "hex_client_impl.h"
#include "hexagon.grpc.pb.h"


using endpoints::hexworld::hexcloud::HexagonService;
using endpoints::hexworld::hexcloud::ConversionRequest;
using endpoints::hexworld::hexcloud::HexAxialResponse;
using endpoints::hexworld::hexcloud::HexagonRingRequest;
using endpoints::hexworld::hexcloud::HexCubeResponse;
using endpoints::hexworld::hexcloud::Hex;
using endpoints::hexworld::hexcloud::HexAxial;
using endpoints::hexworld::hexcloud::HexagonService;

class HexagonClientImpl {
public:
    HexagonClientImpl();

    HexagonClientImpl(std::string server_address, bool ConnectEncrypted);

    hw_conn_state ConnectToServer();

    hw_conn_state GetConnectionState();

    std::vector<Hexagon> GetHexagonRing(const Hexagon *hex, const int64_t radius, bool fill);

private:
    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<HexagonService::Stub> stub;

    Hex Convert2Proto(const Hexagon *x);
};