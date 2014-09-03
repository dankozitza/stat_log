
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef intptr_t intgo;

struct __go_string {
	const unsigned char *__data;
	intgo __length;
};

typedef struct __go_open_array {
	void* __values;
	intgo __count;
	intgo __capacity;
} Slice;

struct __go_string __go_byte_array_to_string(const void* p, intgo len);
struct __go_open_array __go_string_to_byte_array (struct __go_string str);

const char *_cgo_1f0ede5af0db_Cfunc_CString(struct __go_string s) {
	char *p = malloc(s.__length+1);
	memmove(p, s.__data, s.__length);
	p[s.__length] = 0;
	return p;
}

struct __go_string _cgo_1f0ede5af0db_Cfunc_GoString(char *p) {
	intgo len = (p != NULL) ? strlen(p) : 0;
	return __go_byte_array_to_string(p, len);
}

struct __go_string _cgo_1f0ede5af0db_Cfunc_GoStringN(char *p, int32_t n) {
	return __go_byte_array_to_string(p, n);
}

Slice _cgo_1f0ede5af0db_Cfunc_GoBytes(char *p, int32_t n) {
	struct __go_string s = { (const unsigned char *)p, n };
	return __go_string_to_byte_array(s);
}

extern void runtime_throw(const char *);
void *_cgo_1f0ede5af0db_Cfunc__CMalloc(size_t n) {
        void *p = malloc(n);
        if(p == NULL && n == 0)
                p = malloc(1);
        if(p == NULL)
                runtime_throw("runtime: C malloc failed");
        return p;
}

