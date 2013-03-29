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

#include "../core/LogFactory.h"
#include "../core/Types.h"

namespace OGF {

	class ModelBuilder;
	typedef Ogre::SharedPtr<ModelBuilder> ModelBuilderPtr;
	
	class ModelBuilder {
		
		private:
			
			// Mandatory data
			Ogre::SceneManager *_sceneManager;
			ModelPath _modelPath;

			// Set flags
			bool _modelPathSet;
			bool _parentSet, _queryFlagsSet, _visibleSet;
			bool _castShadowsSet, _entityNameSet, _nodeNameSet;
			bool _positionSet, _scaleSet;

			// Configurable data
			Ogre::SceneNode *_parent;
			Ogre::uint32 _queryFlags;
			bool _visible;
			bool _castShadows;
			Ogre::Vector3 _position;
			Ogre::Vector3 _scale;
			Ogre::String _entityName;
			Ogre::String _nodeName;

			void _checkModelPath();
			void _configureEntity(Ogre::Entity *entity);
			void _configureNode(Ogre::Node *node);
		
		public:

			virtual ~ModelBuilder();

			// Initial method as constructor
			ModelBuilder(Ogre::SceneManager *sceneManager);
			ModelBuilder(Ogre::SceneManager *sceneManager, const ModelPath &modelPath);

			// Intermediate methods
			ModelBuilder *modelPath(const ModelPath &modelPath);
			ModelBuilder *parent(Ogre::SceneNode *parent);
			ModelBuilder *queryFlags(const Ogre::uint32 &queryFlags);
			ModelBuilder *visible(const bool &isVisible);
			ModelBuilder *castShadows(const bool &toCastShadows);
			ModelBuilder *position(const Ogre::Vector3 &position);
			ModelBuilder *scale(const Ogre::Vector3 &scale);
			ModelBuilder *entityName(const Ogre::String &name);
			ModelBuilder *nodeName(const Ogre::String &name);

			// Final Methods
			Ogre::SceneNode *buildNode();
			Ogre::Entity *buildEntity();
	};
};

#endif
