#include <asio.hpp>
#include <chrono>
#include <functional>
#include <vector>
#include <cstdint>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>

int main()
{
    using asio::ip::udp;
    using namespace std::chrono_literals;
    asio::io_context io;

    auto receiveForzaPackages = [&io] {
        udp::socket socket(io, udp::endpoint(udp::v4(), 9999));
        std::vector<uint32_t> receive_buffer(512);
        while (true)
        {
            udp::endpoint remote_endpoint;
            size_t len = socket.receive_from(asio::buffer(receive_buffer), remote_endpoint);
            spdlog::info("{}", receive_buffer);
        }
    };

    io.dispatch(receiveForzaPackages);
    io.run();
}
