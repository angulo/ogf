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

Scene::Scene()
{
}

Scene::~Scene()
{
}

void
Scene::preload()
{
	// Default implementation doesn't preload anything
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


