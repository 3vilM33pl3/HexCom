#include <hexworld/hex_client.h>
#include "hex_client_impl.h"

HexagonClient::HexagonClient() {
    impl = new HexagonClientImpl();
}

HexagonClient::HexagonClient(const std::string server_address, bool ConnectEncrypted) {
    impl = new HexagonClientImpl(server_address, ConnectEncrypted);
}

hw_conn_state HexagonClient::ConnectToServer() {
    return impl->ConnectToServer();
}

hw_conn_state HexagonClient::GetConnectionState() {
    return impl->GetConnectionState();
}

std::vector<Hexagon> HexagonClient::GetHexagonRing(Hexagon *hex, const int64_t radius, bool fill) {
    return impl->GetHexagonRing(hex, radius, fill);
}
