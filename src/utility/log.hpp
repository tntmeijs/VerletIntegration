#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

#define LOG_ERROR(msg)  std::cerr << "[ERROR:   ] " << __FILE__ << "(" << __LINE__ << ") " << msg << std::endl;
#define LOG_FATAL(msg)  std::cerr << "[FATAL:   ] " << __FILE__ << "(" << __LINE__ << ") " << msg << std::endl;
#define LOG_WARN(msg)   std::cout << "[WARNING: ] " << __FILE__ << "(" << __LINE__ << ") " << msg << std::endl;
#define LOG_INFO(msg)   std::cout << "[INFO:    ] " << msg << std::endl;

#endif //! LOG_HPP
