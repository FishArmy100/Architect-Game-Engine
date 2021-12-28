#pragma once
#include <vector>
#include <functional>
#include "Core.h"

namespace Architect
{
	template<typename EventData>
	class EventLisener
	{
	public:
		template<class Fx, class... Types>
		EventLisener(Fx&& Func, Types&&... Args) : Func(std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)..., std::placeholders::_1))
		{}

		EventLisener(std::function<void(EventData&)> func) : Func(func)
		{}

		std::function<void(EventData&)> Func;
	};

	template<typename EventData>
	class EventHandler
	{
	public:
		void AddLisener(std::shared_ptr<EventLisener<EventData>> lisener)
		{
			m_Liseners.push_back(lisener);
		}

		std::shared_ptr<EventLisener<EventData>> AddLisener(EventLisener<EventData>* lisener)
		{
			std::shared_ptr<EventLisener<EventData>> ptrLisener(lisener);
			m_Liseners.push_back(ptrLisener);
			return ptrLisener;
		}

		std::vector<std::shared_ptr<EventLisener<EventData>>> GetLiseners() const { return m_Liseners; }

		void RemoveLisener(std::shared_ptr<EventLisener<EventData>> lisener)
		{
			auto it = std::find(m_Liseners.begin(), m_Liseners.end(), lisener);
			if (it != m_Liseners.end())
				m_Liseners.erase(it);
		}

		void Invoke(EventData& eventData)
		{
			for (auto& lisener : m_Liseners)
				lisener->Func(eventData);
		}

	private:
		std::vector<std::shared_ptr<EventLisener<EventData>>> m_Liseners;
	};

	template<>
	class EventLisener<void>
	{
	public:
		template<class Fx, class... Types>
		EventLisener(Fx&& Func, Types&&... Args) : Func(std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)...))
		{}

		EventLisener(std::function<void()> func) : Func(func)
		{}

		std::function<void()> Func;
	};

	template<>
	class EventHandler<void>
	{
	public:
		void AddLisener(std::shared_ptr<EventLisener<void>> lisener)
		{
			m_Liseners.push_back(lisener);
		}

		std::shared_ptr<EventLisener<void>> AddLisener(EventLisener<void>* lisener)
		{
			std::shared_ptr<EventLisener<void>> ptrLisener(lisener);
			m_Liseners.push_back(ptrLisener);
			return ptrLisener;
		}

		std::vector<std::shared_ptr<EventLisener<void>>> GetLiseners() const { return m_Liseners; }

		void RemoveLisener(std::shared_ptr<EventLisener<void>> lisener)
		{
			auto it = std::find(m_Liseners.begin(), m_Liseners.end(), lisener);
			if (it != m_Liseners.end())
				m_Liseners.erase(it);
		}

		void Invoke()
		{
			for (auto& lisener : m_Liseners)
				lisener->Func();
		}

	private:
		std::vector<std::shared_ptr<EventLisener<void>>> m_Liseners;
	};

	template<typename EventData>
	using EventLisenerRef = std::shared_ptr<EventLisener<EventData>>;
}