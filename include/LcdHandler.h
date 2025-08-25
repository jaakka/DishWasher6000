#ifndef LCDHANDLER_H
#define LCDHANDLER_H

#include "LcdHandler.h"
#include "LcdValues.h"
#include "pins.h"
#include "LcdValues.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

class LcdHandler 
{
    public:
        LcdHandler();
        void begin();
        
        void DrawCircleBackground(BgImageLeftBottom image); 
        void DrawCircleBackground(BgImageRightBottom image);
        void DrawCircleBackground(BgImageRightTop image);
        void DrawCircleBackground(BgImageLeftTop image);

        void DrawCircleIcon(SmallIconPositionRightTop pos, SmallIcon icon);
        void DrawCircleIcon(SmallIconPositionRightBottom pos, SmallIcon icon);
        void DrawCircleIcon(SmallIconPositionLeftTop pos, SmallIcon icon);
        void DrawCircleIcon(SmallIconPositionLeftBottom pos, SmallIcon icon);

        void DrawCircleIcon(SmallIconPositionRightTop pos, SmallIconSelected icon);
        void DrawCircleIcon(SmallIconPositionRightBottom pos, SmallIconSelected icon);
        void DrawCircleIcon(SmallIconPositionLeftTop pos, SmallIconSelected icon);
        void DrawCircleIcon(SmallIconPositionLeftBottom pos, SmallIconSelected icon);

        void LcdClear();

        void DrawLargeIcon(LargeIcon icon);

        void DrawText(TextPosition pos, String text);

    private:
        SoftwareSerial LcdSerial;
        void SendLcdCommand(String cmd);
        void UpdateImage(int elementId, int imageId);
        void UpdateText(int elementId, String txt);

        void UpdateImage(BgImagePosition pos, BgImageLeftBottom image);
        void UpdateImage(BgImagePosition pos, BgImageRightBottom image);
        void UpdateImage(BgImagePosition pos, BgImageRightTop image);
        void UpdateImage(BgImagePosition pos, BgImageLeftTop image);

        void UpdateImage(SmallIconPositionRightTop pos, SmallIcon icon);
        void UpdateImage(SmallIconPositionRightBottom pos, SmallIcon icon);
        void UpdateImage(SmallIconPositionLeftTop pos, SmallIcon icon);
        void UpdateImage(SmallIconPositionLeftBottom pos, SmallIcon icon);

        void UpdateImage(SmallIconPositionRightTop pos, SmallIconSelected icon);
        void UpdateImage(SmallIconPositionRightBottom pos, SmallIconSelected icon);
        void UpdateImage(SmallIconPositionLeftTop pos, SmallIconSelected icon);
        void UpdateImage(SmallIconPositionLeftBottom pos, SmallIconSelected icon);

        void UpdateImage(LargeIconPosition pos, LargeIcon icon);

        void UpdateText(TextPosition pos, String text);
};

#endif
