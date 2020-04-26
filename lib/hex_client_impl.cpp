#include <hexworld/hex_client_impl.h>

HexagonClientImpl::HexagonClientImpl() {

}

HexagonClientImpl::HexagonClientImpl(std::string server_address) {

}

HexWorldConnectionState HexagonClientImpl::ConnectToServer() {
    return HexWorldConnectionState::HEXWORLD_CONNECTION_IDLE;
}

HexWorldConnectionState HexagonClientImpl::GetConnectionState() {
    return HexWorldConnectionState::HEXWORLD_CONNECTION_IDLE;
}

std::vector<Hexagon> * HexagonClientImpl::GetHexagonRing(const Hexagon *hex, const int64_t radius) {
    return new std::vector<Hexagon>;
}

