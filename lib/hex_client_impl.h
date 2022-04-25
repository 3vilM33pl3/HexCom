#pragma once

#include <string>
#include <vector>
#include <grpc++/grpc++.h>
#include <hexworld/hex_com_state.h>
#include <hexworld/hex_client.h>
#include "hex_client_impl.h"
#include "hexagon.grpc.pb.h"

using endpoints::hexworld::hexcloud::HexagonService;
using endpoints::hexworld::hexcloud::HexLocation;
using endpoints::hexworld::hexcloud::HexInfo;
using endpoints::hexworld::hexcloud::HexInfoList;
using endpoints::hexworld::hexcloud::HexLocationList;
using endpoints::hexworld::hexcloud::HexagonGetRequest;
using endpoints::hexworld::hexcloud::HexIDList;
using endpoints::hexworld::hexcloud::Status;
using endpoints::hexworld::hexcloud::Result;

class HexagonClientImpl {
public:
    HexagonClientImpl();

    HexagonClientImpl(std::string server_address, bool ConnectEncrypted);

    hw_conn_state ConnectToServer();

    hw_conn_state GetConnectionState();

    std::vector<Hexagon> MapGet(const Hexagon *hex, const int64_t radius, bool fill);

private:
    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<HexagonService::Stub> stub;

    HexLocation Convert2Proto(const Hexagon *x);
};