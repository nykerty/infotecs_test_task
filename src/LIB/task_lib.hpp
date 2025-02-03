#pragma once

#ifdef _WIN32 
    #ifdef TASK_LIB
        #define TASK_LIB_API __declspec(dllexport) 
    #else
        #define TASK_LIB_API __declspec(dllimport) 
    #endif
#else 
    #define TASK_LIB_API 
#endif

extern "C" {
    TASK_LIB_API void inputProcess(char* input_data);
    TASK_LIB_API int sumDigits(char* input_data);
    TASK_LIB_API bool checkNumber(int sum);
}