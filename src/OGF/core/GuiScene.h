/*
 * GuiScene.h -- GUI Scene base class header file.
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

#ifndef __GUI_SCENE_H__
#define __GUI_SCENE_H__

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>

#include "Scene.h"

namespace OGF {
	
	class GuiScene : public Scene {
		
		protected:

			CEGUI::MouseButton _convertMouseButton(OIS::MouseButtonID id);

		public:

			virtual ~GuiScene() = 0;
			
			virtual void enter() = 0;
			virtual void exit() = 0;

			// Facade methods to allow specific base implementations
			virtual bool frameStartedFacade(const Ogre::FrameEvent& event);

			virtual bool keyPressedFacade(const OIS::KeyEvent& event);
			virtual bool keyReleasedFacade(const OIS::KeyEvent& event);

			virtual bool mouseMovedFacade(const OIS::MouseEvent& event);
			virtual bool mousePressedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
			virtual bool mouseReleasedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

	}; // Class GuiScene
}; // Namespace OGF

#endif
