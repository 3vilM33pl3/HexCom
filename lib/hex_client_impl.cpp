#include "hex_client_impl.h"
#include "hexagon.pb.h"


HexagonClientImpl::HexagonClientImpl() {
    auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
    channel = grpc::CreateChannel("localhost:500541", channel_creds);
}

HexagonClientImpl::HexagonClientImpl(std::string server_address) {
    grpc::SslCredentialsOptions sslOpts{};
    channel = grpc::CreateChannel(server_address, grpc::SslCredentials(sslOpts));
//    channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
}



hw_conn_state HexagonClientImpl::ConnectToServer() {
    auto ChannelStatus = channel->GetState(true);

    while(true) {
        if(channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN)))) {
            ChannelStatus = channel->GetState(false);
            if(ChannelStatus == GRPC_CHANNEL_READY || ChannelStatus == GRPC_CHANNEL_IDLE) {
                stub = HexagonService::NewStub(channel);
                return hw_conn_state::HEXWORLD_CONNECTION_READY;
            } else {
                return hw_conn_state::HEXWORLD_CONNECTION_FATAL;
            }
        }
        ChannelStatus = channel->GetState(false);
        if(ChannelStatus == GRPC_CHANNEL_CONNECTING) {
            continue;
        } else {
            return hw_conn_state::HEXWORLD_CONNECTION_TIMEOUT;
        }
    }

}

hw_conn_state HexagonClientImpl::GetConnectionState() {
    switch (channel->GetState(false)) {
        case GRPC_CHANNEL_IDLE:
            return hw_conn_state::HEXWORLD_CONNECTION_IDLE;
            break;
        case GRPC_CHANNEL_READY:
            return hw_conn_state::HEXWORLD_CONNECTION_READY;
            break;
        case GRPC_CHANNEL_CONNECTING:
            return hw_conn_state::HEXWORLD_CONNECTING;
            break;
        case GRPC_CHANNEL_TRANSIENT_FAILURE:
            return hw_conn_state::HEXWORLD_CONNECTION_RETRY;
            break;
        case GRPC_CHANNEL_SHUTDOWN:
        default:
            return hw_conn_state::HEXWORLD_CONNECTION_FATAL;
            break;
    }
}

hexagon::Hex HexagonClientImpl::Convert2Proto(const Hexagon* x) {
    hexagon::Hex pbhex;
    pbhex.set_x(x->X);
    pbhex.set_y(x->Y);
    pbhex.set_z(x->Z);
    pbhex.set_direction("NW");
    pbhex.set_type("straight");
    return pbhex;
}


std::vector<Hexagon> HexagonClientImpl::GetHexagonRing(const Hexagon *hex, const int64_t radius) {
    std::vector<Hexagon> result;
    HexagonRingRequest request;

    auto ha = request.mutable_ha();
    ha->CopyFrom(Convert2Proto(hex));
    request.set_radius(radius);



    grpc::ClientContext context;
    HexCubeResponse response;

    auto status = stub->GetHexagonRing(&context, request, &response);
    if (status.ok()) {

        for(auto hexpb: response.hc()) {
            result.push_back(Hexagon(hexpb.x(), hexpb.y(), hexpb.z()));
        }
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

    return result;
}

