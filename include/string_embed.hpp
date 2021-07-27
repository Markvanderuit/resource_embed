#pragma once

/**
 * Specify an extern const char* to reference an embedded resource file.
 * args:
 * - rsrcName: name of embedded resource file.
 * ret:
 * - void
 */
#define EMBED_RSRC(rsrcName)\
  extern const char* rsrcName

/**
 * Return a resource from an embedded const char pointer.
 * args:
 * - rsrcName: name of embedded resource file.
 * ret:
 * - a const char ptr. to the embedded resource.
 */
#define EXTERN_RSRC(rsrcName)\
  []() -> const char* {\
    embedRsrc(rsrcName);\
    return rsrc;\
  }()