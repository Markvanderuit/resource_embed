/*
 * MIT License
 *
 * Copyright (c) 2021 Mark van de Ruit
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace rsrc {
  // Map in which resource's strings are stored during CMake config/generate
  const extern std::unordered_map<std::string,std::string> __RSRC_MAP__;
  
  /**
   * exists(key)
   * 
   * Check whether a resource exists for the given key.
   * 
   * @param key - key matching a specific resource
   * @return boolean result
   */
  inline
  bool exists(const std::string& key) {
    return __RSRC_MAP__.find(key) != __RSRC_MAP__.end();
  }

  /**
   * get(key)
   * 
   * Obtain a resource's stored string for a given key.
   * 
   * @param key - key matching a specific resource
   * @throws invalid_argument if a resource does not exist for a specific key
   * @return obtained resource as a (multiline) string
   */
  inline
  const std::string& get(const std::string& key) {
    if (__RSRC_MAP__.find(key) == __RSRC_MAP__.end()) {
      throw std::invalid_argument("Resource does not exist: " + key);
    }
    return __RSRC_MAP__.at(key);
  }
} // rsrc