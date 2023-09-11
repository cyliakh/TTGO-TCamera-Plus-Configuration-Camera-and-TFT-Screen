# TTGO-TCamera-Plus-Configuration-Camera-and-TFT-Screen

Codes to help you configure Esp32 TCAM PLUS with arduino framework.

Find in "ttgo tcam plus" code + random image files to upload and display (put your own images and convert them).

TFT_eSPI and esp32cam-main libraries are not the original ones, some changes were applied on pins configuration in order to adapt them to TCAM PLUS.

_ _ _

If you want the original libraries: 

esp32cam-main :  https://github.com/yoursunny/esp32cam

TFT_eSPI : https://github.com/Bodmer/TFT_eSPI

Go to : esp32cam-main/src/internal/pins.hpp and choose the chip you have. 

If you dont find yours create a new one and replace AiThinker in "cfg.setPins(pins::AiThinker);" line in my code (ttgo tcam plus) or the one example in the library, with the one you just created.

Or, if you dont want to create a new one simply go to AiThinker struct and change those pins.

For the screen part, go to : TFT_eSPI/User_Setup_Select.h and uncomment the one you're looking for. 

(in this example, "include <User_Setups/Setup44_TTGO_CameraPlus.h>   // Setup file for ESP32 and TTGO T-CameraPlus ST7789 SPI bus TFT    240x240" was uncommented)

