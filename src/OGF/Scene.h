/*
 * Scene.h -- Base scene header file
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

#ifndef __SCENE_H__
#define __SCENE_H__

#include <Ogre.h>
#include <OIS/OIS.h>

namespace OGF {
	
	class Scene {
		
		protected:
			
			virtual void preload();

			virtual void enter() = 0;
			virtual void exit() = 0;

			virtual void pause() = 0;
			virtual void resume() = 0;

			virtual bool frameStarted(const Ogre::FrameEvent& event);
			virtual bool frameEnded(const Ogre::FrameEvent& event);

			virtual bool keyPressed(const OIS::KeyEvent& event) = 0;
			virtual bool keyReleased(const OIS::KeyEvent& event) = 0;

			virtual bool mouseMoved(const OIS::MouseEvent& event) = 0;
			virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) = 0;
			virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) = 0;

		public:

			Scene();
			virtual ~Scene() = 0;

	}; // Class Scene

}; // Namespace OGF

#endif
