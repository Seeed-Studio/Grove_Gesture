
#include <Arduino.h>
#include <Wire.h>
#include "paj7620.h"
#include "pag7660.h"

class Pixart_Gesture
{
   public:
      virtual bool init();

   protected:
      uint8_t i2c_addr;
      void writeReg(uint8_t addr, uint8_t value);
      void readRegs(uint8_t addr, uint8_t *values, int size);
      uint8_t readReg(uint8_t addr);
};


class paj7620 : public Pixart_Gesture
{
   public:
      paj7620();
      bool init();
      bool getResult(paj7620_gesture_t& res);

   private:
      bool setReportMode(uint8_t reportMode);
};


class pag7660 : public Pixart_Gesture
{
   public:
      pag7660(int mode = GESTURE_COMBINED_MODE) {
         gestureMode = mode;
      };
      bool init();
      bool getResult(pag7660_gesture_t& res);
      bool getOutput(pag7660_out_t& out);

      int getGestureMode();
      int nextGestureMode();

   private:
      uint8_t gestureMode;
      pag7660_out_t regToOutput(const pag7660_reg_out_t& reg);

#ifdef PAG7660_CS
   protected:
      void writeRegs(uint8_t addr, uint8_t *values, int size);
      void writeReg(uint8_t addr, uint8_t value);
      void readRegs(uint8_t addr, uint8_t *values, int size);
      uint8_t readReg(uint8_t addr);
#endif
};