/*
 * ModelFactory.h -- Model factory header file.
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

#ifndef __MODEL_FACTORY_H__
#define __MODEL_FACTORY_H__

#include <map>

#include <Ogre.h>

#include "../core/LogFactory.h"
#include "../core/Types.h"
#include "ModelBuilder.h"

namespace OGF {
	
	typedef std::map<ModelId, ModelPath> ModelMap;
	
	class ModelFactory : public Ogre::Singleton<ModelFactory> {
		
		protected:
			
			ModelMap _modelMap;
		
		public:

			ModelFactory();
			virtual ~ModelFactory();

			static ModelFactory & getSingleton();
			static ModelFactory * getSingletonPtr();

			void initialize(const ModelMap &modelMap);

			ModelBuilder * getBuilder(Ogre::SceneManager *sceneManager, const ModelId &modelId);
	};
};

#endif
