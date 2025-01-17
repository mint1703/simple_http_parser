#include <iostream>
#include <string>
#include <sstream>
#include <map>

class HttpRequest {
public:
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;

    void parse(const std::string& request) {
        std::istringstream stream(request);
        std::string line;

        // Parse request line
        if (std::getline(stream, line)) {
            std::istringstream requestLine(line);
            requestLine >> method >> path >> version;
        }

        // Parse headers
        while (std::getline(stream, line) && !line.empty()) {
            size_t separator = line.find(':');
            if (separator != std::string::npos) {
                std::string key = line.substr(0, separator);
                std::string value = line.substr(separator + 1);
                // Trim leading whitespace from value
                value.erase(0, value.find_first_not_of(" \t"));
                headers[key] = value;
            }
        }
    }

    void print() const {
        std::cout << "Method: " << method << "\n";
        std::cout << "Path: " << path << "\n";
        std::cout << "Version: " << version << "\n";
        std::cout << "Headers:\n";
        for (const auto& header : headers) {
            std::cout << "  " << header.first << ": " << header.second << "\n";
        }
    }
};

int main() {
    std::string httpRequest =
        "GET /index.html HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "User-Agent: curl/7.68.0\r\n"
        "Accept: */*\r\n"
        "\r\n";

    HttpRequest request;
    request.parse(httpRequest);
    request.print();

    return 0;
}
