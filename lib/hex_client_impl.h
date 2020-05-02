#pragma once

#include <string>
#include <vector>
#include <grpc++/grpc++.h>
#include <hexworld/hex_com_state.h>
#include <hexworld/hex_client.h>
#include "hex_client_impl.h"
#include "hexagon.grpc.pb.h"

using hexagon::HexagonService;
using hexagon::ConversionRequest;
using hexagon::HexAxialResponse;
using hexagon::HexagonRingRequest;
using hexagon::HexCubeResponse;
using hexagon::Hex;
using hexagon::HexAxial;
using hexagon::HexagonService;

class HexagonClientImpl {
public:
    HexagonClientImpl();

    HexagonClientImpl(std::string server_address);

    hw_conn_state ConnectToServer();

    hw_conn_state GetConnectionState();

    std::vector<Hexagon> GetHexagonRing(const Hexagon* hex, const int64_t radius);

private:
    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<HexagonService::Stub> stub;

    Hex Convert2Proto(const Hexagon *x);
};