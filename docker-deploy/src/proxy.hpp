#ifndef PROXY_HPP
#define PROXY_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdexcept>
#include "request.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include "logger.hpp"

class Proxy {
public:
    // Default constructor - use system assigned port
    Proxy() : Proxy(0) {}
    
    // Constructor with specified port
    explicit Proxy(int port);
    
    // Destructor
    ~Proxy();
    
    // Start the proxy server
    void run();
    
    // Stop the proxy server
    void stop();
    
    // Get the current port
    int getPort() const { return port; }

private:
    // Setup server socket
    void setup_server();
    
    // Accept client connections
    void start_accepting();
    
    // Static client thread function
    static void client_thread(Proxy* proxy, int client_fd);
    
    // Handle client request
    void handle_client(int client_fd);
    
    // Handle GET request
    void handle_get(int client_fd, const Request& request);
    
    // Handle POST request
    void handle_post(int client_fd, const Request& request);
    
    // Handle CONNECT request
    void handle_connect(int client_fd, const Request& request);
    
    // Build GET request
    std::string build_get_request(const Request& request);
    
    // Build POST request
    std::string build_post_request(const Request& request);
    
    // Connect to target server
    int connect_to_server(const std::string& host, int port);
    
    // Extract host from URL
    std::string extract_host(const std::string& url);
    
    // Parse host and port
    std::pair<std::string, int> parse_host_and_port(const std::string& host_str);
    
    int server_fd;
    int port;
    Logger& logger;
    bool running;
    std::vector<std::thread> threads;
};

#endif
