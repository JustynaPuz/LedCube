/*
 * LedCubeModes.c
 *
 *  Created on: Jun 17, 2024
 *      Author: Justyna
 */
#include "LedCubeModes.h"


typedef struct {
    const char* name;
    GPIO_TypeDef* port;
    uint16_t pin;
} PinMap;
PinMap pinMap[] = {
    {"PIN11", PIN11_GPIO_Port, PIN11_Pin},
    {"PIN12", PIN12_GPIO_Port, PIN12_Pin},
    {"PIN13", PIN13_GPIO_Port, PIN13_Pin},
    {"PIN14", PIN14_GPIO_Port, PIN14_Pin},
    {"PIN21", PIN21_GPIO_Port, PIN21_Pin},
    {"PIN22", PIN22_GPIO_Port, PIN22_Pin},
    {"PIN23", PIN23_GPIO_Port, PIN23_Pin},
    {"PIN24", PIN24_GPIO_Port, PIN24_Pin},
    {"PIN31", PIN31_GPIO_Port, PIN31_Pin},
    {"PIN32", PIN32_GPIO_Port, PIN32_Pin},
    {"PIN33", PIN33_GPIO_Port, PIN33_Pin},
    {"PIN34", PIN34_GPIO_Port, PIN34_Pin},
    {"PIN41", PIN41_GPIO_Port, PIN41_Pin},
    {"PIN42", PIN42_GPIO_Port, PIN42_Pin},
    {"PIN43", PIN43_GPIO_Port, PIN43_Pin},
    {"PIN44", PIN44_GPIO_Port, PIN44_Pin},
};
PinMap layers[] ={
		{"LAYER1", LAYER1_GPIO_Port, LAYER1_Pin},
		{"LAYER2", LAYER2_GPIO_Port, LAYER2_Pin},
		{"LAYER3", LAYER3_GPIO_Port, LAYER3_Pin},
		{"LAYER4", LAYER4_GPIO_Port, LAYER4_Pin}};
int mapSize = sizeof(pinMap) / sizeof(PinMap);
int layersSize = sizeof(layers) / sizeof(PinMap);

PinMap* findPinMap(const char* name) {
    for (int i = 0; i < sizeof(pinMap) / sizeof(PinMap); i++) {
        if (strcmp(name, pinMap[i].name) == 0) {
            return &pinMap[i];
        }
    }
    return NULL;
}
//flicker on
void flickerOn()
{
  int i = 150;
  while(i != 0)
  {
    enableAllPins();
    HAL_Delay(i);
    disableAllPins();
    HAL_Delay(i);
    i-= 5;
  }
}


void disableAllPins() {
    for (int i = 0; i < mapSize; i++) {
        HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    }

    for(int i = 0; i < layersSize; i++) {
    	HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_RESET);
    }
}

void enableAllPins() {
    for (int i = 0; i < mapSize; i++) {
        HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }

    for(int i = 0; i < layersSize; i++) {
    	HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_SET);
    }
}
//turn columns off
void turnColumnsOff() {

	for (int i = 0; i < mapSize; i++) {
	        HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
	    }

}


void turnOnAndOffAllByLayerUpAndDownNotTimed()
{
  int x = 75;
  for(int i = 5; i != 0; i--)
  {
    enableAllPins();
    for(int i = layersSize; i!=0; i--)
    {
    	HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    for(int i = 0; i< layersSize; i++)
    {
    	HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_SET);
    	    	HAL_Delay(x);
    }
      for(int i = 0; i<layersSize; i++)
    {
    	  HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_RESET);
    	      	    	HAL_Delay(x);
    }
    for(int i = layersSize; i!=0; i--)
    {
    	HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_SET);
    	    	HAL_Delay(x);
    }
  }
}

