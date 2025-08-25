#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include "LcdHandler.h"

class ViewHandler {
  public:
    ViewHandler(LcdHandler& lcdHandler);
    void bootView();
    void ecoWash();
    void normalWash();
    void superWash();
    void selectActionView();
    void wlanState(bool connected);
    void mainPower();
  private:
    LcdHandler& lcdHandler_;
};

#endif