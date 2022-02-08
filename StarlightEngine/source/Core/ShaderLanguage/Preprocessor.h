#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "defines.h"

#include <fstream>

namespace Starlight
{
	class Preprocessor
	{
	public:
		Preprocessor() = default;
 
		bool ProcessLine(const std::string& line, std::string& outSource);
		bool IncludeFile(const std::string& name, std::string& outSource);

		~Preprocessor() = default;
	private:
		std::vector<std::string> m_Directives = {
			"#include"
		};
	};
}

#endif // !
