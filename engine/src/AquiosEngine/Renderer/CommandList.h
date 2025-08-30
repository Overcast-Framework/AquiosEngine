#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/Commands.h>

#include <vector>
#include <memory>
#include <cstring>

namespace Aquios
{
	struct ICommandBackend
	{
		virtual void Execute(const struct ClearColorCmd& cmd) = 0;
		virtual void Execute(const struct ClearCmd& cmd) = 0;
		virtual void Execute(const struct BindBufferCmd& cmd) = 0;

		virtual ~ICommandBackend() = default;
	};

	using ExecuteFn = void (*)(void*, ICommandBackend*);
	struct CommandEntry
	{
		ExecuteFn execute;
		void* data;
	};

	class CommandList : public IDestructable
	{
	public:
		template<typename T>
		void Record(T cmd)
		{
			void* storage = Allocate(sizeof(T));
			new(storage) T(std::move(cmd));

			entries.push_back(
				CommandEntry
				{
					+[](void* ptr, ICommandBackend* backend)
					{
						T* c = reinterpret_cast<T*>(ptr);
						backend->Execute(*c);
					},
					storage
				}
			);
		}

		void ExecuteAll()
		{
			for (auto& e : entries)
				e.execute(e.data, m_Backend);
		}

		~CommandList() {
			for (auto ptr : allocations) ::operator delete(ptr);
		}

		virtual void Release() = 0;
	private:
		ICommandBackend* m_Backend;
		std::vector<CommandEntry> entries;
		std::vector<void*> allocations;

		void* Allocate(size_t size)
		{
			void* ptr = ::operator new(size);
			allocations.push_back(ptr);
			return ptr;
		}
	};
}