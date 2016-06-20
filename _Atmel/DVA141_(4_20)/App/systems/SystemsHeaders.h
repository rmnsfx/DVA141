/*
 * SystemsHeaders.h
 *
 *  Created on: 3 окт. 2015 г.
 *      Author: andrei
 */

#ifndef SYSTEMSHEADERS_H_
#define SYSTEMSHEADERS_H_
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
//#include <stdlib.h>
//

#include <asf.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h" 



#define SYSTEMS_MINIMAL_STACK_SIZE ( configMINIMAL_STACK_SIZE )
#define NO_TRHEAD_ID (NULL)
typedef TaskHandle_t os_tid_t;

#endif /* SYSTEMSHEADERS_H_ */
