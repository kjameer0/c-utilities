#ifndef RUN_COMMANDS_H
#define RUN_COMMANDS_H

/* Standard library includes (only what the header requires) */
#include <stddef.h>

/* Macro definitions */
#define MAX_ARGS 10
#define MAX_ARG_SIZE 256
/* Type definitions */
typedef enum {
  SUCCESS,
  FAILURE,
} RunCommandStatus;
typedef struct {
  RunCommandStatus result;
  const char *message;
} RunCommandResult;

/* Function declarations */
RunCommandResult run_command(size_t arg_count, char (*args)[arg_count]);
#endif /* RUN_COMMANDS_H */
