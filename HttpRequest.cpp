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
	
	// \r\n\r\n -> 4
	m_Body = request.substr(pos + 4, request.size());

	ParseQuery();

	// get rid off query
	int qPos = m_Path.find("?");
	if (qPos != std::string::npos) {
		m_Path = m_Path.substr(0, qPos);
	}

	ParseCookies();
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

void HttpRequest::ParseQuery()
{
	// abc/abc?q=123&b=456
	// search query
	int l = 0;
	std::string key = "";
	bool startQuery = false;
	for (int i = 0; i < m_Path.size(); ++i) {
		if (m_Path[i] == '?') {
			startQuery = true;
			l = i + 1;
		}
		
		if (startQuery && m_Path[i] == '=') {
			key = m_Path.substr(l, i - l);
			l = i + 1; // start after '='
		}

		if (!key.empty() && (m_Path[i] == '&' || i == m_Path.size() - 1)) {	
			int count = i == m_Path.size() - 1 ? i - l + 1 : i - l;
			m_Query[key] = m_Path.substr(l, count);
			l = i + 1;
			key = "";
		}
	}
}

void HttpRequest::ParseCookies()
{
	if (m_Headers.find("Cookie") == m_Headers.end())
		return;

	// Cookie: id=a3fWa; Expires=Thu, 21 Oct 2021 07:28:00 GMT; Secure;
	std::string cookies = m_Headers["Cookie"];
	int l = 0;
	std::string key = "";
	for (int i = 0; i < cookies.size(); ++i) {
		if (key.empty() && cookies[i] == '=') {
			key = cookies.substr(l, i - l);
			l = i + 1;
		}

		if (!key.empty() && (cookies[i] == ';' || i == cookies.size() - 1)) {
			int count = i == cookies.size() - 1 ? i - l + 1 : i - l;
			m_Cookies[key] = cookies.substr(l, count);
			l = i + 2; // `; Expires...` cause there's a space
			key = ""; 
		}
	}
}

std::string& HttpRequest::GetQuery(std::string&& q)
{
	if (m_Query.find(q) != m_Query.end()) {
		return m_Query[q];
	}

	return emptyStr;
}

std::string& HttpRequest::GetCookie(std::string& c) 
{
	if (m_Cookies.find(c) != m_Cookies.end())
		return m_Cookies[c];
	return emptyStr;
}

std::string& HttpRequest::GetCookie(std::string&& c) 
{
	if (m_Cookies.find(c) != m_Cookies.end())
		return m_Cookies[c];
	return emptyStr;
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