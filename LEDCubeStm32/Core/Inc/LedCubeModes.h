/*
 * LedCubeModes.h
 *
 *  Created on: Jun 17, 2024
 *      Author: Justyna
 */

#ifndef LEDCUBEMODES_H_
#define LEDCUBEMODES_H_
#include "main.h"

// Function declarations
void disableAllPins(void);
void enableAllPins(void);
void turnColumnsOff(void);
void flickerOn(void);
void turnOnAndOffAllByLayerUpAndDownNotTimed(void);
void turnOnAndOffAllByColumnSideways(void);
void layerstompUpAndDown(void);
void flickerOff(void);
void aroundEdgeDown(void);
void diagonalRectangle(void);
void propeller(void);
void spiralInAndOut(void);
void goThroughAllLedsOneAtATime(void);



#endif /* LEDCUBEMODES_H_ */
