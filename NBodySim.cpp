#include "RunManager.hpp"
#include "SteppingAction.hpp"
#include "GravitationalField.hpp"
#include "ElectromagneticField.hpp"
#include "Body.hpp"
#include "TFileManager.hpp"
#include "CmdLnManager.hpp"

#include <boost/program_options.hpp>
#include <yaml-cpp/yaml.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // Parse command line arguments with Boost
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("config", boost::program_options::value<std::string>(), "configuration file")
        ("output", boost::program_options::value<std::string>(), "output file")
        ("verbosity", boost::program_options::value<int>(), "verbosity level");

    boost::program_options::variables_map varMap;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), varMap);
    boost::program_options::notify(varMap);

    // Print help message
    if (varMap.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    // Set verbosity level
    int verbosity = 0;
    if (varMap.count("verbosity")) {
        verbosity = varMap["verbosity"].as<int>();
    }

    // Initialize command line output manager
    CmdLnManager::set_verbosity( verbosity );

    // Load configuration file
    std::string configFileName = "config.yaml";
    if (varMap.count("config")) {
        configFileName = varMap["config"].as<std::string>();
        OUT( mDebug ) << "Configuration file: " << configFileName;
    }
    YAML::Node configFile = YAML::LoadFile(configFileName);
    if( !configFile ) {
        OUT( mError ) << "Failed to load configuration file: " << configFileName;
        return 1;
    }

    // Load output file
    std::string outputFileName = "output.root";
    if (varMap.count("output")) {
        outputFileName = varMap["output"].as<std::string>();
    }

    // Initialize file manager
    TFileManager::GetInstance().SetOutputFileName(outputFileName);

    // Initialize run manager
    RunManager* runManager = new RunManager(configFileName);

    // Initialize stepping action
    SteppingAction* steppingAction = new SteppingAction(configFileName);