namespace ETL
{
namespace Memory
{
	template<typename T>
	T* MemStack::Push(PtrSize uCount)
	{
		PtrSize uSize = (PtrSize)uCount * sizeof(T);
		PtrSize uTop = m_uTop;
		if (uTop + uSize > m_uStackSize)
			return nullptr;
		m_uTop += uSize;
		return (T*)&((char*)m_pStack)[uTop];
	}
}
}