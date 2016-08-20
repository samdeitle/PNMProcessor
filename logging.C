/*
 * logging.C
 *
 *  Created on: May 27, 2014
 *      Author: Slammy
 */
#include "logging.h"
#include <string.h>
FILE *Logger::logger = fopen("logger", "w");

DataFlowException::DataFlowException(const char *type, const char *error)
{sprintf(msg, "%s---%s", type, error);}

void Logger::LogEvent(const char *event)
{fwrite(event, 1, strlen(event), logger);}

void Logger::Finalize()
{fclose(logger);}
