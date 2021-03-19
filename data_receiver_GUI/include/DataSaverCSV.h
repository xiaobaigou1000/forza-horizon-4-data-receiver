#include"forza_horizon4_structure.h"

#include<fstream>
#include<vector>
#include<memory>
#include<date/date.h>
#include<spdlog/spdlog.h>

class DataSaverCSV
{
public:
	std::unique_ptr<std::ofstream> outFilePtr;

	DataSaverCSV() {}

	void createFile(const std::string& fileNamePrefix)
	{
		std::string fileName = fileNamePrefix + date::format("%F_%H_%M_%S", std::chrono::system_clock::now()) + std::string(".csv");
		spdlog::info("{}", fileName);
		outFilePtr = std::unique_ptr<std::ofstream>{ new std::ofstream(fileName) };
		*outFilePtr << printCSVHeader();
	}

	void saveData(std::shared_ptr<std::vector<ForzaHorizon4Data>> dataToSave)
	{
		for (const auto& i : *dataToSave)
		{
			*outFilePtr << fmt::format("{}", i);
		}
	}

	void close()
	{
		outFilePtr->close();
	}
};
