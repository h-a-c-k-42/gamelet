#ifndef __HACK42_GAMELET_GRAPHICS_HH__
#define __HACK42_GAMELET_GRAPHICS_HH__
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

#include <Adafruit_SSD1306.h>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

#ifndef OLED_RESET
#define OLED_RESET 0
#endif

#ifndef SYS_MENU_LINE_WIDTH
#define SYS_MENU_LINE_WIDTH 100
#endif

#ifndef MAX_MENU_ITEMS
#define MAX_MENU_ITEMS 5
#endif

#ifndef SYS_SCREEN_DEFAULT_FONT_SIZE
#define SYS_SCREEN_DEFAULT_FONT_SIZE 1
#endif

namespace gamelet
{
  typedef enum { UP, DOWN, LEFT, RIGHT } direction_t;

  class Menu
  {
  public:
    Menu () : cur_item_ (0), items_ (std::vector (MAX_MENU_ITEMS)){};
    ~Menu (){};
    void move (direction_t direction);
    int current_item () const
    {
      return cur_item_;
    };
    void select ();

  private:
    std::vector<std::tuple<std::string, std::function<void()>>> items_;
    int cur_item_;
  };

  class SystemMenu : Menu
  {
  public:
    SystemMenu ();
    ~SystemMenu (){};
    int line_width;
    int line_height;
  };

  class Screen : public Adafruit_SSD1306
  {
  public:
    Screen ();
    ~Screen (){};
    virtual void refresh () = 0;
  };

  typedef enum { MENU, WIFI, DOWNLOAD } sys_scr_mode_t;

  class SystemScreen : public Screen
  {
  public:
    SystemScreen ();
    ~SystemScreen (){};
    void splash (int ms = 2000);
    void refresh () override;
    void refresh_menu ();
    void font_config (int size = SYS_SCREEN_DEFAULT_FONT_SIZE, const GFXfont *font = nullptr);
    SystemMenu menu;

  private:
    int count_line_height ();
    void show_menu ();
    void show_keyboard ();
    sys_scr_mode_t mode_;
  };
}
#endif // End of __HACK42_GAMELET_HH__
