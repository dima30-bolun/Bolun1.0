#ifndef BOLUN_CORE_H
#define BOLUN_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

long long bolun_c_add(long long left, long long right);
long long bolun_asm_add(long long left, long long right);
const char *bolun_language_policy(void);

#ifdef __cplusplus
}
#endif

#endif
