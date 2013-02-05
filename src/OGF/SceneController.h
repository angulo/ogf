/*
 * SceneController.h -- Scene controller header file
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

#ifndef __SCENE_CONTROLLER_H__
#define __SCENE_CONTROLLER_H__

#include <map>
#include <stack>

#include <Ogre.h>
#include <OgreSingleton.h>
#include <OIS/OIS.h>

#include "Types.h"
#include "ISceneFactory.h"
#include "Scene.h"

namespace OGF {

	typedef std::map<SceneId, Scene *> SceneMap;
	
	class SceneController : public Ogre::Singleton<SceneController>, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener {

		private:

			SceneMap _sceneMap;
			ISceneFactory *_sceneFactory;
			std::stack<Scene *> _sceneStore;

			Scene * _getScenePtr(SceneId sceneId);

			bool keyPressed(const OIS::KeyEvent &event);
			bool keyReleased(const OIS::KeyEvent &event);

			bool mouseMoved(const OIS::MouseEvent &event);
			bool mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);
			bool mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);
		
		protected:

			Ogre::Root* _root;
			Ogre::RenderWindow* _renderWindow;
			Ogre::SceneManager* _sceneManager;

		public:

			static SceneController& getSingleton();
			static SceneController* getSingletonPtr();

			void initialize(ISceneFactory *sceneFactory);

			void preload(SceneId sceneId);

			void add(SceneId sceneId);
			void remove(SceneId sceneId);

			void push(SceneId sceneId);
			void pop();

			void replace(SceneId sceneId);

	}; // Class SceneController

}; // Namespace OFG

#endif
