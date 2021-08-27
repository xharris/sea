#include "fs.h"

std::vector<std::string> Fs::listDir(const char *path)
{
  int count;
  char** files = GetDirectoryFiles(path, &count);
  std::vector<std::string> ret;

  for (int f = 0; f < count; f++) 
  {
    ret.push_back(files[f]);
  }

  // DIR *dir;
  // struct dirent *ent;
  // if ((dir = opendir(path)) != NULL)
  // {
  //   while ((ent = readdir(dir)) != NULL)
  //   {
  //     if (strcmp(ent->d_name, ".") * strcmp(ent->d_name, "..") != 0)
  //     {
  //       ret.push_back(ent->d_name);
  //     }
  //   }
  //   closedir(dir);
  // } else TraceLog(LOG_WARNING, "FILEIO: Failed to open requested directory");
  return ret;
}

bool Fs::isFile(const char *path)
{
  return FileExists(path) && !DirectoryExists(path);
}

bool Fs::isDirectory(const char *path)
{
  return DirectoryExists(path);
}

const char * Fs::getCwd()
{
  return GetWorkingDirectory();
}

bool Fs::cd(const char* dir)
{
  return ChangeDirectory(dir);
}