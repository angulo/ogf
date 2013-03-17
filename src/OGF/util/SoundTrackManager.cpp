/*
 * SoundTrackManager.cpp -- Basic sound resource manager implementation file
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

#include "SoundTrackManager.h"

using namespace OGF;

template<> SoundTrackManager * Ogre::Singleton<SoundTrackManager>::msSingleton = 0;

Ogre::Resource *
SoundTrackManager::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle,
	const Ogre::String &group, bool isManualLoad, Ogre::ManualResourceLoader *manualLoader,
	const Ogre::NameValuePairList* createParams)
{
	return new SoundTrack(this, name, handle, group, isManualLoad, manualLoader);
}

SoundTrackManager::SoundTrackManager()
{
	mLoadOrder = 30.f;
	mResourceType = SoundTrack::RESOURCE_TYPE;

	Ogre::ResourceGroupManager::getSingletonPtr()->_registerResourceManager(mResourceType, this);
	Mix_AllocateChannels(32);
}

SoundTrackManager::~SoundTrackManager()
{
	Ogre::ResourceGroupManager::getSingletonPtr()->_unregisterResourceManager(mResourceType);
}

SoundTrackManager &
SoundTrackManager::getSingleton()
{
	if (!msSingleton)
		SoundTrackManager *instance = new SoundTrackManager();
	
	return *msSingleton;
}

SoundTrackManager *
SoundTrackManager::getSingletonPtr()
{
	if (!msSingleton)
		SoundTrackManager *instance = new SoundTrackManager();
	
	return msSingleton;
}

SoundTrackPtr
SoundTrackManager::load(const Ogre::String &name, const Ogre::String &group)
{
	SoundTrackPtr soundTrackPtr = getByName(name);

	if (soundTrackPtr.isNull())
		soundTrackPtr = create(name, group);
	
	soundTrackPtr->load();

	return soundTrackPtr;
}
