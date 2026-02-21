#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/Commands.h>

#include <vector>
#include <memory>
#include <cstring>

namespace Aquios
{
	namespace Commands {
		struct ClearColorCmd;
		struct ClearCmd;
		struct UploadBufferDataCmd;
		struct BindBufferBaseCmd;
		struct SetShaderUniformBufferCmd;
		struct SetShaderStorageBlockCmd;
		struct BindPipelineCmd;
		struct LambdaCmd;
		struct DrawMeshCmd;
	}

	struct ICommandBackend
	{
		virtual void Execute(const Commands::ClearColorCmd* cmd) = 0;
		virtual void Execute(const Commands::ClearCmd* cmd) = 0;
		virtual void Execute(const Commands::UploadBufferDataCmd* cmd) = 0;
		virtual void Execute(const Commands::BindBufferBaseCmd* cmd) = 0;
		virtual void Execute(const Commands::SetShaderUniformBufferCmd* cmd) = 0;
		virtual void Execute(const Commands::SetShaderStorageBlockCmd* cmd) = 0;
		virtual void Execute(const Commands::BindPipelineCmd* cmd) = 0;
		virtual void Execute(const Commands::DrawMeshCmd* cmd) = 0;
		virtual void Execute(const Commands::LambdaCmd* cmd)
		{
			cmd->Execute();
		}

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
		bool ExecuteImmediate = false;

		template<typename T>
		void Record(T cmd)
		{
			void* storage = Allocate(sizeof(T));
			new(storage) T(cmd);

			auto cmdEntry = CommandEntry
			{
				+[](void* ptr, ICommandBackend* backend)
				{
					T* c = reinterpret_cast<T*>(ptr);
					backend->Execute(c);
				},
				storage
			};

			if (ExecuteImmediate)
			{
				cmdEntry.execute(cmdEntry.data, m_Backend.get());
			}
			else
				entries.push_back(
					cmdEntry
				);
		}

		void ExecuteAll()
		{
			for (auto& e : entries)
				e.execute(e.data, m_Backend.get());
		}

		~CommandList() {
			for (auto ptr : allocations) ::operator delete(ptr);
		}

		void Release()
		{
			
		}

		void SetBackend(Scope<ICommandBackend> backend)
		{
			m_Backend = std::move(backend);
		}
	private:
		Scope<ICommandBackend> m_Backend;
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