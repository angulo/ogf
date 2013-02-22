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

ModelBuilder::ModelBuilder(const ModelPath &path)
{

}

ModelBuilder::~ModelBuilder()
{

}

ModelBuilder *
ModelBuilder::parent(Ogre::SceneNode *parent)
{

}

ModelBuilder *
ModelBuilder::queryFlags(const Ogre::uint32 queryFlags)
{

}

ModelBuilder *
ModelBuilder::visible(bool isVisible)
{

}

ModelBuilder *
ModelBuilder::castShadows(bool toCastShadows)
{

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
