/*
 * ModelBuilder.h -- Model builder header file.
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

#ifndef __MODEL_BUILDER_H__
#define __MODEL_BUILDER_H__

#include <Ogre.h>

#include "Types.h"

namespace OGF {
	
	class ModelBuilder {
		
		public:

			virtual ~ModelBuilder();

			// Initial method as constructor
			ModelBuilder(const ModelPath &path);

			// Intermediate methods
			ModelBuilder *parent(Ogre::SceneNode *parent);
			ModelBuilder *queryFlags(const Ogre::uint32 queryFlags);
			ModelBuilder *visible(bool isVisible);
			ModelBuilder *castShadows(bool toCastShadows);

			// Final Methods
			Ogre::SceneNode *buildNode();
			Ogre::SceneNode *buildNode(const Ogre::String &nodeName);
			Ogre::SceneNode *buildNode(const Ogre::String &entityName, const Ogre::String &nodeName);

			Ogre::Entity *buildEntity();
			Ogre::Entity *buildEntity(const Ogre::String &entityName);
	};
};

#endif
