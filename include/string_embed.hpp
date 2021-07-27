#pragma once

/**
 * Specify an extern const char* to reference an embedded resource file as string.
 * args:
 * - rsrcName: name of embedded resource file.
 * ret:
 * - void
 */
#define EMBED_STR(rsrcName)\
  extern const char* rsrcName

/**
 * Return a string from an embedded const char pointer referencing a resource file as string.
 * args:
 * - rsrcName: name of embedded resource file.
 * ret:
 * - a const char ptr. to the embedded resource.
 */
#define EXTERN_STR(rsrcName)\
  []() -> const char* {\
    embedRsrc(rsrcName);\
    return rsrc;\
  }()