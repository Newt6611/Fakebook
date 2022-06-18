#include "HttpRequest.h"
#include "Server.h"

HttpRequest::HttpRequest(Server* server, const char* r) 
	: server(server)
{
    std::string request(r);

	int pos = request.find("\r\n\r\n");
	std::string content = request.substr(0, pos);

	/*
		del = '\r\n' it's not work in getline function
		it will become '\n'
	*/
	bool parseRequestLine = false;
	std::stringstream stream(content);
	const char del = '\n';
	std::string line;
	while (std::getline(stream, line, del)) {
		if (!parseRequestLine) {
			ParseRequestLine(line);
			parseRequestLine = true;
		}
		else {
			ParseHeaderLine(line);
		}
	}

}

void HttpRequest::ParseRequestLine(std::string& r) 
{
	int start_pos = 0;
	for (int i = 0; i < r.size(); ++i) {
		if (r[i] == ' ' || i == r.size() - 1) {
			if (m_Method.empty()) {
				m_Method = r.substr(start_pos, i - start_pos);
				start_pos = i + 1;
			}
			else if (m_Path.empty()) {
				m_Path = r.substr(start_pos, i - start_pos);
				start_pos = i + 1;
			}
			else if (m_HttpVersion.empty()) {
				m_HttpVersion = r.substr(start_pos, start_pos + 2);
			}
		}
	}
}

void HttpRequest::ParseHeaderLine(std::string& line) 
{
	int pos = line.find(": ");

	// pos + 2 because we need to remove space ": "
	std::string key = line.substr(0, pos);
	std::string value = line.substr(pos + 2, line.size() - pos);
	value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
	m_Headers[std::move(key)] = value;
}

HttpMethod HttpRequest::StringToHttpMethod(std::string& str) 
{
	if (str == "GET") {
		return HttpMethod::GET;
	}
	else if (str == "POST") {
		return HttpMethod::POST;
	}
	else {
		std::cout << "unsupported http method" << std::endl;
		return HttpMethod::NONE;
	}
}