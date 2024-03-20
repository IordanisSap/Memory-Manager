#pragma once
#include <iostream>

#define throw_invalid_index_error(msg, block_size, size, offset) throw_error(invalid_index_error, __FILE__, __LINE__, msg, block_size, size, offset)
#define throw_invalid_block_error() throw_error(invalid_block_error, __FILE__, __LINE__)

template<typename Func, typename... Args>
inline void throw_error(Func func,const char* file, long line, Args&&... args) {
    std::cerr << "Error in file " << file << " at line " << line << ": ";
    func(std::forward<Args>(args)...);
}



inline void out_of_memory_error()
{
    std::cerr << "Out of memory" << std::endl;
}
inline void invalid_block_error()
{
    throw std::runtime_error("Invalid block address");
}

inline void invalid_index_error(void *ptr, size_t block_size, size_t sizeOfObj, size_t offset)
{
    throw std::runtime_error("Invalid block offset " + std::to_string(offset) +
                             "(" + std::to_string(offset * sizeOfObj) + " bytes)" + " for block with size " +
                             std::to_string(block_size / sizeOfObj) + "(" + std::to_string(block_size) + ") bytes.");
}
