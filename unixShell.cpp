/*
 * This is a sample of code from a project I worked on in
 * my Systems Programming course. Please note that this code
 * will not compile or run becasue it is only code samples.
 */

/*
 * This code is called if the input is cd
 */
int test;
if(myArgc > 1)
{
  const char* directory = myArgv[1].c_str();
  test = chdir(directory);
  if (test == -1)
    cout << "-1730sh: cd: " << myArgv[1] << ": No such file or directory" << endl;
}
else
{
  const char* directory = homeDirectory.c_str();
  test = chdir(directory);
  if (test == -1)
    cout << "error changing to home directory" << endl;
}

/*
 * This function is used to redirect standard input, output, and error
 */
bool ioRedirCheck(int &i, string *myArgv)
{
  bool changed = false;
  if (myArgv[i].compare(">") == 0 || myArgv[i].compare(">&") == 0)
  {
    // Redirect Standard Output truncate
    const char* file = myArgv[i+1].c_str();
    int fd = open(file, O_WRONLY|O_TRUNC);
    if (fd == -1)
      perror("open");
    close(STDOUT_FILENO);
    if (dup(fd) == -1)
      perror("dup");
    i += 2;
    close(fd);
    changed = true;
  }
  if (myArgv[i].compare("e>") == 0 || myArgv[i].compare(">&") == 0)
  {
    // Redirect Standard Error truncate
    const char* file = myArgv[i+1].c_str();
    int fd = open(file, O_WRONLY|O_TRUNC);
    if (fd == -1)
      perror("open");
    close(STDERR_FILENO);
    if (dup(fd) == -1)
      perror("dup");
    i += 2;
    close(fd);
    changed= true;
  }
  if (myArgv[i].compare("<") == 0)
  {
    // Redirect Standard Input
    const char* file = myArgv[i+1].c_str();
    int fd = open(file, O_RDONLY);
    if (fd == -1)
      perror("open");
    close(STDIN_FILENO);
    if (dup(fd) == -1)
      perror("dup");
    i += 2;
    close(fd);
    changed= true;
  }
  if (myArgv[i].compare(">>") == 0 || myArgv[i].compare(">>&") == 0)
  {
    // Redirect Standard Output append
    const char* file = myArgv[i+1].c_str();
    int fd = open(file, O_WRONLY|O_APPEND);
    if (fd == -1)
      perror("open");
    close(STDOUT_FILENO);
    if (dup(fd) == -1)
      perror("dup");
    i += 2;
    close(fd);
    changed= true;
  }
  if (myArgv[i].compare("e>>") == 0 || myArgv[i].compare(">>&") == 0)
  {
    // Redirect Standard Error append
    const char* file = myArgv[i+1].c_str();
    int fd = open(file, O_WRONLY|O_APPEND);
    if (fd == -1)
      perror("open");
    close(STDERR_FILENO);
    if (dup(fd) == -1)
      perror("dup");
    i += 2;
    close(fd);
    changed= true;
  }
  return changed;
}
