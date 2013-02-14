/*
 * SceneController.cpp -- Scene controller implementation
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

#include "SceneController.h"

using namespace OGF;

template<> SceneController * Ogre::Singleton<SceneController>::msSingleton = 0;

Scene *
SceneController::_getScenePtr(const SceneId &sceneId)
{
	Scene *scene = NULL;
	if (_sceneFactory == NULL) {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("SceneController", "_getScenePtr", "Scene factory not initialized", LOG_SEVERITY_ERROR);
	} else {
		SceneMap::iterator it = _sceneMap.find(sceneId);
		if (it == _sceneMap.end()) {
			scene = _sceneFactory->create(sceneId);
			_sceneMap[sceneId] = scene;
		} else {
			scene = it->second;
		}
	}

	assert(scene);

	return scene;
}

bool
SceneController::frameStarted(const Ogre::FrameEvent &event)
{
	InputManager::getSingletonPtr()->capture();

	return _sceneStore.empty() || _sceneStore.top()->frameStartedFacade(event);
}

bool
SceneController::frameEnded(const Ogre::FrameEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->frameEndedFacade(event);
}

bool
SceneController::keyPressed(const OIS::KeyEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->keyPressedFacade(event);
}

bool
SceneController::keyReleased(const OIS::KeyEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->keyReleasedFacade(event);
}

bool
SceneController::mouseMoved(const OIS::MouseEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->mouseMovedFacade(event);
}

bool
SceneController::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _sceneStore.empty() || _sceneStore.top()->mousePressedFacade(event, buttonId);
}

bool
SceneController::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _sceneStore.empty() || _sceneStore.top()->mouseReleasedFacade(event, buttonId);
}

SceneController&
SceneController::getSingleton()
{
	if (!msSingleton) {
		SceneController *instance = new SceneController();
	}

	return *msSingleton;
}


SceneController *
SceneController::getSingletonPtr()
{
	if (!msSingleton) {
		SceneController *instance = new SceneController();
	}

	return msSingleton;
}

void
SceneController::initialize(ISceneFactory *sceneFactory, const SceneId &initialScene)
{
	_sceneFactory = sceneFactory;
	push(initialScene);
}

void
SceneController::preload(SceneId sceneId)
{
	Scene *scene = _getScenePtr(sceneId);
	scene->preload();
}

void
SceneController::add(SceneId sceneId)
{
	// TODO
}

void
SceneController::remove(SceneId sceneId)
{
	// TODO
}

void
SceneController::push(SceneId sceneId)
{
	if (!_sceneStore.empty()) {
		_sceneStore.top()->pause();
	}

	_sceneStore.push(_getScenePtr(sceneId));
	_sceneStore.top()->enter();
}

void
SceneController::pop()
{
	if (!_sceneStore.empty()) {
		_sceneStore.top()->exit();
		_sceneStore.pop();
	}

	if (!_sceneStore.empty()) {
		_sceneStore.top()->resume();
	}
}

void
SceneController::replace(SceneId sceneId)
{
	if (!_sceneStore.empty()) {
		_sceneStore.top()->exit();
		_sceneStore.pop();
	}

	_sceneStore.push(_getScenePtr(sceneId));
	_sceneStore.top()->enter();
}
