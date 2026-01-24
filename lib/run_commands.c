// take an array of args as input and run a command
#include "run_commands.h"
#include <unistd.h>
#include <stdio.h>

RunCommandResult run_command(size_t arg_count, char (*args)[arg_count])
{
  RunCommandResult res;
  if (arg_count > MAX_ARGS)
  {
    res.message = "Too many Args";
    return res;
  }
  for (int i = 0; i < arg_count; i++)
  {
    char *cur = (*args)[i];
    printf("%s\n", cur);
  }
  execv(args[0], &args[1]);
}
