#ifndef CRT_ASM_H
#define CRT_ASM_H

#define CALL_SP(addr) \
    asm volatile("mov %%rsp, %%rdi; call *%%rax;" : : "a"(addr))

#define FIX_SP_JMP(stack, addr, arg) \
    asm volatile("mov %0, %%rsp; mov %1, %%rdi; jmp *%2;" :: "m"(stack), "r"(arg), "a"(addr))

#define INJ_ENTRY(func) \
    asm volatile("nop; nop; call " #func "; int3;")

#endif
