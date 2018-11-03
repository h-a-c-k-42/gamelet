/*
 *  Copyright (C) 2018
      "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gamelet/graphics.hh"

namespace gamelet
{
  void Menu::move (direction_t direction)
  {
    switch (direction)
    {
    case UP:
      cur_item_ = cur_item_ ? --cur_item_ : 0;
    case DOWN:
      cur_item_ = (items_.size () == cur_item_) ? cur_item_ : ++cur_item_;
    default:
      return;
    }
  }

  void Menu::select ()
  {
    items_[cur_item_]();
  }

  Screen::Screen () : Adafruit_SSD1306 (OLED_RESET)
  {
    // init I2C addr 0x3c for the 128x64
    this->begin (SSD1306_SWITCHCAPVCC, 0x3c);
    this->setCursor (0, 0);
  }

  void Screen::font_config (int size, const GFXfont *font)
  {
    this->setFont (font);
    this->setTextSize (size);
    this->setTextColor (WHITE);
  }

  void SystemScreen::show ()
  {
    this->setCursor (14, 0);
    for (auto i : items_)
    {
      this->println (std::get<0> (i));
    }
  }

  void SystemScreen::splash (int ms)
  {
    this->display ();
    delay (ms);
    this->clearDisplay ();
  }

  void SystemScreen::show_keyboard ()
  {
  }
}
