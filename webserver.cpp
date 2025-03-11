#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void handle_request(tcp::socket& socket) {
    try {
        boost::asio::streambuf request;
        boost::asio::read_until(socket, request, "\r\n\r\n");
        
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 24\r\n"
            "\r\n"
            "Hello, World from anish!";
        
        boost::asio::write(socket, boost::asio::buffer(response));
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        
        std::cout << "Server is running on port 8080..." << std::endl;
        
        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            handle_request(socket);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}

