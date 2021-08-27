#ifndef FS_H
#define FS_H

#include "raylib.hpp"
#include <string.h>
// #include "dirent.h"
#include <vector>
#include <map>

class Fs 
{
  public:

  static std::vector<std::string> listDir(const char *path);
  static bool isFile(const char *path);
  static bool isDirectory(const char *path);
  static const char * getCwd();
  static bool cd(const char* dir);
};

#endif