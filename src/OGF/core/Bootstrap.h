/*
 * Bootstrap.h -- Bootstrap header file.
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

#ifndef __BOOTSTRAP_H__
#define __BOOTSTRAP_H__

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "InputManager.h"
#include "SceneController.h"
#include "ModelFactory.h"

namespace OGF {
	
	class Bootstrap : public Ogre::Singleton<Bootstrap> {

		private:
			
			void _loadResources(const std::string &resourcesFilePath);
			bool _configureRenderWindow(const std::string &windowTitle);
			void _initGui();
		
		public:

			static Bootstrap & getSingleton();
			static Bootstrap * getSingletonPtr();
			
			bool init(const std::string &resourcesFilePath, const std::string &windowTitle, ISceneFactory *sceneFactory, const SceneId &initialScene);
			void run();

			void shutdown();
	};
};

#endif
