#ifndef OSCHECK_H
#define OSCHECK_H

/**
 * Determinar la plataforma de compilación del sistema operativo.
 * 
 * Salidas:
 * - Windows: WIN_C
 * - Linux like: LIN_C
 * - MacOS like: MAC_C
 * - No soportado: LIN_C
 * 
 * Información de marcos obtenida de:
 * https://sourceforge.net/p/predef/wiki/OperatingSystems/
*/

#if defined(_WIN32) || defined(_WIN64)
    #define WIN_C
#elif defined(__CYGWIN__) && (!defined(_WIN32) && !defined(_WIN64))
    #define WIN_C
#elif defined(__linux__)
    #define LIN_C
#elif defined(__APPLE__) && defined(__MACH__) && TARGET_OS_MAC == 1
    #define MAC_C
#else
    #warning "Not supported compiler: selected linux compilation."
    #define LIN_C
#endif

#endif
