#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <tuple>
#include <functional>
#include <typeinfo>
#include <iostream>
#include <memory>
#include <mutex>

#include "tracy/Tracy.hpp"
#include "Delegate.h"

/**
 * Stores functions that are called when invoked. Pass a function like Class::Function,
 * or if inside class &Function and a pointer to an instance of that class.
 * You can also pass any parameters you want your function to be called with.
 * ex: AddListener(SceneManager::LoadScene, scenemanager*, "MainMenu").
 * To Remove a function call Remove Listener with the same parameters as you added it
 * or remove it by the id that's stored inside the return type of the call function.
 */
template <typename... Params>
class Event
{
protected:
	std::vector<std::unique_ptr<Delegate<>>> Callback;
	std::vector<std::unique_ptr<Delegate<Params...>>> DynamicCallback;
	TracyLockable(std::mutex, dynamicMutex);
	TracyLockable(std::mutex, staticMutex);

public:
	Event() {};
	~Event() {};

	void AddListener(const Delegate<>& delegate)
	{
		ZoneScoped;
		std::lock_guard lock(staticMutex);
		Callback.emplace_back(std::unique_ptr<Delegate<>>(delegate.clone()));
	}
	void AddDynamicListener(const Delegate<Params...>& delegate)
	{
		ZoneScoped;
		std::lock_guard lock(dynamicMutex);
		DynamicCallback.emplace_back(std::unique_ptr<Delegate<Params...>>(delegate.clone()));
	}
	virtual void RemoveListener(const Delegate<>& delegate)
	{
		std::lock_guard lock(staticMutex);
		for (auto it = Callback.begin(); it != Callback.end(); it++)
		{
			if (*it->get() == delegate)
			{
				Callback.erase(it);
				return;
			}
		}
	}
	virtual void RemoveDynamicListener(const Delegate<Params...>& delegate)
	{
		std::lock_guard lock(dynamicMutex);
		for (auto it = DynamicCallback.begin(); it != DynamicCallback.end(); it++)
		{
			if (*it->get() == delegate)
			{
				DynamicCallback.erase(it);
				return;
			}
		}
	}
	virtual void RemoveObject(void* object)
	{
		{
			std::lock_guard lock(staticMutex);
			for (auto it = Callback.begin(); it != Callback.end();)
			{
				if (it->get()->getObject() == object)
				{
					Callback.erase(it);
				}
				else it++;
			}
		}
		{
			std::lock_guard lock(dynamicMutex);
			for (auto it = DynamicCallback.begin(); it != DynamicCallback.end();)
			{
				if (it->get()->getObject() == object)
				{
					DynamicCallback.erase(it);
				}
				else it++;
			}
		}
	}
	virtual void Invoke(Params... params)
	{
		ZoneScoped;
		{
			std::lock_guard lock(staticMutex);
			for (auto& call : Callback)
			{
				try
				{
					(*call)();
				}
				catch (std::bad_function_call&)
				{
					std::cout << "function is empty"
						<< "\n";
				}
			}
		}
		{
			std::lock_guard lock(dynamicMutex);
			for (auto& call : DynamicCallback)
			{
				try
				{
					(*call)(params...);
				}
				catch (std::bad_function_call&)
				{
					std::cout << "function is empty"
						<< "\n";
				}
			}
		}
	}
	void Clear()
	{
		std::lock_guard<std::mutex> lock(dynamicMutex);
		std::lock_guard<std::mutex> lock2(staticMutex);
		Callback.clear();
		DynamicCallback.clear();
	}
};

template <typename... Params>
class CachedEvent : public Event<Params...>
{
private:

	struct Cache
	{
	private:
		std::vector<Delegate<>*> StaticCache;
		std::vector<Delegate<Params...>*> DynamicCache;
		TracyLockable(std::mutex, cacheSMutex);
		TracyLockable(std::mutex, cacheDyMutex);
		std::tuple<Params...> args;
		template<size_t... Is>
		void InvokeUtil(Delegate<Params...>* del, std::index_sequence<Is...>)
		{
			(*del)(std::get<Is>(args)...);
		}

