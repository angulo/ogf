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
#include "InputManager.h"
#include "LogFactory.h"

namespace OGF {

	typedef std::map<SceneId, Scene *> SceneMap;
	
	class SceneController : public Ogre::Singleton<SceneController>, public Ogre::FrameListener,
		public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener {

		private:

			SceneMap _sceneMap;
			ISceneFactory *_sceneFactory;
			std::stack<Scene *> _sceneStore;
			size_t _childCount;

			Scene * _getScenePtr(const SceneId &sceneId, const bool &useCache = true);

			bool frameStarted(const Ogre::FrameEvent &event);
			bool frameEnded(const Ogre::FrameEvent &event);

			bool keyPressed(const OIS::KeyEvent &event);
			bool keyReleased(const OIS::KeyEvent &event);

			bool mouseMoved(const OIS::MouseEvent &event);
			bool mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);
			bool mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId);

			bool buttonPressed(const OIS::JoyStickEvent &event, int button);
			bool buttonReleased(const OIS::JoyStickEvent &event, int button);
			bool axisMoved(const OIS::JoyStickEvent &event, int axis);
		
		protected:

			Ogre::Root *_root;
			Ogre::RenderWindow *_renderWindow;

		public:

			SceneController();
			~SceneController();

			static SceneController & getSingleton();
			static SceneController * getSingletonPtr();

			void initialize(ISceneFactory *sceneFactory);

			void preload(const SceneId &sceneId);

			ChildId addChild(const SceneId &sceneId);
			ChildId addChild(Scene *child);

			void removeChild(const ChildId &childId);

			void push(const SceneId &sceneId);
			void push(Scene *scene);
			void pop();

			void replace(const SceneId &sceneId);
			void replace(Scene *scene);

	}; // Class SceneController

}; // Namespace OGF

#endif
