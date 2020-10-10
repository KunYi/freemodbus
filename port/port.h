#ifndef _MBED_PORT_FREEMODBUF_H_
#define _MBED_PORT_FREEMODBUF_H_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#define PR_BEGIN_EXTERN_C   extern "C" {
#define PR_END_EXTERN_C     }

typedef unsigned char   UCHAR;
typedef char            CHAR;
typedef uint16_t        USHORT;
typedef uint32_t        ULONG;

typedef uint8_t         BOOL;
#ifndef TRUE 
#define TRUE (1)
#endif
 
#ifndef FALSE
#define FALSE (0)
#endif

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#define ENTER_CRITICAL_SECTION  vMBPortEnterCritical
#define EXIT_CRITICAL_SECTION   vMBPortExitCritical
void vMBPortEnterCritical(void);
void vMBPortExitCritical(void);

#ifdef __cplusplus
PR_END_EXTERN_C
#endif

#endif /* end of  _MBED_PORT_FREEMODBUF_H_ */