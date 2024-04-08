#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Collections.h"))
#endif
#include <initializer_list>

namespace bae
{
	class Collection
	{
	protected:
		template<typename T>
		_NODISCARD_RAW_PTR_ALLOC static constexpr T* Allocate(in<size_t> length)
		{ 
			T* allocationPointer = static_cast<T*>(malloc(sizeof(T) * length));

			if (allocationPointer == nullptr)
				throw new std::bad_alloc();

			return allocationPointer
		}

		template<typename T>
		static constexpr void Deallocate(in<T*> block) noexcept
		{ free(block); }
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class List))
#endif
	template<typename T>
	class List : public Collection
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

	private:
		T* _dataPointer;
		size_t _length;
		size_t _capacity;

	public:
		constexpr List() noexcept :
			_dataPointer(nullptr),
			_length(0),
			_capacity(0) { }

		constexpr List(in<std::initializer_list<T>> initializerList) :
			_length(initializerList.size()),
			_capacity(_length)
		{
			_dataPointer = Allocate<T>(_capacity);

			memcpy(_dataPointer, initializerList.begin(), sizeof(T) * _capacity);
		}

		constexpr List(in<List> originalList) :
			_length(originalList._length),
			_capacity(_length)
		{
			_dataPointer = Allocate<T>(_capacity);

			memcpy(_dataPointer, originalList._dataPointer, sizeof(T) * _capacity);
		}

		constexpr ~List() noexcept
		{ Deallocate(_dataPointer); }

		constexpr size_t Length() const noexcept
		{ return _length; }
		constexpr size_t Capacity() const noexcept
		{ return _capacity; }

		constexpr T& operator[](in<size_t> index)
		{
			if (index >= _length)
				throw std::out_of_range("Index is out of range of bae::List<>.");

			return *(_dataPointer + index);
		}
		constexpr const T& operator[](in<size_t> index) const
		{
			if (index >= _length)
				throw std::out_of_range("Index is out of range of bae::List<>.");

			return *(_dataPointer + index);
		}
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class List))
#endif
	template<typename T>
	class Deck : public Collection
	{

	};
}