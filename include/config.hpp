#pragma once

#define BLOCK_SIZE 28 // 16 Bytes needed for the header
#define BLOCK_NUM 512
#define DEBUG true
#define LOG false

// Uncomment only one of the following
// #define FIRST_FIT
#define NEXT_FIT

// Experimental
#define ENABLE_EXPERIMENTAL_COMPACTION false