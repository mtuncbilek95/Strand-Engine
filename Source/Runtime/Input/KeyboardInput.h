#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API KeyboardInput
	{
		Button_A,
		Button_B,
		Button_C,
		Button_D,
		Button_E,
		Button_F,
		Button_G,
		Button_H,
		Button_I,
		Button_J,
		Button_K,
		Button_L,
		Button_M,
		Button_N,
		Button_O,
		Button_P,
		Button_Q,
		Button_R,
		Button_S,
		Button_T,
		Button_U,
		Button_V,
		Button_W,
		Button_X,
		Button_Y,
		Button_Z,
		Button_1, // 1 & ! (Shift + 1 = !)
		Button_2, // 2 & @ (Shift + 2 = @)
		Button_3, // 3 & # (Shift + 3 = #)
		Button_4, // 4 & $ (Shift + 4 = $)
		Button_5, // 5 & % (Shift + 5 = %)
		Button_6, // 6 & ^ (Shift + 6 = ^)
		Button_7, // 7 & & (Shift + 7 = &)
		Button_8, // 8 & * (Shift + 8 = *)
		Button_9, // 9 & ( (Shift + 9 = ()
		Button_0, // 0 & ) (Shift + 0 = ))

		Button_Minus, // - & _ (Shift + - = _)
		Button_Equals, // = & + (Shift + = = +)
		Button_Left_Bracket, // [ & { (Shift + [ = {)
		Button_Right_Bracket, // ] & } (Shift + ] = })
		Button_Semicolon, // ; & : (Shift + ; = :)
		Button_Quote, // ' & " (Shift + ' = ")
		Button_Reverse_Slash, // \ & | (Shift + \ = |)
		Button_Forward_Slash, // / & ? (Shift + / = ?)
		Button_Dot, // . & > (Shift + . = >)
		Button_Period, // , & < (Shift + , = <)

		NumLock_0,
		NumLock_1,
		NumLock_2,
		NumLock_3,
		NumLock_4,
		NumLock_5,
		NumLock_6,
		NumLock_7,
		NumLock_8,
		NumLock_9,
		NumLock_Plus,
		NumLock_Minus,
		NumLock_Multiply,
		NumLock_Divide,
		NumLock_Period,

		Right_Shift,
		Left_Shift,

		Right_Control,
		Left_Control,

		Right_Alt,
		Left_Alt,

		Right_Windows,
		Left_Windows,

		Escape,
		Tab,
		Caps_Lock,
		Space,
		Enter,
		Backspace,
		Quote_Mark, // ` & ~ (Shift + ` = ~)

		Insert,
		Delete,
		Home,
		End,
		Page_Up,
		Page_Down,

		Print_Screen,
		Scroll_Lock,
		Pause,

		Up_Arrow,
		Down_Arrow,
		Left_Arrow,
		Right_Arrow,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12
	};
}