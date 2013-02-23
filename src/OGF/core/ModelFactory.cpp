/*
 * ModelFactory.cpp -- Model factory header file.
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

#include "ModelFactory.h"

using namespace OGF;

template<> ModelFactory * Ogre::Singleton<ModelFactory>::msSingleton = 0;

ModelFactory::ModelFactory()
{
	_modelMap = ModelMap();
}

ModelFactory::~ModelFactory()
{
}

ModelFactory &
ModelFactory::getSingleton()
{
	if (!msSingleton) {
		ModelFactory *instance = new ModelFactory();
	}

	return *msSingleton;
}

ModelFactory *
ModelFactory::getSingletonPtr()
{
	if (!msSingleton) {
		ModelFactory *instance = new ModelFactory();
	}

	return msSingleton;
}

void
ModelFactory::initialize(const ModelMap &modelMap)
{
	_modelMap = modelMap;
}

ModelBuilderPtr
ModelFactory::getBuilder(Ogre::SceneManager *sceneManager, const ModelId &modelId)
{
	ModelBuilderPtr builder;

	ModelMap::iterator it = _modelMap.find(modelId);
	if (it == _modelMap.end()) {
		std::string message = "Model with id not in the model directory";
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ModelFactory", "getBuilder", message, LOG_SEVERITY_ERROR);
		throw message;
		// TODO: throw custom exception
	} else {
		builder = ModelBuilderPtr(new ModelBuilder(sceneManager, it->second));
	}

	return builder;
}
