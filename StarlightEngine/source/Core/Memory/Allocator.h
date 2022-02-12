#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "defines.h"

namespace Starlight
{
	// Smart pointer
	template<typename T>
	class Ref
	{
	public:
		Ref() = default;
		Ref(T* pointer)
		{
			m_Pointer = pointer;
		}

		Ref(const std::nullptr_t& null)
		{
			m_Pointer = null;
		}

		Ref(const Ref<T>& ref) = default;
		Ref(Ref&& ref) = default;

		Ref<T>& operator=(const Ref<T>& ref) noexcept
		{
			m_Pointer = ref.m_Pointer;
			return (*this);
		}

		Ref<T>& operator=(T* pointer) noexcept
		{
			m_Pointer = pointer;
			return (*this);
		}

		Ref<T>& operator=(const std::nullptr_t& null) noexcept
		{
			m_Pointer = null;
			return (*this);
		}

		// Compares pointers's values
		bool operator==(const Ref<T>& ref) noexcept
		{
			return *(ref.m_Pointer) == *(m_Pointer);
		}

		// Compares pointers's values
		bool operator!=(const Ref<T>& ref) noexcept
		{
			return *(ref.m_Pointer) != *(m_Pointer);
		}

		bool operator==(const std::nullptr_t& null) noexcept
		{
			return m_Pointer == null;
		}

		bool operator!=(const std::nullptr_t& null) noexcept
		{
			return m_Pointer != null;
		}

		Ref<T> operator+(uint32_t value) noexcept
		{
			Ref<T> ref = m_Pointer + value;
			return ref;
		}

		T& operator[](uint32_t index) noexcept
		{
			return m_Pointer[index];
		}

		T* operator->()
		{
			return m_Pointer;
		}

		T& operator*()
		{
			return *m_Pointer;
		}

		inline T* Native() const noexcept { return m_Pointer; }

		// Calling this method means that smart pointer won't clear allocated memory
		void Freeze()
		{
			m_Freezed = true;
		}

		// Calling this method means that smart pointer will clear allocated memory
		void Unfreeze()
		{
			m_Freezed = false;
		}

		~Ref()
		{
			if (!m_Freezed) 
				free(m_Pointer);
		}
	private:
		T* m_Pointer = nullptr;
		bool m_Freezed = false;
	};

	// T defines type of data that allocator will allocate
	// Count defines how much allocator can allocate
	// This class is an array of Refs that have allocated memory in heap.
	// All refs are freezed. Only when Allocator be destroyed it will release all data
	template<typename T, uint32_t count>
	class Allocator
	{
	public:
		Allocator() { };
		Allocator(const Allocator&) = delete;
		Allocator(Allocator&&) = delete;

		Allocator& operator=(const Allocator&) = delete;

		Ref<T> Allocate(const T& initValue)
		{
			if (m_CurrentPosition >= count)
				return Ref<T>(nullptr);

			m_Allocations[m_CurrentPosition].first = new T(initValue);
			m_Allocations[m_CurrentPosition].second = sizeof(T);

			m_Allocations[m_CurrentPosition].first.Freeze();


			return m_Allocations[m_CurrentPosition++].first;
		}

		Ref<T> AllocateArray(uint32_t _count)
		{
			if (m_CurrentPosition >= count)
				return Ref<T>(nullptr);

			m_Allocations[m_CurrentPosition].first = new T[_count];
			m_Allocations[m_CurrentPosition].second = sizeof(T) * _count;

			m_Allocations[m_CurrentPosition].first.Freeze();

			return m_Allocations[m_CurrentPosition++].first;
		}


		void Push(const Ref<T>& ref, size_t size = sizeof(T))
		{
			m_Allocations[m_CurrentPosition++] = { ref, size };
		}

		~Allocator()
		{
			for (int i = 0; i < m_CurrentPosition; i++)
				m_Allocations[i].first.Unfreeze();
		}
	private:
		std::array<std::pair<Ref<T>, size_t>, count> m_Allocations;
		int m_CurrentPosition = 0;
	};
}

#endif // !ALLOCATOR_H
