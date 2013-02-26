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
}

ModelBuilder::ModelBuilder(Ogre::SceneManager *sceneManager, const ModelPath &modelPath)
	: _sceneManager(sceneManager), _modelPath(modelPath),
		_parentSet(false), _queryFlagsSet(false), _visibleSet(false),
		_castShadowsSet(false), _entityNameSet(false), _nodeNameSet(false)
{
}

ModelBuilder::~ModelBuilder()
{

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
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelBuilder", "queryFlags", "Setting query flags < 0, using Root", LOG_SEVERITY_ERROR);
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

Ogre::SceneNode *
ModelBuilder::buildNode()
{
	Ogre::Entity *entity = buildEntity();
	Ogre::SceneNode *node = _sceneManager->createSceneNode();

	_configureEntity(entity);
	_configureNode(node);

	node->attachObject(entity);

	return node;
}

Ogre::SceneNode *
ModelBuilder::buildNode(const Ogre::String &nodeName)
{
	Ogre::Entity *entity = buildEntity();
	Ogre::SceneNode *node = _sceneManager->createSceneNode(nodeName);

	_configureEntity(entity);
	_configureNode(node);

	node->attachObject(entity);

	return node;
}

Ogre::SceneNode *
ModelBuilder::buildNode(const Ogre::String &entityName, const Ogre::String &nodeName)
{
	Ogre::Entity *entity = buildEntity(entityName);
	Ogre::SceneNode *node = _sceneManager->createSceneNode(nodeName);

	_configureEntity(entity);
	_configureNode(node);

	node->attachObject(entity);

	return node;
}

Ogre::Entity *
ModelBuilder::buildEntity()
{
	Ogre::Entity *entity = _sceneManager->createEntity(_modelPath);

	_configureEntity(entity);

	return entity;
}

Ogre::Entity *
ModelBuilder::buildEntity(const Ogre::String &entityName)
{
	Ogre::Entity *entity = _sceneManager->createEntity(entityName, _modelPath);

	_configureEntity(entity);

	return entity;
}
