#include <hexworld/hex_client.h>
#include <hexworld/hex_client_impl.h>

HexagonClient::HexagonClient() {
    impl = new HexagonClientImpl();
}

HexagonClient::HexagonClient(const std::string server_address) {
    impl = new HexagonClientImpl(server_address);
}

HexWorldConnectionState HexagonClient::ConnectToServer() {
    return impl->ConnectToServer();
}

HexWorldConnectionState HexagonClient::GetConnectionState() {
    return impl->GetConnectionState();
}

std::vector<Hexagon>* HexagonClient::GetHexagonRing(const Hexagon* hex, const int64_t radius) {
    return impl->GetHexagonRing(hex, radius);
}


