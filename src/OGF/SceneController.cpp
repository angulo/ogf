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
		std::cerr << "[OGF::ERROR] Class: SceneController, Method: _getScenePtr, Message: Scene factory not initialized" << std::endl;
	} else if (_sceneMap.find(sceneId) == _sceneMap.end()) {
		scene = _sceneFactory->create(sceneId);
		_sceneMap[sceneId] = scene;
	}

	return scene;
}

void
SceneController::_loadResources(const std::string &resourcesFilePath)
{
  Ogre::ConfigFile resourcesFile;
  resourcesFile.load(resourcesFilePath);
  
  Ogre::ConfigFile::SectionIterator iterator = resourcesFile.getSectionIterator();
  Ogre::String sectionString;

  while (iterator.hasMoreElements()) {
    sectionString = iterator.peekNextKey();

    Ogre::ConfigFile::SettingsMultiMap *settings = iterator.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;

    for (i = settings->begin(); i != settings->end(); ++i) {
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				i->second, i->first, sectionString
			);	
    }
  }

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool
SceneController::_configureRenderWindow(const std::string &windowTitle)
{
	if (!_root->restoreConfig()) {
		if (!_root->showConfigDialog()) {
			return false;
		}
	}

	_renderWindow = _root->initialise(true, windowTitle);
	return true;
}

bool
SceneController::frameStarted(const Ogre::FrameEvent &event)
{
	InputManager::getSingletonPtr()->capture();

	return _sceneStore.empty() || _sceneStore.top()->frameStarted(event);
}

bool
SceneController::frameEnded(const Ogre::FrameEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->frameEnded(event);
}

bool
SceneController::keyPressed(const OIS::KeyEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->keyPressed(event);
}

bool
SceneController::keyReleased(const OIS::KeyEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->keyReleased(event);
}

bool
SceneController::mouseMoved(const OIS::MouseEvent &event)
{
	return _sceneStore.empty() || _sceneStore.top()->mouseMoved(event);
}

bool
SceneController::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _sceneStore.empty() || _sceneStore.top()->mousePressed(event, buttonId);
}

bool
SceneController::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return _sceneStore.empty() || _sceneStore.top()->mouseReleased(event, buttonId);
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
SceneController::initialize(ISceneFactory *sceneFactory, const std::string &resourcesFilePath,
	const std::string &windowTitle, const SceneId &initialScene)
{
	_sceneFactory = sceneFactory;

	_root = new Ogre::Root();

	_loadResources(resourcesFilePath);

	if (!_configureRenderWindow(windowTitle))
		return;

	_root->addFrameListener(this);

	push(initialScene);

	InputManager *inputManager = InputManager::getSingletonPtr();
	inputManager->initialize(_renderWindow, this, this);

	_root->startRendering();
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
