/*
 * Bootstrap.cpp -- Bootstrap implementation file.
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

#include "Bootstrap.h"

using namespace OGF;

template<> Bootstrap * Ogre::Singleton<Bootstrap>::msSingleton = 0;

void
Bootstrap::_loadResources(const std::string &resourcesFilePath)
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
Bootstrap::_configureRenderWindow(const std::string &windowTitle)
{
	Ogre::Root *root = Ogre::Root::getSingletonPtr();

	if (!root->restoreConfig()) {
		if (!root->showConfigDialog()) {
			return false;
		}
	}

	root->initialise(true, windowTitle);
	return true;
}

void
Bootstrap::_initGui()
{
	CEGUI::OgreRenderer::bootstrapSystem();
	
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
}

void
Bootstrap::_initSound()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("Bootstrap", "_initSound", "Sound could not be initialized", LOG_SEVERITY_WARN);
		return;
	}

	atexit(SDL_Quit);

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0) {
		LogFactory::getSingletonPtr()->get(LOG_ERR)->log("Bootstrap", "_initSound", "Sound could not be initialized", LOG_SEVERITY_WARN);
		return;
	}

	atexit(Mix_CloseAudio);
}

Bootstrap&
Bootstrap::getSingleton()
{
	if (!msSingleton) {
		Bootstrap *instance = new Bootstrap();
	}

	return *msSingleton;
}


Bootstrap *
Bootstrap::getSingletonPtr()
{
	if (!msSingleton) {
		Bootstrap *instance = new Bootstrap();
	}

	return msSingleton;
}

bool
Bootstrap::init(const std::string &resourcesFilePath, const std::string &windowTitle, ISceneFactory *sceneFactory, const SceneId &initialScene)
{
	Ogre::Root *root = new Ogre::Root();

	if (!_configureRenderWindow(windowTitle))
		return false;

	_loadResources(resourcesFilePath);

	SceneController *sceneController = SceneController::getSingletonPtr();
	root->addFrameListener(sceneController);

	sceneController->initialize(sceneFactory);
	_initialScene = initialScene;

	InputManager::getSingletonPtr()->initialize(root->getAutoCreatedWindow(), sceneController, sceneController);

	_initGui();
	_initSound();

	return true;
}

void
Bootstrap::run()
{
	OGF::SceneController::getSingletonPtr()->push(_initialScene);
	Ogre::Root::getSingletonPtr()->startRendering();
}

void
Bootstrap::shutdown()
{
	if (InputManager::getSingletonPtr())
		delete InputManager::getSingletonPtr();

	if (LogFactory::getSingletonPtr())
		delete LogFactory::getSingletonPtr();

	if (ModelFactory::getSingletonPtr()) 
		delete ModelFactory::getSingletonPtr();

	if (SceneController::getSingletonPtr())
		delete SceneController::getSingletonPtr();

	delete Ogre::Root::getSingletonPtr();

	delete this;
}

