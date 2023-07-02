#!/bin/bash

sed -i '/^\/\/ \(This file was generated\|SquareLine\|EDITOR\|LVGL\|PROJECT\|Project name\)/d' $(find . -name '*.c' -or -name '*.h')
rm -f filelist.txt
rm -f CMakeLists.txt

sed -i '/ SCREENS /,+100d' ui.c
sed -i '/Describes an animation/,+6d' ui_helpers.h
sed -i 's/_UI_EVENTS_H/_UI_MAINSCREEN_EVENTS_H/' ui_events.h

# already covered by shared component
rm -rf fonts/
rm -f ui_helpers.c
