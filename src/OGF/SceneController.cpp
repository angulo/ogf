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

Scene *
SceneController::_getScenePtr(SceneId sceneId)
{
	Scene *scene;
	if (_sceneMap.find(sceneId) == _sceneMap.end()) {
		scene = _sceneFactory->create(sceneId);
		_sceneMap[sceneId] = scene;
	}

	return scene;
}

bool
SceneController::keyPressed(const OIS::KeyEvent &event)
{

}

bool
SceneController::keyReleased(const OIS::KeyEvent &event)
{

}

bool
SceneController::mouseMoved(const OIS::MouseEvent &event)
{

}

bool
SceneController::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{

}

bool
SceneController::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{

}

SceneController&
SceneController::getSingleton()
{
	return *msSingleton;
}


SceneController *
SceneController::getSingletonPtr()
{
	return msSingleton;
}

void
SceneController::initialize(ISceneFactory *sceneFactory)
{
	_sceneFactory = sceneFactory;
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
