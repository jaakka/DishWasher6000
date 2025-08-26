#include "LcdHandler.h"

void LcdHandler::SendLcdCommand(String cmd)
{
  lcdSerial_.print(cmd);
  lcdSerial_.write(0xFF); 
  lcdSerial_.write(0xFF);
  lcdSerial_.write(0xFF);
}

LcdHandler::LcdHandler() : lcdSerial_(LCD_RX, LCD_TX) {
  lcdSerial_.begin(9600);
  SendLcdCommand("baud=115200");
  lcdSerial_.begin(115200);
}

void LcdHandler::begin() {
  LcdClear();
}

void LcdHandler::startCommunication() {
    lcdSerial_.begin(115200);
    delay(10);
}

void LcdHandler::stopCommunication() {
    lcdSerial_.end();
    delay(10); 
}

void LcdHandler::UpdateText(int elementId, String txt)
{
  SendLcdCommand("t"+String(elementId)+".txt=\""+String(txt)+"\"");
}

void LcdHandler::UpdateText(TextPosition pos, String text)
{
  UpdateText(static_cast<int>(pos), text);
}

void LcdHandler::UpdateImage(int elementId, int imageId)
{
  SendLcdCommand("p"+String(elementId)+".pic="+String(imageId));
}

// I want to use the enum classes to make the code more readable & bugfree
void LcdHandler::UpdateImage(BgImagePosition pos, BgImageLeftBottom image)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(image));
}

void LcdHandler::UpdateImage(BgImagePosition pos, BgImageRightBottom image)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(image));
}

void LcdHandler::UpdateImage(BgImagePosition pos, BgImageRightTop image)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(image));
}

void LcdHandler::UpdateImage(BgImagePosition pos, BgImageLeftTop image)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(image));
}

void LcdHandler::UpdateImage(SmallIconPositionRightTop pos, SmallIcon icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionRightBottom pos, SmallIcon icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionLeftTop pos, SmallIcon icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionLeftBottom pos, SmallIcon icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}


void LcdHandler::UpdateImage(SmallIconPositionRightTop pos, SmallIconSelected icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionRightBottom pos, SmallIconSelected icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionLeftTop pos, SmallIconSelected icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::UpdateImage(SmallIconPositionLeftBottom pos, SmallIconSelected icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}


void LcdHandler::UpdateImage(LargeIconPosition pos, LargeIcon icon)
{
  UpdateImage(static_cast<int>(pos), static_cast<int>(icon));
}

void LcdHandler::LcdClear()
{
  UpdateImage(BgImagePosition::LEFT_TOP, BgImageLeftTop::EMPTY);
  UpdateImage(BgImagePosition::LEFT_BOTTOM, BgImageLeftBottom::EMPTY);
  UpdateImage(BgImagePosition::RIGHT_BOTTOM, BgImageRightBottom::EMPTY);
  UpdateImage(BgImagePosition::RIGHT_TOP, BgImageRightTop::EMPTY);
}


void LcdHandler::DrawCircleBackground(BgImageLeftBottom image) 
{
  UpdateImage(BgImagePosition::LEFT_BOTTOM, image);
}

void LcdHandler::DrawCircleBackground(BgImageRightBottom image) 
{
  UpdateImage(BgImagePosition::RIGHT_BOTTOM, image);
}

void LcdHandler::DrawCircleBackground(BgImageRightTop image) 
{
  UpdateImage(BgImagePosition::RIGHT_TOP, image);
}

void LcdHandler::DrawCircleBackground(BgImageLeftTop image) 
{
  UpdateImage(BgImagePosition::LEFT_TOP, image);
}



void LcdHandler::DrawCircleIcon(SmallIconPositionRightTop pos, SmallIcon icon)
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionRightBottom pos, SmallIcon icon) 
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionLeftTop pos, SmallIcon icon) 
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionLeftBottom pos, SmallIcon icon) 
{
  UpdateImage(pos, icon);
}


void LcdHandler::DrawCircleIcon(SmallIconPositionRightTop pos, SmallIconSelected icon)
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionRightBottom pos, SmallIconSelected icon) 
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionLeftTop pos, SmallIconSelected icon) 
{
  UpdateImage(pos, icon);
}

void LcdHandler::DrawCircleIcon(SmallIconPositionLeftBottom pos, SmallIconSelected icon) 
{
  UpdateImage(pos, icon);
}



void LcdHandler::DrawLargeIcon(LargeIcon icon)
{
  UpdateImage(LargeIconPosition::CENTER_ICON, icon);
}


void LcdHandler::DrawText(TextPosition pos, String text)
{
  UpdateText(pos, text);
}