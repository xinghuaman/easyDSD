/*
	Direct Stream Digital (DSD) player core module.

	License: GPL 3.0
	Copyright (C) 2020 Lukas Neverauskis
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <dsd.hpp>

#include "wucyFont8pt7b.h"

/*void* operator new(size_t size) {
	return pvPortMalloc(size);
}

void* operator new[](size_t size) {
	return pvPortMalloc(size);
}

void operator delete(void *ptr) {
	vPortFree(ptr);
}

void operator delete[](void *ptr) {
	vPortFree(ptr);
}*/

#ifdef __cplusplus
extern "C" {
#endif

// all of your legacy C code here

#ifdef __cplusplus
}
#endif

//osThreadId defaultTaskHandle;

#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

TFT_ILI9163C tft = TFT_ILI9163C(TFT_PIN_CS, TFT_PIN_A0, TFT_PIN_RESET);

unsigned long testText() {

	static char c = 0;

	tft.setFont(&wucyFont8pt7b);

	tft.setTextWrap(true);
	tft.setBounds(tft.width(), tft.height());

	//tft.fillScreen();

	tft.setTextColor(COLOR_YELLOW);
	tft.setTextSize(2);
	tft.setCursor(0, tft.getCharMaxHeight());
	tft.println("openDSD\n");
	tft.setCursor(0, tft.getCharMaxHeight()*3);
	tft.setTextColor(COLOR_LIME);
	tft.setTextSize(1);
	for(unsigned int i = c; i <= 4*0xFF; i++)
		tft.write((char)i);
	c++;
}

void openDSD::th_dsd_task(void const * argument)
{


	static openDSD dsd;

	  tft.begin();
	dsd.buttonsBegin();

	while (true) {

		dsd.buttonsUpdate();

		HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin,
				(GPIO_PinState) (dsd.btn[BTN_OK].pressedFor(500) | dsd.btn[BTN_OK].wasPressed()));
		HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin,
				(GPIO_PinState) (dsd.btn[BTN_OK].pressedFor(1000) | dsd.btn[BTN_OK].wasReleased()));

	  testText();
	  HAL_Delay(1);
	}
}

void th_dsd_start(void) {

//	osThreadDef(th_dsd, openDSD::th_dsd_task, osPriorityAboveNormal, 0, 3*1024);
//	defaultTaskHandle = osThreadCreate(osThread(th_dsd), NULL);

	openDSD::th_dsd_task(NULL);

}


/* end of th_dsd.cpp */
