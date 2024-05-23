#pragma unmanaged
#include <CPool.h>

#pragma managed

template <typename T, typename U, typename V = T>
private ref class PoolEnumerator : public System::Collections::Generic::IEnumerator<U^>
{
private:
    CPool<T, V>* m_pool;
    int m_index;

public:
    PoolEnumerator(CPool<T, V>* pool)
    {
        m_pool = pool;
        m_index = -1;
    }

    virtual bool MoveNext()
    {
        // Increment the index until a non-empty slot is found or the end of the pool is reached
        while (++m_index < m_pool->m_nSize)
        {
            if (!m_pool->IsFreeSlotAtIndex(m_index))
                return true;
        }

        // No more non-empty slots, end of enumeration
        return false;
    }

    virtual void Reset()
    {
        m_index = -1;
    }

    virtual property U^ Current
    {
        U^ get()
        {
            if (m_index < 0 || m_index >= m_pool->m_nSize)
                throw gcnew System::InvalidOperationException();

            return gcnew U(&m_pool->m_pObjects[m_index]);
        }
    }

    virtual property System::Object^ Current2
    {
        virtual System::Object^ get() = System::Collections::IEnumerator::Current::get
        {
            return Current;
        }
    }

    ~PoolEnumerator()
    {
        // Clean up
    }
};
