#ifndef RPC_EXPORT_H  
#define RPC_EXPORT_H  

#include "kvpService.h"

#ifdef Kvp_API  
#define Kvp_API _declspec(dllexport)  
#else  
#define Kvp_API _declspec(dllimport)  
#endif  

#endif  