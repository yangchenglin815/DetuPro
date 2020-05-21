#ifndef STR_UTILS_H
#define STR_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif
int strUtils_startsWith(const char *full, const char *prefix);
int strUtils_strsplit(const char *str, char *parts[], const char *delimiter);
const char* strUtils_hasPrefix(const char* str, const char* prefix);


#ifdef __cplusplus
}
#endif
#endif //STR_UTILS_H