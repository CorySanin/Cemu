#include <boost/container/small_vector.hpp>

#include "input/api/Keyboard/KeyboardController.h"
#include "WindowSystem.h"

KeyboardController::KeyboardController()
	: base_type("keyboard", "Keyboard")
{
	
}

std::string KeyboardController::get_button_name(uint64 button) const
{
	if(button == UINT32_MAX) {
		return "LEFT_MOUSE";
	}
	else if(button == UINT32_MAX - 1) {
		return "RIGHT_MOUSE";
	}
	else if(button == UINT32_MAX - 2) {
		return "MOUSE_3"; // center button
	}
	else if(button == UINT32_MAX - 3) {
		return "MOUSE_4"; // "forward" button
	}
	else if(button == UINT32_MAX - 4) {
		return "MOUSE_5"; // "back" button
	}
	return WindowSystem::GetKeyCodeName(button);
}

ControllerState KeyboardController::raw_state()
{
	ControllerState result{};

	if (WindowSystem::GetWindowInfo().debugger_focused)
		return result;

	boost::container::small_vector<uint32, 16> pressedKeys;
	auto& instance = InputManager::instance();
	WindowSystem::GetWindowInfo().iter_keystates([&pressedKeys](const std::pair<const uint32, bool>& keyState) { if (keyState.second) pressedKeys.emplace_back(keyState.first); });
	if (!instance.m_main_gyro.pause) {
		if (instance.m_main_mouse.left_down) {
			pressedKeys.emplace_back(UINT32_MAX);
		}
		if (instance.m_main_mouse.right_down) {
			pressedKeys.emplace_back(UINT32_MAX - 1);
		}
		if (instance.m_main_mouse.middle_down) {
			pressedKeys.emplace_back(UINT32_MAX - 2);
		}
		if (instance.m_main_mouse.forward_down) {
			pressedKeys.emplace_back(UINT32_MAX - 3);
		}
		if (instance.m_main_mouse.back_down) {
			pressedKeys.emplace_back(UINT32_MAX - 4);
		}
	}
	result.buttons.SetPressedButtons(pressedKeys);
	return result;
}