	public:
		Cache(Params... params) : args(params...) {}
		void AddDelegate(Delegate<>* del)
		{
			std::lock_guard lock2(cacheSMutex);
			StaticCache.push_back(del);
		}
		void AddDynamicDelegate(Delegate<Params...>* del)
		{
			std::lock_guard lock2(cacheDyMutex);
			DynamicCache.push_back(del);
		}
		void RemoveDelegate(const Delegate<>& del)
		{
			std::lock_guard lock2(cacheSMutex);
			for (auto it = StaticCache.begin(); it != StaticCache.end();)
			{
				if (**it == del) StaticCache.erase(it);
				else it++;
			}
		}
		void RemoveDynamicDelegate(const Delegate<Params...>& del)
		{
			std::lock_guard lock2(cacheDyMutex);
			for (auto it = DynamicCache.begin(); it != DynamicCache.end();)
			{
				if (**it == del) DynamicCache.erase(it);
				else it++;
			}
		}
		void RemoveObject(void* object)
		{
			{
				std::lock_guard lock(cacheSMutex);
				for (auto it = StaticCache.begin(); it != StaticCache.end();)
				{
					if ((*it)->getObject() == object) StaticCache.erase(it);
					else it++;
				}
			}
			{
				std::lock_guard lock(cacheDyMutex);
				for (auto it = DynamicCache.begin(); it != DynamicCache.end();)
				{
					if ((*it)->getObject() == object) DynamicCache.erase(it);
					else it++;
				}
			}
		}
		void Invoke()
		{
			std::lock_guard lock(cacheSMutex);
			std::lock_guard lock2(cacheDyMutex);
			for (auto& call : StaticCache)
			{
				try
				{
					(*call)();
				}
				catch (std::bad_function_call&)
				{
					std::cout << "function is empty"
						<< "\n";
				}
			}
			for (auto& call : DynamicCache)
			{
				try
				{
					InvokeUtil(call, std::index_sequence_for<Params...>());
				}
				catch (std::bad_function_call&)
				{
					std::cout << "function is empty"
						<< "\n";
				}
			}
		}

	};

	std::vector<std::unique_ptr<Cache>> cachedEvents;
	TracyLockable(std::mutex, cacheMutex);
public:
	void Invoke(Params... params) override
	{
		std::unique_ptr<Cache> cache = std::make_unique<Cache>(params...);
		{
			std::lock_guard lock(this->staticMutex);
			for (auto& call : this->Callback)
			{
				cache->AddDelegate(call.get());
			}
		}
		{
			std::lock_guard lock(this->dynamicMutex);
			for (auto& call : this->DynamicCallback)
			{
				cache->AddDynamicDelegate(call.get());
			}
		}
		cachedEvents.push_back(std::move(cache));
	}
	void RemoveObject(void* object) override
	{
		std::lock_guard lock(cacheMutex);
		for (auto& cache : cachedEvents)
		{
			cache->RemoveObject(object);
		}
		Event<Params...>::RemoveObject(object);
	}
	void RemoveListener(const Delegate<>& delegate) override
	{
		std::lock_guard lock(cacheMutex);
		for (auto& cache : cachedEvents)
		{
			cache->RemoveDelegate(delegate);
		}
		Event<Params...>::RemoveListener(delegate);
	}
	void RemoveDynamicListener(const Delegate<Params...>& delegate) override
	{
		std::lock_guard lock(cacheMutex);
		for (auto& cache : cachedEvents)
		{
			cache->RemoveDynamicDelegate(delegate);
		}
		Event<Params...>::RemoveDynamicListener(delegate);
	}
	void ReleaseCache()
	{
		std::vector<std::unique_ptr<Cache>> temp;
		{

			std::lock_guard lock(cacheMutex);
			for (auto& cache : cachedEvents)
			{
				temp.push_back(std::move(cache));
			}
			ClearCache();
		}
		for (auto& cache : temp)
		{
			cache->Invoke();
		}
	}
	void ClearCache()
	{
		cachedEvents.clear();
	}
};
#endif // EVENT_H
