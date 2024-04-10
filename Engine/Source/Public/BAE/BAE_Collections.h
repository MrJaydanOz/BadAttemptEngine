#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Collections.h"))
#endif

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(struct Pair))
#endif
	template<typename TFirst, typename TSecond>
	struct Pair
	{
		TFirst first;
		TSecond second;

	public:
		constexpr Pair() noexcept requires EmptyConstructor<TFirst> && EmptyConstructor<TSecond> :
			first(),
			second() { }

		constexpr Pair(TFirst first, TSecond second) noexcept :
			first(first),
			second(second) { }
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Collection))
#endif
	class Collection
	{
	protected:
		template<typename T>
		_NODISCARD_RAW_PTR_ALLOC static constexpr T* Allocate(in<size_t> length)
		{ 
			T* allocationPointer = static_cast<T*>(malloc(sizeof(T) * length));

			if (allocationPointer == nullptr)
				throw new std::bad_alloc();

			return allocationPointer;
		}

		template<typename T>
		static constexpr void Deallocate(in<T*> block) noexcept
		{ free(block); }

		template<typename T>
		static constexpr void Copy(in<const T*> from, in<T*> to, size_t size) noexcept
		{ memcpy(to, from, sizeof(T) * size); }
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class List))
#endif
	template<typename T>
	class List : public Collection
	{
	public:
		typedef size_t size_type;
		typedef T* iterator;
		typedef const T* const_iterator;

	private:
		T* _dataPointer;
		size_type _listSize;
		size_type _listCapacity;

	public:
		constexpr List(in_initializer_list<T> initializerList) :
			_listSize(initializerList.size()),
			_listCapacity(_listSize > 1 ? _listSize : 1)
		{
			_dataPointer = Allocate<T>(_listCapacity);

			if (_listSize > 0)
				Copy<T>(initializerList.begin(), _dataPointer, _listCapacity);
		}

		constexpr List(in<size_type> capacity) :
			_listSize(0),
			_listCapacity(capacity > 1 ? capacity : 1)
		{
			_dataPointer = Allocate<T>(_listCapacity);
		}

		constexpr List() :
			List::List(0) { }

		constexpr List(in<List> originalList) :
			_listSize(originalList._listSize),
			_listCapacity(_listSize > 1 ? _listSize : 1)
		{
			_dataPointer = Allocate<T>(_listSize);

			if (_listSize > 0)
				Copy<T>(originalList._dataPointer, _dataPointer, _listCapacity);
		}

		template<typename TOriginal>
		constexpr List(in<TOriginal> originalList) requires CopyOperator<T> && requires(TOriginal originalList, size_type index) { (T)originalList[index]; }&& Sizable<TOriginal, size_type> :
			_listSize(originalList.size()),
			_listCapacity(_listSize > 1 ? _listSize : 1)
		{
			_dataPointer = std::unique_ptr<T>(Allocate<T>(_listCapacity));

			for (size_type i = 0; i < _listSize; i++)
				*(_dataPointer + i) = (T)originalList[i];
		}

		constexpr ~List() noexcept
		{ Deallocate<T>(_dataPointer); }

		_NODISCARD_ONLY_READ constexpr size_type Size() const noexcept
		{ return _listSize; }
		_NODISCARD_ONLY_READ constexpr size_type Capacity() const noexcept
		{ return _listCapacity; }

		constexpr void SetCapacity(in<size_type> capacity)
		{
			if (_listCapacity == capacity)
				return;

			T* newPointer = Allocate<T>(capacity);
			Copy<T>(_dataPointer, newPointer, capacity < _listCapacity ? capacity : _listCapacity);
			Deallocate<T>(_dataPointer);
			_dataPointer = newPointer;

			_listCapacity = capacity;
			_listSize = _listSize < _listCapacity ? _listSize : _listCapacity;
		}
		constexpr void SetCapacityAtLeast(in<size_type> minimumCapacity)
		{
			if (_listCapacity < minimumCapacity)
				SetCapacity(minimumCapacity);
		}

		_NODISCARD_RESULT constexpr bool WithinRange(in<size_type> index) const noexcept
		{ return index < _listSize; }

		constexpr void Clear() noexcept
		{ _listSize = 0; }

		_NODISCARD_RESULT constexpr iterator Find(in<T> item) requires Equatable<T>
		{
			iterator itEnd = _dataPointer + _listSize;
			for (iterator it = _dataPointer; it < itEnd; it++)
				if (*it == item)
					return it;

			return itEnd;
		}
		_NODISCARD_RESULT constexpr const_iterator Find(in<T> item) const requires Equatable<T>
		{ return const_cast<List&>(*this).Find(item); }

		constexpr bool TryFind(in<T> item, out<iterator> iterator) requires Equatable<T>
		{ return (iterator = Find(item)) != _dataPointer + _listSize; }
		constexpr bool TryFind(in<T> item, out<const_iterator> iterator) const requires Equatable<T>
		{ return const_cast<List&>(*this).TryFind(item, iterator); }

		template<typename TPredicate = bool(T)>
		_NODISCARD_RESULT constexpr iterator FindIf(in_delegate<TPredicate> predicate) requires Callable<TPredicate, bool, in<T>>
		{
			iterator itEnd = _dataPointer + _listSize;
			for (iterator it = _dataPointer; it < itEnd; it++)
				if (predicate(*it))
					return it;

			return itEnd;
		}
		template<typename TPredicate = bool(T)>
		_NODISCARD_RESULT constexpr const_iterator FindIf(in_delegate<TPredicate> predicate) const requires Callable<TPredicate, bool, in<T>>
		{ return const_cast<List&>(*this).FindIf(predicate); }

		template<typename TPredicate = bool(T)>
		constexpr bool TryFindIf(in_delegate<TPredicate> predicate, out<iterator> iterator) requires Callable<TPredicate, bool, in<T>>
		{ return (iterator = FindIf(predicate)) != _dataPointer + _listSize; }
		template<typename TPredicate = bool(T)>
		constexpr bool TryFindIf(in_delegate<TPredicate> predicate, out<const_iterator> iterator) const requires Callable<TPredicate, bool, in<T>>
		{ return const_cast<List&>(*this).TryFindIf(predicate, iterator); }

		constexpr void Append(in<T> item) requires CopyOperator<T>
		{
			size_type newSize = _listSize + 1;
			if (newSize > _listCapacity)
				SetCapacity(_listCapacity * 2);

			Copy<T>(&item, _dataPointer + _listSize, 1);
			_listSize = newSize;
		}

		constexpr void AppendMany(in_initializer_list<T> initializerList)
		{
			size_type valuesSize = initializerList.size();
			size_type newSize = _listSize + valuesSize;
			size_type newCapacity = _listCapacity;
			while (newSize > newCapacity)
				newCapacity *= 2;

			SetCapacity(newCapacity);

			Copy<T>(initializerList.begin(), _dataPointer + _listSize, initializerList.size());
			_listSize = newSize;
		}

		template<typename TCollection = List>
		constexpr void InsertRangeAt(in<size_type> index, in<TCollection> values) requires CopyOperator<T> && Iterable<TCollection> && Sizable<TCollection, size_type>
		{
			size_type valuesSize = values.size();

			if (valuesSize <= 0)
				return;

			if (index > _listSize)
				throw new std::bad_array_new_length();

			size_type newSize = _listSize + valuesSize;
			size_type newCapacity = _listCapacity > 1 ? _listCapacity : 1;
			while (newSize > newCapacity)
				newCapacity *= 2;
			bool newAllocation = newCapacity != _listCapacity;

			T* dataTo = newAllocation ? Allocate<T>(newCapacity) : _dataPointer;

			if (newAllocation)
				Copy<T>(_dataPointer, dataTo, index);

			Copy<T>(_dataPointer + index, dataTo + (index + valuesSize), newSize - (index + valuesSize));

			T* dataInsertTo = dataTo + index;

			for (auto& value : values)
				*(dataInsertTo++) = value;

			if (newAllocation)
			{
				Deallocate<T>(_dataPointer);
				_dataPointer = dataTo;
				_listCapacity = newCapacity;
			}

			_listSize = newSize;
		}
		template<typename TCollection = List>
		constexpr void InsertRangeAt(in<const_iterator> iterator, in<TCollection> values) requires CopyOperator<T> && Iterable<TCollection> && Sizable<TCollection, size_type>
		{ InsertRangeAt<TCollection>(iterator - _dataPointer, values); }

		constexpr void InsertAt(in<size_type> index, in<T> value) requires CopyOperator<T>
		{ InsertRangeAt(index, std::initializer_list({ value })); }
		constexpr void InsertAt(in<const_iterator> iterator, in<T> value) requires CopyOperator<T>
		{ InsertRangeAt(iterator, std::initializer_list({ value })); }

		constexpr void RemoveRange(in<size_type> from, in<size_type> to)
		{
			if (from > to || to >= _listSize)
				throw new std::bad_array_new_length();

			size_type deltaSize = (to - from + 1);
			size_type copySize = _listSize - to - 1;

			if (copySize > 0)
				Copy<T>(_dataPointer + (to + 1), _dataPointer + from, copySize);

			_listSize -= deltaSize;
		}
		constexpr void RemoveRange(in<const_iterator> from, in<const_iterator> to)
		{ RemoveRange(from - _dataPointer, to - _dataPointer); }
		
		constexpr void RemoveAt(in<const_iterator> iterator)
		{ RemoveRange(iterator, iterator); }
		constexpr void RemoveAt(in<size_type> index)
		{ RemoveRange(index, index); }
		
		constexpr bool Remove(in<T> value) requires Equatable<T>
		{ 
			iterator found = Find(value);
			if (found != end())
			{
				RemoveAt(found);
				return true;
			}
			else
				return false;
		}

		template<typename TPredicate = bool(T)>
		constexpr bool RemoveFirstWhere(in_delegate<TPredicate> predicate) requires Callable<TPredicate, bool, in<T>>
		{
			iterator found = FindIf(predicate);
			if (found != end())
			{
				RemoveAt(found);
				return true;
			}
			else
				return false;
		}

		template<typename TPredicate = bool(T)>
		constexpr size_type RemoveWhere(in_delegate<TPredicate> predicate) requires Callable<TPredicate, bool, in<T>>
		{
			size_type removedCounter = 0;
			iterator itFrom = _dataPointer;
			iterator itTo = _dataPointer;
			iterator itEnd = end();

			while (itFrom < itEnd)
			{
				if (itFrom != itTo)
					Copy<T>(itFrom, itTo, 1);

				if (predicate(*itFrom))
					removedCounter++;
				else
					itTo++;

				itFrom++;
			}

			_listSize -= removedCounter;
			return removedCounter;
		}

		/* Support for standard features and templates: */
		constexpr void push_back(in<T> item) requires CopyOperator<T>
		{ Append(item); }
		constexpr void erase(in<const_iterator> from, in<const_iterator> to) requires CopyOperator<T>
		{ RemoveRange(from, to); }
		constexpr void erase(in<const_iterator> index) requires CopyOperator<T>
		{ RemoveAt(index); }

		_NODISCARD_ONLY_READ constexpr iterator begin() noexcept
		{ return _dataPointer; }
		_NODISCARD_ONLY_READ constexpr const_iterator begin() const noexcept
		{ return _dataPointer; }
		_NODISCARD_ONLY_READ constexpr const_iterator cbegin() const noexcept
		{ return _dataPointer; }

		_NODISCARD_ONLY_READ constexpr iterator end() noexcept
		{ return _dataPointer + _listSize; }
		_NODISCARD_ONLY_READ constexpr const_iterator end() const noexcept
		{ return _dataPointer + _listSize; }
		_NODISCARD_ONLY_READ constexpr const_iterator cend() const noexcept
		{ return _dataPointer + _listSize; }

		constexpr void swap(ref<List> other) noexcept
		{
			std::swap(_dataPointer, other._dataPointer);
			std::swap(_listSize, other._listSize);
			std::swap(_listCapacity, other._listCapacity);
		}

		_NODISCARD_ONLY_READ constexpr size_type size() const noexcept
		{ return _listSize; }

		_NODISCARD_RESULT constexpr bool empty() const noexcept
		{ return _listSize <= 0; }
		/**/

		_NODISCARD_ONLY_READ constexpr T& operator[](in<size_type> index)
		{
			if (index >= _listSize)
				throw std::out_of_range("Index is out of range of bae::List<>.");

			return *(_dataPointer + index);
		}
		_NODISCARD_ONLY_READ constexpr const T& operator[](in<size_type> index) const
		{ return const_cast<List&>(*this).operator[](index); }

		constexpr List& operator=(in<List> other) noexcept
		{
			_listSize = other._listSize;

			SetCapacityAtLeast(_listSize);

			if (_listSize > 0)
				Copy<T>(other._dataPointer, _dataPointer, _listSize);

			return *this;
		}

		_NODISCARD_RESULT constexpr bool operator==(in<List> other) const requires Equatable<T>
		{
			if (_listSize != other._listSize)
				return false;

			for (size_type i = 0; i < _listSize; i++)
				if (*(_dataPointer + i) != *(other._dataPointer + i))
					return false;

			return true;
		}
		_NODISCARD_RESULT constexpr bool operator!=(in<List> other) const requires Equatable<T>
		{
			if (_listSize != other._listSize)
				return true;

			for (size_type i = 0; i < _listSize; i++)
				if (*(_dataPointer + i) != *(other._dataPointer + i))
					return true;

			return false;
		}
	};

	template<typename T>
	static constexpr void swap(ref<List<T>> a, ref<List<T>> b) noexcept
	{ a.swap(b); }

	template<typename T>
	std::ostream& operator<<(ref<std::ostream> stream, in<List<T>> list) requires Printable<T>
	{
		stream << '{';

		bool isFirst = true;

		for (auto& element : list)
		{
			if (!isFirst)
			{
				stream << ", ";
				isFirst = true;
			}

			stream << element;
		}

		stream << '}';

		return stream;
	}
}