//turn everything on and off by column sideways
void turnOnAndOffAllByColumnSideways()
{
  int x = 75;
  disableAllPins();
  //turn on layers
  for(int i = 0; i<layersSize; i++)
  {
	  HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_SET);
  }
  for(int y = 0; y<3; y++)
  {
    //turn on 0-3
    for(int i = 0; i<4; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    //turn on 4-7
    for(int i = 4; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    //turn on 8-11
    for(int i = 8; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    //turn on 12-15
    for(int i = 12; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    //turn off 0-3
    for(int i = 0; i<4; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	HAL_Delay(x);
    }
    //turn off 4-7
    for(int i = 4; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	HAL_Delay(x);
    }
    //turn off 8-11
    for(int i = 8; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	HAL_Delay(x);
    }
    //turn off 12-15
    for(int i = 12; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	HAL_Delay(x);
    }
    //turn on 12-15
    for(int i = 12; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
    //turn on 8-11
    for(int i = 8; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	    	HAL_Delay(x);
    }
    //turn on 4-7
    for(int i = 4; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	    	HAL_Delay(x);
    }
    //turn on 0-3
    for(int i = 0; i<4; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	    	HAL_Delay(x);
    }
    //turn off 12-15
    for(int i = 12; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	    	HAL_Delay(x);
    }
    //turn off 8-11
    for(int i = 8; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	    	    	HAL_Delay(x);
    }
    //turn off 4-7
    for(int i = 4; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	    	    	HAL_Delay(x);
    }
    //turn off 0-3
    for(int i = 0; i<4; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	    	    	HAL_Delay(x);
    }
  }
}

//up and down single layer stomp
void layerstompUpAndDown()
{
  int x = 75;
  for(int i = 0; i<4; i++)
  {
	  HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_RESET);
  }
  for(int y = 0; y<5; y++)
  {
    for(int count = 0; count<1; count++)
    {
      for(int i = 0; i<4; i++)
      {
    	  HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_SET);
    	  HAL_Delay(x);
          HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_RESET);
      }
      for(int i = 4; i !=0; i--)
      {
    	  HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_SET);
    	  HAL_Delay(x);
    	  HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_RESET);
      }
    }
    for(int i = 0; i<4; i++)
    {
    	HAL_GPIO_WritePin(layers[i].port, layers[i].pin, GPIO_PIN_SET);
    	HAL_Delay(x);
    }
    for(int i = 4; i!=0; i--)
    {
    	HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);
    }
  }
}

//flicker off
void flickerOff()
{
  enableAllPins();
  for(int i = 0; i!= 150; i+=5)
  {
    disableAllPins();
    HAL_Delay(i+50);
    enableAllPins();
    HAL_Delay(i);
  }
}
//around edge of the cube down
void aroundEdgeDown()
{
  for(int x = 200; x != 0; x -=50)
  {
    disableAllPins();
    for(int i = 4; i != 0; i--)
    {
    	HAL_GPIO_WritePin(layers[i-1].port, layers[i-1].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);

    	HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_RESET);
    	HAL_Delay(x);

    	HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_SET);
    }
  }
}

