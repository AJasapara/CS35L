#include "randcpuid.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
        perror (argv[1]);
      else
        valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  unsigned long long (*rand64) (void);
  void* dl;

  if (rdrand_supported ())
    {
      dl = dlopen("randlibhw.so", RTLD_LAZY);
      if (!dl) {
        printf("ERROR: could not open randlibhw.so: %s\n", dlerror());
        exit(1);
      }
      rand64 = dlsym(dl, "hardware_rand64");
      if(dlerror())
      {
        printf("ERROR: could not locate hardware_rand64: %s\n", dlerror());
        exit(1);
      }
    }
  else
    {
      dl = dlopen("randlibsw.so", RTLD_LAZY);
      if (!dl) {
        printf("ERROR: could not open randlibsw.so: %s\n", dlerror());
        exit(1);
      }
      rand64 = dlsym(dl, "software_rand64");
      if(dlerror())
      {
        printf("ERROR: could not locate software_rand64: %s\n", dlerror());
        exit(1);
      }
    }

  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (fwrite (&x, 1, outbytes, stdout) != outbytes)
      {
        output_errno = errno;
        break;
      }
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      return 1;
    }

  if (dlclose(dl)) {
    printf("ERROR: could not close dlhandle: %s\n", dlerror());
    exit(1);
  }
  return 0;
}