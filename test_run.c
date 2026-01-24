#include "run_commands.h"

int main()
{
  char **args={"/bin/echo", "this is a test"};
  run_command(2, args);
  return 0;
}
