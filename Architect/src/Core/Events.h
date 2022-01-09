#pragma once
#include <vector>
#include <functional>
#include <memory>

namespace Architect
{
	template<typename EventData>
	class EventLisener
	{
	public:
		template<class Fx, class... Types>
		EventLisener(std::function<void(EventLisener<EventData>*)> detachFunc, Fx&& Func, Types&&... Args) : Func(std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)..., std::placeholders::_1))
		{
			m_DetachFunc = detachFunc;
		}

		EventLisener(std::function<void(EventLisener<EventData>*)> detachFunc, std::function<void(EventData&)> func) : Func(func)
		{
			m_DetachFunc = detachFunc;
		}

		void OnHandlerDestroyed()
		{
			m_IsHandlerAlive = false;
		}

		void Detach()
		{
			if (m_IsHandlerAlive)
				m_DetachFunc(this);
		}

		std::function<void(EventData&)> Func;

	private:
		bool m_IsHandlerAlive = true;
		std::function<void(EventLisener<EventData>*)> m_DetachFunc;
	};

	template<>
	class EventLisener<void>
	{
	public:
		template<class Fx, class... Types>
		EventLisener(std::function<void(EventLisener<void>*)> detachFunc, Fx&& Func, Types&&... Args) : Func(std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)...))
		{
			m_DetachFunc = detachFunc;
		}

		EventLisener(std::function<void(EventLisener<void>*)> detachFunc, std::function<void()> func) : Func(func)
		{
			m_DetachFunc = detachFunc;
		}

		void OnHandlerDestroyed()
		{
			m_IsHandlerAlive = false;
		}

		void Detach()
		{
			if (m_IsHandlerAlive)
				m_DetachFunc(this);
		}

		std::function<void()> Func;

	private:
		bool m_IsHandlerAlive = true;
		std::function<void(EventLisener<void>*)> m_DetachFunc;
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

		template<class Fx, class... Types>
		std::shared_ptr<EventLisener<EventData>> AddLisener(Fx&& Func, Types&&... Args)
		{
			std::function<void(EventLisener<EventData>*)> detachFunc = [&](EventLisener<EventData>* lisener) { RemoveLisener(lisener); };
			auto eventLisener = new EventLisener<EventData>(detachFunc, std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)..., std::placeholders::_1));
			return AddLisener(eventLisener);
		}

		std::vector<std::shared_ptr<EventLisener<EventData>>> GetLiseners() const { return m_Liseners; }

		void RemoveLisener(std::shared_ptr<EventLisener<EventData>> lisener)
		{
			auto it = std::find(m_Liseners.begin(), m_Liseners.end(), lisener);
			if (it != m_Liseners.end())
				m_Liseners.erase(it);
		}

		void RemoveLisener(EventLisener<EventData>* lisener)
		{
			for (std::shared_ptr<EventLisener<EventData>> containedLisener : m_Liseners)
			{
				if (containedLisener.get() == lisener)
				{
					RemoveLisener(containedLisener);
					break;
				}
			}
		}

		void Invoke(EventData& eventData)
		{
			for (auto& lisener : m_Liseners)
				lisener->Func(eventData);
		}

		~EventHandler()
		{
			for (auto& lisener : m_Liseners)
				lisener->OnHandlerDestroyed();
		}

	private:
		std::vector<std::shared_ptr<EventLisener<EventData>>> m_Liseners;
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

		template<class Fx, class... Types>
		std::shared_ptr<EventLisener<void>> AddLisener(Fx&& Func, Types&&... Args)
		{
			std::function<void(EventLisener<void>*)> detachFunc = [&](EventLisener<void>* lisener) { RemoveLisener(lisener);};
			auto eventLisener = new EventLisener<void>(detachFunc, std::bind(std::forward<Fx>(Func), std::forward<Types>(Args)...));
			return AddLisener(eventLisener);
		}

		std::vector<std::shared_ptr<EventLisener<void>>> GetLiseners() const { return m_Liseners; }

		void RemoveLisener(std::shared_ptr<EventLisener<void>> lisener)
		{
			auto it = std::find(m_Liseners.begin(), m_Liseners.end(), lisener);
			if (it != m_Liseners.end())
				m_Liseners.erase(it);
		}

		void RemoveLisener(EventLisener<void>* lisener)
		{
			for (std::shared_ptr<EventLisener<void>> containedLisener : m_Liseners)
			{
				if (containedLisener.get() == lisener)
				{
					RemoveLisener(containedLisener);
					break;
				}
			}
		}

		void Invoke()
		{
			for (auto& lisener : m_Liseners)
				lisener->Func();
		}

		~EventHandler()
		{
			for (auto& lisener : m_Liseners)
				lisener->OnHandlerDestroyed();
		}

	private:
		std::vector<std::shared_ptr<EventLisener<void>>> m_Liseners;
	};

	template<typename EventData>
	using EventLisenerRef = std::shared_ptr<EventLisener<EventData>>;
}