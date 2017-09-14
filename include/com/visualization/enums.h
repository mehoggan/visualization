#ifndef COM_VISUALIZATION_ENUMS_H_INCLUDED
#define COM_VISUALIZATION_ENUMS_H_INCLUDED

#include <QKeyEvent>

namespace com
{
  namespace visualization
  {
    enum keyboard_modifiers
    {
      no_modifier = Qt::NoModifier,
      shift_modifier = Qt::ShiftModifier,
      control_modifier = Qt::ControlModifier,
      alt_modifier = Qt::AltModifier,
      meta_modifier = Qt::MetaModifier,
      keypad_modifier = Qt::KeypadModifier,
      group_switch_modifier = Qt::GroupSwitchModifier
    };

    enum mouse_button
    {
      no_button = Qt::NoButton,
      all_buttons = Qt::AllButtons,
      left_button = Qt::LeftButton,
      right_button = Qt::RightButton,
      middle_button = Qt::MiddleButton,
      back_button = Qt::BackButton,
      forward_button = Qt::ForwardButton,
      task_button = Qt::TaskButton,
      extra_button_4 = Qt::ExtraButton4,
      extra_button_5 = Qt::ExtraButton5,
      extra_button_6 = Qt::ExtraButton6,
      extra_button_7 = Qt::ExtraButton7,
      extra_button_8 = Qt::ExtraButton8,
      extra_button_9 = Qt::ExtraButton9,
      extra_button_10 = Qt::ExtraButton10,
      extra_button_11 = Qt::ExtraButton11,
      extra_button_12 = Qt::ExtraButton12,
      extra_button_13 = Qt::ExtraButton13,
      extra_button_14 = Qt::ExtraButton14,
      extra_button_15 = Qt::ExtraButton15,
      extra_button_16 = Qt::ExtraButton16,
      extra_button_17 = Qt::ExtraButton17,
      extra_button_18 = Qt::ExtraButton18,
      extra_button_19 = Qt::ExtraButton19,
      extra_button_20 = Qt::ExtraButton20,
      extra_button_21 = Qt::ExtraButton21,
      extra_button_22 = Qt::ExtraButton22,
      extra_button_23 = Qt::ExtraButton23,
      extra_button_24 = Qt::ExtraButton24
    };

    enum scroll_phase
    {
      no_scroll_phase, /*= Qt::NoScrollPhase,*/
      scroll_begin = Qt::ScrollBegin,
      scroll_update = Qt::ScrollUpdate,
      scroll_end = Qt::ScrollEnd
    };
  }
}

#endif
