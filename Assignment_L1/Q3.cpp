#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>


/**
 * @brief Convert String to Number
 */
template <typename TP>
TP str2num( std::string const& value ){

    std::stringstream sin;
    sin << value;
    TP output;
    sin >> output;
    return output;
}


/**
 * @brief Convert number to string
 */
template <typename TP>
std::string num2str( TP const& value ){
    std::stringstream sin;
    sin << value;
    return sin.str();
}


/**
 * @brief Execute Generic Shell Command
 *
 * @param[in]   command Command to execute.
 * @param[out]  output  Shell output.
 * @param[in]   mode read/write access
 *
 * @return 0 for success, 1 otherwise.
 *
*/
int Execute_Command( const std::string&  command,
                     std::string&        output,
                     const std::string&  mode = "r")
{
    // Create the stringstream
    std::stringstream sout;

    // Run Popen
    FILE *in;
    char buff[512];

    // Test output
    if(!(in = popen(command.c_str(), mode.c_str()))){
        return 1;
    }

    // Parse output
    while(fgets(buff, sizeof(buff), in)!=NULL){
        sout << buff;
    }

    // Close
    int exit_code = pclose(in);

    // set output
    output = sout.str();

    // Return exit code
    return exit_code;
}


/**
 * @brief Ping
 *
 * @param[in] address Address to ping.
 * @param[in] max_attempts Number of attempts to try and ping.
 * @param[out] details Details of failure if one occurs.
 *
 * @return True if responsive, false otherwise.
 *
 * @note { I am redirecting stderr to stdout.  I would recommend 
 *         capturing this information separately.}
 */
bool Ping( const std::string& address,
           const int&         max_attempts,
           std::string&       details )
{
    // Format a command string
    std::string command = "ping -c " + num2str(max_attempts) + " " + address + " 2>&1";
    std::string output;

    // Execute the ping command
    int code = Execute_Command( command, details );

    return (code == 0);
}


/**
 * @brief Main Function
 */
int main( int argc, char* argv[] )
{
    // Parse input
    if( argc < 2 ){
        std::cerr << "usage: " << argv[0] << " <address> <max-attempts = 3>" << std::endl;
        return 1;
    }

    // Get the address
    std::string host = argv[1];

    // Get the max attempts
    int max_attempts = 1;
    if( argc > 2 ){
        max_attempts = str2num<int>(argv[2]);
    }
    if( max_attempts < 1 ){
        std::cerr << "max-attempts must be > 0" << std::endl;
        return 1;
    }

    // Execute the command
    std::string details;
    bool result = Ping( host, max_attempts, details );

    // Print the result
    std::cout << host << " ";
    if( result == true ){
        std::cout << " is responding." << std::endl;
    }
    else{
        std::cout << " is not responding.  Cause: " << details << std::endl;
    }

    return 0;
}