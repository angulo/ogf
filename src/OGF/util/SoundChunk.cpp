/*
 * SoundChunk.cpp -- Basic sound resource implementation file
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

#include "SoundChunk.h"

using namespace OGF;

std::string SoundChunk::RESOURCE_TYPE = "SoundChunk";

SoundChunk::SoundChunk(Ogre::ResourceManager *resourceManager, const Ogre::String &name,
	const Ogre::ResourceHandle handle, const Ogre::String &group,
	const bool &manualLoad, Ogre::ManualResourceLoader *manualLoader)
	:	Ogre::Resource(resourceManager, name, handle, group, manualLoad, manualLoader),
		_playableSource(NULL), _path(""), _size(0)
{
	createParamDictionary("SoundChunk");
}

SoundChunk::~SoundChunk()
{
	unload();
}

void
SoundChunk::loadImpl()
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	Ogre::FileInfoListPtr resourceInfo = Ogre::ResourceGroupManager::getSingletonPtr()->findResourceFileInfo(mGroup, mName);

	for(Ogre::FileInfoList::iterator it = resourceInfo->begin(); it != resourceInfo->end(); it++)
		_path = it->archive->getName() + "/" + it->filename;
	
	if (_path == "") {
		std::string errorMessage = "Impossible to find sound resource: " + mName;
		errorLog->log("SoundChunk", "loadImpl", errorMessage, OGF::LOG_SEVERITY_ERROR);
		throw errorMessage;
	}

	if ((_playableSource = Mix_LoadWAV(_path.c_str())) == NULL) {
		std::string errorMessage = "Impossible to load sound resource: " + _path;
		errorLog->log("SoundChunk", "loadImpl", errorMessage, OGF::LOG_SEVERITY_ERROR);
		throw errorMessage;
	}
}

void
SoundChunk::unloadImpl()
{
	if (_playableSource != NULL)
		Mix_FreeChunk(_playableSource);
}

size_t
SoundChunk::calculateSize() const
{
	return _playableSource->alen;
}

void
SoundChunk::play()
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	if (Mix_PlayChannel(-1, _playableSource, 0) == -1) {
		std::string errorMessage = "Impossible to play sound resource: " + mName;
		errorLog->log("SoundChunk", "play", errorMessage, OGF::LOG_SEVERITY_ERROR);
		throw errorMessage;
	}
}

SoundChunkPtr::SoundChunkPtr()
	:	Ogre::SharedPtr<SoundChunk>()
{
}

SoundChunkPtr::SoundChunkPtr(SoundChunk *instancePtr)
	:	Ogre::SharedPtr<SoundChunk>(instancePtr)
{
}

SoundChunkPtr::SoundChunkPtr(const SoundChunkPtr &instance)
	:	Ogre::SharedPtr<SoundChunk>(instance)
{
}

SoundChunkPtr::SoundChunkPtr(const Ogre::ResourcePtr &resourcePtr)
{
	Log *errorLog = OGF::LogFactory::getSingletonPtr()->get(OGF::LOG_ERR);

	if (resourcePtr.isNull()) {
		return;
	}

	OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)

	pRep = static_cast<SoundChunk *>(resourcePtr.getPointer());
	pUseCount = resourcePtr.useCountPointer();
	useFreeMethod = resourcePtr.freeMethod();

	// Incremento del contador de referencias.
	if (pUseCount)
		++(*pUseCount);
}

SoundChunkPtr &
SoundChunkPtr::operator= (const Ogre::ResourcePtr &resourcePtr)
{
	if (pRep == static_cast<SoundChunk *>(resourcePtr.getPointer()))
		return *this;

	release();

	if (resourcePtr.isNull())
		return *this;

	OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)

	pRep = static_cast<SoundChunk*>(resourcePtr.getPointer());
	pUseCount = resourcePtr.useCountPointer();
	useFreeMethod = resourcePtr.freeMethod();

	if (pUseCount)
		++(*pUseCount);

	return *this;
}
