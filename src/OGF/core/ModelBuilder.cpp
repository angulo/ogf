/*
 * ModelBuilder.cpp -- Model builder implementation file.
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

#include "ModelBuilder.h"

using namespace OGF;

ModelBuilder::ModelBuilder(Ogre::SceneManager *sceneManager, const ModelPath &path)
	: _parentSet(false), _queryFlagsSet(false), _visibleSet(false),
		_castShadowsSet(false), _entityNameSet(false), _nodeNameSet(false)
{
}

ModelBuilder::~ModelBuilder()
{

}

void
ModelBuilder::initialize(const ModelBuilderPtr &selfInstance)
{
	_selfInstance = selfInstance;
}

ModelBuilderPtr
ModelBuilder::parent(Ogre::SceneNode *parent)
{
	if (parent != NULL) {
		_parent = parent;
		_parentSet = true;
	} else {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "parent", "Setting NULL parent, using Root", LOG_SEVERITY_ERROR);
	}

	return _selfInstance;
}

ModelBuilderPtr
ModelBuilder::queryFlags(const Ogre::uint32 &queryFlags)
{
	if (queryFlags > 0) {
		_queryFlags = queryFlags;
	} else {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "queryFlags", "Setting query flags < 0, using Root", LOG_SEVERITY_ERROR);
	}

	return _selfInstance;
}

ModelBuilderPtr
ModelBuilder::visible(const bool &isVisible)
{
	_visible = isVisible;
	_visibleSet = true;

	return _selfInstance;
}

ModelBuilderPtr
ModelBuilder::castShadows(const bool &toCastShadows)
{
	_castShadows = toCastShadows;
	_castShadowsSet = true;

	return _selfInstance;
}

Ogre::SceneNode *
ModelBuilder::buildNode()
{

}

Ogre::SceneNode *
ModelBuilder::buildNode(const Ogre::String &nodeName)
{

}

Ogre::SceneNode *
ModelBuilder::buildNode(const Ogre::String &entityName, const Ogre::String &nodeName)
{

}

Ogre::Entity *
ModelBuilder::buildEntity()
{

}

Ogre::Entity *
ModelBuilder::buildEntity(const Ogre::String &entityName)
{

}
