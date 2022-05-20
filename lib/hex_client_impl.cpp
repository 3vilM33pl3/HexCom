#include <hexagon.pb.h>
#include "hex_client_impl.h"

std::string root_certs =
        "# Issuer: CN=GlobalSign O=GlobalSign OU=GlobalSign Root CA - R2\n"
        "# Subject: CN=GlobalSign O=GlobalSign OU=GlobalSign Root CA - R2\n"
        "# Label: \"GlobalSign Root CA - R2\"\n"
        "# Serial: 4835703278459682885658125\n"
        "# MD5 Fingerprint: 94:14:77:7e:3e:5e:fd:8f:30:bd:41:b0:cf:e7:d0:30\n"
        "# SHA1 Fingerprint: 75:e0:ab:b6:13:85:12:27:1c:04:f8:5f:dd:de:38:e4:b7:24:2e:fe\n"
        "# SHA256 Fingerprint: ca:42:dd:41:74:5f:d0:b8:1e:b9:02:36:2c:f9:d8:bf:71:9d:a1:bd:1b:1e:fc:94:6f:5b:4c:99:f4:2c:1b:9e\n"
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n"
        "A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n"
        "Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n"
        "MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n"
        "A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n"
        "hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n"
        "v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n"
        "eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n"
        "tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n"
        "C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n"
        "zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n"
        "mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n"
        "V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n"
        "bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n"
        "3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n"
        "J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n"
        "291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n"
        "ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n"
        "AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n"
        "TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n"
        "-----END CERTIFICATE-----\n";


HexagonClientImpl::HexagonClientImpl() {
    auto options = grpc::SslCredentialsOptions();
    options.pem_root_certs = root_certs;

    auto channel_creds = grpc::SslCredentials(options);
    channel = grpc::CreateChannel("127.0.0.1:8080", channel_creds);
}

HexagonClientImpl::HexagonClientImpl(std::string server_address, bool ConnectEncrypted) {
    auto options = grpc::SslCredentialsOptions();
    options.pem_root_certs = root_certs;

    if (ConnectEncrypted) {
        channel = grpc::CreateChannel(server_address, grpc::SslCredentials(options));
    } else {
        channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    }
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

HexLocation HexagonClientImpl::Convert2Proto(const Hexagon* x) {
    HexLocation pbhex;
    pbhex.set_x(x->X);
    pbhex.set_y(x->Y);
    pbhex.set_z(x->Z);
    pbhex.set_hexid("1000-0000-0000-0000");
    return pbhex;
}

std::vector<Hexagon> HexagonClientImpl::MapGet(const Hexagon *hex, const int64_t radius, bool fill) {
    std::vector<Hexagon> result;
    HexagonGetRequest request;

    auto pHex = request.mutable_hexloc();
    pHex->CopyFrom(Convert2Proto(hex));
    request.set_radius(radius);
    request.set_fill(fill);

    grpc::ClientContext context;
    hexcloud::HexLocationList hexLocationList;

    auto status = stub->MapGet(&context, request, &hexLocationList);
    if (status.ok()) {

        for(auto hexpb: hexLocationList.hexloc()) {
            std::map<std::string, std::string> globaldata = std::map<std::string, std::string> {};
            for (auto & [key, value] : hexpb.globaldata())
            {
                globaldata.insert_or_assign(key, value);
            }

            std::map<std::string, std::string> localdata = std::map<std::string, std::string> {};
            for (auto & [key, value] : hexpb.localdata())
            {
                localdata.insert_or_assign(key, value);
            }

            result.push_back(Hexagon(hexpb.x(), hexpb.y(), hexpb.z(), hexpb.hexid(), globaldata, localdata));
        }
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

    return result;
}

