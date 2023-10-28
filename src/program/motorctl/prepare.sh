#!/bin/bash

sed -i '/^\/\/ \(This file was generated\|SquareLine\|EDITOR\|LVGL\|PROJECT\|Project name\)/d' $(find . -name '*.c' -or -name '*.h')
rm -f filelist.txt
rm -f CMakeLists.txt

sed -i '/ui_[A-Za-z]*Screen_screen_init(void)/s|(void)|(lv_obj_t *root)|' screens/ui_* ui.h ui.c
sed -i '/ui_[A-Za-z]*Screen = lv_obj_create/s|NULL|root|' screens/ui_*
sed -i '/ SCREENS /,+100d' ui.c
sed -i 's/<{Style_bg}>//' screens/ui*.c
sed -i 's/_UI_EVENTS_H/_UI_DOZATOR_EVENTS_H/' ui_events.h


# already covered by shared component
rm -rf fonts/
rm -f ui_helpers.c
rm -f ui_helpers.h
