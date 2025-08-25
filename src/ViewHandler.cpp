#include "ViewHandler.h"

ViewHandler::ViewHandler(LcdHandler& lcdHandler) 
: lcdHandler_(lcdHandler) 
{
}

void ViewHandler::bootView() {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Tiskikone");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "6000");
    lcdHandler_.DrawLargeIcon(LargeIcon::SOAP);
}

void ViewHandler::ecoWash() {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Eko");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "pesu");
    lcdHandler_.DrawLargeIcon(LargeIcon::LEAF);
}

void ViewHandler::normalWash() {
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Perus");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "pesu");
    lcdHandler_.DrawLargeIcon(LargeIcon::WATER);
}

void ViewHandler::superWash() {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Super");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "pesu");
    lcdHandler_.DrawLargeIcon(LargeIcon::SOAP);
}

void ViewHandler::selectActionView() {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Valitse");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "toiminto");
    lcdHandler_.DrawLargeIcon(LargeIcon::RESTART);
}

void ViewHandler::wlanState(bool connected) {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Wlan");
    if(connected) {
        lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "yhdistetty");
    } else {
        lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "katkaistu");
    }
    lcdHandler_.DrawLargeIcon(LargeIcon::HOME);
}

void ViewHandler::mainPower() {
    lcdHandler_.LcdClear();
    lcdHandler_.DrawText(TextPosition::CENTER_TOP, "Katkaise");
    lcdHandler_.DrawText(TextPosition::CENTER_BOTTOM, "virta");
    lcdHandler_.DrawLargeIcon(LargeIcon::CABLE);
}

