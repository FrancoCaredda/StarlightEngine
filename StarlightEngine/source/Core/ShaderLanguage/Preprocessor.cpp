#include "Preprocessor.h"

#include "Core/Log.h"

#include <sstream>
#include <algorithm>

namespace Starlight
{
	bool Preprocessor::ProcessLine(const std::string& line, std::string& outSource)
	{
		std::stringstream stream(line);
		
		std::string token;
		stream >> token;

		if (std::find(m_Directives.cbegin(), m_Directives.cend(), token) != m_Directives.cend())
		{
			if (token == m_Directives[0])
			{
				std::string fileName;
				stream >> fileName;

				if (!IncludeFile(fileName, outSource))
				{
					SL_ERROR("No such file or directory: " + fileName);
					return false;
				}
			}

			return true;
		}

		return false;
	}
	
	bool Preprocessor::IncludeFile(const std::string& name, std::string& outSource)
	{
		std::ifstream file(name);

		if (!file.is_open())
			return false;

		char Buffer[BUFFER_SIZE] = { 0 };
		outSource += "\n";

		while (file.good())
		{
			file.getline(Buffer, BUFFER_SIZE);

			if (!ProcessLine(Buffer, outSource))
			{
				outSource += Buffer;
				outSource += "\n";
			}
			
			memset(Buffer, 0, strlen(Buffer));

			if (file.eof() || file.fail())
				break;
		}

		return true;
	}
}