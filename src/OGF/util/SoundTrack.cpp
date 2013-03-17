/*
 * SoundTrack.cpp -- Track sound resource implementation file
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

#include "SoundTrack.h"

using namespace OGF;

std::string SoundTrack::RESOURCE_TYPE = "SoundTrack";

SoundTrack::SoundTrack(Ogre::ResourceManager *resourceManager, const Ogre::String &name,
	const Ogre::ResourceHandle handle, const Ogre::String &group,
	const bool &manualLoad, Ogre::ManualResourceLoader *manualLoader)
	:	Ogre::Resource(resourceManager, name, handle, group, manualLoad, manualLoader),
		_playableSource(NULL), _path(""), _size(0)
{
	createParamDictionary("SoundTrack");
}

SoundTrack::~SoundTrack()
{
	unload();
}

void
SoundTrack::loadImpl()
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	Ogre::FileInfoListPtr resourceInfo = Ogre::ResourceGroupManager::getSingletonPtr()->findResourceFileInfo(mGroup, mName);

	for(Ogre::FileInfoList::iterator it = resourceInfo->begin(); it != resourceInfo->end(); it++)
		_path = it->archive->getName() + "/" + it->filename;
	
	if (_path == "") {
		std::string errorMessage = "Impossible to find sound resource: " + mName;
		errorLog->log("SoundTrack", "loadImpl", errorMessage, OGF::LOG_SEVERITY_ERROR);
		throw errorMessage;
	}

	if ((_playableSource = Mix_LoadMUS(_path.c_str())) == NULL) {
		std::string errorMessage = "Impossible to load sound resource: " + _path;
		errorLog->log("SoundTrack", "loadImpl", errorMessage, OGF::LOG_SEVERITY_ERROR);
		throw errorMessage;
	}

	// Calculate size
	std::ifstream stream;
	stream.open(_path.c_str(), std::ios_base::binary);
	char temp;

	while (stream >> temp)
		_size++;

	stream.close();
}

void
SoundTrack::unloadImpl()
{
	if (_playableSource != NULL)
		Mix_FreeMusic(_playableSource);
}

size_t
SoundTrack::calculateSize() const
{
	return _size;
}

void
SoundTrack::play(const bool &toLoop)
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	} else if (Mix_PlayMusic(_playableSource, toLoop ? -1 : 1) == -1) {
			std::string errorMessage = "Impossible to play sound resource: " + mName;
			errorLog->log("SoundTrack", "play", errorMessage, OGF::LOG_SEVERITY_ERROR);
			throw errorMessage;
	}
}

void
SoundTrack::pause()
{
	Mix_PauseMusic();
}

void
SoundTrack::stop()
{
	Mix_HaltMusic();
}

SoundTrackPtr::SoundTrackPtr()
	:	Ogre::SharedPtr<SoundTrack>()
{
}

SoundTrackPtr::SoundTrackPtr(SoundTrack *instancePtr)
	:	Ogre::SharedPtr<SoundTrack>(instancePtr)
{
}

SoundTrackPtr::SoundTrackPtr(const SoundTrackPtr &instance)
	:	Ogre::SharedPtr<SoundTrack>(instance)
{
}

SoundTrackPtr::SoundTrackPtr(const Ogre::ResourcePtr &resourcePtr)
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	if (resourcePtr.isNull()) {
		return;
	}

	OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)

	pRep = static_cast<SoundTrack *>(resourcePtr.getPointer());
	pUseCount = resourcePtr.useCountPointer();
	useFreeMethod = resourcePtr.freeMethod();

	// Incremento del contador de referencias.
	if (pUseCount)
		++(*pUseCount);
}

SoundTrackPtr &
SoundTrackPtr::operator= (const Ogre::ResourcePtr &resourcePtr)
{
	if (pRep == static_cast<SoundTrack *>(resourcePtr.getPointer()))
		return *this;

	release();

	if (resourcePtr.isNull())
		return *this;

	OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)

	pRep = static_cast<SoundTrack*>(resourcePtr.getPointer());
	pUseCount = resourcePtr.useCountPointer();
	useFreeMethod = resourcePtr.freeMethod();

	if (pUseCount)
		++(*pUseCount);

	return *this;
}
