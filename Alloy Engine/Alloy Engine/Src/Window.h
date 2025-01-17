#pragma once
#include <string>


class Window
{
public:
	Window(std::string _window_title, unsigned int _width, unsigned int _height, int _initial_x_pos = 100, int _initial_y_pos = 100);

	HWND GetHandle() const;
	unsigned int GetWindowWidth() const;
	unsigned int GetWindowHeight() const;
	float GetAspectRatio() const;

private:
	HWND m_handle;
	unsigned int m_width = 0;
	unsigned int m_height = 0;	
	const std::string W_CLASS_NAME = "Alloy Engine Window";
};
