#ifndef GamePointers_H
#define GamePointers_H

#include <memory>
#include <vector>
#include <concepts>

#include <tracy/Tracy.hpp>


class _BaseMainPtr;
template<class Type>
class WeakPtr;
template<class Type, class Deleter = std::default_delete<Type>>
class MainPtr;


class _BaseWeakPtr
{
protected:
	_BaseMainPtr* mainptr = nullptr;
	virtual void Nullify() = 0;

	_BaseWeakPtr(_BaseMainPtr* mainptr) : mainptr(mainptr){}
public:
	virtual operator bool() const = 0;

	_BaseWeakPtr() {}
	virtual ~_BaseWeakPtr() = default;
	template<class T, class Deleter> friend class MainPtr;
};

class _BaseMainPtr
{
protected:
	std::vector<_BaseWeakPtr*> references;
public:
	virtual operator bool() const = 0;

	_BaseMainPtr(){}
	virtual ~_BaseMainPtr() = default;
	template<class T> friend class WeakPtr;
};

template<class Type>
class WeakPtr : public  _BaseWeakPtr
{
private:
	Type* ptr = nullptr;
	void Nullify()
	{
		ptr = nullptr;
		mainptr = nullptr;
	}
public:
	WeakPtr(){};

	WeakPtr(const WeakPtr&)
	{
		if (mainptr) mainptr->references.emplace_back(this);
	}

	template<class T, class Deleter>
	WeakPtr(MainPtr<T, Deleter>& other)
	{
		reset(other);
	}

	virtual ~WeakPtr()
	{
		ZoneScoped;
		reset();
	}

	void reset()
	{
		if(mainptr)std::erase(mainptr->references, this);
		Nullify();
	}
	template<class T, class Deleter>
	void reset(MainPtr<T, Deleter>& mptr)
	{
		if (mainptr)std::erase(mainptr->references, this);
		mainptr = &mptr;
		mainptr->references.emplace_back(this);
		this->ptr = dynamic_cast<Type*>(mptr.get());
	}
	Type* get() const
	{
		return ptr;
	}
	operator bool() const override
	{
		return ptr;
	}
	Type* operator->() const
	{
		return ptr;
	}
	Type& operator*() const
	{
		return *ptr;
	}
	template<std::convertible_to<Type> T>
	WeakPtr& operator=(MainPtr<T>& other)
	{
		if (*this == other)  return *this;
		reset(other);
		return *this;
	}
	friend _BaseMainPtr;
	template<class T, class Deleter> friend class MainPtr;
};

template<class Type, class Deleter>
class MainPtr : public  _BaseMainPtr
{
private:
	std::unique_ptr<Type, Deleter> ownedptr;
public:
	MainPtr(){}
	MainPtr(Type* ptr)
	{
		ownedptr.reset(ptr);
	}
	MainPtr(MainPtr&&) = default;

	virtual ~MainPtr()
	{
		for (auto reference : references) reference->Nullify();
	}


	operator bool() const override
	{
		return ownedptr.get();
	}
	Type* get() const
	{
		return ownedptr.get();
	}
	Type* operator->() const
	{
		return ownedptr.get();
	}
	Type& operator*() const 
	{
		return *ownedptr.get();
	}
	template<class T>
	MainPtr<T>& operator=(MainPtr<T>&& other)
	{
		if (this == &other)
			return *this;
		ownedptr = std::move(other.ownedptr);
		references = other.references;
		other.references.clear();
		return *this;
	}
};
template<class T, class U>
bool operator==(const WeakPtr<T>& lhs, const WeakPtr<U>& rhs)
{
	return lhs.get() == rhs.get();
}
template<class T, class U>
bool operator==(const MainPtr<T>& lhs, const  WeakPtr<U>& rhs)
{
	return lhs.get() == rhs.get();
}

template<class T, class U>
bool operator==(const WeakPtr<T>& lhs, const MainPtr<U>& rhs)
{
	return lhs.get() == rhs.get();
}

template<class T, class U>
bool operator==(const MainPtr<T>& lhs, const MainPtr<U>& rhs)
{
	return lhs.get() == rhs.get();
}


#endif //GamePointers_H	


