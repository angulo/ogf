/*
 * InputManager.cpp -- Input manager implementation file.
 *
 * Copyright (C) 2013 Javier Angulo Luceron <javier.angulo1@gmail.com>
 * 
 * ogf is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ogf is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "InputManager.h"

using namespace OGF;

template<> InputManager * Ogre::Singleton<InputManager>::msSingleton = 0;

CEGUI::MouseButton
InputManager::_convertMouseButton(OIS::MouseButtonID id)
{
	CEGUI::MouseButton ceguiId;

	switch(id) {
		case OIS::MB_Left:
			ceguiId = CEGUI::LeftButton;
			break;
		case OIS::MB_Right:
			ceguiId = CEGUI::RightButton;
			break;
		case OIS::MB_Middle:
			ceguiId = CEGUI::MiddleButton;
			break;
		default:
			ceguiId = CEGUI::LeftButton;
	}

	return ceguiId;
}

bool
InputManager::keyPressed(const OIS::KeyEvent &event)
{
	CEGUI::System::getSingleton().injectKeyDown(event.key);
	CEGUI::System::getSingleton().injectChar(event.text);

	return _keyListener == NULL || _keyListener->keyPressed(event);
}

bool
InputManager::keyReleased(const OIS::KeyEvent &event)
{
	CEGUI::System::getSingleton().injectKeyUp(event.key);

	return _keyListener == NULL || _keyListener->keyReleased(event);
}

bool
InputManager::mouseMoved(const OIS::MouseEvent &event)
{
	CEGUI::System::getSingleton().injectMouseMove(event.state.X.rel, event.state.Y.rel);

	return _mouseListener == NULL || _mouseListener->mouseMoved(event);
}

bool
InputManager::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(_convertMouseButton(buttonId));

	return _mouseListener == NULL || _mouseListener->mousePressed(event, buttonId);
}

bool
InputManager::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(_convertMouseButton(buttonId));

	return _mouseListener == NULL || _mouseListener->mouseReleased(event, buttonId);
}

bool
InputManager::buttonPressed(const OIS::JoyStickEvent &event, int button)
{
	return _joystickListener == NULL || _joystickListener->buttonPressed(event, button);
}

bool
InputManager::buttonReleased(const OIS::JoyStickEvent &event, int button)
{
	return _joystickListener == NULL || _joystickListener->buttonReleased(event, button);
}

bool
InputManager::axisMoved(const OIS::JoyStickEvent &event, int axis)
{
	return _joystickListener == NULL || _joystickListener->axisMoved(event, axis);
}

InputManager::InputManager()
{
	_eventSource = NULL;
	_keyListener = NULL;
	_mouseListener = NULL;
	_joystickListener = NULL;
	_mouse = NULL;
	_keyboard = NULL;
	_joystick = NULL;
}

InputManager::~InputManager()
{
	if (_eventSource != NULL) {
		if (_keyboard) {
			_eventSource->destroyInputObject(_keyboard);
			_keyboard = NULL;
		}

		if (_mouse) {
			_eventSource->destroyInputObject(_mouse);
			_mouse = NULL;
		}

		if (_joystick) {
			_eventSource->destroyInputObject(_joystick);
			_joystick = NULL;
		}

		OIS::InputManager::destroyInputSystem(_eventSource);

		_eventSource = NULL;
		_keyListener = NULL;
		_mouseListener = NULL;
		_joystickListener = NULL;
	}
}

InputManager &
InputManager::getSingleton()
{
	if (!msSingleton) {
		InputManager *instance = new InputManager();
	}

	return *msSingleton;
}

InputManager *
InputManager::getSingletonPtr()
{
	if (!msSingleton) {
		InputManager *instance = new InputManager();
	}

	return msSingleton;
}

OIS::Keyboard *
InputManager::getKeyboard() const
{
	return _keyboard;
}

OIS::Mouse *
InputManager::getMouse() const
{
	return _mouse;
}

OIS::JoyStick *
InputManager::getJoystick() const
{
	return _joystick;
}

void
InputManager::initialize(Ogre::RenderWindow *renderWindow, OIS::KeyListener *keyListener, OIS::MouseListener *mouseListener)
{
	_renderWindow = renderWindow;
	_keyListener = keyListener;
	_mouseListener = mouseListener;

	if (_eventSource == NULL) {
		OIS::ParamList windowParamList;
		size_t windowHandler = 0;
		_renderWindow->getCustomAttribute("WINDOW", &windowHandler);
		windowParamList.insert(std::make_pair(std::string("WINDOW"), Ogre::StringConverter::toString(windowHandler)));

		_eventSource = OIS::InputManager::createInputSystem(windowParamList);
		
		_keyboard = static_cast<OIS::Keyboard *> (
			_eventSource->createInputObject(OIS::OISKeyboard, true)
		);
		_keyboard->setEventCallback(this);

		_mouse = static_cast<OIS::Mouse *> (
			_eventSource->createInputObject(OIS::OISMouse, true)
		);
		_mouse->setEventCallback(this);
		updateMouseLimits();
		
		try {
			_joystick = static_cast<OIS::JoyStick *> (
				_eventSource->createInputObject(OIS::OISJoyStick, true)
			);
			_joystick->setEventCallback(this);
		} catch (OIS::Exception) {
			// No joystick plugged in
		}
	}
}

void
InputManager::updateMouseLimits()
{
	unsigned int width, height, dummy;
	int dumb;
	_renderWindow->getMetrics(width, height, dummy, dumb, dumb);

	const OIS::MouseState &mouseState = _mouse->getMouseState();
	mouseState.width = width;
	mouseState.height = height;
}

void
InputManager::capture()
{
	if (_mouse != NULL)
		_mouse->capture();

	if (_keyboard != NULL)
		_keyboard->capture();
	
	if (_joystick != NULL)
		_joystick->capture();
}
