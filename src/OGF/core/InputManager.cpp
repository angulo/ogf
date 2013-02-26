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

bool
InputManager::keyPressed(const OIS::KeyEvent &event)
{
	return _keyListener == NULL || _keyListener->keyPressed(event);
}

bool
InputManager::keyReleased(const OIS::KeyEvent &event)
{
	return _keyListener == NULL || _keyListener->keyReleased(event);
}

bool
InputManager::mouseMoved(const OIS::MouseEvent &event)
{
	return _mouseListener == NULL || _mouseListener->mouseMoved(event);
}

bool
InputManager::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _mouseListener == NULL || _mouseListener->mousePressed(event, buttonId);
}

bool
InputManager::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _mouseListener == NULL || _mouseListener->mouseReleased(event, buttonId);
}

InputManager::InputManager()
{
	_eventSource = NULL;
	_keyListener = NULL;
	_mouseListener = NULL;
	_mouse = NULL;
	_keyboard = NULL;
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

		OIS::InputManager::destroyInputSystem(_eventSource);

		_eventSource = NULL;
		_keyListener = NULL;
		_mouseListener = NULL;
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
}
