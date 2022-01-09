#pragma once
#include "Core/Events.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/pattern_formatter.h"
#include <spdlog/common.h>
#include <iostream>

namespace Architect
{
	enum class MessageType
	{
		Trace,
		Info,
		Warning,
		Error
	};

	struct LogCallbackData
	{
		MessageType Type;
		std::string Message;
	};

	template<typename Mutex>
	class SpdLogCallbackSink : public spdlog::sinks::base_sink <Mutex>
	{
	public:
		SpdLogCallbackSink(const std::string& pattern) 
			: m_Formatter(std::make_shared<spdlog::pattern_formatter>(pattern)) {}
		~SpdLogCallbackSink() {}

		EventHandler<const LogCallbackData>& GetLogEventHandler() { return m_MessageLogged; }

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			m_Formatter->format(msg, formatted);
			std::string message = fmt::to_string(formatted);
			
			MessageType type;

			switch (msg.level)
			{
			case spdlog::level::err:
				type = MessageType::Error;
				break;
			case spdlog::level::warn:
				type = MessageType::Warning;
				break;
			case spdlog::level::info:
				type = MessageType::Info;
				break;
			case spdlog::level::trace:
				type = MessageType::Trace;
				break;
			default:
				break;
			}

			LogCallbackData data = { type, message };
			m_MessageLogged.Invoke(data);
		}

		void flush_() override
		{
			std::cout << std::flush;
		}

	private:
		EventHandler<const LogCallbackData> m_MessageLogged;
		std::shared_ptr<spdlog::pattern_formatter> m_Formatter;
	};

#include <mutex>
	using SpdLogCallbackSink_mt = SpdLogCallbackSink<std::mutex>;
}

