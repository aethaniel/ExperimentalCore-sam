/*
  Copyright (c) 2015 Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "core_private.h"

void initVariant( void )
{
  // Initialize Serial port Flexcom7 pins
  pinPeripheral(PIN_SERIAL_RX, GPIO_PERIPH_B);
  pinPeripheral(PIN_SERIAL_TX, GPIO_PERIPH_B);

  // Initialize Serial port Flexcom0 pins
  pinPeripheral(PIN_SERIAL1_RX, GPIO_PERIPH_A);
  pinPeripheral(PIN_SERIAL1_TX, GPIO_PERIPH_A);

  // Initialize Serial port Flexcom6 pins
  pinPeripheral(PIN_SERIAL2_RX, GPIO_PERIPH_B);
  pinPeripheral(PIN_SERIAL2_TX, GPIO_PERIPH_B);
    
  //ADC setup
  PMC->PMC_PCR = PMC_PCR_PID(ID_ADC)|PMC_PCR_CMD|PMC_PCR_DIV(1)|PMC_PCR_EN; //Set ADC peripheral clock to MCK/1 = 120MHz
  PMC->PMC_PCER0 = (1<<ID_ADC);   //enable ADC peripheral clock
    
  //ADCCLK=PERIPHCLK/(2*(PRESCAL+1))  <=>  PRESCAL=(PERIPHCLK/(2*ADCCLK))-1
  ADC->ADC_MR =ADC_MR_PRESCAL(5); //fastest ADC conversion clock (10MHz with 120MHz peripheral clock)
}
