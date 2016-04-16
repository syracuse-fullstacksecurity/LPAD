#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */

#include <string.h>
#include <sgx_cpuid.h>

#include "sgx_trts.h"
#include "Enclave.h"
#include "Enclave_t.h"  /* bar*/



/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
void bar1(const char *fmt, ...)
{
  char buf[BUFSIZ] = {'\0'};
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, BUFSIZ, fmt, ap);
  va_end(ap);
  ocall_bar(buf);
}

/* ecall_foo:
 *   Uses malloc/free to allocate/free trusted memory.
 */
extern void EnclCompact(int* input1, int* input2, int* output);
int ecall_foo(int* input1,int* input2,int* output)
{
  EnclCompact(input1, input2, output);
  bar1("haha\n");
  return 3;
}

/* ecall_sgx_cpuid:
 *   Uses sgx_cpuid to get CPU features and types.
 */
void ecall_sgx_cpuid(int cpuinfo[4], int leaf)
{
  sgx_status_t ret = sgx_cpuid(cpuinfo, leaf);
  if (ret != SGX_SUCCESS)
    abort();
}
