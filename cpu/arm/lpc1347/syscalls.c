#include <sys/stat.h>
#include "LPC13Uxx.h"
//#include "stm32f4xx_conf.h"
//#include "usbd_cdc_vcp.h"
#include "contiki-conf.h"
//#include "debug-buffer.h"

//ds
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

int __errno;

int _close(int file) {
	return 0;
}

int _fstat(int file, struct stat *st) {
	return 0;
}

int _isatty(int file) {
	return 1;
}

int _lseek(int file, int ptr, int dir) {
	return 0;
}

int _open(const char *name, int flags, int mode) {
	return -1;
}

int _read(int file, char *ptr, int len) {
	if (file != 0) {
		return 0;
	}

	// Use USB CDC Port for stdin
	//while(!VCP_get_char((uint8_t*)ptr)){};

	// Echo typed characters
	//VCP_put_char((uint8_t)*ptr);

	return 1;
}

// Register name faking - works in collusion with the linker.
register char * stack_ptr asm ("sp");

/*caddr_t _sbrk_r (struct _reent *r, int incr) {
	extern char   end asm ("end"); // Defined by the linker.
	static char * heap_end;
	char *        prev_heap_end;

	if (heap_end == NULL)
		heap_end = & end;

	prev_heap_end = heap_end;

	if (heap_end + incr > stack_ptr) {
		//errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}
*/

caddr_t
_sbrk(int incr)
{
	return 0;
}


int _write(int file, char *ptr, int len) {
#if PRINTF_VCP
	VCP_send_buffer((uint8_t*)ptr, len);
	return len;
#else
	//debug_buffer_append(ptr, len);
	return len;
#endif
}


// ds
int _gettimeofday (struct timeval * tp, struct timezone * tzp)
{

  if (tp)
    {
      tp->tv_sec = 0;
      tp->tv_usec = 0;
    }

  /* Return fixed data for the timezone.  */
  if (tzp)
    {
      tzp->tz_minuteswest = 0;
      tzp->tz_dsttime = 0;
    }

  return 0;
}

