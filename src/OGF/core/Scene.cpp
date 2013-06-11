/*
 * Scene.h -- Base scene implementation
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

#include "Scene.h"

using namespace OGF;

void
Scene::_initConfigReader(const std::string &configFile, const bool &useCache)
{
	_configReader = new ConfigReader(configFile, useCache);
}

Scene::Scene()
{
	_configReader = 0;
	_sceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
}

Scene::Scene(Ogre::SceneManager *sceneManager)
	:	_sceneManager(sceneManager)
{
	_configReader = 0;
}

Scene::~Scene()
{
	if (_configReader) 
		delete _configReader;
}

Ogre::SceneManager *
Scene::getSceneManager() const
{
	return _sceneManager;
}

void
Scene::addChild(Scene *scene, const ChildId &childId)
{
	_childs[childId] = scene;
	scene->enterFacade();
}

void
Scene::removeChild(const ChildId &childId)
{
	ChildMap::iterator it = _childs.find(childId);

	if (it == _childs.end()) {
		std::string errorMessage = "Child not found";
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("Scene", "removeChild", errorMessage, LOG_SEVERITY_ERROR);
		throw errorMessage;
	} else {
		it->second->exitFacade();
		delete it->second;
		_childs.erase(it);
	}
}

void
Scene::preload()
{
	// Default implementation doesn't preload anything
}

void
Scene::pause()
{

}

void
Scene::resume()
{

}

void
Scene::enterFacade()
{
	enter();	
}

void
Scene::exitFacade()
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++) {
		it->second->exitFacade();
		delete it->second;
	}

	_childs.erase(_childs.begin(), _childs.end());
	exit();
}

void
Scene::pauseFacade()
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->pauseFacade();
	
	pause();
}

void
Scene::resumeFacade()
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->resumeFacade();
	
	resume();
}


bool
Scene::frameStartedFacade(const Ogre::FrameEvent& event)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->frameStartedFacade(event);

	return frameStarted(event);
}

bool
Scene::frameEndedFacade(const Ogre::FrameEvent& event)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->frameEndedFacade(event);

	return frameEnded(event);
}

bool
Scene::keyPressedFacade(const OIS::KeyEvent &event)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->keyPressedFacade(event);

	return keyPressed(event);
}

bool
Scene::keyReleasedFacade(const OIS::KeyEvent &event)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->keyReleasedFacade(event);

	return keyReleased(event);
}

bool
Scene::mouseMovedFacade(const OIS::MouseEvent &event)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->mouseMovedFacade(event);

	return mouseMoved(event);
}

bool
Scene::mousePressedFacade(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->mousePressedFacade(event, buttonId);

	return mousePressed(event, buttonId);
}

bool
Scene::mouseReleasedFacade(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	for (ChildMap::iterator it = _childs.begin(); it != _childs.end(); it++)
		it->second->mouseReleasedFacade(event, buttonId);

	return mouseReleased(event, buttonId);
}

bool
Scene::frameStarted(const Ogre::FrameEvent& event)
{
	return true;
}

bool
Scene::frameEnded(const Ogre::FrameEvent& event)
{
	return true;
}


bool
Scene::keyPressed(const OIS::KeyEvent &event)
{
	return true;
}

bool
Scene::keyReleased(const OIS::KeyEvent &event)
{
	return true;
}

bool
Scene::mouseMoved(const OIS::MouseEvent &event)
{
	return true;
}

bool
Scene::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return true;
}

bool
Scene::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID buttonId)
{
	return true;
}
