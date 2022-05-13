#include <iostream>
#include <hexworld/hex_client.h>
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

ABSL_FLAG(std::string, address, "127.0.0.1:8080", "address to connect to [ip:port]");
ABSL_FLAG(bool, ssl, true, "connect encrypted");

int main(int ac, char** av) {
    absl::ParseCommandLine(ac, av);

    std::string ServerAddress = absl::GetFlag(FLAGS_address);
    bool EncryptedConnection = absl::GetFlag(FLAGS_ssl);

    HexagonClient hc(ServerAddress, EncryptedConnection);
    hc.ConnectToServer();

    if(hc.GetConnectionState() == hw_conn_state::HEXWORLD_CONNECTION_READY || hc.GetConnectionState() == hw_conn_state::HEXWORLD_CONNECTION_IDLE) {
        auto hexes = hc.GetHexagonRing(new Hexagon(0, 0, 0, "", std::map<std::string, std::string>{} ), 2, true);
        for (const auto &hex : hexes) {
            std::cout << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]" << std::endl;
            for(const auto& [key, value] : hex.Data ) {
                std::cout << "\t" << key << " - " << value << std::endl;
            }
        }
        for (const auto &hex : hexes) {
            std::cout << hex.X << "," << hex.Y << "," << hex.Z << "," << hex.Type << " " << std::endl;
            for(const auto& [key, value] : hex.Data ) {
                std::cout << "\t" << key << " - " << value << std::endl;
            }
        }
    }
}
