#pragma once

#include <string>

/**
 * RSRC_REF(rsrc)
 * 
 * Define an extern-const-char-ptr matching an embedded resource file.
 * 
 * @author M. van de Ruit
 * 
 * @param rsrc - name of embedded resource file
 */
#define RSRC_REF(rsrc)\
  extern const char* rsrc

/**
 * RSRC_EMBED(rsrc)
 * 
 * Return a string matching an extern-const-char-ptr matching an embedded resource file.
 * 
 * @author M. van de Ruit
 * 
 * @param rsrc - name of embedded resource file
 * @return string object with embedded resource
 */
#define RSRC_EMBED(rsrc)\
  []() -> std::string {\
    RSRC_REF(rsrc);\
    return std::string(rsrc);\
  }()
  
/**
 * RSRC_EMBED_C(rsrc)
 * 
 * Return a char pointer matching an extern-const-char-ptr matching an embedded resource file.
 * 
 * @author M. van de Ruit
 * 
 * @param rsrc - name of embedded resource file
 * @return char pointer with embedded resource
 */
#define RSRC_EMBED_C(rsrc)\
  []() -> const char* {\
    RSRC_REF(rsrc);\
    return rsrc;\
  }()