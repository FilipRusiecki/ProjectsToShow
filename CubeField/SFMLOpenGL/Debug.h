//Undefine DEBUG
#ifdef DEBUG
#undef DEBUG
#endif
//Define DEBUG 1 or 2 for greater level of debug messages
#define DEBUG 1
//MACRO for streaming DEBUG
#if defined DEBUG
#if (DEBUG >= 1)
#define DEBUG_MSG(x) (std::cout << (x) << std::endl)
#else
#define DEBUG_MSG(x)
#endif
#else
#define DEBUG_MSG(x)
#endif