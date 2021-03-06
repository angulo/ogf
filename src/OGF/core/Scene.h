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

#include <map>

#include <Ogre.h>
#include <OIS/OIS.h>

#include "ConfigReader.h"
#include "LogFactory.h"
#include "Types.h"

namespace OGF {

	class Scene;
	typedef std::map<ChildId, Scene *> ChildMap;
	
	class Scene {
		
		protected:
			
			Ogre::SceneManager *_sceneManager;
			ConfigReader *_configReader;
			ChildMap _childs;

			void _initConfigReader(const std::string &configFile, const bool &useCache = true);

			template<class T>
			T _configValue(const std::string &key);

		public:
			
			Scene();
			Scene(Ogre::SceneManager *sceneManager);

			virtual ~Scene() = 0;

			Ogre::SceneManager *getSceneManager() const;

			void addChild(Scene* childScene, const ChildId &childId);
			void removeChild(const ChildId &childId);
			
			virtual void preload();

			virtual void enter() = 0;
			virtual void exit() = 0;

			virtual void pause();
			virtual void resume();

			// Facade methods to allow specific base implementations
			
			virtual void enterFacade();
			virtual void exitFacade();
			virtual void pauseFacade();
			virtual void resumeFacade();

			virtual bool frameStartedFacade(const Ogre::FrameEvent& event);
			virtual bool frameEndedFacade(const Ogre::FrameEvent& event);

			virtual bool keyPressedFacade(const OIS::KeyEvent& event);
			virtual bool keyReleasedFacade(const OIS::KeyEvent& event);

			virtual bool mouseMovedFacade(const OIS::MouseEvent& event);
			virtual bool mousePressedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
			virtual bool mouseReleasedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

			virtual bool buttonPressedFacade(const OIS::JoyStickEvent &event, int button);
			virtual bool buttonReleasedFacade(const OIS::JoyStickEvent &event, int button);
			virtual bool axisMovedFacade(const OIS::JoyStickEvent &event, int axis);


			// Methods that can be overriden in the child classes

			virtual bool frameStarted(const Ogre::FrameEvent& event);
			virtual bool frameEnded(const Ogre::FrameEvent& event);

			virtual bool keyPressed(const OIS::KeyEvent& event);
			virtual bool keyReleased(const OIS::KeyEvent& event);

			virtual bool mouseMoved(const OIS::MouseEvent& event);
			virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
			virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

			virtual bool buttonPressed(const OIS::JoyStickEvent &event, int button);
			virtual bool buttonReleased(const OIS::JoyStickEvent &event, int button);
			virtual bool axisMoved(const OIS::JoyStickEvent &event, int axis);

	}; // Class Scene
	
	// Template implementations

	template<class T>
	T
	Scene::_configValue(const std::string &key)
	{
		if (!_configReader) {
			std::string errorMessage = "Config reader not initialized when reading value";

			LogFactory::getSingletonPtr()->get(LOG_ERR)->log("Scene", "configValue", errorMessage, LOG_SEVERITY_ERROR);
			throw errorMessage;
		}

		return _configReader->get<T>(key);
	}


}; // Namespace OGF

#endif