//diagonal rectangle
void diagonalRectangle()
{
  int x = 350;
  disableAllPins();
  for(int count = 0; count<5; count++)
  {
    //top left
    for(int i = 0; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);

    }
    HAL_GPIO_WritePin(layers[3].port, layers[3].pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);
    HAL_Delay(x);

    disableAllPins();
    //middle middle
    for(int i = 4; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[1].port, layers[1].pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);

    HAL_Delay(x);

    disableAllPins();
    //bottom right
    for(int i = 8; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[0].port, layers[0].pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(layers[1].port, layers[1].pin, GPIO_PIN_SET);
    HAL_Delay(x);

    disableAllPins();
    //bottom middle
    for(int i = 4; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[0].port, layers[0].pin, GPIO_PIN_SET);
       HAL_GPIO_WritePin(layers[1].port, layers[1].pin, GPIO_PIN_SET);
       HAL_Delay(x);
       disableAllPins();
    //bottom left
    for(int i = 0; i<8; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[0].port, layers[0].pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(layers[1].port, layers[1].pin, GPIO_PIN_SET);
    HAL_Delay(x);
    disableAllPins();
    //middle middle
    for(int i = 4; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[1].port, layers[1].pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);
    HAL_Delay(x);
    disableAllPins();
    //top right
    for(int i = 8; i<16; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(layers[3].port, layers[3].pin, GPIO_PIN_SET);
        HAL_Delay(x);
        disableAllPins();
    //top middle
    for(int i = 4; i<12; i++)
    {
    	HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);
           HAL_GPIO_WritePin(layers[3].port, layers[3].pin, GPIO_PIN_SET);
           HAL_Delay(x);
           disableAllPins();
  }
  //top left
  for(int i = 0; i<8; i++)
  {
	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
  }
  HAL_GPIO_WritePin(layers[3].port, layers[3].pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(layers[2].port, layers[2].pin, GPIO_PIN_SET);
  HAL_Delay(x);
  disableAllPins();
}

//propeller
void propeller()
{
  disableAllPins();
  int x = 90;
  for(int y = 4; y>0; y--)
  {
    for(int i = 0; i<6; i++)
    {
      //turn on layer
    	HAL_GPIO_WritePin(layers[y-1].port, layers[y-1].pin, GPIO_PIN_SET);
      //a1
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
      //b1
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
      //c1
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
      //d1
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
      //d2
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
      //d3
      turnColumnsOff();
      HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_RESET);
      HAL_Delay(x);
    }
  }
  //d4
  turnColumnsOff();
  HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_RESET);
  HAL_Delay(x);
}

//spiral in and out
void spiralInAndOut()
{
  enableAllPins();
  int x = 60;
  for(int i = 0; i<6; i++)
  {
    //spiral in clockwise
	  HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_SET);
	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	      HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_RESET);
	      HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_RESET);
	      HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	  HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	      HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	      HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_RESET);
	  	  HAL_Delay(x);
	  	      HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		  HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_SET);
	  		  HAL_Delay(x);
	  		          HAL_GPIO_WritePin(pinMap[6].port, pinMap[6].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[10].port, pinMap[10].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[9].port, pinMap[9].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[5].port, pinMap[5].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[1].port, pinMap[1].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[2].port, pinMap[2].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[3].port, pinMap[3].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[7].port, pinMap[7].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[11].port, pinMap[11].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			      HAL_GPIO_WritePin(pinMap[15].port, pinMap[15].pin, GPIO_PIN_RESET);
	  			      HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[14].port, pinMap[14].pin, GPIO_PIN_RESET);
	  			      HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[13].port, pinMap[13].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[12].port, pinMap[12].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			  	  HAL_GPIO_WritePin(pinMap[8].port, pinMap[8].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			      HAL_GPIO_WritePin(pinMap[4].port, pinMap[4].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
	  			      HAL_GPIO_WritePin(pinMap[0].port, pinMap[0].pin, GPIO_PIN_RESET);
	  			  	  HAL_Delay(x);
  }
}
//go through all leds one at a time
void goThroughAllLedsOneAtATime()
{
  int x = 15;
  disableAllPins();
  for(int y = 0; y<5; y++)
  {
    //0-3
    for(int count = 4; count != 0; count--)
    {
    	HAL_GPIO_WritePin(layers[count-1].port, layers[count-1].pin, GPIO_PIN_SET);
      for(int i = 0; i<4; i++)
      {
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	  HAL_Delay(x);
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
        HAL_Delay(x);
      }
      HAL_GPIO_WritePin(layers[count-1].port, layers[count-1].pin, GPIO_PIN_RESET);
    }
    //4-7
    for(int count = 0; count < 4; count++)
    {
    	HAL_GPIO_WritePin(layers[count].port, layers[count].pin, GPIO_PIN_SET);
      for(int i = 4; i<8; i++)
      {
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	  HAL_Delay(x);
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	  HAL_Delay(x);
      }
      HAL_GPIO_WritePin(layers[count].port, layers[count].pin, GPIO_PIN_RESET);
    }
    //8-11
    for(int count = 4; count != 0; count--)
    {
    	HAL_GPIO_WritePin(layers[count-1].port, layers[count-1].pin, GPIO_PIN_SET);
      for(int i = 8; i<12; i++)
      {
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	      	  HAL_Delay(x);
    	      	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	      	  HAL_Delay(x);
      }
      HAL_GPIO_WritePin(layers[count-1].port, layers[count-1].pin, GPIO_PIN_RESET);
    }
    //12-15
    for(int count = 0; count < 4; count++)
    {
    	HAL_GPIO_WritePin(layers[count].port, layers[count].pin, GPIO_PIN_SET);
      for(int i = 12; i<16; i++)
      {
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_RESET);
    	  HAL_Delay(x);
    	  HAL_GPIO_WritePin(pinMap[i].port, pinMap[i].pin, GPIO_PIN_SET);
    	  HAL_Delay(x);
      }
      HAL_GPIO_WritePin(layers[count].port, layers[count].pin, GPIO_PIN_RESET);
    }
  }
}


