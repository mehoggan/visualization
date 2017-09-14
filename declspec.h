#if defined (WIN32) || defined (_WIN32) || defined (__WIN32__) || \
  defined(__CYGWIN__) || defined(__MINGW32__)
  #if defined(COM_VISUALIZATION_SHARED)
      #if defined(COM_VISUALIZATION_EXPORTS)
          #define DLLSPEC_COM_VISUALIZATION __declspec(dllexport)
      #else
          #define DLLSPEC_COM_VISUALIZATION __declspec(dllimport)
      #endif
  #elif defined(COM_VISUALIZATION_STATIC)
      #define DLLSPEC_COM_VISUALIZATION
  #else
      #define DLLSPEC_COM_VISUALIZATION
  #endif
  #define OGLAPI __declspec(dllimport)
  #include <stdint.h>
  #ifndef OGLAPIENTRY
  #  define OGLAPIENTRY __stdcall
  #endif
#else
  #define DLLSPEC_COM_VISUALIZATION
  #define OGLAPI extern
  #ifndef OGLAPIENTRY
  #  define OGLAPIENTRY
  #endif
#endif
