//
// Created by xtx on 25-5-14.
//

#include "Work.h"

#include <stdbool.h>

#include "main.h"
#include "stm32g4xx_hal_gpio.h"
#include "TJCScreen.h"
extern volatile bool nowExit[6], isWorking,isBeeping;
void Hot() {
    if (HAL_GPIO_ReadPin(DoorIN_GPIO_Port,DoorIN_Pin) == GPIO_PIN_RESET) {
        TJCSendAny("noWork.en=1");
        TJCSendAny("isHotting.val=0");
        TJCSendAny("isLighting.val=0");
        TJCSendAny("WorkingTIM.en=0");
        TJCSendAny("WorkingLast.val=0");
        return;
    }
    Stop();
    isWorking = true;
    if (nowExit[0]) {
        HAL_GPIO_WritePin(Hot1_GPIO_Port, Hot1_Pin, GPIO_PIN_SET);
    }
    if (nowExit[1]) {
        HAL_GPIO_WritePin(Hot2_GPIO_Port, Hot2_Pin, GPIO_PIN_SET);
    }
    if (nowExit[2]) {
        HAL_GPIO_WritePin(Hot3_GPIO_Port, Hot3_Pin, GPIO_PIN_SET);
    }
    if (nowExit[3]) {
        HAL_GPIO_WritePin(Hot4_GPIO_Port, Hot4_Pin, GPIO_PIN_SET);
    }
    if (nowExit[4]) {
        HAL_GPIO_WritePin(Hot5_GPIO_Port, Hot5_Pin, GPIO_PIN_SET);
    }
    if (nowExit[5]) {
        HAL_GPIO_WritePin(Hot6_GPIO_Port, Hot6_Pin, GPIO_PIN_SET);
    }

    //加热开启排风
    HAL_GPIO_WritePin(Hot0_GPIO_Port, Hot0_Pin, GPIO_PIN_SET);
}
void Light() {
    if (HAL_GPIO_ReadPin(DoorIN_GPIO_Port,DoorIN_Pin) == GPIO_PIN_RESET) {
        TJCSendAny("noWork.en=1");
        TJCSendAny("noWork.en=1");
        TJCSendAny("isHotting.val=0");
        TJCSendAny("isLighting.val=0");
        TJCSendAny("WorkingTIM.en=0");
        TJCSendAny("WorkingLast.val=0");
        return;
    }
    Stop();
    isWorking = true;
    if (nowExit[0]) {
        HAL_GPIO_WritePin(Light1_GPIO_Port, Light1_Pin, GPIO_PIN_SET);
    }
    if (nowExit[1]) {
        HAL_GPIO_WritePin(Light2_GPIO_Port, Light2_Pin, GPIO_PIN_SET);
    }
    if (nowExit[2]) {
        HAL_GPIO_WritePin(Light3_GPIO_Port, Light3_Pin, GPIO_PIN_SET);
    }
    if (nowExit[3]) {
        HAL_GPIO_WritePin(Light4_GPIO_Port, Light4_Pin, GPIO_PIN_SET);
    }
    if (nowExit[4]) {
        HAL_GPIO_WritePin(Light5_GPIO_Port, Light5_Pin, GPIO_PIN_SET);
    }
    if (nowExit[5]) {
        HAL_GPIO_WritePin(Light6_GPIO_Port, Light6_Pin, GPIO_PIN_SET);
    }
}

void Stop() {
    isWorking = false;
    HAL_GPIO_WritePin(Hot0_GPIO_Port, Hot0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot1_GPIO_Port, Hot1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot2_GPIO_Port, Hot2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot3_GPIO_Port, Hot3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot4_GPIO_Port, Hot4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot5_GPIO_Port, Hot5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot6_GPIO_Port, Hot6_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(Light1_GPIO_Port, Light1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light2_GPIO_Port, Light2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light3_GPIO_Port, Light3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light4_GPIO_Port, Light4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light5_GPIO_Port, Light5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light6_GPIO_Port, Light6_Pin, GPIO_PIN_RESET);

    isBeeping=false;
    HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET);
}
