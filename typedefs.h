// Signed typedefs
typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;

// Unsigned typedefs
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

// Signed typedefs limits
#define INT8_MIN    -0x7f - 1
#define INT8_MAX    0x7f 
#define INT16_MIN   -0x7fff - 1
#define INT16_MAX   0x7fff 
#define INT32_MIN   -0x7fffffff - 1
#define INT32_MAX   0x7fffffff 
#define INT64_MIN   -0x7fffffffffffffff - 1
#define INT64_MAX   0x7fffffffffffffff 

// Unsigned typedefs limits
#define UINT8_MAX   0xff 
#define UINT16_MAX  0xffff 
#define UINT32_MAX  0xffffffff 
#define UINT64_MAX  0xffffffffffffffff 