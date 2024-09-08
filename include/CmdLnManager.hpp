#ifndef CMDLNMANAGER_HPP
#define CMDLNMANAGER_HPP

#include <ostream>
#include <memory>
#include <string>
#include <map>

#define OUT( m_verbosity ) CmdLnManager::get_instance( m_verbosity, __FILE__, __FUNCTION__, __LINE__ )
#define mFatal   CmdLnManager::kFatal
#define mError   CmdLnManager::kError
#define mWarning CmdLnManager::kWarning
#define mInfo    CmdLnManager::kInfo
#define mDebug   CmdLnManager::kDebug

class CmdLnManager : private std::ostream {
public:
    enum VerbosityLevel {
        kFatal = 0,
        kError    ,
        kWarning  ,
        kInfo     ,
        kDebug
    };
    static const std::map< VerbosityLevel, std::string > m_verbosity_map;
    static void set_verbosity( int t_verbosity ) { m_verbosity = t_verbosity; }

private:
    static int m_verbosity;

    // Temporary variables for output
    int         m_message_verbosity;
    std::string m_message_file;
    std::string m_message_function;
    int         m_message_line;

private:
    CmdLnManager();
    static std::shared_ptr< CmdLnManager > m_instance;

public:
    static CmdLnManager& get_instance( const int         t_message_verbosity     ,
                                                         const std::string t_message_file      = "",
                                                         const std::string t_message_function  = "",
                                                         const int         t_message_line      = -1 ) {
        // Check if instance exists
        if( m_instance == nullptr ) {
            m_instance = std::make_shared< CmdLnManager >();
        }

        // Set temporary variables
        m_instance->m_message_verbosity = t_message_verbosity;
        m_instance->m_message_file      = t_message_file;
        m_instance->m_message_function  = t_message_function;
        m_instance->m_message_line      = t_message_line;

        return *m_instance;
    }

    // Define << operator for output
    template< typename T >
    CmdLnManager& operator<<( const T& t_message ) {
        if( m_message_verbosity > m_verbosity ) {
            goto end;
        }

        // Output message without file and function information
        if( m_message_file == "" ) {
            std::cout << m_verbosity_map.at( static_cast< VerbosityLevel >( m_message_verbosity ) )
                      << " || " << t_message
                      << std::endl;
            goto end;
        }

        // Output message normally
        std::cout <<           m_verbosity_map.at( static_cast< VerbosityLevel >( m_message_verbosity ) )
                  << " || " << m_message_file
                  << "::"   << m_message_function
                  << " ("   << m_message_line 
                  << "): "  << t_message 
                  << std::endl;

        end:
        // Reset temporary variables
        m_message_verbosity = -1;
        m_message_file      = "";
        m_message_function  = "";
        m_message_line      = -1;

        return *this;
    }

};

const std::map< CmdLnManager::VerbosityLevel, std::string > CmdLnManager::m_verbosity_map = {
    { CmdLnManager::kFatal  , "FATAL"   },
    { CmdLnManager::kError  , "ERROR"   },
    { CmdLnManager::kWarning, "WARNING" },
    { CmdLnManager::kInfo   , "INFO"    },
    { CmdLnManager::kDebug  , "DEBUG"   }
};

#endif // CMDLNMANAGER_HPP