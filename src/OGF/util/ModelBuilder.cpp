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

void
ModelBuilder::_checkModelPath()
{
	if (_modelPath.size() == 0) {
		std::string errorMessage = "Building an entity with no model path";
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "buildEntity", errorMessage, LOG_SEVERITY_ERROR);
		throw errorMessage;
	}
}

void
ModelBuilder::_configureEntity(Ogre::Entity *entity)
{
	if (_queryFlagsSet)
		entity->setQueryFlags(_queryFlags);

	if (_visibleSet)
		entity->setVisible(_visible);

	if (_castShadowsSet)
		entity->setCastShadows(_castShadows);
}

void
ModelBuilder::_configureNode(Ogre::Node *node)
{
	if (_parentSet)
		_parent->addChild(node);
	
	if (_positionSet)
		node->setPosition(_position);
	
	if (_scaleSet)
		node->setScale(_scale);
}

ModelBuilder::ModelBuilder(Ogre::SceneManager *sceneManager)
	: _sceneManager(sceneManager), _modelPathSet(false),
		_entityName(""), _nodeName(""),
		_parentSet(false), _queryFlagsSet(false), _visibleSet(false),
		_castShadowsSet(false), _entityNameSet(false), _nodeNameSet(false),
		_positionSet(false), _scaleSet(false)
{
}

ModelBuilder::ModelBuilder(Ogre::SceneManager *sceneManager, const ModelPath &modelPath)
	: _sceneManager(sceneManager), _modelPathSet(false),
		_parentSet(false), _queryFlagsSet(false), _visibleSet(false),
		_castShadowsSet(false), _entityNameSet(false), _nodeNameSet(false),
		_positionSet(false), _scaleSet(false)
{
	this->modelPath(modelPath);
}

ModelBuilder::~ModelBuilder()
{

}

ModelBuilder *
ModelBuilder::modelPath(const ModelPath &modelPath)
{
	if (modelPath.size() > 0) {
		_modelPath = modelPath;
		_modelPathSet = true;
	} else {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "modelPath", "Setting empty model path, property not set", LOG_SEVERITY_ERROR);
	}

	return this;
}

ModelBuilder *
ModelBuilder::parent(Ogre::SceneNode *parent)
{
	if (parent != NULL) {
		_parent = parent;
		_parentSet = true;
	} else {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "parent", "Setting NULL parent, using Root", LOG_SEVERITY_ERROR);
	}

	return this;
}

ModelBuilder *
ModelBuilder::queryFlags(const Ogre::uint32 &queryFlags)
{
	if (queryFlags > 0) {
		_queryFlags = queryFlags;
		_queryFlagsSet = true;
	} else {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "queryFlags", "Setting query flags < 0", LOG_SEVERITY_ERROR);
	}

	return this;
}

ModelBuilder *
ModelBuilder::visible(const bool &isVisible)
{
	_visible = isVisible;
	_visibleSet = true;

	return this;
}

ModelBuilder *
ModelBuilder::castShadows(const bool &toCastShadows)
{
	_castShadows = toCastShadows;
	_castShadowsSet = true;

	return this;
}

ModelBuilder *
ModelBuilder::position(const Ogre::Vector3 &position)
{
	_position = position;
	_positionSet = true;

	return this;
}

ModelBuilder *
ModelBuilder::scale(const Ogre::Vector3 &scale)
{
	_scale = scale;
	_scaleSet = true;

	return this;
}

ModelBuilder *
ModelBuilder::entityName(const Ogre::String &name)
{
	_entityName = name;
	_entityNameSet = true;

	return this;
}

ModelBuilder *
ModelBuilder::nodeName(const Ogre::String &name)
{
	_nodeName = name;
	_nodeNameSet = true;

	return this;
}

Ogre::SceneNode *
ModelBuilder::buildNode()
{
	Ogre::SceneNode *node = NULL;
	Ogre::Entity *entity = buildEntity();

	if (_nodeName.size() > 0) {
		node = _sceneManager->createSceneNode(_nodeName);
	} else {
		node = _sceneManager->createSceneNode();
	}

	_configureNode(node);

	node->attachObject(entity);

	return node;
}

Ogre::Entity *
ModelBuilder::buildEntity()
{
	Ogre::Entity *entity = NULL;

	_checkModelPath();

	if (_entityName.size() > 0) {
		entity = _sceneManager->createEntity(_entityName, _modelPath);
	} else {
		entity = _sceneManager->createEntity(_modelPath);
	}

	_configureEntity(entity);

	return entity;
}
