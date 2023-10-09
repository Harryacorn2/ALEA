#ifndef BN_SOUND_ITEMS_INFO_H
#define BN_SOUND_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_sound_item.h"
#include "bn_string_view.h"

namespace bn::sound_items_info
{
    constexpr inline pair<sound_item, string_view> array[] = {
        make_pair(sound_item(0), string_view("confirm")),
        make_pair(sound_item(1), string_view("deselect")),
        make_pair(sound_item(2), string_view("excelent")),
        make_pair(sound_item(3), string_view("good")),
        make_pair(sound_item(4), string_view("great")),
        make_pair(sound_item(5), string_view("ping")),
        make_pair(sound_item(6), string_view("select")),
    };

    constexpr inline span<const pair<sound_item, string_view>> span(array);
}

#endif

