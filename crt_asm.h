#ifndef CRT_ASM_H
#define CRT_ASM_H

#define CALL_SP(addr) \
    asm volatile("mov %%rsp, %%rdi; call *%%rax;" : : "a"(addr));

#define FIX_SP_JMP(stack, addr) \
    asm volatile("xchg %%rsp, %0; jmp *%%rax;" : "=r"(stack) : "0"(stack), "a"(addr));

#define INJ_ENTRY(func) \
    asm volatile("nop; nop; call " #func "; int3;");

#endif
