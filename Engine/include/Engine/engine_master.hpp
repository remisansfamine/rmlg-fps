#pragma once

#include "singleton.hpp"

namespace Core::Engine
{
	class EngineMaster final : public Singleton<EngineMaster>
	{
		friend class Singleton<EngineMaster>;

	private:
		EngineMaster();
		~EngineMaster();
		
	public:
		static void update();
	};
}