/*
 * GuiScene.cpp -- Gui Scene base class implementation
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

#include "GuiScene.h"

using namespace OGF;

CEGUI::MouseButton
GuiScene::_convertMouseButton(OIS::MouseButtonID id)
{
	CEGUI::MouseButton ceguiId;

	switch(id) {
		case OIS::MB_Left:
			ceguiId = CEGUI::LeftButton;
			break;
		case OIS::MB_Right:
			ceguiId = CEGUI::RightButton;
			break;
		case OIS::MB_Middle:
			ceguiId = CEGUI::MiddleButton;
			break;
		default:
			ceguiId = CEGUI::LeftButton;
	}

	return ceguiId;
}

GuiScene::~GuiScene()
{
}

bool
GuiScene::frameStartedFacade(const Ogre::FrameEvent& event)
{
	CEGUI::System::getSingleton().injectTimePulse(event.timeSinceLastFrame);

	return frameStarted(event);
}

bool
GuiScene::keyPressedFacade(const OIS::KeyEvent& event)
{
	CEGUI::System::getSingleton().injectKeyDown(event.key);
	CEGUI::System::getSingleton().injectChar(event.text);

	return keyPressed(event);
}

bool
GuiScene::keyReleasedFacade(const OIS::KeyEvent& event)
{
	CEGUI::System::getSingleton().injectKeyUp(event.key);

	return keyReleased(event);
}

bool
GuiScene::mouseMovedFacade(const OIS::MouseEvent& event)
{
	CEGUI::System::getSingleton().injectMouseMove(event.state.X.rel, event.state.Y.rel);

	return mouseMoved(event);
}

bool
GuiScene::mousePressedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(_convertMouseButton(buttonId));

	return mousePressed(event, buttonId);
}

bool
GuiScene::mouseReleasedFacade(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(_convertMouseButton(buttonId));

	return mouseReleased(event, buttonId);
}
