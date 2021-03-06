/*
 * InputManager.h -- Input manager header file.
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

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>

namespace OGF {
	
	class InputManager : public Ogre::Singleton<InputManager>, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener {

		private:
			
			Ogre::RenderWindow *_renderWindow;
			OIS::InputManager *_eventSource;

			OIS::Keyboard *_keyboard;
			OIS::KeyListener *_keyListener;

			OIS::Mouse *_mouse;
			OIS::MouseListener *_mouseListener;

			OIS::JoyStick *_joystick;
			OIS::JoyStickListener *_joystickListener;

			CEGUI::MouseButton _convertMouseButton(OIS::MouseButtonID id);

			bool keyPressed(const OIS::KeyEvent &event);
			bool keyReleased(const OIS::KeyEvent &event);

			bool mouseMoved(const OIS::MouseEvent &event);
			bool mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);
			bool mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);

			bool buttonPressed(const OIS::JoyStickEvent &arg, int button);
			bool buttonReleased(const OIS::JoyStickEvent &arg, int button);
			bool axisMoved(const OIS::JoyStickEvent &arg, int axis);

		public:

			InputManager();
			virtual ~InputManager();

			static InputManager & getSingleton();
			static InputManager * getSingletonPtr();

			OIS::Keyboard * getKeyboard() const;
			OIS::Mouse * getMouse() const;
			OIS::JoyStick * getJoystick() const;

			void initialize(Ogre::RenderWindow *renderWindow, OIS::KeyListener *keyListener,
				OIS::MouseListener *mouseListener, OIS::JoyStickListener *joystickListener);
			void updateMouseLimits();
			void capture();
	};
};

#endif
