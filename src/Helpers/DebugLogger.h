#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>

class DebugLogger
{
public:
    // Constructor to initialize the log file name
    DebugLogger(const std::string& filename = "../DebugLogs/debug_log.txt")
        : m_filename(filename)
    {
        // Open the log file in append mode
        m_logFile.open(m_filename, std::ios::app);

        if (!m_logFile.is_open())
        {
            std::cerr << "Failed to open log file: " << m_filename << std::endl;
        }
    }

    // Destructor to ensure the file is properly closed
    ~DebugLogger()
    {
        if (m_logFile.is_open())
        {
            m_logFile.close();
        }
    }

    // Log a message to the file
    void Log(const std::string& message)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // Ensures thread-safety

        if (m_logFile.is_open())
        {
            m_logFile << message << std::endl;
        }
    }

    // Log a formatted message to the file
    template <typename... Args>
    void Log(const std::string& format, Args... args)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // Ensures thread-safety

        if (m_logFile.is_open())
        {
            m_logFile << FormatString(format, args...) << std::endl;
        }
    }

private:
    // Helper function to format the string
    template <typename... Args>
    std::string FormatString(const std::string& format, Args... args)
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Calculate required buffer size
        std::unique_ptr<char[]> buffer(new char[size]);

        snprintf(buffer.get(), size, format.c_str(), args...); // Format the string
        return std::string(buffer.get(), buffer.get() + size - 1); // Return formatted string
    }

    std::string m_filename;  // Log file name
    std::ofstream m_logFile;  // Output file stream
    std::mutex m_mutex;       // Mutex for thread-safety
};

#endif  // DEBUG_LOGGER_H
