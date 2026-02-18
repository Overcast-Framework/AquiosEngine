#pragma once
#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/Renderer/Commands.h>

namespace Aquios::Commands {
	struct ClearColorCmd;
	struct ClearCmd;
	struct UploadBufferDataCmd;
}

namespace Aquios::OpenGL
{
	class OpenGLCommandBackend : public ICommandBackend
	{
		void Execute(const Aquios::Commands::ClearColorCmd* cmd) override;
		void Execute(const Aquios::Commands::ClearCmd* cmd) override;
		void Execute(const Aquios::Commands::UploadBufferDataCmd* cmd) override;
		void Execute(const Commands::BindBufferBaseCmd* cmd) override;
		void Execute(const Commands::SetShaderUniformBufferCmd* cmd) override;
		void Execute(const Commands::SetShaderStorageBlockCmd* cmd) override;
		void Execute(const Commands::BindPipelineCmd* cmd) override;
		void Execute(const Commands::DrawMeshCmd* cmd) override;
	};
}