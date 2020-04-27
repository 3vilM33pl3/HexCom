#include "hex_client_impl.h"

HexagonClientImpl::HexagonClientImpl() {
    auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
    channel = grpc::CreateChannel("localhost:500541", channel_creds);
}

HexagonClientImpl::HexagonClientImpl(std::string server_address) {
    auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
    channel = grpc::CreateChannel(server_address, channel_creds);
}

hw_conn_state HexagonClientImpl::ConnectToServer() {
    auto ChannelStatus = channel->GetState(true);

    if(channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN)))) {
        if(ChannelStatus == GRPC_CHANNEL_READY || ChannelStatus == GRPC_CHANNEL_IDLE) {
            stub = HexagonService::NewStub(channel);
            return hw_conn_state::HEXWORLD_CONNECTION_READY;
        } else {
            return hw_conn_state::HEXWORLD_CONNECTION_FATAL;
        }
    } else {
        return hw_conn_state::HEXWORLD_CONNECTION_TIMEOUT;
    }
}

hw_conn_state HexagonClientImpl::GetConnectionState() {
    return hw_conn_state::HEXWORLD_CONNECTION_IDLE;
}

std::vector<Hexagon> * HexagonClientImpl::GetHexagonRing(const Hexagon *hex, const int64_t radius) {



    return new std::vector<Hexagon>;
}

