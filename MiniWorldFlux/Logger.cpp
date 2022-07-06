#include "pch.h"
#include "Logger.h"


Logger::Logger() {
	
}

Logger& Logger::getInstance() {
	static Logger inst;
	return inst;
}

// ֱ�Ӵ�INFO Log
Logger& Logger::operator<<(const wchar_t* message) {
	this->queue.push_back(Message(message, LogRank::INFO));
	return *this;
}

// ֱ�Ӵ�INFO Log
Logger& Logger::operator<<(const WString message) {
	this->queue.push_back(Message(message, LogRank::INFO));
	return *this;
}

Logger& Logger::operator<<(const Message message) {
	this->queue.push_back(message);
	return *this;
}

void Logger::flush() {
	if (this->queue.empty()) return;
	for (const Message& msg : this->queue) {
		wprintf(msg.content.c_str());
	}
	this->queue.clear();
}
