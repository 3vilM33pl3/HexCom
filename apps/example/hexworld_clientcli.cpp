#include <iostream>
#include <boost/program_options.hpp>
#include <hexworld/hex_client.h>

namespace po = boost::program_options;

int main(int ac, char** av) {
    std::string ServerAddress;
    bool EncryptedConnection = true;

    try {
        po::options_description desc("Hexagon client options");
        desc.add_options()
                ("help", "help message")
                ("address", po::value<std::string>(&ServerAddress)->default_value("127.0.0.1:8080"),
                 "address to connect to [ip:port]")
                ("nossl","connect unencrypted");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 1;
        }

        if(vm.count("address")) {
            ServerAddress = vm["address"].as<std::string>();
        }

        if(vm.count("nossl")) {
            EncryptedConnection = false;
        }

    } catch(po::error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }

    HexagonClient hc(ServerAddress, EncryptedConnection);
    hc.ConnectToServer();

    if(hc.GetConnectionState() == hw_conn_state::HEXWORLD_CONNECTION_READY || hc.GetConnectionState() == hw_conn_state::HEXWORLD_CONNECTION_IDLE) {
        auto hexes = hc.GetHexagonRing(new Hexagon(0, 0, 0), 2, true);
        for (const auto &hex : hexes) {
            std::cout << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]" << std::endl;
        }
    }

}
